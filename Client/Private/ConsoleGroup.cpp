#include "pch.h"
#include "ConsoleGroup.h"

#include "StaticMeshComponent.h"

HRESULT Client::CConsoleGroup::PreInitialize()
{
	m_wpStaticMeshComponent = CreateActorComponent<CStaticMeshComponent>(L"StaticMeshComponent", EComponentType::STATIC_MESH);
	SetRootComponent(m_wpStaticMeshComponent.lock());

	return CActor::PreInitialize();
}

HRESULT Client::CConsoleGroup::Initialize()
{
	switch (m_eConsoleType)
	{
	case Client::EConsoleType::HYPERLOOP:		m_wpStaticMeshComponent.lock()->SetModelDesc(L"HyperloopSpawnPoint");		break;
	case Client::EConsoleType::SECURITY_CONSOLE:m_wpStaticMeshComponent.lock()->SetModelDesc(L"SecurityConsoleSpawnPoint");	break;
	case Client::EConsoleType::SECURITY_CAMERA:	m_wpStaticMeshComponent.lock()->SetModelDesc(L"SecurityCameraSpawnPoint");	break;
	case Client::EConsoleType::ENUM_END:		break;
	default:									break;
	}

	m_wpStaticMeshComponent.lock()->SetVertexShaderDesc(L"VS_StaticMesh");
	m_wpStaticMeshComponent.lock()->SetPixelShaderDesc(L"PS_StaticMesh");
	return CActor::Initialize();
}

HRESULT Client::CConsoleGroup::PostInitialize()
{
	if (FAILED(CActor::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CConsoleGroup::BeginPlay()
{
	if (FAILED(CActor::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Client::CConsoleGroup::PreTick(float _fDeltaSeconds)
{
	switch (CActor::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}
	return 0;
}

int32 Client::CConsoleGroup::Tick(float _fDeltaSeconds)
{
	switch (CActor::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}
	return 0;
}

int32 Client::CConsoleGroup::PostTick(float _fDeltaSeconds)
{
	switch (CActor::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}
	return 0;
}

HRESULT Client::CConsoleGroup::EndPlay()
{
	if (FAILED(CActor::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Client::CConsoleGroup::Render()
{
	return CActor::Render();
}

void Client::CConsoleGroup::Release()
{
	return CActor::Release();
}

void Client::CConsoleGroup::AddConsole(const shared_ptr<CConsole>& _spConsole)
{
	m_vecConsoles.push_back(_spConsole);
}
