#include "pch.h"
#include "ShaderLoader.h"

#include "DeviceManager.h"
#include "ShaderHandler.h"

std::shared_ptr<CShaderLoader> Engine::CShaderLoader::Create()
{
	const std::shared_ptr<CShaderLoader> spLoader = make_shared<CShaderLoader>();
	ENSUREF(spLoader->Initialize(), L"Failed to create shader loader.");
	return spLoader;
}

HRESULT Engine::CShaderLoader::Initialize()
{
	m_wpShaderHandler = CShaderHandler::GetInstance();
	m_wpDeviceManager = CShaderHandler::GetInstance()->GetDeviceManager();

	// 외부 파일을 불러옵니다.
	LoadVertexShaderFromFile();
	LoadGeometryShaderFromFile();
	LoadPixelShaderFromFile();
	LoadBasicEffect();
	return S_OK;
}

void Engine::CShaderLoader::Release()
{
}

HRESULT Engine::CShaderLoader::LoadVertexShaderFromFile()
{
	for (const filesystem::directory_entry& fsEntry : filesystem::recursive_directory_iterator(m_wstrVertexShaderFilePath))
	{
		// 파일이 아닌 경우, 건너뜁니다.
		if (!filesystem::is_regular_file(fsEntry)) { continue; }

		// 버텍스 셰이더 파일 이름은 VS로 시작해야 합니다.
		wstring wstrShaderFileName = fsEntry.path().stem().generic_wstring();
		if (!wstrShaderFileName.starts_with(L"VS")) { continue; }

		ComPtr<ID3D11ShaderReflection> cpReflection = nullptr;
		ComPtr<ID3DBlob> cpShaderBlob = nullptr;

		// 셰이더 문맥
		shared_ptr<FShaderDesc> spShaderDesc = make_shared<FVertexShaderDesc>();

		ENSURE(CompileShaderFromFile(EShaderType::VERTEX, spShaderDesc, cpShaderBlob, fsEntry));

		ENSURE(CreateShaderReflection(cpReflection, cpShaderBlob));

		ENSURE(CreateInputLayout(EShaderType::VERTEX, spShaderDesc, cpReflection, cpShaderBlob, fsEntry));

		ENSURE(CreateConstantBuffer(EShaderType::VERTEX, spShaderDesc, cpReflection));

		ENSURE(CreateDescInfo(spShaderDesc, cpReflection));

		shared_ptr<FVertexShaderDesc> spVertexShaderDesc = static_pointer_cast<FVertexShaderDesc>(spShaderDesc);
		m_wpShaderHandler.lock()->AddVertexShaderDesc(spVertexShaderDesc->m_wstrVertexShaderName, spVertexShaderDesc);
	}
	return S_OK;
}

HRESULT Engine::CShaderLoader::LoadGeometryShaderFromFile()
{
	for (const filesystem::directory_entry& fsEntry : filesystem::recursive_directory_iterator(m_wstrGeometryShaderFilePath))
	{
		// 파일이 아닌 경우, 건너뜁니다.
		if (!filesystem::is_regular_file(fsEntry)) { continue; }

		// 지오메트리 셰이더 파일 이름은 GS로 시작해야 합니다.
		wstring wstrShaderFileName = fsEntry.path().stem().generic_wstring();
		if (!wstrShaderFileName.starts_with(L"GS")) { continue; }

		ComPtr<ID3D11ShaderReflection> cpReflection = nullptr;
		ComPtr<ID3DBlob> cpShaderBlob = nullptr;

		// 셰이더 문맥
		shared_ptr<FShaderDesc> spShaderDesc = make_shared<FGeometryShaderDesc>();

		ENSURE(CompileShaderFromFile(EShaderType::GEOMETRY, spShaderDesc, cpShaderBlob, fsEntry));

		ENSURE(CreateShaderReflection(cpReflection, cpShaderBlob));

		ENSURE(CreateConstantBuffer(EShaderType::GEOMETRY, spShaderDesc, cpReflection));

		ENSURE(CreateDescInfo(spShaderDesc, cpReflection));

		shared_ptr<FGeometryShaderDesc> spGeometryShaderDesc = static_pointer_cast<FGeometryShaderDesc>(spShaderDesc);
		m_wpShaderHandler.lock()->AddGeometryShaderDesc(spGeometryShaderDesc->m_wstrGeometryShaderName, spGeometryShaderDesc);
	}
	return S_OK;
}

