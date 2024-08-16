// default
#include "pch.h"
#include "ActorComponent.h"

// world
#include "World.h"

HRESULT Engine::CActorComponent::PreInitializeComponent()
{
	return S_OK;
}

HRESULT Engine::CActorComponent::InitializeComponent()
{
	return S_OK;
}

HRESULT Engine::CActorComponent::PostInitializeComponent()
{
	return S_OK;
}

HRESULT Engine::CActorComponent::BeginPlay()
{
	return S_OK;
}

int32 Engine::CActorComponent::PreTickComponent(float _fDeltaSeconds)
{
	return 0;
}

int32 Engine::CActorComponent::TickComponent(float _fDeltaSeconds)
{
	return 0;
}

int32 Engine::CActorComponent::PostTickComponent(float _fDeltaSeconds)
{
	return 0;
}

HRESULT Engine::CActorComponent::EndPlay()
{
	return S_OK;
}

void Engine::CActorComponent::Render()
{
	return;
}

void Engine::CActorComponent::RenderShadow()
{
	return;
}

void Engine::CActorComponent::Release()
{
	return;
}

const std::shared_ptr<CActor> Engine::CActorComponent::GetOwnerActor() const
{
	return m_wpOwnerActor.expired() ? nullptr : m_wpOwnerActor.lock();
}
