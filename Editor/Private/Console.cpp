#include "pch.h"
#include "Console.h"

#include "SphereComponent.h"

HRESULT Editor::CConsole::PreInitialize()
{
    m_wpSphereComponents = CreateActorComponent<CSphereComponent>(L"SphereComponent", EComponentType::SPHERE);
    SetRootComponent(m_wpSphereComponents.lock());

    return CActor::PreInitialize();
}

HRESULT Editor::CConsole::Initialize()
{
    if (FAILED(CActor::Initialize())) { return E_FAIL; }

    m_wpSphereComponents.lock()->SetCollisionLayer(ECollisionLayer::STRUCTURE);
    m_wpSphereComponents.lock()->AddCollisionFlag(ECollisionLayer::PLAYER);

    return S_OK;
}

HRESULT Editor::CConsole::PostInitialize()
{
    if (FAILED(CActor::PostInitialize())) { return E_FAIL; }

    return S_OK;
}

HRESULT Editor::CConsole::BeginPlay()
{
    if (FAILED(CActor::BeginPlay())) { return E_FAIL; }

    return S_OK;
}

int32 Editor::CConsole::PreTick(float _fDeltaSeconds)
{
    switch (CActor::PreTick(_fDeltaSeconds))
    {
    case -1:	return -1;
    default:	break;
    }
    return 0;
}

int32 Editor::CConsole::Tick(float _fDeltaSeconds)
{
    switch (CActor::Tick(_fDeltaSeconds))
    {
    case -1:	return -1;
    default:	break;
    }
    return 0;
}

int32 Editor::CConsole::PostTick(float _fDeltaSeconds)
{
    switch (CActor::PostTick(_fDeltaSeconds))
    {
    case -1:	return -1;
    default:	break;
    }
    return 0;
}

HRESULT Editor::CConsole::EndPlay()
{
    if (FAILED(CActor::EndPlay())) { return E_FAIL; }

    return S_OK;
}

void Editor::CConsole::Render()
{
    return CActor::Render();
}

void Editor::CConsole::Release()
{
    return CActor::Release();
}

void Editor::CConsole::OnCollisionEnter(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
}

void Editor::CConsole::OnCollisionStay(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
}

void Editor::CConsole::OnCollisionExit(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
}
