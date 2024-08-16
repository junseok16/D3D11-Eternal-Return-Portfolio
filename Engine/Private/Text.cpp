#include "pch.h"
#include "Text.h"

#include "FontHandler.h"
#include "CustomFont.h"

HRESULT Engine::CText::PreInitialize()
{
	m_wpFontHandler = CFontHandler::GetInstance();
	m_wpFont = m_wpFontHandler.lock()->FindFont(m_wstrFontName);
	return S_OK;
}

HRESULT Engine::CText::Initialize()
{
	return S_OK;
}

HRESULT Engine::CText::PostInitialize()
{
	return S_OK;
}

HRESULT Engine::CText::BeginPlay()
{
	return S_OK;
}

int32 Engine::CText::PreTick(float _fDeltaSeconds)
{
	if (!m_bActive) { return 0; }

	switch (CUI::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Engine::CText::Tick(float _fDeltaSeconds)
{
	if (!m_bActive) { return 0; }

	switch (CUI::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Engine::CText::PostTick(float _fDeltaSeconds)
{
	if (!m_bActive) { return 0; }

	switch (CUI::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Engine::CText::EndPlay()
{
	if (FAILED(CUI::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Engine::CText::Render()
{
	if (!m_bActive) { return; }

	CUI::Render();
	m_wpFont.lock()->Render(m_wstrText, m_vTextPosition, m_vTextColor, m_fRadian, m_vOrigin, m_fScale);
}

void Engine::CText::Release()
{
	CUI::Release();
}
