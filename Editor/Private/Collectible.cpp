#include "pch.h"
#include "Collectible.h"

#include "SphereComponent.h"

HRESULT Editor::CCollectible::PreInitialize()
{
    m_wpSphereComponents = CreateActorComponent<CSphereComponent>(L"SphereComponent", EComponentType::SPHERE);
    SetRootComponent(m_wpSphereComponents.lock());

    return CActor::PreInitialize();
}

HRESULT Editor::CCollectible::Initialize()
{
    if (FAILED(CActor::Initialize())) { return E_FAIL; }

    m_wpSphereComponents.lock()->SetCollisionLayer(ECollisionLayer::ITEM);
    m_wpSphereComponents.lock()->AddCollisionFlag(ECollisionLayer::PLAYER);

    return S_OK;
}

HRESULT Editor::CCollectible::PostInitialize()
{
    if (FAILED(CActor::PostInitialize())) { return E_FAIL; }

    return S_OK;
}

HRESULT Editor::CCollectible::BeginPlay()
{
    if (FAILED(CActor::BeginPlay())) { return E_FAIL; }

    return S_OK;
}

int32 Editor::CCollectible::PreTick(float _fDeltaSeconds)
{
    switch (CActor::PreTick(_fDeltaSeconds))
    {
    case -1:	return -1;
    default:	break;
    }
    return 0;
}

int32 Editor::CCollectible::Tick(float _fDeltaSeconds)
{
    switch (CActor::Tick(_fDeltaSeconds))
    {
    case -1:	return -1;
    default:	break;
    }
    return 0;
}

int32 Editor::CCollectible::PostTick(float _fDeltaSeconds)
{
    switch (CActor::PostTick(_fDeltaSeconds))
    {
    case -1:	return -1;
    default:	break;
    }
    return 0;
}

HRESULT Editor::CCollectible::EndPlay()
{
    if (FAILED(CActor::EndPlay())) { return E_FAIL; }

    return S_OK;
}

void Editor::CCollectible::Render()
{
    return CActor::Render();
}

void Editor::CCollectible::Release()
{
    return CActor::Release();
}

void Editor::CCollectible::OnCollisionEnter(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
}

void Editor::CCollectible::OnCollisionStay(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
}

void Editor::CCollectible::OnCollisionExit(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
}
