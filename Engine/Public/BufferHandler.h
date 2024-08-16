#pragma once

namespace Engine
{
	class CDeviceManager;
	class CBufferLoader;

	class CBufferHandler
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		DECLARE_SINGLETON(CBufferHandler)
		
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
		void AddVertexBuffer(const std::wstring& _wstrVertexBufferName, const ComPtr<ID3D11Buffer>& _cpVertexBuffer);

		void AddIndexBuffer(const std::wstring& _wstrIndexBufferName, const ComPtr<ID3D11Buffer>& _cpIndexBuffer);

		ComPtr<ID3D11Buffer> FindVertexBuffer(const std::wstring& _wstrVertexBufferName);

		ComPtr<ID3D11Buffer> FindIndexBuffer(const std::wstring& _wstrIndexBufferName);

		void AddInstanceVertexBuffer(const std::wstring& _wstrInstanceVertexBufferName, const ComPtr<ID3D11Buffer>& _cpVertexBuffer);

		void AddInstanceIndexBuffer(const std::wstring& _wstrInstanceIndexBufferName, const ComPtr<ID3D11Buffer>& _cpIndexBuffer);

		void AddInstanceTransformBuffer(const std::wstring& _wstrInstanceTransformBufferName, const ComPtr<ID3D11Buffer>& _cpTransformBuffer);

		ComPtr<ID3D11Buffer> FindInstanceVertexBuffer(const std::wstring& _wstrInstanceVertexBufferName);

		ComPtr<ID3D11Buffer> FindInstanceIndexBuffer(const std::wstring& _wstrInstanceIndexBufferName);

		ComPtr<ID3D11Buffer> FindInstanceTransformBuffer(const std::wstring& _wstrInstanceTransformBufferName);

	public:
		void IASetVertexBuffers(UINT _iStartSlot, UINT _iNumBuffers, ID3D11Buffer* const* _ppVertexBuffers, const UINT* _pStrides, const UINT* _pOffsets);

		void IASetIndexBuffer(ID3D11Buffer* _pIndexBuffer, DXGI_FORMAT _tFormat, UINT _iOffset);

		void IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY _tPrimitiveTopology);

		void DrawIndexed(UINT _iIndexCount, UINT _iStartIndexLocation, UINT _iBaseVertexLocation);
		
		void Draw(UINT _iVertexCount, UINT _iStartVertexLocation);

		void DrawIndexedInstanced(UINT _iIndexCountPerInstance, UINT _iInstanceCount, UINT _iStartIndexLocation, UINT _iBaseVertexLocation, UINT _iStartInstanceLocation);

	public:
		HRESULT LoadInstanceIndex(const std::wstring& _wstrInstanceIndexDataName, int32 _iNumInstances);

		HRESULT CreateInstanceIndexBuffer(const std::wstring& _wstrInstanceIndexDataName);

		HRESULT LoadInstanceTransform(const std::wstring& _wstrInstanceTransformDataName, int32 _iNumInstances);

		HRESULT CreateInstanceTransformBuffer(const std::wstring& _wstrInstanceTransformDataName);

	/********************
		Getter/Setter
	********************/
	public:
		shared_ptr<CDeviceManager> GetDeviceManager() const { return m_wpDeviceManager.expired() ? nullptr : m_wpDeviceManager.lock(); }

	/********************
		Data Members
	********************/
	private:
		// 버텍스 버퍼들
		std::unordered_map<std::wstring, ComPtr<ID3D11Buffer>> m_umapVertexBuffers;

		// 인덱스 버퍼들
		std::unordered_map<std::wstring, ComPtr<ID3D11Buffer>> m_umapIndexBuffers;

		// 인스턴스 버텍스 버퍼들
		std::unordered_map<std::wstring, ComPtr<ID3D11Buffer>> m_umapInstanceVertexBuffers;

		// 인스턴스 인덱스 버퍼들
		std::unordered_map<std::wstring, ComPtr<ID3D11Buffer>> m_umapInstanceIndexBuffers;

		// 인스턴스 트랜스폼 버퍼들
		std::unordered_map<std::wstring, ComPtr<ID3D11Buffer>> m_umapInstanceTranformBuffers;

	private:
		std::weak_ptr<CDeviceManager> m_wpDeviceManager;

		std::shared_ptr<CBufferLoader> m_spBufferLoader = nullptr;
	};
}
