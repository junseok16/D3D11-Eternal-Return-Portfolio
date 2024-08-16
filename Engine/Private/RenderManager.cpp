// default
#include "pch.h"
#include "RenderManager.h"

// manager
#include "DeviceManager.h"
#include "PostProcessManager.h"
#include "EffectManager.h"
#include "GraphicsPipelineManager.h"

// module
#include "EngineModule.h"

// engine
#include "World.h"
#include "Actor.h"
#include "UI.h"

#include "StateHandler.h"
#include "ViewHandler.h"

HRESULT Engine::CRenderManager::PreInitialize()
{
	return S_OK;
}

HRESULT Engine::CRenderManager::Initialize()
{
	m_wpDeviceManager			= m_wpEngineModule.lock()->GetDeviceManager();
	m_wpPostProcessManager		= m_wpEngineModule.lock()->GetPostProcessManager();
	m_wpEffectManager			= m_wpEngineModule.lock()->GetEffectManager();
	m_wpGraphicsPipelineManager = CGraphicsPipelineManager::GetInstance();

	m_wpViewHandler = CViewHandler::GetInstance();
	return S_OK;
}

int32 Engine::CRenderManager::Tick()
{
	// 월드가 갖고 있는 모든 액터들을 렌더러에 추가합니다.
	const std::unordered_map<std::wstring, std::shared_ptr<CActor>>& umapActors = CWorld::GetInstance()->GetActors();

	for (const auto& pair : umapActors)
	{
		switch (pair.second->GetActorRenderType())
		{
		case ERenderType::PRE_RENDER:
			m_arrActors[(uint8)ERenderType::PRE_RENDER].push_back(pair.second);
			break;

		case ERenderType::OPAQUE_OBJECT:
			m_arrActors[(uint8)ERenderType::OPAQUE_OBJECT].push_back(pair.second);
			break;

		case ERenderType::PARTICLE_OBJECT:
			m_arrActors[(uint8)ERenderType::PARTICLE_OBJECT].push_back(pair.second);
			break;

		case ERenderType::TRANSLUCENT_OBJECT:
			m_arrActors[(uint8)ERenderType::TRANSLUCENT_OBJECT].push_back(pair.second);
			break;

		case ERenderType::OPAQUE_USER_INTERFACE:
			m_arrActors[(uint8)ERenderType::OPAQUE_USER_INTERFACE].push_back(pair.second);
			break;

		case ERenderType::TRANSLUCENT_USER_INTERFACE:
			m_arrActors[(uint8)ERenderType::TRANSLUCENT_USER_INTERFACE].push_back(pair.second);
			break;

		case ERenderType::POST_RENDER:
			m_arrActors[(uint8)ERenderType::POST_RENDER].push_back(pair.second);
			break;

		case ERenderType::NOT_RENDER:
		case ERenderType::ENUM_END:
			break;
		}
	}

	const std::vector<std::shared_ptr<CUI>>& vecUIs = CWorld::GetInstance()->GetUIs();
	
	for (const auto& spUI : vecUIs)
	{
		switch (spUI->GetActorRenderType())
		{
		case ERenderType::PRE_RENDER:
			m_arrActors[(uint8)ERenderType::PRE_RENDER].push_back(spUI);
			break;

		case ERenderType::OPAQUE_OBJECT:
			m_arrActors[(uint8)ERenderType::OPAQUE_OBJECT].push_back(spUI);
			break;

		case ERenderType::PARTICLE_OBJECT:
			m_arrActors[(uint8)ERenderType::PARTICLE_OBJECT].push_back(spUI);
			break;

		case ERenderType::TRANSLUCENT_OBJECT:
			m_arrActors[(uint8)ERenderType::TRANSLUCENT_OBJECT].push_back(spUI);
			break;

		case ERenderType::OPAQUE_USER_INTERFACE:
			m_arrActors[(uint8)ERenderType::OPAQUE_USER_INTERFACE].push_back(spUI);
			break;

		case ERenderType::TRANSLUCENT_USER_INTERFACE:
			m_arrActors[(uint8)ERenderType::TRANSLUCENT_USER_INTERFACE].push_back(spUI);
			break;

		case ERenderType::POST_RENDER:
			m_arrActors[(uint8)ERenderType::POST_RENDER].push_back(spUI);
			break;

		case ERenderType::NOT_RENDER:
		case ERenderType::ENUM_END:
			break;
		}
	}

	return 0;
}

