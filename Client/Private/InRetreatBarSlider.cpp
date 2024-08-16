#include "pch.h"
#include "InRetreatBarSlider.h"

#include "WildAnimal.h"
#include "Boss.h"

HRESULT Client::CInRetreatBarSlider::PreInitialize()
{
	SetActorRenderType(ERenderType::OPAQUE_USER_INTERFACE);
	SetPrimitiveType(EPrimitiveType::POINT);
	SetFrontSliderName(L"Img_Main_Gage_01");

	m_wstrGeometryShaderName = L"GS_InGameSlider";
	m_wstrPixelShaderName = L"PS_InRetreatSlider";

	switch (m_eEnemyType)
	{
	case EEnemyType::WILD_ANIMAL:
		m_wpWildAnimal = dynamic_pointer_cast<CWildAnimal>(m_wpActor.lock());
		m_vSliderOffset = { 0.0f, 1.43f, 0.0f };
		break;

	case EEnemyType::BOSS:
		m_wpBoss = dynamic_pointer_cast<CBoss>(m_wpActor.lock());
		m_vSliderOffset = { 0.0f, 3.0f, 0.0f };
		break;
	}

	return CSlider::PreInitialize();
}

HRESULT Client::CInRetreatBarSlider::Initialize()
{
	switch (m_eEnemyType)
	{
	case EEnemyType::WILD_ANIMAL:
		SetWidth(1.0f);
		SetHeight(0.06f);
		SetMaxWidth(1.0f);
		SetMaxHeight(0.06f);
		break;

	case EEnemyType::BOSS:
		break;
	}

	return CSlider::Initialize();
}

HRESULT Client::CInRetreatBarSlider::PostInitialize()
{
	if (FAILED(CSlider::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CInRetreatBarSlider::BeginPlay()
{
	if (FAILED(CSlider::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Client::CInRetreatBarSlider::PreTick(float _fDeltaSeconds)
{
	if (m_wpWildAnimal.lock()->IsDead())
	{
		SetActive(false);
		return 0;
	}

	SetActive(false);

	if (m_wpWildAnimal.lock()->IsAttacked())
	{
		SetActive(true);
	}

	switch (CSlider::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CInRetreatBarSlider::Tick(float _fDeltaSeconds)
{
	switch (CSlider::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	Vector3 vPosition = m_wpActor.lock()->GetActorWorldPosition().value();
	SetActorLocalPosition(vPosition + m_vSliderOffset);
	return 0;
}

int32 Client::CInRetreatBarSlider::PostTick(float _fDeltaSeconds)
{
	switch (CSlider::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	TickSlider();
	return 0;
}

HRESULT Client::CInRetreatBarSlider::EndPlay()
{
	if (FAILED(CSlider::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Client::CInRetreatBarSlider::Render()
{
	CSlider::Render();
}

void Client::CInRetreatBarSlider::Release()
{
	CSlider::Release();
}

void Client::CInRetreatBarSlider::TickSlider()
{
	float fCurRetreat = 0.0f;
	float fMaxRetreat = 0.0f;

	switch (m_eEnemyType)
	{
	case Client::EEnemyType::WILD_ANIMAL:
		fCurRetreat = m_wpWildAnimal.lock()->GetCurChaseSeconds();
		fMaxRetreat = m_wpWildAnimal.lock()->GetMaxChaseSeconds();
		break;

	default:
		CHECKF(false, L"Enemy type is not designated.")
		break;
	}

	if (fCurRetreat <= 0.0f) { fCurRetreat = 0.0f; }

	m_fWidth = m_fMaxWidth * fCurRetreat / fMaxRetreat;
}
