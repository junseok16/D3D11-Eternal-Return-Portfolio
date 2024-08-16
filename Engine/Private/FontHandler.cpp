#include "pch.h"
#include "FontHandler.h"

#include "FontLoader.h"
#include "CustomFont.h"

IMPLEMENT_SINGLETON(CFontHandler)

HRESULT Engine::CFontHandler::Initialize(const std::shared_ptr<CDeviceManager>& _spDeviceManager)
{
	m_wpDeviceManager = _spDeviceManager;
	m_spFontLoader = CFontLoader::Create();
	return S_OK;
}

void Engine::CFontHandler::Release()
{
	for (auto& pair : m_umapFonts)
	{
		pair.second->Release();
		pair.second = nullptr;
	}
	m_umapFonts.clear();

	m_spFontLoader->Release();
	m_spFontLoader = nullptr;

	m_spInstance.reset();
}

HRESULT Engine::CFontHandler::AddFont(const std::wstring& _wstrFontName, const std::shared_ptr<CFont>& _spFont)
{
	if (m_umapFonts.find(_wstrFontName) != m_umapFonts.end()) { return E_FAIL; }

	m_umapFonts.emplace(_wstrFontName, _spFont);
	return S_OK;
}

const std::shared_ptr<CFont>& Engine::CFontHandler::FindFont(const std::wstring& _wstrFontName)
{
	return m_umapFonts.at(_wstrFontName);
}
