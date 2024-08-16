#include "pch.h"
#include "InHPBarSlider.h"

#include "WildAnimal.h"
#include "Boss.h"

HRESULT Client::CInHPBarSlider::PreInitialize()
{
	SetActorRenderType(ERenderType::TRANSLUCENT_OBJECT);
	SetPrimitiveType(EPrimitiveType::POINT);
	SetFrontSliderName(L"Img_Main_Gage_04");

	m_wstrGeometryShaderName = L"GS_InGameSlider";
	m_wstrPixelShaderName = L"PS_InGameSlider";

	switch (m_eEnemyType)
	{
	case EEnemyType::WILD_ANIMAL:
		m_wpWildAnimal = dynamic_pointer_cast<CWildAnimal>(m_wpActor.lock());
		m_vSliderOffset = { 0.0f, 1.53f, 0.0f };
		break;

	case EEnemyType::BOSS:
		m_wpBoss = dynamic_pointer_cast<CBoss>(m_wpActor.lock());
		m_vSliderOffset = { 0.0f, 3.0f, 0.0f };
		break;
	}

	return CSlider::PreInitialize();
}

HRESULT Client::CInHPBarSlider::Initialize()
{
	switch (m_eEnemyType)
	{
	case EEnemyType::WILD_ANIMAL:
		SetWidth(1.0f);
		SetHeight(0.125f);
		SetMaxWidth(1.0f);
		SetMaxHeight(0.125f);
		break;

	case EEnemyType::BOSS:
		SetWidth(2.0f);
		SetHeight(0.25f);
		SetMaxWidth(2.0f);
		SetMaxHeight(0.25f);
		break;
	}

	return CSlider::Initialize();
}

HRESULT Client::CInHPBarSlider::PostInitialize()
{
	if (FAILED(CSlider::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CInHPBarSlider::BeginPlay()
{
	if (FAILED(CSlider::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Client::CInHPBarSlider::PreTick(float _fDeltaSeconds)
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

	Vector3 vPosition = m_wpActor.lock()->GetActorWorldPosition().value();
	SetActorLocalPosition(vPosition + m_vSliderOffset);
	return 0;
}

int32 Client::CInHPBarSlider::Tick(float _fDeltaSeconds)
{
	switch (CSlider::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}
	
	return 0;
}

int32 Client::CInHPBarSlider::PostTick(float _fDeltaSeconds)
{
	switch (CSlider::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	TickSlider();
	return 0;
}

HRESULT Client::CInHPBarSlider::EndPlay()
{
	if (FAILED(CSlider::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Client::CInHPBarSlider::Render()
{
	CSlider::Render();
}

void Client::CInHPBarSlider::Release()
{
	CSlider::Release();
}

void Client::CInHPBarSlider::TickSlider()
{
	float fCurHP = 0.0f;
	float fMaxHP = 0.0f;

	switch (m_eEnemyType)
	{
	case Client::EEnemyType::WILD_ANIMAL:
		fCurHP = m_wpWildAnimal.lock()->GetCurHP();
		fMaxHP = m_wpWildAnimal.lock()->GetMaxHP();
		break;

	case Client::EEnemyType::SURVIVOR:
		break;

	case Client::EEnemyType::BOSS:
		fCurHP = m_wpBoss.lock()->GetCurHP();
		fMaxHP = m_wpBoss.lock()->GetMaxHP();
		break;

	default:
		CHECKF(false, L"Enemy type is not designated.")
			break;
	}

	if (fCurHP <= 0.0f) { fCurHP = 0.0f; }

	m_fWidth = m_fMaxWidth * fCurHP / fMaxHP;
}
