#include "pch.h"
#include "BufferLoader.h"
#include "BufferHandler.h"

#include "DeviceManager.h"
#include "BufferHandler.h"

#include "MathUtility.h"

std::shared_ptr<CBufferLoader> Engine::CBufferLoader::Create()
{
	const std::shared_ptr<CBufferLoader> spLoader = make_shared<CBufferLoader>();
	ENSUREF(spLoader->Initialize(), L"Failed to create buffer loader.");
	return spLoader;
}

HRESULT Engine::CBufferLoader::Initialize()
{
	m_wpBufferHandler = CBufferHandler::GetInstance();
	m_wpDeviceManager = CBufferHandler::GetInstance()->GetDeviceManager();

	// 외부 파일을 불러옵니다.
	LoadBufferFromFile();
	return S_OK;
}

void Engine::CBufferLoader::Release()
{
}

HRESULT Engine::CBufferLoader::LoadBufferFromFile()
{
	ENSUREF(LoadPoint(), L"Failed to load point buffer.");
	ENSUREF(LoadRect(), L"Failed to load rect buffer.");
	ENSUREF(LoadCube(), L"Failed to load cube buffer.");
	
	CreateVertexBuffer();
	CreateIndexBuffer();

	ENSUREF(LoadInstanceVertex(), L"Failed to load instance point buffer");
	CreateInstanceVertexBuffer();
	return S_OK;
}

HRESULT Engine::CBufferLoader::LoadPoint()
{
	// 점 버텍스 데이터
	TPosition tPosition;
	tPosition.m_vPosition = Vector3(0.0f, 0.0f, 0.0f);
	m_umapPointVertices.emplace(L"Point", tPosition);
	return S_OK;
}

HRESULT Engine::CBufferLoader::LoadRect()
{
	// 렉트 버텍스 데이터들
	vector<TPositionTexCoord2> vecRectVertices;
	vecRectVertices.reserve(4);
	vecRectVertices.resize(4);

	vecRectVertices[0].m_vPosition = Vector3(-0.5f, 0.5f, 0.0f);
	vecRectVertices[0].m_vTexCoord2 = Vector2(0.0f, 0.0f);

	vecRectVertices[1].m_vPosition = Vector3(0.5f, 0.5f, 0.0f);
	vecRectVertices[1].m_vTexCoord2 = Vector2(1.0f, 0.0f);

	vecRectVertices[2].m_vPosition = Vector3(0.5f, -0.5f, 0.0f);
	vecRectVertices[2].m_vTexCoord2 = Vector2(1.0f, 1.0f);

	vecRectVertices[3].m_vPosition = Vector3(-0.5f, -0.5f, 0.0f);
	vecRectVertices[3].m_vTexCoord2 = Vector2(0.0f, 1.0f);

	m_umapRectVertices.emplace(L"Rect", vecRectVertices);

	// 렉터 인덱스 데이터
	vector<uint32> vecRectIndices;
	vecRectIndices.reserve(6);
	vecRectIndices.resize(6);

	vecRectIndices[0] = 0; vecRectIndices[1] = 1; vecRectIndices[2] = 2;
	vecRectIndices[3] = 0; vecRectIndices[4] = 2; vecRectIndices[5] = 3;

	m_umapRectIndices.emplace(L"Rect", vecRectIndices);
	return S_OK;
}

