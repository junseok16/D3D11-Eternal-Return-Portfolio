#include "pch.h"
#include "EditorModule.h"

#include "IMGUIManager.h"
#include "GameManager.h"

HRESULT Editor::CEditorModule::PreInitialize(const std::shared_ptr<CEngineModule>& _spEngineModule)
{
	m_spIMGUIManager = CManager::Create<CIMGUIManager>(shared_from_this());
	m_spGameManager = CGameManager::GetInstance();

	m_spIMGUIManager->PreInitialize(_spEngineModule);
	return S_OK;
}

HRESULT Editor::CEditorModule::Initialize()
{
	m_spIMGUIManager->Initialize();
	m_spGameManager->Initialize();
	return S_OK;
}

HRESULT Editor::CEditorModule::PostInitialize()
{
	m_spIMGUIManager->PostInitialize();
	m_spGameManager->PostInitialize();
	return S_OK;
}

int32 Editor::CEditorModule::PreTick()
{
	m_spIMGUIManager->PreTick();
	return 0;
}

int32 Editor::CEditorModule::Tick(float _fDeltaSeconds)
{
	m_spIMGUIManager->Tick(_fDeltaSeconds);
	m_spGameManager->Tick(_fDeltaSeconds);
	return 0;
}

int32 Editor::CEditorModule::PostTick()
{
	m_spIMGUIManager->PostTick();
	return 0;
}

void Editor::CEditorModule::Render()
{
	m_spIMGUIManager->Render();
}

void Editor::CEditorModule::Release()
{
	m_spIMGUIManager->Release();
	m_spGameManager->Release();

	m_spGameManager.reset();
}
