#pragma once

namespace Engine
{
	class CDeviceManager;
	class CFontLoader;
	class CFont;

	class ENGINE_DLL CFontHandler final
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		DECLARE_SINGLETON(CFontHandler)
		
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
		HRESULT AddFont(const std::wstring& _wstrFontName, const std::shared_ptr<CFont>& _spFont);

		const std::shared_ptr<CFont>& FindFont(const std::wstring& _wstrFontName);
		
	/********************
		Data Members
	********************/
	private:
		// ÆùÆ®µé
		std::unordered_map<std::wstring, std::shared_ptr<CFont>> m_umapFonts;

	private:
		std::weak_ptr<CDeviceManager> m_wpDeviceManager;

		std::shared_ptr<CFontLoader> m_spFontLoader = nullptr;
	};
}
