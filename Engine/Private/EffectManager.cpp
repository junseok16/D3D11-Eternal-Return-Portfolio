#include "pch.h"
#include "EffectManager.h"

#include "EffectComponent.h"

HRESULT Engine::CEffectManager::PreInitialize()
{
    return S_OK;
}

HRESULT Engine::CEffectManager::Initialize()
{
    return S_OK;
}

void Engine::CEffectManager::Release()
{
}

void Engine::CEffectManager::Render()
{
	for (const auto& pair : m_umapEffectComponents)
	{
		pair.second.lock()->Render();
	}
}

HRESULT Engine::CEffectManager::AddEffectComponent(const std::wstring& _wstrEffectComponentName, const std::shared_ptr<CEffectComponent>& _spEffectComponent)
{
	if (m_umapEffectComponents.find(_wstrEffectComponentName) != m_umapEffectComponents.end()) { return E_FAIL; }

	m_umapEffectComponents.emplace(_wstrEffectComponentName, _spEffectComponent);
	return S_OK;
}

HRESULT Engine::CEffectManager::RemoveEffectComponent(const std::wstring& _wstrEffectComponentName)
{
	if (m_umapEffectComponents.find(_wstrEffectComponentName) == m_umapEffectComponents.end()) { return E_FAIL; }

	m_umapEffectComponents.erase(_wstrEffectComponentName);
	return S_OK;
}
