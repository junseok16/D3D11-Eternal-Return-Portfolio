#include "pch.h"
#include "SkillUpgradeSlider.h"

#include "GameManager.h"
#include "Survivor.h"

HRESULT Client::CSkillUpgradeSlider::PreInitialize()
{
	SetActorRenderType(ERenderType::OPAQUE_USER_INTERFACE);
	SetPrimitiveType(EPrimitiveType::POINT);
	SetFrontSliderName(L"Img_Main_Gage_03");

	m_wstrPixelShaderName = L"PS_BoldSlider";

	m_wpGameManager = CGameManager::GetInstance();
	m_wpSurvivor = m_wpGameManager.lock()->GetSurvivor();

	return CSlider::PreInitialize();
}

HRESULT Client::CSkillUpgradeSlider::Initialize()
{

	switch (m_eSkillType)
	{
	case Client::ESkillType::FIRST:
	{
		SetPivot({ 463.0f, 686.0f });
		SetWidth(20.0f);
		SetHeight(8.0f);
		SetMaxWidth(41.0f);
		SetMaxHeight(8.0f);
	}
	break;

	case Client::ESkillType::SECOND:
	{
		SetPivot({ 513.0f, 686.0f });
		SetWidth(0.0f);
		SetHeight(8.0f);
		SetMaxWidth(41.0f);
		SetMaxHeight(8.0f);
	}
	break;

	case Client::ESkillType::THIRD:
	{
		SetPivot({ 563.0f, 686.0f });
		SetWidth(0.0f);
		SetHeight(8.0f);
		SetMaxWidth(41.0f);
		SetMaxHeight(8.0f);
	}
	break;

	case Client::ESkillType::FOURTH:
	{
		SetPivot({ 613.0f, 686.0f });
		SetWidth(0.0f);
		SetHeight(8.0f);
		SetMaxWidth(41.0f);
		SetMaxHeight(8.0f);
	}
	break;

	case Client::ESkillType::PASSIVE:
	{
		SetPivot({ 663.0f, 686.0f });
		SetWidth(0.0f);
		SetHeight(8.0f);
		SetMaxWidth(41.0f);
		SetMaxHeight(8.0f);
	}
	break;

	default: CHECKF(false, L"Skill type is not designated.");	break;
	}

	return CSlider::Initialize();
}

HRESULT Client::CSkillUpgradeSlider::PostInitialize()
{
	if (FAILED(CSlider::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CSkillUpgradeSlider::BeginPlay()
{
	if (FAILED(CSlider::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Client::CSkillUpgradeSlider::PreTick(float _fDeltaSeconds)
{
	switch (CSlider::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CSkillUpgradeSlider::Tick(float _fDeltaSeconds)
{
	switch (CSlider::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CSkillUpgradeSlider::PostTick(float _fDeltaSeconds)
{
	switch (CSlider::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	TickSlider();
	return 0;
}

HRESULT Client::CSkillUpgradeSlider::EndPlay()
{
	if (FAILED(CSlider::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Client::CSkillUpgradeSlider::Render()
{
	CSlider::Render();
}

void Client::CSkillUpgradeSlider::Release()
{
	CSlider::Release();
}

void Client::CSkillUpgradeSlider::TickSlider()
{
	float fCurSkillLevel = (float)m_wpGameManager.lock()->GetSurvivor()->GetCurSkillLevel(m_eSkillType) + 1;
	float fMaxSkillLevel = (float)m_wpGameManager.lock()->GetSurvivor()->GetMaxSkillLevel(m_eSkillType);

	m_fWidth = m_fMaxWidth * fCurSkillLevel / fMaxSkillLevel;
}
