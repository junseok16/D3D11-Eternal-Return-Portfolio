#include "pch.h"
#include "WildAnimalGroup.h"

HRESULT Client::CWildAnimalGroup::PreInitialize()
{
	return CActor::PreInitialize();
}

HRESULT Client::CWildAnimalGroup::Initialize()
{
	return CActor::Initialize();
}

HRESULT Client::CWildAnimalGroup::PostInitialize()
{
	if (FAILED(CActor::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CWildAnimalGroup::BeginPlay()
{
	if (FAILED(CActor::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Client::CWildAnimalGroup::PreTick(float _fDeltaSeconds)
{
	switch (CActor::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}
	return 0;
}

int32 Client::CWildAnimalGroup::Tick(float _fDeltaSeconds)
{
	switch (CActor::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}
	return 0;
}

int32 Client::CWildAnimalGroup::PostTick(float _fDeltaSeconds)
{
	switch (CActor::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}
	return 0;
}

HRESULT Client::CWildAnimalGroup::EndPlay()
{
	if (FAILED(CActor::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Client::CWildAnimalGroup::Render()
{
	return CActor::Render();
}

void Client::CWildAnimalGroup::Release()
{
	return CActor::Release();
}

void Client::CWildAnimalGroup::AddWildAnimal(const std::shared_ptr<CWildAnimal>& _spWildAnimal)
{
	m_vecWildAnimals.push_back(_spWildAnimal);
}
