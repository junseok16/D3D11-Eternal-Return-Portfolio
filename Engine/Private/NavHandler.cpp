#include "pch.h"
#include "NavHandler.h"

#include "NavLoader.h"
#include "Cell.h"

IMPLEMENT_SINGLETON(CNavHandler)

HRESULT Engine::CNavHandler::Initialize(const std::shared_ptr<CDeviceManager>& _spDeviceManager)
{
	m_wpDeviceManager = _spDeviceManager;
	m_spNavLoader = CNavLoader::Create();
	return S_OK;
}

void Engine::CNavHandler::Release()
{
	for (auto& pair : m_umapNavigations)
	{
		for (auto& spCell : pair.second)
		{
			spCell->Release();
			spCell = nullptr;
		}
		pair.second.clear();
	}
	m_umapNavigations.clear();

	for (auto& pair : m_umapVertexBuffers)
	{
		pair.second = nullptr;
	}
	m_umapVertexBuffers.clear();

	for (auto& pair : m_umapIndexBuffers)
	{
		pair.second = nullptr;
	}
	m_umapIndexBuffers.clear();

	m_spNavLoader->Release();
	m_spNavLoader = nullptr;

	m_spInstance.reset();
}

HRESULT Engine::CNavHandler::AddNavigation(const std::wstring& _wstrNavName, const std::vector<std::shared_ptr<CCell>>& _vecCells)
{
	if (m_umapNavigations.find(_wstrNavName) != m_umapNavigations.end()) { return E_FAIL; }

	m_umapNavigations.emplace(_wstrNavName, _vecCells);
	return S_OK;
}

const std::vector<std::shared_ptr<CCell>>& Engine::CNavHandler::FindNavigation(const std::wstring& _wstrNavName)
{
	return m_umapNavigations.at(_wstrNavName);
}
