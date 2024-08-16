#pragma once

namespace Engine
{
	class CDeviceManager;
	class CShaderLoader;

	class ENGINE_DLL CShaderHandler final
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		DECLARE_SINGLETON(CShaderHandler)
		
	/********************
		Events
	********************/
	public:
		HRESULT Initialize(const std::shared_ptr<CDeviceManager>& _spDeviceManager);

		void Release();
		
	/******************
		Methods
	******************/
	public:
		ComPtr<ID3D11VertexShader> FindVertexShader(const std::wstring& _wstrVertexShaderName);

		ComPtr<ID3D11GeometryShader> FindGeometryShader(const std::wstring& _wstrGeometryShaderName);

		ComPtr<ID3D11PixelShader> FindPixelShader(const std::wstring& _wstrPixelShaderName);

		ComPtr<ID3D11InputLayout> FindInputLayout(const std::wstring& _wstrInputLayoutName);

		ComPtr<ID3D11Buffer> FindConstantBuffer(const std::wstring& _wstrConstantBufferName);

	public:
		HRESULT AddVertexShader(const std::wstring& _wstrVertexShaderName, const ComPtr<ID3D11VertexShader>& _cpVertexShader);

		HRESULT AddGeometryShader(const std::wstring& _wstrGeometryShaderName, const ComPtr<ID3D11GeometryShader>& _cpGeometryShader);

		HRESULT AddPixelShader(const std::wstring& _wstrPixelShaderName, const ComPtr<ID3D11PixelShader>& _cpPixelShader);

		HRESULT AddInputLayout(const std::wstring& _wstrInputLayoutName, const ComPtr<ID3D11InputLayout>& _cpInputLayout);

		HRESULT AddConstantBuffer(const std::wstring& _wstrConstantBufferName, const ComPtr<ID3D11Buffer>& _cpConstantBuffer);

	public:
		void VSSetShader(ID3D11VertexShader* _pVertexShader, ID3D11ClassInstance* const* _ppClassInstances, UINT _iNumClassInstances);

		void GSSetShader(ID3D11GeometryShader* _pGeometryShader, ID3D11ClassInstance* const* _ppClassInstances, UINT _iNumClassInstances);

		void PSSetShader(ID3D11PixelShader* _pPixelShader, ID3D11ClassInstance* const* _ppClassInstances, UINT _iNumClassInstances);

		void IASetInputLayout(ID3D11InputLayout* _pInputLayout);

		void VSSetConstantBuffers(UINT _iStartSlot, UINT _iNumBuffers, ID3D11Buffer* const* _ppConstantBuffers);

		void GSSetConstantBuffers(UINT _iStartSlot, UINT _iNumBuffers, ID3D11Buffer* const* _ppConstantBuffers);

		void PSSetConstantBuffers(UINT _iStartSlot, UINT _iNumBuffers, ID3D11Buffer* const* _ppConstantBuffers);

		template<typename T>
		void CopyConstantBuffer(const ComPtr<ID3D11Buffer>& _cpBuffer, const T& _tConstantBuffer)
		{
			D3D11_MAPPED_SUBRESOURCE tMappedSubresource;
			m_wpDeviceManager.lock()->GetDeviceContext()->Map(_cpBuffer.Get(), NULL, D3D11_MAP_WRITE_DISCARD, NULL, &tMappedSubresource);
			memcpy(tMappedSubresource.pData, &_tConstantBuffer, sizeof(_tConstantBuffer));
			m_wpDeviceManager.lock()->GetDeviceContext()->Unmap(_cpBuffer.Get(), NULL);
		}

	public:
		HRESULT AddVertexShaderDesc(const std::wstring& _wstrVertexShaderName, std::shared_ptr<FVertexShaderDesc> _spVertexShaderDesc);

		HRESULT AddGeometryShaderDesc(const std::wstring& _wstrGeometryShaderName, std::shared_ptr<FGeometryShaderDesc> _spGeometryShaderDesc);

