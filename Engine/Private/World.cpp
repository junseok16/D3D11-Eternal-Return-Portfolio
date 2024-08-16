#include "pch.h"
#include "World.h"

#include "Level.h"
#include "Actor.h"
#include "UI.h"

IMPLEMENT_SINGLETON(CWorld)

HRESULT Engine::CWorld::PreInitialize(std::function<std::shared_ptr<CLevel>()> _fnLevelFactory, const std::shared_ptr<CEngineModule>& _spEngineModule)
{
	m_wpEngineModule = _spEngineModule;
	m_wpCurLevel = CreateLevel(_fnLevelFactory);
	return S_OK;
}

HRESULT Engine::CWorld::Initialize()
{
	// 레벨에 있는 액터를 생성한다.
	CHECK(!m_wpCurLevel.expired());
	if (FAILED(m_wpCurLevel.lock()->PreInitialize())) { return E_FAIL; }

	// 레벨에 있는 액터를 초기화한다.
	CHECK(!m_wpCurLevel.expired());
	if (FAILED(m_wpCurLevel.lock()->Initialize())) { return E_FAIL; }

	CHECK(!m_wpCurLevel.expired());
	if (FAILED(m_wpCurLevel.lock()->PostInitialize())) { return E_FAIL; }
	return S_OK;
}

HRESULT Engine::CWorld::PostInitialize()
{
	return S_OK;
}

HRESULT Engine::CWorld::BeginPlay()
{
	for (const auto& spActor : m_umapActors)
	{
		if (FAILED(spActor.second->BeginPlay())) { return E_FAIL; }
	}

	for (const auto& spUI : m_umapUIs)
	{
		if (FAILED(spUI.second->BeginPlay())) { return E_FAIL; }
	}

	m_vecUIs.shrink_to_fit();
	sort(m_vecUIs.begin(), m_vecUIs.end(), [](const std::shared_ptr<CUI>& _spFirst, const std::shared_ptr<CUI>& _spSecond) { return _spFirst->GetPriority() > _spSecond->GetPriority(); });
	return S_OK;
}

HRESULT Engine::CWorld::Tick(float _fDeltaSeconds)
{
	m_fCurDeltaSeconds = _fDeltaSeconds;

	for (const auto& spActor : m_umapActors)
	{
		if (FAILED(spActor.second->PreTick(_fDeltaSeconds))) { return E_FAIL; }
	}

	for (const auto& spUI : m_umapUIs)
	{
		if (FAILED(spUI.second->PreTick(_fDeltaSeconds))) { return E_FAIL; }
	}

	for (const auto& spActor : m_umapActors)
	{
		if (FAILED(spActor.second->Tick(_fDeltaSeconds))) { return E_FAIL; }
	}

	for (const auto& spUI : m_umapUIs)
	{
		if (FAILED(spUI.second->Tick(_fDeltaSeconds))) { return E_FAIL; }
	}

	for (const auto& spActor : m_umapActors)
	{
		if (FAILED(spActor.second->PostTick(_fDeltaSeconds))) { return E_FAIL; }
	}

	for (const auto& spUI : m_umapUIs)
	{
		if (FAILED(spUI.second->PostTick(_fDeltaSeconds))) { return E_FAIL; }
	}

	return S_OK;
}

HRESULT Engine::CWorld::EndPlay()
{
	for (const auto& spActor : m_umapActors)
	{
		if (FAILED(spActor.second->EndPlay())) { return E_FAIL; }
	}

	for (const auto& spUI : m_umapUIs)
	{
		if (FAILED(spUI.second->EndPlay())) { return E_FAIL; }
	}
	return S_OK;
}

void Engine::CWorld::Release()
{
	for (auto& spActor : m_umapActors)
	{
		spActor.second->Release();
		spActor.second = nullptr;
	}
	m_umapActors.clear();

	for (auto& spUI : m_vecUIs)
	{
		spUI = nullptr;
	}
	m_vecUIs.clear();

	for (auto& spUI : m_umapUIs)
	{
		spUI.second->Release();
		spUI.second = nullptr;
	}
	m_umapUIs.clear();

	for (auto& spLayer : m_umapLayers)
	{
		spLayer.second = nullptr;
	}
	m_umapLayers.clear();

	for (auto& spLevel : m_umapLevels)
	{
		spLevel.second = nullptr;
	}
	m_umapLevels.clear();

	// 싱글턴 월드를 메모리에서 해제합니다.
	m_spInstance = nullptr;
}

std::shared_ptr<CLevel> Engine::CWorld::GetCurLevel() const
{
	return m_wpCurLevel.expired() ? nullptr : m_wpCurLevel.lock();
}

std::shared_ptr<CLevel> Engine::CWorld::GetLevel(const std::wstring& _wstrLevelName) const
{
	return std::shared_ptr<CLevel>();
}

std::shared_ptr<CActor> Engine::CWorld::GetActor(const std::wstring& _wstrActorName) const
{
	return std::shared_ptr<CActor>();
}

std::shared_ptr<CLevel> Engine::CWorld::CreateLevel(function<shared_ptr<CLevel>()> _fnLevel)
{
	shared_ptr<CLevel> spLevel = _fnLevel();
	const char* szLevelName = typeid(*spLevel).name();
	wstring wstrLevelName(&szLevelName[0], &szLevelName[strlen(szLevelName)]);

	spLevel->SetOwnerWorld(static_pointer_cast<CWorld>(shared_from_this()));
	spLevel->SetLevelName(wstrLevelName);
	AddLevelToWorld(wstrLevelName, spLevel);
	return spLevel;
}

void Engine::CWorld::AddActorToWorld(const std::wstring& _wstrActorName, std::shared_ptr<CActor> _spActor)
{
	m_umapActors.emplace(_wstrActorName, _spActor);
}

void Engine::CWorld::AddUIToWorld(const std::wstring& _wstrUIName, std::shared_ptr<CUI> _spUI)
{
	m_umapUIs.emplace(_wstrUIName, _spUI);
	m_vecUIs.emplace_back(_spUI);
}

void Engine::CWorld::AddLevelToWorld(const wstring& _wstrLevelName, std::shared_ptr<CLevel> _spLevel)
{
	m_umapLevels.emplace(_wstrLevelName, _spLevel);
}
