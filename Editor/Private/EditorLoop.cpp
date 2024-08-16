#include "pch.h"
#include "EditorLoop.h"

#include "EngineModule.h"
#include "EditorModule.h"

#include "World.h"
#include "EditorLevel.h"

HRESULT Editor::CEditorLoop::PreInitialize()
{
	m_spEngineModule = make_shared<CEngineModule>();
	m_spEditorModule = make_shared<CEditorModule>();

	m_spEngineModule->PreInitialize(g_hWnd, g_hInst, g_iWindowSizeX, g_iWindowSizeY);
	m_spEditorModule->PreInitialize(m_spEngineModule);
	return S_OK;
}

HRESULT Editor::CEditorLoop::Initialize()
{
	m_spEngineModule->Initialize();
	m_spEditorModule->Initialize();

	// 월드를 생성하고 초기화합니다.
	m_spWorld = CWorld::GetInstance();
	ENSUREF(m_spWorld->PreInitialize(make_shared<CEditorLevel>, m_spEngineModule), L"Failed to preinitialize World.");
	ENSUREF(m_spWorld->Initialize(), L"Failed to initialize World.");
	ENSUREF(m_spWorld->PostInitialize(), L"Failed to postinitialize World.");
	return S_OK;
}

HRESULT Editor::CEditorLoop::PostInitialize()
{
	ENSUREF(m_spEngineModule->PostInitialize(), L"Failed to postinitialize engine module.");
	ENSUREF(m_spEditorModule->PostInitialize(), L"Failed to postinitialize editor module.");
	ENSUREF(m_spWorld->BeginPlay(), L"Failed to beginplay world.");
	return S_OK;
}

int32 Editor::CEditorLoop::Tick()
{
	float fDeltaSeconds = 0.0f;
	if (m_spEngineModule->PreTick(&fDeltaSeconds)) { return -1; }
	m_spEditorModule->PreTick();

	m_spEditorModule->Tick(fDeltaSeconds);
	m_spWorld->Tick(fDeltaSeconds);

	m_spEngineModule->Tick();
	m_spEngineModule->PostTick();
	m_spEditorModule->PostTick();
	return 0;
}

void Editor::CEditorLoop::Render()
{
	m_spEngineModule->PreRender();
	m_spEditorModule->Render();
	m_spEngineModule->PostRender();
}

void Editor::CEditorLoop::Release()
{
	m_spWorld->Release();
	m_spWorld = nullptr;

	m_spEngineModule->Release();
	m_spEditorModule->Release();
	
	m_spEngineModule = nullptr;
	m_spEditorModule = nullptr;
}
