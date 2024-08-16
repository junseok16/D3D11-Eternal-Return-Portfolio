#include "pch.h"
#include "ClientLoop.h"

#include "EngineModule.h"
#include "ClientModule.h"

#include "World.h"
#include "ClientLevel.h"

HRESULT Client::CClientLoop::PreInitialize()
{
	m_spEngineModule = make_shared<CEngineModule>();
	m_spClientModule = make_shared<CClientModule>();

	m_spEngineModule->PreInitialize(g_hWnd, g_hInst, g_iWindowSizeX, g_iWindowSizeY);
	m_spClientModule->PreInitialize(m_spEngineModule);
	return S_OK;
}

HRESULT Client::CClientLoop::Initialize()
{
	ENSUREF(m_spEngineModule->Initialize(), L"Failed to preinitialize engine module.");
	ENSUREF(m_spClientModule->Initialize(), L"Failed to preinitialize client module.");

	// 월드를 생성하고 초기화합니다.
	m_spWorld = CWorld::GetInstance();
	ENSUREF(m_spWorld->PreInitialize(make_shared<CClientLevel> , m_spEngineModule), L"Failed to preinitialize World.");
	ENSUREF(m_spWorld->Initialize(), L"Failed to initialize World.");
	ENSUREF(m_spWorld->PostInitialize(), L"Failed to postinitialize World.");
	return S_OK;
}

HRESULT Client::CClientLoop::PostInitialize()
{
	ENSUREF(m_spEngineModule->PostInitialize(), L"Failed to postinitialize engine module.");
	ENSUREF(m_spClientModule->PostInitialize(), L"Failed to postinitialize client module.");
	ENSUREF(m_spWorld->BeginPlay(), L"Failed to beginplay world.");
	return S_OK;
}

int32 Client::CClientLoop::Tick()
{
	float fDeltaSeconds = 0.0f;
	if (m_spEngineModule->PreTick(&fDeltaSeconds)) { return -1; }
	m_spClientModule->PreTick();

	if (0.1f <= fDeltaSeconds) { fDeltaSeconds = 0.1f; }

	m_spClientModule->Tick(fDeltaSeconds);
	m_spWorld->Tick(fDeltaSeconds);

	m_spEngineModule->Tick();
	m_spEngineModule->PostTick();
	m_spClientModule->PostTick();
	return 0;
}

void Client::CClientLoop::Render()
{
	m_spEngineModule->PreRender();
	m_spClientModule->Render();
	m_spEngineModule->PostRender();
}

void Client::CClientLoop::Release()
{
	m_spWorld->Release();
	m_spWorld = nullptr;

	m_spEngineModule->Release();
	m_spClientModule->Release();

	m_spEngineModule = nullptr;
	m_spClientModule = nullptr;
}
