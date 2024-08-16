#include "pch.h"
#include "IMGUIManager.h"

#include "EngineModule.h"
#include "EditorModule.h"

#include "CameraManager.h"
#include "DeviceManager.h"

#include "EditorCamera.h"
#include "DetailWindow.h"
#include "ModeWindow.h"
#include "TabWindow.h"
#include "EffectWindow.h"

HRESULT Editor::CIMGUIManager::PreInitialize(const std::shared_ptr<CEngineModule>& _spEngineModule)
{
	m_wpEngineModule = _spEngineModule;
	m_wpDeviceManager = _spEngineModule->GetDeviceManager();
	m_wpCameraManager = _spEngineModule->GetCameraManager();
	m_wpInputManager = _spEngineModule->GetInputManager();
	return S_OK;
}

HRESULT Editor::CIMGUIManager::Initialize()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	// io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	ImGui::StyleColorsDark();

	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	if (!ImGui_ImplWin32_Init(g_hWnd)) { return E_FAIL; }

	if (!ImGui_ImplDX11_Init(m_wpDeviceManager.lock()->GetDevice().Get(), m_wpDeviceManager.lock()->GetDeviceContext().Get())) { return E_FAIL; }
	return S_OK;
}

HRESULT Editor::CIMGUIManager::PostInitialize()
{
	m_spEditorCamera = CEditorCamera::Create(m_wpEngineModule.lock());
	m_spDetailWindow = CDetailWindow::Create(static_pointer_cast<CIMGUIManager>(shared_from_this()));
	// m_spModeWindow = CModeWindow::Create(static_pointer_cast<CIMGUIManager>(shared_from_this()));
	m_spTabWindow = CTabWindow::Create(static_pointer_cast<CIMGUIManager>(shared_from_this()));
	m_spEffectWindow = CEffectWindow::Create(static_pointer_cast<CIMGUIManager>(shared_from_this()));
	return S_OK;
}

int32 Editor::CIMGUIManager::PreTick()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	return 0;
}

int32 Editor::CIMGUIManager::Tick(float _fDeltaSeconds)
{
	// 에디터 모드일 때만 카메라를 업데이트합니다.
	if (m_eEditorState == EEditorState::EDIT)
	{
		m_spEditorCamera->Tick(_fDeltaSeconds);
	}

	m_spDetailWindow->Tick();
	// m_spModeWindow->Tick();
	m_spTabWindow->Tick();
	m_spEffectWindow->Tick();
	return 0;
}

int32 Editor::CIMGUIManager::PostTick()
{
	ImGui::Render();
	return 0;
}

void Editor::CIMGUIManager::Render()
{
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	
	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
	}
}

void Editor::CIMGUIManager::Release()
{
	m_spEffectWindow->Release();
	m_spDetailWindow->Release();
	// m_spModeWindow->Release();
	m_spTabWindow->Release();
	m_spEditorCamera->Release();

	m_spEffectWindow = nullptr;
	m_spDetailWindow = nullptr;
	// m_spModeWindow = nullptr;
	m_spTabWindow = nullptr;
	m_spEditorCamera = nullptr;

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}