void Engine::CRenderManager::Render()
{
	PreRender();

	// RenderShadow();

	// 오브젝트 전처리
	RenderOpaqueObject();

	// 오브젝트 후처리
	RenderLight();
	RenderPostProcess();

	// 빛을 연산하지 않는 객체들
	RenderParticle();

	RenderTranslucentObject();

	// 사용자 인터페이스
	RenderOpaqueUserInterface();

	RenderTranslucentUserInterface();

	PostRender();

	// RenderDebug();
}

void Engine::CRenderManager::Release()
{
	// 렌더할 액터들을 널포인터로 초기화하여 레퍼런스 카운트를 감소시킵니다.
	for (size_t iIndex = 0; iIndex < (uint8)ERenderType::ENUM_END; ++iIndex)
	{
		for (auto& spActor : m_arrActors[iIndex]) { spActor = nullptr; }
		m_arrActors[iIndex].clear();
	}

	// 렌더할 사용자 인터페이스들을 널포인터로 초기화하여 레퍼런스 카운트를 감소시킵니다.
	for (size_t iIndex = 0; iIndex < (uint8)ERenderType::ENUM_END; ++iIndex)
	{
		for (auto& spUI : m_arrUIs[iIndex]) { spUI = nullptr; }
		m_arrUIs[iIndex].clear();
	}
}

HRESULT Engine::CRenderManager::AddActorToRenderer(std::shared_ptr<CActor> _spActor, ERenderType _eRenderType)
{
	m_arrActors[static_cast<uint8>(_eRenderType)].push_back(_spActor);
	return S_OK;
}

HRESULT Engine::CRenderManager::RemoveActorFromRenderer(std::shared_ptr<CActor> _spActor, ERenderType _eRenderType)
{
	return S_OK;
}

void Engine::CRenderManager::PreRender()
{
	m_wpGraphicsPipelineManager.lock()->BeginRenderState(ERenderType::PRE_RENDER);

	for (auto& spActor : m_arrActors[(uint8)ERenderType::PRE_RENDER])
	{
		if (spActor != nullptr) { spActor->Render(); }
		spActor = nullptr;
	}
	m_arrActors[(uint8)ERenderType::PRE_RENDER].clear();

	m_wpGraphicsPipelineManager.lock()->EndRenderState();
}

void Engine::CRenderManager::RenderShadow()
{
	{
		D3D11_VIEWPORT tViewPortDesc;
		ZeroMemory(&tViewPortDesc, sizeof(tViewPortDesc));
		tViewPortDesc.TopLeftX = 0;
		tViewPortDesc.TopLeftY = 0;
		tViewPortDesc.Width = 8192.0f;
		tViewPortDesc.Height = 4608.0f;
		tViewPortDesc.MinDepth = 0.0f;
		tViewPortDesc.MaxDepth = 1.0f;
		m_wpDeviceManager.lock()->GetDeviceContext()->RSSetViewports(1, &tViewPortDesc);
	}

	m_wpGraphicsPipelineManager.lock()->BeginRenderState(ERenderType::SHADOW);

	{
		ComPtr<ID3D11DepthStencilView> cpDSV = m_wpViewHandler.lock()->FindDepthStencilView(L"DSV_SHADOW");
		m_wpViewHandler.lock()->BeginViewGroup(L"VG_SHADOW", cpDSV);

		for (auto& spActor : m_arrActors[(uint8)ERenderType::OPAQUE_OBJECT])
		{
			if (nullptr != spActor)
			{
				spActor->RenderShadow();
			}
		}

		m_wpViewHandler.lock()->EndViewGroup();
	}

	m_wpGraphicsPipelineManager.lock()->EndRenderState();

	{
		D3D11_VIEWPORT tViewPortDesc;
		ZeroMemory(&tViewPortDesc, sizeof(tViewPortDesc));
		tViewPortDesc.TopLeftX = 0;
		tViewPortDesc.TopLeftY = 0;
		tViewPortDesc.Width = 1280.0f;
		tViewPortDesc.Height = 720.0f;
		tViewPortDesc.MinDepth = 0.0f;
		tViewPortDesc.MaxDepth = 1.0f;
		m_wpDeviceManager.lock()->GetDeviceContext()->RSSetViewports(1, &tViewPortDesc);
	}
}

