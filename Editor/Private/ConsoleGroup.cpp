#include "pch.h"
#include "ConsoleGroup.h"

#include "StaticMeshComponent.h"

HRESULT Editor::CConsoleGroup::PreInitialize()
{
	m_wpStaticMeshComponent = CreateActorComponent<CStaticMeshComponent>(L"StaticMeshComponent", EComponentType::STATIC_MESH);
	SetRootComponent(m_wpStaticMeshComponent.lock());

	return CActor::PreInitialize();
}

HRESULT Editor::CConsoleGroup::Initialize()
{
	switch (m_eConsoleType)
	{
	case Editor::EConsoleType::HYPERLOOP:		m_wpStaticMeshComponent.lock()->SetModelDesc(L"HyperloopSpawnPoint");		break;
	case Editor::EConsoleType::SECURITY_CONSOLE:m_wpStaticMeshComponent.lock()->SetModelDesc(L"SecurityConsoleSpawnPoint");	break;
	case Editor::EConsoleType::SECURITY_CAMERA:	m_wpStaticMeshComponent.lock()->SetModelDesc(L"SecurityCameraSpawnPoint");	break;
	case Editor::EConsoleType::ENUM_END:		break;
	default:									break;
	}

	m_wpStaticMeshComponent.lock()->SetVertexShaderDesc(L"VS_StaticMesh");
	m_wpStaticMeshComponent.lock()->SetPixelShaderDesc(L"PS_StaticMesh");
	return CActor::Initialize();
}

HRESULT Editor::CConsoleGroup::PostInitialize()
{
	if (FAILED(CActor::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Editor::CConsoleGroup::BeginPlay()
{
	if (FAILED(CActor::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Editor::CConsoleGroup::PreTick(float _fDeltaSeconds)
{
	switch (CActor::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}
	return 0;
}

int32 Editor::CConsoleGroup::Tick(float _fDeltaSeconds)
{
	switch (CActor::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}
	return 0;
}

int32 Editor::CConsoleGroup::PostTick(float _fDeltaSeconds)
{
	switch (CActor::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}
	return 0;
}

HRESULT Editor::CConsoleGroup::EndPlay()
{
	if (FAILED(CActor::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Editor::CConsoleGroup::Render()
{
	return CActor::Render();
}

void Editor::CConsoleGroup::Release()
{
	return CActor::Release();
}

void Editor::CConsoleGroup::AddConsole(const shared_ptr<CConsole>& _spConsole)
{
	m_vecConsoles.push_back(_spConsole);
}