HRESULT Engine::CBufferLoader::LoadCube()
{
	// 큐브 버텍스 데이터들
	vector<TPositionTexCoord3> vecCubeVertices;
	vecCubeVertices.reserve(8);
	vecCubeVertices.resize(8);

	vecCubeVertices[0].m_vPosition = Vector3(-0.5f, 0.5f, -0.5f);
	vecCubeVertices[0].m_vTexCoord3 = vecCubeVertices[0].m_vPosition;

	vecCubeVertices[1].m_vPosition = Vector3(0.5f, 0.5f, -0.5f);
	vecCubeVertices[1].m_vTexCoord3 = vecCubeVertices[1].m_vPosition;

	vecCubeVertices[2].m_vPosition = Vector3(0.5f, -0.5f, -0.5f);
	vecCubeVertices[2].m_vTexCoord3 = vecCubeVertices[2].m_vPosition;

	vecCubeVertices[3].m_vPosition = Vector3(-0.5f, -0.5f, -0.5f);
	vecCubeVertices[3].m_vTexCoord3 = vecCubeVertices[3].m_vPosition;

	vecCubeVertices[4].m_vPosition = Vector3(-0.5f, 0.5f, 0.5f);
	vecCubeVertices[4].m_vTexCoord3 = vecCubeVertices[4].m_vPosition;

	vecCubeVertices[5].m_vPosition = Vector3(0.5f, 0.5f, 0.5f);
	vecCubeVertices[5].m_vTexCoord3 = vecCubeVertices[5].m_vPosition;

	vecCubeVertices[6].m_vPosition = Vector3(0.5f, -0.5f, 0.5f);
	vecCubeVertices[6].m_vTexCoord3 = vecCubeVertices[6].m_vPosition;

	vecCubeVertices[7].m_vPosition = Vector3(-0.5f, -0.5f, 0.5f);
	vecCubeVertices[7].m_vTexCoord3 = vecCubeVertices[7].m_vPosition;

	m_umapCubeVertices.emplace(L"Cube", vecCubeVertices);

	// 큐브 인덱스 데이터들
	vector<uint32> vecCubeIndices;
	vecCubeIndices.reserve(36);
	vecCubeIndices.resize(36);

	// +X
	vecCubeIndices[0] = 1; vecCubeIndices[1] = 5; vecCubeIndices[2] = 6;
	vecCubeIndices[3] = 1; vecCubeIndices[4] = 6; vecCubeIndices[5] = 2;

	// -X
	vecCubeIndices[6] = 4; vecCubeIndices[7] = 0; vecCubeIndices[8] = 3;
	vecCubeIndices[9] = 4; vecCubeIndices[10] = 3; vecCubeIndices[11] = 7;

	// +Y
	vecCubeIndices[12] = 4; vecCubeIndices[13] = 5; vecCubeIndices[14] = 1;
	vecCubeIndices[15] = 4; vecCubeIndices[16] = 1; vecCubeIndices[17] = 0;

	// -Y
	vecCubeIndices[18] = 3; vecCubeIndices[19] = 2; vecCubeIndices[20] = 6;
	vecCubeIndices[21] = 3; vecCubeIndices[22] = 6; vecCubeIndices[23] = 7;

	// +Z
	vecCubeIndices[24] = 5; vecCubeIndices[25] = 4; vecCubeIndices[26] = 7;
	vecCubeIndices[27] = 5; vecCubeIndices[28] = 7; vecCubeIndices[29] = 6;

	// -Z
	vecCubeIndices[30] = 0; vecCubeIndices[31] = 1; vecCubeIndices[32] = 2;
	vecCubeIndices[33] = 0; vecCubeIndices[34] = 2; vecCubeIndices[35] = 3;

	m_umapCubeIndices.emplace(L"Cube", vecCubeIndices);
	return S_OK;
}

HRESULT Engine::CBufferLoader::LoadInstanceVertex()
{
	// 인스턴스 포인트 버텍스 데이터
	vector<TPositionSize> vecPointVertices;
	vecPointVertices.reserve(1);
	vecPointVertices.resize(1);

	vecPointVertices[0].m_vPosition = Vector3(0.0f, 0.0f, 0.0f);
	vecPointVertices[0].m_vPSize = Vector2(1.0f, 1.0f);

	m_umapInstancePointVertices.emplace(L"InstancePoint", vecPointVertices);
	return S_OK;
}

HRESULT Engine::CBufferLoader::LoadInstanceIndex(const std::wstring& _wstrInstanceIndexDataName, int32 _iNumInstances)
{
	// 인스턴스 포인트 인덱스 데이터
	vector<uint32> vecRectIndices;
	vecRectIndices.reserve(_iNumInstances);
	vecRectIndices.resize(_iNumInstances);

	m_umapInstancePointIndices.emplace(_wstrInstanceIndexDataName, vecRectIndices);
	return S_OK;
}