HRESULT Engine::CShaderLoader::LoadPixelShaderFromFile()
{
	for (const filesystem::directory_entry& fsEntry : filesystem::recursive_directory_iterator(m_wstrPixelShaderFilePath))
	{
		// 파일이 아닌 경우, 건너뜁니다.
		if (!filesystem::is_regular_file(fsEntry)) { continue; }

		// 픽셀 셰이더 파일 이름은 PS로 시작해야 합니다.
		wstring wstrShaderFileName = fsEntry.path().stem().generic_wstring();
		if (!wstrShaderFileName.starts_with(L"PS")) { continue; }

		ComPtr<ID3D11ShaderReflection> cpReflection = nullptr;
		ComPtr<ID3DBlob> cpShaderBlob = nullptr;
		shared_ptr<FShaderDesc> spShaderDesc = make_shared<FPixelShaderDesc>();

		ENSURE(CompileShaderFromFile(EShaderType::PIXEL, spShaderDesc, cpShaderBlob, fsEntry));

		ENSURE(CreateShaderReflection(cpReflection, cpShaderBlob));

		ENSURE(CreateConstantBuffer(EShaderType::PIXEL, spShaderDesc, cpReflection));

		ENSURE(CreateDescInfo(spShaderDesc, cpReflection));

		shared_ptr<FPixelShaderDesc> spPixelShaderDesc = static_pointer_cast<FPixelShaderDesc>(spShaderDesc);
		m_wpShaderHandler.lock()->AddPixelShaderDesc(spPixelShaderDesc->m_wstrPixelShaderName, spPixelShaderDesc);
	}
	return S_OK;
}

HRESULT Engine::CShaderLoader::LoadBasicEffect()
{
	shared_ptr<PrimitiveBatch<VertexPositionColor>> spPrimitiveBatch = make_shared<PrimitiveBatch<VertexPositionColor>>(m_wpDeviceManager.lock()->GetDeviceContext().Get());
	shared_ptr<BasicEffect> spBasicEffect = make_shared<BasicEffect>(m_wpDeviceManager.lock()->GetDevice().Get());
	spBasicEffect->SetVertexColorEnabled(true);
	
	const void* pShaderByteCode = nullptr;
	size_t iByteCodeLength = 0;
	spBasicEffect->GetVertexShaderBytecode(&pShaderByteCode, &iByteCodeLength);

	ComPtr<ID3D11InputLayout> cpInputLayout = nullptr;
	ENSURE(m_wpDeviceManager.lock()->GetDevice()->CreateInputLayout(VertexPositionColor::InputElements, VertexPositionColor::InputElementCount, pShaderByteCode, iByteCodeLength, cpInputLayout.GetAddressOf()));

	m_wpShaderHandler.lock()->SetPrimitiveBatch(spPrimitiveBatch);
	m_wpShaderHandler.lock()->SetBasicEffect(spBasicEffect);
	m_wpShaderHandler.lock()->AddInputLayout(L"VertexPositionColor", cpInputLayout);
	return S_OK;
}

