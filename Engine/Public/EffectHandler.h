#pragma once

namespace Engine
{
	class CDeviceManager;
	class CEffectLoader;

	class ENGINE_DLL CEffectHandler final
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		DECLARE_SINGLETON(CEffectHandler)
		
	/********************
		Events
	********************/
	public:
		HRESULT Initialize(const std::shared_ptr<CDeviceManager>& _spDeviceManager);

		void Release();
		
	/********************
		Methods
	********************/
	public:
		HRESULT AddVertexBuffer(const std::wstring& _wstrVertexBufferName, const ComPtr<ID3D11Buffer>& _spVertexBuffer);

		HRESULT AddIndexBuffer(const std::wstring& _wstrIndexBufferName, const ComPtr<ID3D11Buffer>& _spIndexBuffer);

		HRESULT AddMaskShaderResourceView(const std::wstring& _wstrShaderResourceViewName, const ComPtr<ID3D11ShaderResourceView>& _cpShaderResouceView);

		HRESULT AddNoiseShaderResourceView(const std::wstring& _wstrShaderResourceViewName, const ComPtr<ID3D11ShaderResourceView>& _cpShaderResouceView);

		HRESULT AddModelDesc(const std::wstring& _wstrModelDescName, const std::shared_ptr<FModelDesc>& _spModelDesc);
		
		HRESULT AddEffectMeshDataGroup(const std::wstring& _wstrMeshEffectDataGroupName, const std::shared_ptr<FMeshEffectDataGroupProperty>& _spMeshEffectDataGroupProperty);

	public:
		ComPtr<ID3D11Buffer> FindVertexBuffer(const std::wstring& _wstrVertexBufferName);

		ComPtr<ID3D11Buffer> FindIndexBuffer(const std::wstring& _wstrIndexBufferName);

		ComPtr<ID3D11ShaderResourceView> FindMaskShaderResourceView(const std::wstring& _wstrShaderResourceViewName);

		ComPtr<ID3D11ShaderResourceView> FindNoiseShaderResourceView(const std::wstring& _wstrShaderResourceViewName);

		std::shared_ptr<FModelDesc> FindModelDesc(const std::wstring& _wstrModelDescName);
		
		std::shared_ptr<FMeshEffectDataGroupProperty> FindEffectMeshDataGroup(const std::wstring& _wstrMeshEffectDataGroupName);

	public:
		void IASetVertexBuffers(UINT _iStartSlot, UINT _iNumBuffers, ID3D11Buffer* const* _ppVertexBuffers, const UINT* _pStrides, const UINT* _pOffsets);

		void IASetIndexBuffer(ID3D11Buffer* _pIndexBuffer, DXGI_FORMAT _tFormat, UINT _iOffset);

		void IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY _tPrimitiveTopology);

		void DrawIndexed(UINT _iIndexCount, UINT _iStartIndexLocation, UINT _iBaseVertexLocation);

		void VSSetShaderResources(UINT _iStartSlot, UINT _iNumViews, ID3D11ShaderResourceView* const* _ppShaderResourceViews);

		void PSSetShaderResources(UINT _iStartSlot, UINT _iNumViews, ID3D11ShaderResourceView* const* _ppShaderResourceViews);

	public:
		int32 GetNumVertice(EModelType _eModelType, const std::wstring& _wstrVertexBufferName) const;

		int32 GetNumIndices(const std::wstring& _wstrIndexBufferName) const;

	/********************
		Getter/Setter
	********************/
	public:
		shared_ptr<CDeviceManager> GetDeviceManager() const { return m_wpDeviceManager.expired() ? nullptr : m_wpDeviceManager.lock(); }
		
		const std::unordered_map<std::wstring, std::shared_ptr<FModelDesc>>& GetEffectModelDescs() { return m_umapEffectModelDescs; }

		const std::unordered_map<std::wstring, ComPtr<ID3D11ShaderResourceView>>& GetMaskShaderResourceViews() { return m_umapMaskShaderResourceViews; }

		const std::unordered_map<std::wstring, ComPtr<ID3D11ShaderResourceView>>& GetNoiseShaderResourceViews() { return m_umapNoiseShaderResourceViews; }

	/********************
		Data Members
	********************/
	private:
		// 버텍스 버퍼들
		std::unordered_map<std::wstring, ComPtr<ID3D11Buffer>> m_umapVertexBuffers;

		// 인덱스 버퍼들
		std::unordered_map<std::wstring, ComPtr<ID3D11Buffer>> m_umapIndexBuffers;

		// 마스크 셰이더 리소스 뷰들
		std::unordered_map<std::wstring, ComPtr<ID3D11ShaderResourceView>> m_umapMaskShaderResourceViews;

		// 노이즈 셰이더 리소스 뷰들
		std::unordered_map<std::wstring, ComPtr<ID3D11ShaderResourceView>> m_umapNoiseShaderResourceViews;

	private:
		// 이펙트 모델 문맥들
		std::unordered_map<std::wstring, std::shared_ptr<FModelDesc>> m_umapEffectModelDescs;

		// 메시 이펙트 프로퍼티들
		std::unordered_map<std::wstring, std::shared_ptr<FMeshEffectDataGroupProperty>> m_umapMeshEffectDataGroup;

		// 파티클 이펙트 프로퍼티들
		// std::unordered_map<std::wstring, std::shared_ptr<FParticleEffectDataGroupProperty>> m_umapParticleEffectDataGroup;

	private:
		std::weak_ptr<CDeviceManager> m_wpDeviceManager;

		std::shared_ptr<CEffectLoader> m_spEffectLoader = nullptr;
	};
}
