#pragma once

namespace Engine
{
	class CDeviceManager;
	class CNavHandler;

	class CNavLoader final
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CNavLoader() = default;

		virtual ~CNavLoader() = default;
		
	/********************
		Events
	********************/
	public:
		static std::shared_ptr<CNavLoader> Create();

		HRESULT Initialize();

		void Release();
		
	/********************
		Methods
	********************/
	public:
		HRESULT LoadNavigationFromFile();

		void LoadCell(std::ifstream& _inFile, const std::filesystem::directory_entry& _fsEntry);

	/********************
		Data Members
	********************/
	private:
		std::weak_ptr<CDeviceManager> m_wpDeviceManager;

		std::weak_ptr<CNavHandler> m_wpNavHandler;

		std::wstring m_wstrNavigationFilePath = L"../../Resource/Navigations/Lumia/";
	};
}
