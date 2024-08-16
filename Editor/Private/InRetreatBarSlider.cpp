#include "pch.h"
#include "InRetreatBarSlider.h"

#include "WildAnimal.h"
#include "Boss.h"

HRESULT Editor::CInRetreatBarSlider::PreInitialize()
{
	SetActorRenderType(ERenderType::OPAQUE_USER_INTERFACE);
	SetPrimitiveType(EPrimitiveType::POINT);
	SetFrontSliderName(L"Img_Main_Gage_01");

	switch (m_eEnemyType)
	{
	case EEnemyType::WILD_ANIMAL:
		m_wpWildAnimal = dynamic_pointer_cast<CWildAnimal>(m_wpActor.lock());
		break;

	case EEnemyType::BOSS:
		m_wpBoss = dynamic_pointer_cast<CBoss>(m_wpActor.lock());
		break;
	}

	return CSlider::PreInitialize();
}

HRESULT Editor::CInRetreatBarSlider::Initialize()
{
	SetWidth(85.0f);
	SetHeight(10.0f);
	SetMaxWidth(85.0f);
	SetMaxHeight(10.0f);
	return CSlider::Initialize();
}

HRESULT Editor::CInRetreatBarSlider::PostInitialize()
{
	if (FAILED(CSlider::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Editor::CInRetreatBarSlider::BeginPlay()
{
	if (FAILED(CSlider::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Editor::CInRetreatBarSlider::PreTick(float _fDeltaSeconds)
{
	switch (CSlider::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Editor::CInRetreatBarSlider::Tick(float _fDeltaSeconds)
{
	switch (CSlider::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	SetActorLocalPosition(m_wpActor.lock()->GetActorWorldPosition().value() + m_fSliderOffset);
	return 0;
}

int32 Editor::CInRetreatBarSlider::PostTick(float _fDeltaSeconds)
{
	switch (CSlider::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	TickSlider();
	return 0;
}

HRESULT Editor::CInRetreatBarSlider::EndPlay()
{
	if (FAILED(CSlider::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Editor::CInRetreatBarSlider::Render()
{
	CSlider::Render();
}

void Editor::CInRetreatBarSlider::Release()
{
	CSlider::Release();
}

void Editor::CInRetreatBarSlider::TickSlider()
{
	switch (m_eEnemyType)
	{
	case Editor::EEnemyType::WILD_ANIMAL:
		break;

	case Editor::EEnemyType::SURVIVOR:
		break;

	case Editor::EEnemyType::BOSS:
		break;

	default:
		CHECKF(false, L"Enemy type is not designated.")
		break;
	}
}