		HRESULT AddPixelShaderDesc(const std::wstring& _wstrPixelShaderName, std::shared_ptr<FPixelShaderDesc> _spPixelShaderDesc);

		std::shared_ptr<FVertexShaderDesc> FindVertexShaderDesc(const std::wstring& _wstrVertexShaderName);

		std::shared_ptr<FGeometryShaderDesc> FindGeometryShaderDesc(const std::wstring& _wstrGeometryShaderName);

		std::shared_ptr<FPixelShaderDesc> FindPixelShaderDesc(const std::wstring& _wstrPixelShaderName);

	public:
		void SetPrimitiveBatch(const std::shared_ptr<PrimitiveBatch<VertexPositionColor>> _spPrimitiveBatch) { m_spPrimitiveBatch = _spPrimitiveBatch; }

		void SetBasicEffect(const std::shared_ptr<BasicEffect> _spBasicEffect) { m_spBasicEffect = _spBasicEffect; }

		std::shared_ptr<PrimitiveBatch<VertexPositionColor>> GetPrimitiveBatch() const { return m_spPrimitiveBatch; }

		std::shared_ptr<BasicEffect> GetBasicEffect() const { return m_spBasicEffect; }

	/********************
		Getter/Setter
	********************/
	public:
		shared_ptr<CDeviceManager> GetDeviceManager() const { return m_wpDeviceManager.expired() ? nullptr : m_wpDeviceManager.lock(); }

		const std::unordered_map<std::wstring, std::shared_ptr<FVertexShaderDesc>>& GetVertexShaderDescs() const { return m_umapVertexShaderDescs; }

		const std::unordered_map<std::wstring, std::shared_ptr<FPixelShaderDesc>>& GetPixelShaderDescs() const { return m_umapPixelShaderDescs; }

		const std::unordered_map<std::wstring, std::shared_ptr<FGeometryShaderDesc>>& GetGeometryShaderDescs() const { return m_umapGeometryShaderDescs; }

	/********************
		Data Members
	********************/
	private:
		// 버텍스 셰이더들
		std::unordered_map<std::wstring, ComPtr<ID3D11VertexShader>> m_umapVertexShaders;

		// 지오메트리 셰이더들
		std::unordered_map<std::wstring, ComPtr<ID3D11GeometryShader>> m_umapGeometryShaders;

		// 픽셀 셰이더들
		std::unordered_map<std::wstring, ComPtr<ID3D11PixelShader>> m_umapPixelShaders;

		// 입력 레이아웃들
		std::unordered_map<std::wstring, ComPtr<ID3D11InputLayout>> m_umapInputLayouts;

		// 상수 버퍼들
		std::unordered_map<std::wstring, ComPtr<ID3D11Buffer>> m_umapConstantBuffers;

	private:
		// 버텍스 세이더 문맥들
		std::unordered_map<std::wstring, std::shared_ptr<FVertexShaderDesc>> m_umapVertexShaderDescs;

		// 지오메트리 셰이더 문맥들
		std::unordered_map<std::wstring, std::shared_ptr<FGeometryShaderDesc>> m_umapGeometryShaderDescs;

		// 픽셀 셰이더 문맥들
		std::unordered_map<std::wstring, std::shared_ptr<FPixelShaderDesc>> m_umapPixelShaderDescs;

	private:
		// 디버그 배치
		std::shared_ptr<PrimitiveBatch<VertexPositionColor>> m_spPrimitiveBatch = nullptr;

		// 디버그 이펙트
		std::shared_ptr<BasicEffect> m_spBasicEffect = nullptr;

	private:
		// 디바이스 매니저
		std::weak_ptr<CDeviceManager> m_wpDeviceManager;

		// 셰이더 로더
		std::shared_ptr<CShaderLoader> m_spShaderLoader = nullptr;
	};
}
