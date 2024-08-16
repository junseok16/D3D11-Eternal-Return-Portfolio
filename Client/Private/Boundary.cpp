#include "pch.h"
#include "Boundary.h"

#include "AABBComponent.h"

HRESULT Client::CBoundary::PreInitialize()
{
	{
		m_wpAABBComponent = CreateActorComponent<CAABBComponent>(L"AABBComponent", EComponentType::AABB);
		SetRootComponent(m_wpAABBComponent.lock());
	}

	return CActor::PreInitialize();
}

HRESULT Client::CBoundary::Initialize()
{
	if (FAILED(CActor::Initialize())) { return E_FAIL; }

	{
		SetActorLocalPosition(m_vSpawnPosition);
	}
	
	{
		m_wpAABBComponent.lock()->SetExtent({ 1.0f, 1.0f, 1.0f });
		m_wpAABBComponent.lock()->SetCenter({ 0.0f, 1.0f, 0.0f });
		m_wpAABBComponent.lock()->SetCollisionLayer(ECollisionLayer::BOUNDARY);
		m_wpAABBComponent.lock()->AddCollisionFlag(ECollisionLayer::PLAYER);
		m_wpAABBComponent.lock()->AddCollisionFlag(ECollisionLayer::MONSTER);
	}

	return S_OK;
}

HRESULT Client::CBoundary::PostInitialize()
{
	if (FAILED(CActor::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CBoundary::BeginPlay()
{
	if (FAILED(CActor::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Client::CBoundary::PreTick(float _fDeltaSeconds)
{
	switch (CActor::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CBoundary::Tick(float _fDeltaSeconds)
{
	switch (CActor::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CBoundary::PostTick(float _fDeltaSeconds)
{
	switch (CActor::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Client::CBoundary::EndPlay()
{
	if (FAILED(CActor::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Client::CBoundary::Render()
{
	CActor::Render();
}

void Client::CBoundary::Release()
{
	CActor::Release();
}

void Client::CBoundary::OnCollisionEnter(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
}

void Client::CBoundary::OnCollisionStay(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
}

void Client::CBoundary::OnCollisionExit(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
}
