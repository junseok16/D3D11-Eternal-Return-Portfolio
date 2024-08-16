// default
#include "pch.h"
#include "Level.h"

// world
#include "World.h"
#include "Pawn.h"

// actor
#include "Actor.h"
#include "UI.h"

#include "Controller.h"

HRESULT Engine::CLevel::PreInitialize()
{
	// TODO: 레벨을 생성할 때 플레이어 컨트롤러가 중복되어 생성되지 않도록 해야 합니다.
	m_wpController = CreateActor<CController>(L"Controller");
	return S_OK;
}

HRESULT Engine::CLevel::Initialize()
{
	// 액터를 초기화합니다.
	for (const auto& spActor : m_umapActors)
	{
		if (FAILED(spActor.second.lock()->PreInitialize())) { return E_FAIL; }
	}

	m_wpController.lock()->Possess(FindActor<CPawn>(m_wstrPossessedPawnName));

	for (const auto& spActor : m_umapActors)
	{
		if (FAILED(spActor.second.lock()->Initialize())) { return E_FAIL; }
	}

	for (const auto& spActor : m_umapActors)
	{
		if (FAILED(spActor.second.lock()->PostInitialize())) { return E_FAIL; }
	}

	// 사용자 인터페이스를 초기화합니다.
	for (const auto& spUI : m_umapUIs)
	{
		if (FAILED(spUI.second.lock()->PreInitialize())) { return E_FAIL; }
	}

	for (const auto& spUI : m_umapUIs)
	{
		if (FAILED(spUI.second.lock()->Initialize())) { return E_FAIL; }
	}

	for (const auto& spUI : m_umapUIs)
	{
		if (FAILED(spUI.second.lock()->PostInitialize())) { return E_FAIL; }
	}
	return S_OK;
}

HRESULT Engine::CLevel::PostInitialize()
{
	return S_OK;
}

void Engine::CLevel::AddActorToWorld(const std::wstring& _wstrActorName, std::shared_ptr<CActor> _spActor)
{
	m_wpOwnerWorld.lock()->AddActorToWorld(_wstrActorName, _spActor);
	m_umapActors.emplace(_wstrActorName, _spActor);
}

void Engine::CLevel::AddUIToWorld(const std::wstring& _wstrUIName, std::shared_ptr<CUI> _spUI)
{
	m_wpOwnerWorld.lock()->AddUIToWorld(_wstrUIName, _spUI);
	m_umapUIs.emplace(_wstrUIName, _spUI);
}

std::shared_ptr<CWorld> Engine::CLevel::GetOwnerWorld() const
{
	return m_wpOwnerWorld.expired() ? nullptr : m_wpOwnerWorld.lock();
}