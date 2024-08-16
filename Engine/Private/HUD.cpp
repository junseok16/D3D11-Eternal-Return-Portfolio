#include "pch.h"
#include "HUD.h"

HRESULT Engine::CHUD::PreInitialize()
{
	if (FAILED(CActor::PreInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Engine::CHUD::Initialize()
{
	if (FAILED(CActor::Initialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Engine::CHUD::PostInitialize()
{
	if (FAILED(CActor::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Engine::CHUD::BeginPlay()
{
	if (FAILED(CActor::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Engine::CHUD::PreTick(float _fDeltaSeconds)
{
	switch (CActor::PreTick(_fDeltaSeconds))
	{
	case -1: return -1;
	default: break;
	}

	return 0;
}

int32 Engine::CHUD::Tick(float _fDeltaSeconds)
{
	switch (CActor::Tick(_fDeltaSeconds))
	{
	case -1: return -1;
	default: break;
	}

	return 0;
}

int32 Engine::CHUD::PostTick(float _fDeltaSeconds)
{
	switch (CActor::PostTick(_fDeltaSeconds))
	{
	case -1: return -1;
	default: break;
	}

	return 0;
}

HRESULT Engine::CHUD::EndPlay()
{
	if (FAILED(CActor::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Engine::CHUD::Render()
{
	CActor::Render();
}

void Engine::CHUD::Release()
{
	CActor::Release();
}

HRESULT Engine::CHUD::AddPanel(const std::wstring& _wstrPanelName, const std::shared_ptr<CPanel> _spPanel)
{
	return S_OK;
}

HRESULT Engine::CHUD::RemovePanel(const std::wstring& _wstrPanelName)
{
	return S_OK;
}
