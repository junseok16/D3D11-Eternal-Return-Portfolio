#pragma once

namespace Engine
{
	class CMeshBone;
	class CDeviceManager;
	class CModelLoader;
	class CBoneOffset;
	class CBone;
	class CAnimation;

	class ENGINE_DLL CModelHandler final
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		DECLARE_SINGLETON(CModelHandler)
		
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

		HRESULT AddShaderResourceView(const std::wstring& _wstrShaderResourceViewName, const ComPtr<ID3D11ShaderResourceView>& _cpShaderResouceView);

		HRESULT AddBoneOffset(const std::wstring& _wstrMeshName, const shared_ptr<CBoneOffset>& _spBoneOffset);

		HRESULT AddBone(const std::wstring& _wstrBoneName, const std::vector<shared_ptr<CBone>>& _vecBones);

		HRESULT AddAnimation(const std::wstring& _wstrAnimationName, const std::unordered_map<std::string, std::shared_ptr<CAnimation>>& _umapAnimations);

		HRESULT AddModelDesc(const std::wstring& _wstrModelDescName, const std::shared_ptr<FModelDesc>& _spModelDesc);

	public:
		ComPtr<ID3D11Buffer> FindVertexBuffer(const std::wstring& _wstrVertexBufferName);

		ComPtr<ID3D11Buffer> FindIndexBuffer(const std::wstring& _wstrIndexBufferName);

		std::shared_ptr<CBoneOffset> FindBoneOffset(const std::wstring& _wstrMeshName);

		ComPtr<ID3D11ShaderResourceView> FindShaderResourceView(const std::wstring& _wstrShaderResourceViewName);

		std::shared_ptr<FModelDesc> FindModelDesc(const std::wstring& _wstrModelDescName);
		
		int32 FindBoneIndex(const std::wstring& _wstrModelName, const std::string& _strBoneName);

		const std::unordered_map<std::string, std::shared_ptr<CAnimation>>& FindAnimations(const std::wstring& _wstrModelName);

	public:
		std::vector<std::shared_ptr<CBone>> CloneBone(const std::wstring& _wstrBoneName, const std::shared_ptr<CMeshBone> _spMeshBone);

		std::unordered_map<std::string, std::shared_ptr<CAnimation>> CloneAnimation(const std::wstring& _wstrAnimationName, const std::shared_ptr<CMeshBone> _spMeshBone);

	public:
		int32 GetNumVertice(EModelType _eModelType, const std::wstring& _wstrVertexBufferName) const;

		int32 GetNumIndices(const std::wstring& _wstrIndexBufferName) const;

		Vector3 GetAverageWorldPosition(EModelType _eModelType, const std::wstring& _wstrVertexBufferName) const;

	public:
		void IASetVertexBuffers(UINT _iStartSlot, UINT _iNumBuffers, ID3D11Buffer* const* _ppVertexBuffers, const UINT* _pStrides, const UINT* _pOffsets);

		void IASetIndexBuffer(ID3D11Buffer* _pIndexBuffer, DXGI_FORMAT _tFormat, UINT _iOffset);

		void IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY _tPrimitiveTopology);

		void DrawIndexed(UINT _iIndexCount, UINT _iStartIndexLocation, UINT _iBaseVertexLocation);

		void VSSetShaderResources(UINT _iStartSlot, UINT _iNumViews, ID3D11ShaderResourceView* const* _ppShaderResourceViews);

		void PSSetShaderResources(UINT _iStartSlot, UINT _iNumViews, ID3D11ShaderResourceView* const* _ppShaderResourceViews);

	/********************
		Getter/Setter
	********************/
	public:
		shared_ptr<CDeviceManager> GetDeviceManager() const { return m_wpDeviceManager.expired() ? nullptr : m_wpDeviceManager.lock(); }

		const std::unordered_map<std::wstring, std::shared_ptr<FModelDesc>>& GetModelDescs() const { return m_umapModelDescs; }

		const std::unordered_map<std::wstring, std::unordered_map<std::string, std::shared_ptr<CAnimation>>>& GetAnimations() const { return m_umapAnimations; }

	/********************
		Data Members
	********************/
	private:
		// 버텍스 버퍼들 L"Hyunwoo0", L"Hyunwoo1", ...
		std::unordered_map<std::wstring, ComPtr<ID3D11Buffer>> m_umapVertexBuffers;

		// 인덱스 버퍼들 L"Hyunwoo0", L"Hyunwoo1", ...
		std::unordered_map<std::wstring, ComPtr<ID3D11Buffer>> m_umapIndexBuffers;

		// 본 오프셋들 L"Hyunwoo0", L"Hyunwoo1", ...
		std::unordered_map<std::wstring, std::shared_ptr<CBoneOffset>> m_umapBoneOffsets;

		// 셰이더 리소스 뷰들 L"Hyunwoo0_0", L"Hyunwoo0_1", ...
		std::unordered_map<std::wstring, ComPtr<ID3D11ShaderResourceView>> m_umapShaderResourceViews;

		// 본들 L"Hyunwoo"
		std::unordered_map<std::wstring, std::vector<std::shared_ptr<CBone>>> m_umapBones;

		// 애니메이션들 L"Hyunwoo"
		std::unordered_map<std::wstring, std::unordered_map<std::string, std::shared_ptr<CAnimation>>> m_umapAnimations;

	private:
		// 모델 문맥들
		std::unordered_map<std::wstring, std::shared_ptr<FModelDesc>> m_umapModelDescs;

	private:
		std::weak_ptr<CDeviceManager> m_wpDeviceManager;

		std::shared_ptr<CModelLoader> m_spModelLoader = nullptr;
	};
}