HRESULT Engine::CShaderLoader::CompileShaderFromFile(EShaderType _eShaderType, std::shared_ptr<FShaderDesc>& _spShaderDesc, ComPtr<ID3DBlob>& _cpShaderBlob, const filesystem::directory_entry& _fsEntry)
{
	wstring wstrShaderFileName = _fsEntry.path().stem().generic_wstring();
	ComPtr<ID3DBlob> cpErrorBlob = nullptr;
	UINT iCompileFlag = 0;

#ifdef _DEBUG
	iCompileFlag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	switch (_eShaderType)
	{
	case EShaderType::VERTEX:
	{
		ENSURE(D3DCompileFromFile(_fsEntry.path().generic_wstring().c_str(), 0, D3D_COMPILE_STANDARD_FILE_INCLUDE, "main", "vs_5_0", iCompileFlag, 0, _cpShaderBlob.GetAddressOf(), &cpErrorBlob));

		ComPtr<ID3D11VertexShader> cpVertexShader = nullptr;
		ENSURE(m_wpDeviceManager.lock()->GetDevice()->CreateVertexShader(_cpShaderBlob->GetBufferPointer(), _cpShaderBlob->GetBufferSize(), nullptr, &cpVertexShader));

		m_wpShaderHandler.lock()->AddVertexShader(wstrShaderFileName, cpVertexShader);

		shared_ptr<FVertexShaderDesc> spVertexShaderDesc = static_pointer_cast<FVertexShaderDesc>(_spShaderDesc);
		spVertexShaderDesc->m_eShaderType = EShaderType::VERTEX;
		spVertexShaderDesc->m_wstrVertexShaderName = wstrShaderFileName;
	}
	break;

	case EShaderType::PIXEL:
	{
		ENSURE(D3DCompileFromFile(_fsEntry.path().generic_wstring().c_str(), 0, D3D_COMPILE_STANDARD_FILE_INCLUDE, "main", "ps_5_0", iCompileFlag, 0, _cpShaderBlob.GetAddressOf(), &cpErrorBlob));

		ComPtr<ID3D11PixelShader> cpPixelShader = nullptr;
		ENSURE(m_wpDeviceManager.lock()->GetDevice()->CreatePixelShader(_cpShaderBlob->GetBufferPointer(), _cpShaderBlob->GetBufferSize(), nullptr, &cpPixelShader));

		m_wpShaderHandler.lock()->AddPixelShader(wstrShaderFileName, cpPixelShader);

		shared_ptr<FPixelShaderDesc> spPixelShaderDesc = static_pointer_cast<FPixelShaderDesc>(_spShaderDesc);
		spPixelShaderDesc->m_eShaderType = EShaderType::PIXEL;
		spPixelShaderDesc->m_wstrPixelShaderName = wstrShaderFileName;
	}
	break;

	case EShaderType::GEOMETRY:
	{
		ENSURE(D3DCompileFromFile(_fsEntry.path().generic_wstring().c_str(), 0, D3D_COMPILE_STANDARD_FILE_INCLUDE, "main", "gs_5_0", iCompileFlag, 0, _cpShaderBlob.GetAddressOf(), &cpErrorBlob));

		ComPtr<ID3D11GeometryShader> cpGeometryShader = nullptr;
		ENSURE(m_wpDeviceManager.lock()->GetDevice()->CreateGeometryShader(_cpShaderBlob->GetBufferPointer(), _cpShaderBlob->GetBufferSize(), nullptr, &cpGeometryShader));

		m_wpShaderHandler.lock()->AddGeometryShader(wstrShaderFileName, cpGeometryShader);

		shared_ptr<FGeometryShaderDesc> spGeometryShaderDesc = static_pointer_cast<FGeometryShaderDesc>(_spShaderDesc);
		spGeometryShaderDesc->m_eShaderType = EShaderType::GEOMETRY;
		spGeometryShaderDesc->m_wstrGeometryShaderName = wstrShaderFileName;
	}
	break;

	case EShaderType::COMPUTE:
		break;

	default:
		CHECKF(false, L"Shader type is not designated.")
		break;
	}
	return S_OK;
}

HRESULT Engine::CShaderLoader::CreateShaderReflection(const ComPtr<ID3D11ShaderReflection>& _cpReflection, const ComPtr<ID3DBlob>& _cpShaderBlob)
{
	return D3DReflect(_cpShaderBlob->GetBufferPointer(), _cpShaderBlob->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)_cpReflection.GetAddressOf());
}

HRESULT Engine::CShaderLoader::CreateInputLayout(EShaderType _eShaderType, std::shared_ptr<FShaderDesc>& _spShaderDesc, const ComPtr<ID3D11ShaderReflection>& _cpReflection, const ComPtr<ID3DBlob>& _cpShaderBlob, const filesystem::directory_entry& _fsEntry)
{
	// 세이더 디스크립션을 불러옵니다.
	D3D11_SHADER_DESC tShaderDesc;
	ZeroMemory(&tShaderDesc, sizeof(tShaderDesc));
	_cpReflection->GetDesc(&tShaderDesc);

	// 버텍스 셰이더에서 사용되는 입력 레이아웃을 생성합니다.
	vector<D3D11_INPUT_ELEMENT_DESC> vecInputElementDesc;
	vecInputElementDesc.reserve(static_cast<size_t>(tShaderDesc.InputParameters));

	for (UINT iIndex = 0; iIndex < tShaderDesc.InputParameters; iIndex++)
	{
		D3D11_SIGNATURE_PARAMETER_DESC tParamDesc;
		ZeroMemory(&tParamDesc, sizeof(tParamDesc));
		_cpReflection->GetInputParameterDesc(iIndex, &tParamDesc);

		D3D11_INPUT_ELEMENT_DESC tInputElementDesc;
		ZeroMemory(&tInputElementDesc, sizeof(tInputElementDesc));
		tInputElementDesc.SemanticName = tParamDesc.SemanticName;
		tInputElementDesc.SemanticIndex = tParamDesc.SemanticIndex;
		tInputElementDesc.Format = FindFormat(tParamDesc.Mask, tParamDesc.ComponentType);
		tInputElementDesc.InputSlot = 0;
		tInputElementDesc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		tInputElementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		tInputElementDesc.InstanceDataStepRate = 0;

		vecInputElementDesc.push_back(tInputElementDesc);
	}

	ComPtr<ID3D11InputLayout> cpInputLayout = nullptr;
	ENSURE(m_wpDeviceManager.lock()->GetDevice()->CreateInputLayout
	(
		vecInputElementDesc.data(),
		static_cast<UINT>(vecInputElementDesc.size()),
		_cpShaderBlob->GetBufferPointer(),
		_cpShaderBlob->GetBufferSize(),
		cpInputLayout.GetAddressOf())
	);

	// 셰이더 파일의 이름을 입력 레이아웃의 이름으로 사용합니다.
	wstring wstrInputLayoutName = _fsEntry.path().stem().generic_wstring();
	m_wpShaderHandler.lock()->AddInputLayout(wstrInputLayoutName, cpInputLayout);

	shared_ptr<FVertexShaderDesc> spVertexShaderDesc = static_pointer_cast<FVertexShaderDesc>(_spShaderDesc);
	spVertexShaderDesc->m_wstrInputLayoutName = wstrInputLayoutName;
	return S_OK;
}

