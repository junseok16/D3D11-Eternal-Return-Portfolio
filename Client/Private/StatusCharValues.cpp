#include "pch.h"
#include "StatusCharValues.h"

#include "GameManager.h"
#include "Survivor.h"

HRESULT Client::CStatusCharValues::PreInitialize()
{
	m_wpGameManager = CGameManager::GetInstance();
	m_wpSurvivor = m_wpGameManager.lock()->GetSurvivor();

	switch (m_eCharacterStatusType)
	{
	case Client::ECharacterStatusType::ATTACK_POWER:
		SetTextPosition({ 140.0f, 642.0f });
		break;

	case Client::ECharacterStatusType::DEFENSE:
		SetTextPosition({ 196.0f, 642.0f });
		break;

	case Client::ECharacterStatusType::INCREASE_BASIC_ATTACK_DAMAGE_RATIO:
		SetTextPosition({ 140.0f, 662.0f });
		break;

	case Client::ECharacterStatusType::NORMAL_ATTACK_DAMAGE_REDUCTION:
		SetTextPosition({ 196.0f, 662.0f });
		break;

	case Client::ECharacterStatusType::SKILL_AMP_RATIO:
		SetTextPosition({ 140.0f, 682.0f });
		break;

	case Client::ECharacterStatusType::SKILL_DAMAGE_REDUCTION:
		SetTextPosition({ 196.0f, 682.0f });
		break;

	case Client::ECharacterStatusType::ATTACK_SPEED_RATIO:
		SetTextPosition({ 140.0f, 702.0f });
		break;

	case Client::ECharacterStatusType::MOVE_SPEED_RATIO:
		SetTextPosition({ 196.0f, 702.0f });
		break;

	default:
		break;
	}

	SetTextScale(0.3f);
	SetActorRenderType(ERenderType::OPAQUE_USER_INTERFACE);
	return CText::PreInitialize();
}

HRESULT Client::CStatusCharValues::Initialize()
{
	return S_OK;
}

HRESULT Client::CStatusCharValues::PostInitialize()
{
	return S_OK;
}

HRESULT Client::CStatusCharValues::BeginPlay()
{
	return S_OK;
}

int32 Client::CStatusCharValues::PreTick(float _fDeltaSeconds)
{
	switch (CText::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CStatusCharValues::Tick(float _fDeltaSeconds)
{
	switch (CText::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	shared_ptr<CSurvivor> spSurvivor = m_wpGameManager.lock()->GetSurvivor();

	switch (m_eCharacterStatusType)
	{
	case Client::ECharacterStatusType::ATTACK_POWER:
	{
		int32 iAttackPower = static_cast<int32>(spSurvivor->GetCurAttackPower());
		SetText(to_wstring(iAttackPower));
	}
	break;

	case Client::ECharacterStatusType::DEFENSE:
	{
		int32 iDefensePower = static_cast<int32>(spSurvivor->GetCurDefensePower());
		SetText(to_wstring(iDefensePower));
	}
	break;

	// 추가 공격력
	case Client::ECharacterStatusType::INCREASE_BASIC_ATTACK_DAMAGE_RATIO:
	{
		int32 iDefensePower = static_cast<int32>(spSurvivor->GetAdditionalAttackPower());
		SetText(to_wstring(iDefensePower));
	}
	break;

	// 추가 방어력
	case Client::ECharacterStatusType::NORMAL_ATTACK_DAMAGE_REDUCTION:
	{
		int32 iDefensePower = static_cast<int32>(spSurvivor->GetAdditionalDefensePower());
		SetText(to_wstring(iDefensePower));
	}
	break;

	// 체력 회복량
	case Client::ECharacterStatusType::SKILL_AMP_RATIO:
	{
		float fHPRegeneration = spSurvivor->GetHPRegeneration();
		SetText(std::format(L"{:.2f}", fHPRegeneration));
	}
	break;

	// 스테미나 회복량
	case Client::ECharacterStatusType::SKILL_DAMAGE_REDUCTION:
	{
		float fSPRegeneration = spSurvivor->GetSPRegeneration();
		SetText(std::format(L"{:.2f}", fSPRegeneration));
	}
	break;

	case Client::ECharacterStatusType::ATTACK_SPEED_RATIO:
	{
		SetText(L"0");
	}
	break;

	case Client::ECharacterStatusType::MOVE_SPEED_RATIO:
	{
		float fCurMoveSpeed = spSurvivor->GetCurMoveSpeed();
		SetText(std::format(L"{:.2f}", fCurMoveSpeed));
	}
	break;

	default:
		break;
	}

	return 0;
}

int32 Client::CStatusCharValues::PostTick(float _fDeltaSeconds)
{
	switch (CText::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Client::CStatusCharValues::EndPlay()
{
	if (FAILED(CText::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Client::CStatusCharValues::Render()
{
	CText::Render();
}

void Client::CStatusCharValues::Release()
{
	CText::Release();
}
