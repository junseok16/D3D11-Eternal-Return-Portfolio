#include "pch.h"
#include "FontLoader.h"

#include "FontHandler.h"

#include "CustomFont.h"

std::shared_ptr<CFontLoader> Engine::CFontLoader::Create()
{
	const std::shared_ptr<CFontLoader> spLoader = make_shared<CFontLoader>();
	ENSUREF(spLoader->Initialize(), L"Failed to create font loader.");
	return spLoader;
}

HRESULT Engine::CFontLoader::Initialize()
{
	m_wpFontHandler = CFontHandler::GetInstance();
	m_wpDeviceManager = CFontHandler::GetInstance()->GetDeviceManager();

	// 외부에서 파일을 불러옵니다.
	LoadFontFromFile();
	return S_OK;
}

void Engine::CFontLoader::Release()
{
}

HRESULT Engine::CFontLoader::LoadFontFromFile()
{
	for (const std::filesystem::directory_entry& fsEntry : filesystem::recursive_directory_iterator(m_wstrFontFilePath))
	{
		// 파일이 아닌 경우
		if (!filesystem::is_regular_file(fsEntry)) { continue; }

		// spritefont 파일이 아닌 경우
		if (fsEntry.path().extension().generic_string() != ".spritefont" && fsEntry.path().extension().generic_string() != ".SPRITEFONT") { continue; }

		LoadFont(fsEntry);
	}
	return S_OK;
}

void Engine::CFontLoader::LoadFont(const std::filesystem::directory_entry& _fsEntry)
{
	// 파일의 이름을 구합니다.
	wstring wstrFileName = _fsEntry.path().stem().generic_wstring();
	wstring wstrFilePath = _fsEntry.path().generic_wstring();
	
	std::shared_ptr<CFont> spFont = CFont::Create(m_wpDeviceManager.lock(), wstrFilePath);
	m_wpFontHandler.lock()->AddFont(wstrFileName, spFont);
}