HRESULT Engine::CBufferLoader::LoadInstanceTransform(const std::wstring& _wstrInstanceTransformDataName, int32 _iNumInstances)
{
	if (m_umapInstanceTransforms.find(_wstrInstanceTransformDataName) != m_umapInstanceTransforms.end()) { return E_FAIL; }

	vector<TInstanceTransform> vecInstanceTransforms;
	vecInstanceTransforms.resize(_iNumInstances);
	vecInstanceTransforms.reserve(_iNumInstances);

	for (int32 iIndex = 0; iIndex < _iNumInstances; ++iIndex)
	{
		// vecInstanceTransforms[iIndex].m_vRight		= Vector4(fSize, 0.0f, 0.0f, 0.0f);
		// vecInstanceTransforms[iIndex].m_vUp			= Vector4(0.0f, fSize, 0.0f, 0.0f);
		// vecInstanceTransforms[iIndex].m_vLook		= Vector4(0.0f, 0.0f, fSize, 0.0f);
		// vecInstanceTransforms[iIndex].m_vPosition	= Vector4(0.0f, 0.0f, 0.0f, 1.0f);
		// 
		// vecInstanceTransforms[iIndex].m_vColor		= 
	}

	m_umapInstanceTransforms.emplace(_wstrInstanceTransformDataName, vecInstanceTransforms);
	return S_OK;
}

HRESULT Engine::CBufferLoader::CreateVertexBuffer()
{
	// 점에서 버텍스 버퍼를 생성합니다.
	for (const auto& pair : m_umapPointVertices)
	{
		D3D11_BUFFER_DESC tBufferDesc;
		ZeroMemory(&tBufferDesc, sizeof(tBufferDesc));
		tBufferDesc.ByteWidth = static_cast<UINT>(sizeof(TPosition));
		tBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		tBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		tBufferDesc.CPUAccessFlags = 0;
		tBufferDesc.StructureByteStride = sizeof(TPosition);

		D3D11_SUBRESOURCE_DATA tVertexSubResourceData;
		ZeroMemory(&tVertexSubResourceData, sizeof(tVertexSubResourceData));
		tVertexSubResourceData.pSysMem = &pair.second;
		tVertexSubResourceData.SysMemPitch = 0;
		tVertexSubResourceData.SysMemSlicePitch = 0;

		ComPtr<ID3D11Buffer> cpBuffer = nullptr;
		ENSURE(m_wpDeviceManager.lock()->GetDevice()->CreateBuffer(&tBufferDesc, &tVertexSubResourceData, cpBuffer.GetAddressOf()));
		m_wpBufferHandler.lock()->AddVertexBuffer(pair.first, cpBuffer);
	}

	// 렉트에서 버텍스 버퍼를 생성합니다.
	for (const auto& pair : m_umapRectVertices)
	{
		D3D11_BUFFER_DESC tBufferDesc;
		ZeroMemory(&tBufferDesc, sizeof(tBufferDesc));
		tBufferDesc.ByteWidth = static_cast<UINT>(sizeof(pair.second[0]) * pair.second.size());
		tBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		tBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		tBufferDesc.CPUAccessFlags = 0;
		tBufferDesc.StructureByteStride = sizeof(pair.second[0]);

		D3D11_SUBRESOURCE_DATA tVertexSubResourceData;
		ZeroMemory(&tVertexSubResourceData, sizeof(tVertexSubResourceData));
		tVertexSubResourceData.pSysMem = pair.second.data();
		tVertexSubResourceData.SysMemPitch = 0;
		tVertexSubResourceData.SysMemSlicePitch = 0;

		ComPtr<ID3D11Buffer> cpBuffer = nullptr;
		ENSURE(m_wpDeviceManager.lock()->GetDevice()->CreateBuffer(&tBufferDesc, &tVertexSubResourceData, cpBuffer.GetAddressOf()));
		m_wpBufferHandler.lock()->AddVertexBuffer(pair.first, cpBuffer);
	}

	// 큐브에서 버텍스 버퍼를 생성합니다.
	for (const auto& pair : m_umapCubeVertices)
	{
		D3D11_BUFFER_DESC tBufferDesc;
		ZeroMemory(&tBufferDesc, sizeof(tBufferDesc));
		tBufferDesc.ByteWidth = static_cast<UINT>(sizeof(pair.second[0]) * pair.second.size());
		tBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		tBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		tBufferDesc.CPUAccessFlags = 0;
		tBufferDesc.StructureByteStride = sizeof(pair.second[0]);

		D3D11_SUBRESOURCE_DATA tVertexSubResourceData;
		ZeroMemory(&tVertexSubResourceData, sizeof(tVertexSubResourceData));
		tVertexSubResourceData.pSysMem = pair.second.data();
		tVertexSubResourceData.SysMemPitch = 0;
		tVertexSubResourceData.SysMemSlicePitch = 0;

		ComPtr<ID3D11Buffer> cpBuffer = nullptr;
		ENSURE(m_wpDeviceManager.lock()->GetDevice()->CreateBuffer(&tBufferDesc, &tVertexSubResourceData, cpBuffer.GetAddressOf()));
		m_wpBufferHandler.lock()->AddVertexBuffer(pair.first, cpBuffer);
	}

	return S_OK;
}

