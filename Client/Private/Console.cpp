#include "pch.h"
#include "Console.h"

#include "SphereComponent.h"

HRESULT Client::CConsole::PreInitialize()
{
    m_wpSphereComponents = CreateActorComponent<CSphereComponent>(L"SphereComponent", EComponentType::SPHERE);
    SetRootComponent(m_wpSphereComponents.lock());

    return CActor::PreInitialize();
}

HRESULT Client::CConsole::Initialize()
{
    if (FAILED(CActor::Initialize())) { return E_FAIL; }

    m_wpSphereComponents.lock()->SetCollisionLayer(ECollisionLayer::STRUCTURE);
    m_wpSphereComponents.lock()->AddCollisionFlag(ECollisionLayer::PLAYER);

    return S_OK;
}

HRESULT Client::CConsole::PostInitialize()
{
    if (FAILED(CActor::PostInitialize())) { return E_FAIL; }

    return S_OK;
}

HRESULT Client::CConsole::BeginPlay()
{
    if (FAILED(CActor::BeginPlay())) { return E_FAIL; }

    return S_OK;
}

int32 Client::CConsole::PreTick(float _fDeltaSeconds)
{
    switch (CActor::PreTick(_fDeltaSeconds))
    {
    case -1:	return -1;
    default:	break;
    }
    return 0;
}

int32 Client::CConsole::Tick(float _fDeltaSeconds)
{
    switch (CActor::Tick(_fDeltaSeconds))
    {
    case -1:	return -1;
    default:	break;
    }
    return 0;
}

int32 Client::CConsole::PostTick(float _fDeltaSeconds)
{
    switch (CActor::PostTick(_fDeltaSeconds))
    {
    case -1:	return -1;
    default:	break;
    }
    return 0;
}

HRESULT Client::CConsole::EndPlay()
{
    if (FAILED(CActor::EndPlay())) { return E_FAIL; }

    return S_OK;
}

void Client::CConsole::Render()
{
    return CActor::Render();
}

void Client::CConsole::Release()
{
    return CActor::Release();
}

void Client::CConsole::OnCollisionEnter(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
}

void Client::CConsole::OnCollisionStay(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
}

void Client::CConsole::OnCollisionExit(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
}
