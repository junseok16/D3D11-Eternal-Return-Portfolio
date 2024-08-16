#pragma once

namespace Engine
{
	class CDeviceManager;
	class CShaderHandler;

	class CShaderLoader final
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CShaderLoader() = default;

		virtual ~CShaderLoader() = default;

	/********************
		Events
	********************/
	public:
		static std::shared_ptr<CShaderLoader> Create();

		HRESULT Initialize();

		void Release();
		
	/********************
		Methods
	********************/
	public:
		HRESULT LoadVertexShaderFromFile();

		HRESULT LoadGeometryShaderFromFile();

		HRESULT LoadPixelShaderFromFile();
		
		HRESULT LoadBasicEffect();

	public:
		HRESULT CompileShaderFromFile(EShaderType _eShaderType, std::shared_ptr<FShaderDesc>& _spShaderDesc, ComPtr<ID3DBlob>& _cpShaderBlob, const filesystem::directory_entry& _fsEntry);

		HRESULT CreateShaderReflection(const ComPtr<ID3D11ShaderReflection>& _cpReflection, const ComPtr<ID3DBlob>& _cpShaderBlob);

		HRESULT CreateInputLayout(EShaderType _eShaderType, std::shared_ptr<FShaderDesc>& _spShaderDesc, const ComPtr<ID3D11ShaderReflection>& _cpReflection, const ComPtr<ID3DBlob>& _cpShaderBlob, const filesystem::directory_entry& _fsEntry);

		HRESULT CreateConstantBuffer(EShaderType _eShaderType, std::shared_ptr<FShaderDesc>& _spShaderDesc, const ComPtr<ID3D11ShaderReflection>& _cpReflection);

		HRESULT CreateDescInfo(std::shared_ptr<FShaderDesc>& _spShaderDesc, const ComPtr<ID3D11ShaderReflection>& _cpReflection);

		DXGI_FORMAT FindFormat(BYTE _iMask, D3D_REGISTER_COMPONENT_TYPE _eComponentType);

	/********************
		Data Members
	********************/
	private:
		std::weak_ptr<CDeviceManager> m_wpDeviceManager;

		std::weak_ptr<CShaderHandler> m_wpShaderHandler;

		std::wstring m_wstrVertexShaderFilePath = L"../../Resource/Shaders/";

		std::wstring m_wstrPixelShaderFilePath = L"../../Resource/Shaders/";

		std::wstring m_wstrGeometryShaderFilePath = L"../../Resource/Shaders/";
	};
}