HRESULT Engine::CBufferLoader::CreateIndexBuffer()
{
	// 렉트에서 인덱스 버퍼를 생성합니다.
	for (const auto& pair : m_umapRectIndices)
	{
		D3D11_BUFFER_DESC tBufferDesc;
		ZeroMemory(&tBufferDesc, sizeof(tBufferDesc));
		tBufferDesc.ByteWidth = static_cast<UINT>(sizeof(pair.second[0]) * pair.second.size());
		tBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		tBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		tBufferDesc.CPUAccessFlags = 0;
		tBufferDesc.StructureByteStride = sizeof(pair.second[0]);

		D3D11_SUBRESOURCE_DATA tIndexSubResourceData;
		ZeroMemory(&tIndexSubResourceData, sizeof(tIndexSubResourceData));
		tIndexSubResourceData.pSysMem = pair.second.data();
		tIndexSubResourceData.SysMemPitch = 0;
		tIndexSubResourceData.SysMemSlicePitch = 0;

		ComPtr<ID3D11Buffer> cpBuffer = nullptr;
		ENSURE(m_wpDeviceManager.lock()->GetDevice()->CreateBuffer(&tBufferDesc, &tIndexSubResourceData, cpBuffer.GetAddressOf()));
		m_wpBufferHandler.lock()->AddIndexBuffer(pair.first, cpBuffer);
	}

	// 큐브에서 인덱스 버퍼를 생성합니다.
	for (const auto& pair : m_umapCubeIndices)
	{
		D3D11_BUFFER_DESC tBufferDesc;
		ZeroMemory(&tBufferDesc, sizeof(tBufferDesc));
		tBufferDesc.ByteWidth = static_cast<UINT>(sizeof(pair.second[0]) * pair.second.size());
		tBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		tBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		tBufferDesc.CPUAccessFlags = 0;
		tBufferDesc.StructureByteStride = sizeof(pair.second[0]);

		D3D11_SUBRESOURCE_DATA tIndexSubResourceData;
		ZeroMemory(&tIndexSubResourceData, sizeof(tIndexSubResourceData));
		tIndexSubResourceData.pSysMem = pair.second.data();
		tIndexSubResourceData.SysMemPitch = 0;
		tIndexSubResourceData.SysMemSlicePitch = 0;

		ComPtr<ID3D11Buffer> cpBuffer = nullptr;
		ENSURE(m_wpDeviceManager.lock()->GetDevice()->CreateBuffer(&tBufferDesc, &tIndexSubResourceData, cpBuffer.GetAddressOf()));
		m_wpBufferHandler.lock()->AddIndexBuffer(pair.first, cpBuffer);
	}

	return S_OK;
}

