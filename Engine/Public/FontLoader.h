#pragma once

namespace Engine
{
	class CDeviceManager;
	class CFontHandler;

	class CFontLoader final
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CFontLoader() = default;

		virtual ~CFontLoader() = default;
		
	/********************
		Events
	********************/
	public:
		static std::shared_ptr<CFontLoader> Create();

		HRESULT Initialize();

		void Release();
		
	/********************
		Methods
	********************/
	public:
		HRESULT LoadFontFromFile();

	private:
		void LoadFont(const std::filesystem::directory_entry& _fsEntry);

	/********************
		Data Members
	********************/
	private:
		std::weak_ptr<CDeviceManager> m_wpDeviceManager;

		std::weak_ptr<CFontHandler> m_wpFontHandler;

		std::wstring m_wstrFontFilePath = L"../../Resource/Fonts/";
	};
}