HRESULT Engine::CShaderLoader::CreateConstantBuffer(EShaderType _eShaderType, std::shared_ptr<FShaderDesc>& _spShaderDesc, const ComPtr<ID3D11ShaderReflection>& _cpReflection)
{
	// 세이더 디스크립션을 불러옵니다.
	D3D11_SHADER_DESC tShaderDesc;
	ZeroMemory(&tShaderDesc, sizeof(tShaderDesc));
	_cpReflection->GetDesc(&tShaderDesc);

	shared_ptr<FVertexShaderDesc>	spVertexShaderDesc	= nullptr;
	shared_ptr<FPixelShaderDesc>	spPixelShaderDesc	= nullptr;
	shared_ptr<FGeometryShaderDesc> spGeometryShaderDesc= nullptr;

	switch (_eShaderType)
	{
	case EShaderType::VERTEX:
	{
		spVertexShaderDesc = static_pointer_cast<FVertexShaderDesc>(_spShaderDesc);
		spVertexShaderDesc->m_vecConstantBufferInfo.reserve(tShaderDesc.ConstantBuffers);
	}
	break;

	case EShaderType::PIXEL:
	{
		spPixelShaderDesc = static_pointer_cast<FPixelShaderDesc>(_spShaderDesc);
		spPixelShaderDesc->m_vecConstantBufferInfo.reserve(tShaderDesc.ConstantBuffers);
	}
	break;

	case EShaderType::GEOMETRY:
	{
		spGeometryShaderDesc = static_pointer_cast<FGeometryShaderDesc>(_spShaderDesc);
		spGeometryShaderDesc->m_vecConstantBufferInfo.reserve(tShaderDesc.ConstantBuffers);
	}
	break;

	default:
		CHECKF(false, L"Shader type is not designated.")
		break;
	}

	// 셰이더에서 사용되는 상수 버퍼를 생성합니다.
	for (UINT iIndex = 0; iIndex < tShaderDesc.ConstantBuffers; iIndex++)
	{
		D3D11_SHADER_BUFFER_DESC tShaderBufferDesc;
		ZeroMemory(&tShaderBufferDesc, sizeof(tShaderBufferDesc));

		ID3D11ShaderReflectionConstantBuffer* pShaderReflectionConstantBuffer = _cpReflection->GetConstantBufferByIndex(iIndex);
		ENSURE(pShaderReflectionConstantBuffer->GetDesc(&tShaderBufferDesc));

		wstring wstrBufferName(tShaderBufferDesc.Name, tShaderBufferDesc.Name + strlen(tShaderBufferDesc.Name));
		if (m_wpShaderHandler.lock()->FindConstantBuffer(wstrBufferName)) { continue; }

		D3D11_BUFFER_DESC tBufferDesc;
		ZeroMemory(&tBufferDesc, sizeof(tBufferDesc));
		tBufferDesc.ByteWidth = tShaderBufferDesc.Size;
		tBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		tBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		tBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		tBufferDesc.StructureByteStride = 0;
		tBufferDesc.MiscFlags = 0;

		ComPtr<ID3D11Buffer> cpBuffer = nullptr;
		ENSURE(m_wpDeviceManager.lock()->GetDevice()->CreateBuffer(&tBufferDesc, nullptr, cpBuffer.GetAddressOf()));
		m_wpShaderHandler.lock()->AddConstantBuffer(wstrBufferName, cpBuffer);
	}

	return S_OK;
}