void Engine::CRenderManager::RenderOpaqueObject()
{
	m_wpViewHandler.lock()->BeginViewGroup(L"VG_OPAQUE_OBJECT");

	for (auto& spActor : m_arrActors[(uint8)ERenderType::OPAQUE_OBJECT])
	{
		if (spActor != nullptr) { spActor->Render(); }
		spActor = nullptr;
	}
	m_arrActors[(uint8)ERenderType::OPAQUE_OBJECT].clear();

	m_wpViewHandler.lock()->EndViewGroup();
}

void Engine::CRenderManager::RenderLight()
{
	m_wpPostProcessManager.lock()->BeginViewGroup(L"VG_LIGHT");

	m_wpGraphicsPipelineManager.lock()->BeginRenderState(ERenderType::LIGHT);

	m_wpPostProcessManager.lock()->RenderLight();

	m_wpGraphicsPipelineManager.lock()->EndRenderState();

	m_wpPostProcessManager.lock()->EndViewGroup();
}

void Engine::CRenderManager::RenderPostProcess()
{
	m_wpGraphicsPipelineManager.lock()->BeginRenderState(ERenderType::POST_PROCESS);

	m_wpPostProcessManager.lock()->RenderPostProcess();

	m_wpGraphicsPipelineManager.lock()->EndRenderState();
}

void Engine::CRenderManager::RenderParticle()
{
	m_wpGraphicsPipelineManager.lock()->BeginRenderState(ERenderType::EFFECT);

	m_wpEffectManager.lock()->Render();

	m_wpGraphicsPipelineManager.lock()->EndRenderState();

	for (auto& spActor : m_arrActors[(uint8)ERenderType::PARTICLE_OBJECT])
	{
		if (spActor != nullptr) { spActor->Render(); }
		spActor = nullptr;
	}
	m_arrActors[(uint8)ERenderType::PARTICLE_OBJECT].clear();
}

void Engine::CRenderManager::RenderTranslucentObject()
{
	m_wpGraphicsPipelineManager.lock()->BeginRenderState(ERenderType::TRANSLUCENT_OBJECT);

	for (auto& spActor : m_arrActors[(uint8)ERenderType::TRANSLUCENT_OBJECT])
	{
		if (spActor != nullptr) { spActor->Render(); }
		spActor = nullptr;
	}
	m_arrActors[(uint8)ERenderType::TRANSLUCENT_OBJECT].clear();

	m_wpGraphicsPipelineManager.lock()->EndRenderState();
}

void Engine::CRenderManager::RenderOpaqueUserInterface()
{
	for (auto& spActor : m_arrActors[(uint8)ERenderType::OPAQUE_USER_INTERFACE])
	{
		if (spActor != nullptr) { spActor->Render(); }
		spActor = nullptr;
	}
	m_arrActors[(uint8)ERenderType::OPAQUE_USER_INTERFACE].clear();
}

void Engine::CRenderManager::RenderTranslucentUserInterface()
{
	m_wpGraphicsPipelineManager.lock()->BeginRenderState(ERenderType::TRANSLUCENT_USER_INTERFACE);

	for (auto& spActor : m_arrActors[(uint8)ERenderType::TRANSLUCENT_USER_INTERFACE])
	{
		if (spActor != nullptr) { spActor->Render(); }
		spActor = nullptr;
	}
	m_arrActors[(uint8)ERenderType::TRANSLUCENT_USER_INTERFACE].clear();

	m_wpGraphicsPipelineManager.lock()->EndRenderState();
}

void Engine::CRenderManager::PostRender()
{
	for (auto& spActor : m_arrActors[(uint8)ERenderType::POST_RENDER])
	{
		if (spActor != nullptr) { spActor->Render(); }
		spActor = nullptr;
	}
	m_arrActors[(uint8)ERenderType::PRE_RENDER].clear();
}

void Engine::CRenderManager::RenderDebug()
{
	m_wpPostProcessManager.lock()->RenderDebug();
}
