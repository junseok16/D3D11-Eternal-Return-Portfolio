#include "pch.h"
#include "ClientModule.h"

#include "GameManager.h"
#include "UIManager.h"

HRESULT Client::CClientModule::PreInitialize(const std::shared_ptr<CEngineModule>& _spEngineModule)
{
	m_spGameManager = CGameManager::GetInstance();
	m_spUIManager = CUIManager::GetInstance();
	return S_OK;
}

HRESULT Client::CClientModule::Initialize()
{
	m_spGameManager->Initialize();
	m_spUIManager->Initialize();
	return S_OK;
}

HRESULT Client::CClientModule::PostInitialize()
{
	m_spGameManager->PostInitialize();
	return S_OK;
}

int32 Client::CClientModule::PreTick()
{
	return 0;
}

int32 Client::CClientModule::Tick(float _fDeltaSeconds)
{
	m_spGameManager->Tick(_fDeltaSeconds);
	return 0;
}

int32 Client::CClientModule::PostTick()
{
	return 0;
}

void Client::CClientModule::Render()
{
}

void Client::CClientModule::Release()
{
	m_spGameManager->Release();
	m_spUIManager->Release();

	m_spGameManager = nullptr;
	m_spUIManager = nullptr;
}