HRESULT Engine::CShaderLoader::CreateDescInfo(std::shared_ptr<FShaderDesc>& _spShaderDesc, const ComPtr<ID3D11ShaderReflection>& _cpReflection)
{
	// 세이더 디스크립션을 불러옵니다.
	D3D11_SHADER_DESC tShaderDesc;
	ZeroMemory(&tShaderDesc, sizeof(tShaderDesc));
	_cpReflection->GetDesc(&tShaderDesc);

	for (UINT iIndex = 0; iIndex < tShaderDesc.BoundResources; iIndex++)
	{
		D3D11_SHADER_INPUT_BIND_DESC tShaderInputBindDesc;
		ZeroMemory(&tShaderInputBindDesc, sizeof(tShaderInputBindDesc));
		_cpReflection->GetResourceBindingDesc(iIndex, &tShaderInputBindDesc);

		wstring wstrName(tShaderInputBindDesc.Name, tShaderInputBindDesc.Name + strlen(tShaderInputBindDesc.Name));
		uint8 iBindPoint = tShaderInputBindDesc.BindPoint;

		switch (tShaderInputBindDesc.Type)
		{
		case D3D_SHADER_INPUT_TYPE::D3D_SIT_CBUFFER:
			_spShaderDesc->m_vecConstantBufferInfo.push_back({ iBindPoint, wstrName });
			break;

		case D3D_SHADER_INPUT_TYPE::D3D_SIT_SAMPLER:
			_spShaderDesc->m_vecSamplerInfo.push_back({ iBindPoint, wstrName });
			break;

		case D3D_SHADER_INPUT_TYPE::D3D_SIT_TEXTURE:
			_spShaderDesc->m_vecTextureInfo.push_back({ iBindPoint, wstrName });
			break;

		default:
			break;
		}
	}

	// 레지스터 번호를 오름차순으로 정렬합니다.
	sort(_spShaderDesc->m_vecConstantBufferInfo.begin(), _spShaderDesc->m_vecConstantBufferInfo.end());
	sort(_spShaderDesc->m_vecSamplerInfo.begin(), _spShaderDesc->m_vecSamplerInfo.end());
	sort(_spShaderDesc->m_vecTextureInfo.begin(), _spShaderDesc->m_vecTextureInfo.end());
	return S_OK;
}

DXGI_FORMAT Engine::CShaderLoader::FindFormat(BYTE _iMask, D3D_REGISTER_COMPONENT_TYPE _eComponentType)
{
	switch (_iMask)
	{
	case 0b0000'0001:
		switch (_eComponentType)
		{
		case D3D_REGISTER_COMPONENT_UINT32:		return DXGI_FORMAT_R32_UINT;
		case D3D_REGISTER_COMPONENT_SINT32:		return DXGI_FORMAT_R32_SINT;
		case D3D_REGISTER_COMPONENT_FLOAT32:	return DXGI_FORMAT_R32_FLOAT;
		}
		break;

	case 0b0000'0011:
		switch (_eComponentType)
		{
		case D3D_REGISTER_COMPONENT_UINT32:		return DXGI_FORMAT_R32G32_UINT;
		case D3D_REGISTER_COMPONENT_SINT32:		return DXGI_FORMAT_R32G32_SINT;
		case D3D_REGISTER_COMPONENT_FLOAT32:	return DXGI_FORMAT_R32G32_FLOAT;
		}
		break;

	case 0b0000'0111:
		switch (_eComponentType)
		{
		case D3D_REGISTER_COMPONENT_UINT32:		return DXGI_FORMAT_R32G32B32_UINT;
		case D3D_REGISTER_COMPONENT_SINT32:		return DXGI_FORMAT_R32G32B32_SINT;
		case D3D_REGISTER_COMPONENT_FLOAT32:	return DXGI_FORMAT_R32G32B32_FLOAT;
		}
		break;

	case 0b0000'1111:
		switch (_eComponentType)
		{
		case D3D_REGISTER_COMPONENT_UINT32:		return DXGI_FORMAT_R32G32B32A32_UINT;
		case D3D_REGISTER_COMPONENT_SINT32:		return DXGI_FORMAT_R32G32B32A32_SINT;
		case D3D_REGISTER_COMPONENT_FLOAT32:	return DXGI_FORMAT_R32G32B32A32_FLOAT;
		}
		break;

	default:
		break;
	}

	return DXGI_FORMAT_UNKNOWN;
}