HRESULT Engine::CBufferLoader::CreateInstanceVertexBuffer()
{
	for (const auto& pair : m_umapInstancePointVertices)
	{
		D3D11_BUFFER_DESC tBufferDesc;
		ZeroMemory(&tBufferDesc, sizeof(tBufferDesc));
		tBufferDesc.ByteWidth = static_cast<UINT>(sizeof(pair.second[0]) * pair.second.size());
		tBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		tBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		tBufferDesc.CPUAccessFlags = 0;
		tBufferDesc.StructureByteStride = sizeof(pair.second[0]);

		D3D11_SUBRESOURCE_DATA tVertexSubResourceData;
		ZeroMemory(&tVertexSubResourceData, sizeof(tVertexSubResourceData));
		tVertexSubResourceData.pSysMem = pair.second.data();
		tVertexSubResourceData.SysMemPitch = 0;
		tVertexSubResourceData.SysMemSlicePitch = 0;

		ComPtr<ID3D11Buffer> cpBuffer = nullptr;
		ENSURE(m_wpDeviceManager.lock()->GetDevice()->CreateBuffer(&tBufferDesc, &tVertexSubResourceData, cpBuffer.GetAddressOf()));
		m_wpBufferHandler.lock()->AddInstanceVertexBuffer(pair.first, cpBuffer);
	}

	return S_OK;
}

HRESULT Engine::CBufferLoader::CreateInstanceIndexBuffer(const std::wstring& _wstrInstanceIndexDataName)
{
	D3D11_BUFFER_DESC tBufferDesc;
	ZeroMemory(&tBufferDesc, sizeof(tBufferDesc));
	tBufferDesc.ByteWidth = static_cast<UINT>(sizeof(m_umapInstancePointIndices[_wstrInstanceIndexDataName][0]) * m_umapInstancePointIndices[_wstrInstanceIndexDataName].size());
	tBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	tBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	tBufferDesc.CPUAccessFlags = 0;
	tBufferDesc.MiscFlags = 0;
	tBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA tIndexSubResourceData;
	ZeroMemory(&tIndexSubResourceData, sizeof(tIndexSubResourceData));
	tIndexSubResourceData.pSysMem = m_umapInstancePointIndices[_wstrInstanceIndexDataName].data();
	tIndexSubResourceData.SysMemPitch = 0;
	tIndexSubResourceData.SysMemSlicePitch = 0;

	ComPtr<ID3D11Buffer> cpBuffer = nullptr;
	ENSURE(m_wpDeviceManager.lock()->GetDevice()->CreateBuffer(&tBufferDesc, &tIndexSubResourceData, cpBuffer.GetAddressOf()));
	m_wpBufferHandler.lock()->AddInstanceIndexBuffer(_wstrInstanceIndexDataName, cpBuffer);
	
	return S_OK;
}

HRESULT Engine::CBufferLoader::CreateInstanceTransformBuffer(const std::wstring& _wstrInstanceTransformDataName)
{
	D3D11_BUFFER_DESC tBufferDesc;
	ZeroMemory(&tBufferDesc, sizeof(tBufferDesc));
	tBufferDesc.ByteWidth = static_cast<UINT>(sizeof(m_umapInstanceTransforms[_wstrInstanceTransformDataName][0]) * m_umapInstanceTransforms[_wstrInstanceTransformDataName].size());
	tBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	tBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	tBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	tBufferDesc.StructureByteStride = sizeof(m_umapInstanceTransforms[_wstrInstanceTransformDataName][0]);

	D3D11_SUBRESOURCE_DATA tVertexSubResourceData;
	ZeroMemory(&tVertexSubResourceData, sizeof(tVertexSubResourceData));
	tVertexSubResourceData.pSysMem = m_umapInstanceTransforms[_wstrInstanceTransformDataName].data();
	tVertexSubResourceData.SysMemPitch = 0;
	tVertexSubResourceData.SysMemSlicePitch = 0;

	ComPtr<ID3D11Buffer> cpBuffer = nullptr;
	ENSURE(m_wpDeviceManager.lock()->GetDevice()->CreateBuffer(&tBufferDesc, &tVertexSubResourceData, cpBuffer.GetAddressOf()));
	m_wpBufferHandler.lock()->AddInstanceTransformBuffer(_wstrInstanceTransformDataName, cpBuffer);

	return S_OK;
}
