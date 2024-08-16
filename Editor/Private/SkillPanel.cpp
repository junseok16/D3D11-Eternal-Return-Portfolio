#include "pch.h"
#include "SkillPanel.h"

#include "SkillBackground.h"
#include "SkillUpgradeButton.h"
#include "SkillImage.h"
#include "HPBarSlider.h"
#include "StaminaBarSlider.h"
#include "SkillCoolDownText.h"
#include "SkillUpgradeSlider.h"

#include "World.h"
#include "Level.h"
#include "Controller.h"
#include "Survivor.h"

HRESULT Editor::CSkillPanel::PreInitialize()
{
	if (FAILED(CPanel::PreInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Editor::CSkillPanel::Initialize()
{
	if (FAILED(CPanel::Initialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Editor::CSkillPanel::PostInitialize()
{
	if (FAILED(CPanel::PostInitialize())) { return E_FAIL; }

	shared_ptr<CLevel> spLevel = CWorld::GetInstance()->GetCurLevel();

	// shared_ptr<CSurvivor> spSurvivor = static_pointer_cast<CSurvivor>(spLevel->GetController()->GetPawn());
	// m_eSurvivorType = spSurvivor->GetSurvivorType();

	// 패널 1개
	shared_ptr<CSkillBackground> spSkillBackground = spLevel->CreateUI<CSkillBackground>(L"SkillBackgroundImage");
	spSkillBackground->SetPriority(20);
	AddUI(L"SkillBackgroundImage", spSkillBackground);

	// 스킬 이미지 5개
	shared_ptr<CSkillImage> spFirstSkillImage = spLevel->CreateUI<CSkillImage>(L"FirstSkillImage");
	shared_ptr<CSkillImage> spSecondSkillImage = spLevel->CreateUI<CSkillImage>(L"SecondSkillImage");
	shared_ptr<CSkillImage> spThirdSkillImage = spLevel->CreateUI<CSkillImage>(L"ThirdSkillImage");
	shared_ptr<CSkillImage> spFourthSkillImage = spLevel->CreateUI<CSkillImage>(L"FourthSkillImage");
	shared_ptr<CSkillImage> spPassiveSkillImage = spLevel->CreateUI<CSkillImage>(L"PassiveSkillImage");

	spFirstSkillImage->SetPriority(10);
	spSecondSkillImage->SetPriority(10);
	spThirdSkillImage->SetPriority(10);
	spFourthSkillImage->SetPriority(10);
	spPassiveSkillImage->SetPriority(10);

	/*
	spFirstSkillImage->SetSurvivorType(m_eSurvivorType);
	spSecondSkillImage->SetSurvivorType(m_eSurvivorType);
	spThirdSkillImage->SetSurvivorType(m_eSurvivorType);
	spFourthSkillImage->SetSurvivorType(m_eSurvivorType);
	spPassiveSkillImage->SetSurvivorType(m_eSurvivorType);
	*/

	spFirstSkillImage->SetSkillType(ESkillType::FIRST);
	spSecondSkillImage->SetSkillType(ESkillType::SECOND);
	spThirdSkillImage->SetSkillType(ESkillType::THIRD);
	spFourthSkillImage->SetSkillType(ESkillType::FOURTH);
	spPassiveSkillImage->SetSkillType(ESkillType::PASSIVE);

	AddUI(L"FirstSkillImage", spFirstSkillImage);
	AddUI(L"SecondSkillImage", spSecondSkillImage);
	AddUI(L"ThirdSkillImage", spThirdSkillImage);
	AddUI(L"FourthSkillImage", spFourthSkillImage);
	AddUI(L"PassiveSkillImage", spPassiveSkillImage);

	// 스킬 쿨다운 텍스트 4개
	shared_ptr<CSkillCoolDownText> spFirstSkillCoolDownText = spLevel->CreateUI<CSkillCoolDownText>(L"FirstSkillCoolDownText");
	shared_ptr<CSkillCoolDownText> spSecondSkillCoolDownText = spLevel->CreateUI<CSkillCoolDownText>(L"SecondSkillCoolDownText");
	shared_ptr<CSkillCoolDownText> spThirdSkillCoolDownText = spLevel->CreateUI<CSkillCoolDownText>(L"ThirdSkillCoolDownText");
	shared_ptr<CSkillCoolDownText> spFourthSkillCoolDownText = spLevel->CreateUI<CSkillCoolDownText>(L"FourthSkillCoolDownText");

	spFirstSkillCoolDownText->SetSkillType(ESkillType::FIRST);
	spSecondSkillCoolDownText->SetSkillType(ESkillType::SECOND);
	spThirdSkillCoolDownText->SetSkillType(ESkillType::THIRD);
	spFourthSkillCoolDownText->SetSkillType(ESkillType::FOURTH);

	spFirstSkillCoolDownText->SetFontName(L"EternalReturn");
	spSecondSkillCoolDownText->SetFontName(L"EternalReturn");
	spThirdSkillCoolDownText->SetFontName(L"EternalReturn");
	spFourthSkillCoolDownText->SetFontName(L"EternalReturn");

	spFirstSkillCoolDownText->SetPriority(7);
	spSecondSkillCoolDownText->SetPriority(7);
	spThirdSkillCoolDownText->SetPriority(7);
	spFourthSkillCoolDownText->SetPriority(7);

	AddUI(L"FirstSkillCoolDownText", spFirstSkillCoolDownText);
	AddUI(L"SecondSkillCoolDownText", spSecondSkillCoolDownText);
	AddUI(L"ThirdSkillCoolDownText", spThirdSkillCoolDownText);
	AddUI(L"FourthSkillCoolDownText", spFourthSkillCoolDownText);

	// 스킬 업그레이드 버튼 5개
	shared_ptr<CSkillUpgradeButton> spFirstSkillUpgradeButton = spLevel->CreateUI<CSkillUpgradeButton>(L"FirstSkillUpgradeButton");
	shared_ptr<CSkillUpgradeButton> spSecondSkillUpgradeButton = spLevel->CreateUI<CSkillUpgradeButton>(L"SecondSkillUpgradeButton");
	shared_ptr<CSkillUpgradeButton> spThirdSkillUpgradeButton = spLevel->CreateUI<CSkillUpgradeButton>(L"ThirdSkillUpgradeButton");
	shared_ptr<CSkillUpgradeButton> spFourthSkillUpgradeButton = spLevel->CreateUI<CSkillUpgradeButton>(L"FourthSkillUpgradeButton");
	shared_ptr<CSkillUpgradeButton> spPassiveSkillUpgradeButton = spLevel->CreateUI<CSkillUpgradeButton>(L"PassiveSkillUpgradeButton");

	spFirstSkillUpgradeButton->SetPriority(10);
	spSecondSkillUpgradeButton->SetPriority(10);
	spThirdSkillUpgradeButton->SetPriority(10);
	spFourthSkillUpgradeButton->SetPriority(10);
	spPassiveSkillUpgradeButton->SetPriority(10);

	spFirstSkillUpgradeButton->SetSkillType(ESkillType::FIRST);
	spSecondSkillUpgradeButton->SetSkillType(ESkillType::SECOND);
	spThirdSkillUpgradeButton->SetSkillType(ESkillType::THIRD);
	spFourthSkillUpgradeButton->SetSkillType(ESkillType::FOURTH);
	spPassiveSkillUpgradeButton->SetSkillType(ESkillType::PASSIVE);

	AddUI(L"FirstSkillUpgradeButton", spFirstSkillUpgradeButton);
	AddUI(L"SecondSkillUpgradeButton", spSecondSkillUpgradeButton);
	AddUI(L"ThirdSkillUpgradeButton", spThirdSkillUpgradeButton);
	AddUI(L"FourthSkillUpgradeButton", spFourthSkillUpgradeButton);
	AddUI(L"PassiveSkillUpgradeButton", spPassiveSkillUpgradeButton);

	// 스킬 슬라이더 5개
	shared_ptr<CSkillUpgradeSlider> spFirstSkillUpgradeSlider = spLevel->CreateUI<CSkillUpgradeSlider>(L"FirstSkillUpgradeSlider");
	shared_ptr<CSkillUpgradeSlider> spSecondSkillUpgradeSlider = spLevel->CreateUI<CSkillUpgradeSlider>(L"SecondSkillUpgradeSlider");
	shared_ptr<CSkillUpgradeSlider> spThirdSkillUpgradeSlider = spLevel->CreateUI<CSkillUpgradeSlider>(L"ThirdSkillUpgradeSlider");
	shared_ptr<CSkillUpgradeSlider> spFourthSkillUpgradeSlider = spLevel->CreateUI<CSkillUpgradeSlider>(L"FourthSkillUpgradeSlider");
	shared_ptr<CSkillUpgradeSlider> spPassiveSkillUpgradeSlider = spLevel->CreateUI<CSkillUpgradeSlider>(L"PassiveSkillUpgradeSlider");

	spFirstSkillUpgradeSlider->SetPriority(7);
	spSecondSkillUpgradeSlider->SetPriority(7);
	spThirdSkillUpgradeSlider->SetPriority(7);
	spFourthSkillUpgradeSlider->SetPriority(7);
	spPassiveSkillUpgradeSlider->SetPriority(7);

	spFirstSkillUpgradeSlider->SetSkillType(ESkillType::FIRST);
	spSecondSkillUpgradeSlider->SetSkillType(ESkillType::SECOND);
	spThirdSkillUpgradeSlider->SetSkillType(ESkillType::THIRD);
	spFourthSkillUpgradeSlider->SetSkillType(ESkillType::FOURTH);
	spPassiveSkillUpgradeSlider->SetSkillType(ESkillType::PASSIVE);

	AddUI(L"FirstSkillUpgradeSlider", spFirstSkillUpgradeSlider);
	AddUI(L"SecondSkillUpgradeSlider", spSecondSkillUpgradeSlider);
	AddUI(L"ThirdSkillUpgradeSlider", spThirdSkillUpgradeSlider);
	AddUI(L"FourthSkillUpgradeSlider", spFourthSkillUpgradeSlider);
	AddUI(L"PassiveSkillUpgradeSlider", spPassiveSkillUpgradeSlider);

	// 체력, 스테미나 슬라이더 2개
	shared_ptr<CHPBarSlider> spHPBarSlider = spLevel->CreateUI<CHPBarSlider>(L"HPBarSlider");
	shared_ptr<CStaminaBarSlider> spStaminaBarSlider = spLevel->CreateUI<CStaminaBarSlider>(L"StaminaBarSlider");

	spHPBarSlider->SetPriority(10);
	spStaminaBarSlider->SetPriority(10);

	// spHPBarSlider->SetActor(spSurvivor);
	// spStaminaBarSlider->SetActor(spSurvivor);

	AddUI(L"HPBarSlider", spHPBarSlider);
	AddUI(L"StaminaBarSlider", spStaminaBarSlider);

	return S_OK;
}

HRESULT Editor::CSkillPanel::BeginPlay()
{
	if (FAILED(CPanel::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Editor::CSkillPanel::PreTick(float _fDeltaSeconds)
{
	switch (CPanel::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Editor::CSkillPanel::Tick(float _fDeltaSeconds)
{
	switch (CPanel::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Editor::CSkillPanel::PostTick(float _fDeltaSeconds)
{
	switch (CPanel::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Editor::CSkillPanel::EndPlay()
{
	if (FAILED(CPanel::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Editor::CSkillPanel::Render()
{
	CPanel::Render();
}

void Editor::CSkillPanel::Release()
{
	CPanel::Release();
}
