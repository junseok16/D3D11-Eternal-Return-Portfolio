#pragma once

namespace Engine
{
	class CDeviceManager;
	class CNavLoader;
	class CCell;

	class ENGINE_DLL CNavHandler final
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		DECLARE_SINGLETON(CNavHandler)
		
	/********************
		Events
	********************/
	public:
		HRESULT Initialize(const std::shared_ptr<CDeviceManager>& _spDeviceManager);

		void Release();
		
	/********************
		Getter/Setter
	********************/
	public:
		shared_ptr<CDeviceManager> GetDeviceManager() const { return m_wpDeviceManager.expired() ? nullptr : m_wpDeviceManager.lock(); }

	/********************
		Methods
	********************/
	public:
		HRESULT AddNavigation(const std::wstring& _wstrNavName, const std::vector<std::shared_ptr<CCell>>& _vecCells);

		const std::vector<std::shared_ptr<CCell>>& FindNavigation(const std::wstring& _wstrNavName);
		
	/********************
		Data Members
	********************/
	private:
		// ���ؽ� ���۵�
		std::unordered_map<std::wstring, ComPtr<ID3D11Buffer>> m_umapVertexBuffers;

		// �ε��� ���۵�
		std::unordered_map<std::wstring, ComPtr<ID3D11Buffer>> m_umapIndexBuffers;

		// �׺���̼ǵ�
		std::unordered_map<std::wstring, std::vector<std::shared_ptr<CCell>>> m_umapNavigations;

	private:
		std::weak_ptr<CDeviceManager> m_wpDeviceManager;

		std::shared_ptr<CNavLoader> m_spNavLoader = nullptr;
	};
}
