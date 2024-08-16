#include "pch.h"
#include "Collectible.h"

#include "SphereComponent.h"

HRESULT Client::CCollectible::PreInitialize()
{
    m_wpSphereComponents = CreateActorComponent<CSphereComponent>(L"SphereComponent", EComponentType::SPHERE);
    SetRootComponent(m_wpSphereComponents.lock());

    return CActor::PreInitialize();
}

HRESULT Client::CCollectible::Initialize()
{
    if (FAILED(CActor::Initialize())) { return E_FAIL; }

    m_wpSphereComponents.lock()->SetCollisionLayer(ECollisionLayer::ITEM);
    m_wpSphereComponents.lock()->AddCollisionFlag(ECollisionLayer::PLAYER);

    return S_OK;
}

HRESULT Client::CCollectible::PostInitialize()
{
    if (FAILED(CActor::PostInitialize())) { return E_FAIL; }

    return S_OK;
}

HRESULT Client::CCollectible::BeginPlay()
{
    if (FAILED(CActor::BeginPlay())) { return E_FAIL; }

    return S_OK;
}

int32 Client::CCollectible::PreTick(float _fDeltaSeconds)
{
    switch (CActor::PreTick(_fDeltaSeconds))
    {
    case -1:	return -1;
    default:	break;
    }
    return 0;
}

int32 Client::CCollectible::Tick(float _fDeltaSeconds)
{
    switch (CActor::Tick(_fDeltaSeconds))
    {
    case -1:	return -1;
    default:	break;
    }
    return 0;
}

int32 Client::CCollectible::PostTick(float _fDeltaSeconds)
{
    switch (CActor::PostTick(_fDeltaSeconds))
    {
    case -1:	return -1;
    default:	break;
    }
    return 0;
}

HRESULT Client::CCollectible::EndPlay()
{
    if (FAILED(CActor::EndPlay())) { return E_FAIL; }

    return S_OK;
}

void Client::CCollectible::Render()
{
    return CActor::Render();
}

void Client::CCollectible::Release()
{
    return CActor::Release();
}

void Client::CCollectible::OnCollisionEnter(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
}

void Client::CCollectible::OnCollisionStay(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
}

void Client::CCollectible::OnCollisionExit(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
}
