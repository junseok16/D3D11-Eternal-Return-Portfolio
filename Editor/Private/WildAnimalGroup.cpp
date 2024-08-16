#include "pch.h"
#include "WildAnimalGroup.h"

HRESULT Editor::CWildAnimalGroup::PreInitialize()
{
	return CActor::PreInitialize();
}

HRESULT Editor::CWildAnimalGroup::Initialize()
{
	return CActor::Initialize();
}

HRESULT Editor::CWildAnimalGroup::PostInitialize()
{
	if (FAILED(CActor::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Editor::CWildAnimalGroup::BeginPlay()
{
	if (FAILED(CActor::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Editor::CWildAnimalGroup::PreTick(float _fDeltaSeconds)
{
	switch (CActor::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}
	return 0;
}

int32 Editor::CWildAnimalGroup::Tick(float _fDeltaSeconds)
{
	switch (CActor::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}
	return 0;
}

int32 Editor::CWildAnimalGroup::PostTick(float _fDeltaSeconds)
{
	switch (CActor::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}
	return 0;
}

HRESULT Editor::CWildAnimalGroup::EndPlay()
{
	if (FAILED(CActor::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Editor::CWildAnimalGroup::Render()
{
	return CActor::Render();
}

void Editor::CWildAnimalGroup::Release()
{
	return CActor::Release();
}

void Editor::CWildAnimalGroup::AddWildAnimal(const std::shared_ptr<CWildAnimal>& _spWildAnimal)
{
	m_vecWildAnimals.push_back(_spWildAnimal);
}
