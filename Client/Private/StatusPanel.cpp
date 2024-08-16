#include "pch.h"
#include "StatusPanel.h"

#include "StatusBackground.h"
#include "StatusProfile.h"
#include "StatusCharIcon.h"
#include "EquipSlotImage.h"
#include "ItemButton.h"
#include "ExpBarSlider.h"
#include "StatusCharLevelText.h"
#include "StatusCharValues.h"
#include "StatusCharLevelCircleImage.h"

#include "World.h"
#include "Level.h"
#include "Controller.h"
#include "Survivor.h"

HRESULT Client::CStatusPanel::PreInitialize()
{
	if (FAILED(CPanel::PreInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CStatusPanel::Initialize()
{
	if (FAILED(CPanel::Initialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CStatusPanel::PostInitialize()
{
	if (FAILED(CPanel::PostInitialize())) { return E_FAIL; }

	shared_ptr<CLevel> spLevel = CWorld::GetInstance()->GetCurLevel();
	shared_ptr<CSurvivor> spSurvivor = static_pointer_cast<CSurvivor>(spLevel->GetController()->GetPawn());
	m_eSurvivorType = spSurvivor->GetSurvivorType();

	// 패널 1개
	shared_ptr<CStatusBackground> spStatusBackground = spLevel->CreateUI<CStatusBackground>(L"StatusBackground");
	spStatusBackground->SetPriority(20);
	AddUI(L"StatusBackground", spStatusBackground);

	// 프로필 이미지 1장
	shared_ptr<CStatusProfile> spStatusProfileImage = spLevel->CreateUI<CStatusProfile>(L"StatusProfileImage");
	spStatusProfileImage->SetPriority(10);
	spStatusProfileImage->SetSurvivorType(m_eSurvivorType);
	AddUI(L"StatusProfileImage", spStatusProfileImage);

	// 경험치 슬라이더 1개
	shared_ptr<CExpBarSlider> spExpBarSlider = spLevel->CreateUI<CExpBarSlider>(L"ExpBarSlider");
	spExpBarSlider->SetPriority(7);
	spExpBarSlider->SetActor(spSurvivor);
	AddUI(L"ExpBarSlider", spExpBarSlider);

	// 레벨 배경 이미지 1장
	shared_ptr<CStatusCharLevelCircleImage> spLevelCircleImage = spLevel->CreateUI<CStatusCharLevelCircleImage>(L"LevelCircleImage");
	spLevelCircleImage->SetPriority(5);
	AddUI(L"LevelCircleImage", spLevelCircleImage);

	// 레벨 텍스트 1개
	shared_ptr<CStatusCharLevelText> spStatusCharLevelText = spLevel->CreateUI<CStatusCharLevelText>(L"StatusCharLevelText");
	spStatusCharLevelText->SetFontName(L"EternalReturn");
	spStatusCharLevelText->SetPriority(3);
	AddUI(L"StatusCharLevelText", spStatusCharLevelText);

	// 스텟 이미지 8장
	shared_ptr<CStatusCharIcon> spAttackPowerIcon = spLevel->CreateUI<CStatusCharIcon>(L"AttackPowerImage");
	shared_ptr<CStatusCharIcon> spDefenseIcon = spLevel->CreateUI<CStatusCharIcon>(L"DefenseImage");
	shared_ptr<CStatusCharIcon> spIncreaseAttackDamageIcon = spLevel->CreateUI<CStatusCharIcon>(L"IncreaseAttackDamageImage");
	shared_ptr<CStatusCharIcon> spAttackDamageReductionIcon = spLevel->CreateUI<CStatusCharIcon>(L"AttackDamageReductionImage");
	shared_ptr<CStatusCharIcon> spSkillAmpRatioIcon = spLevel->CreateUI<CStatusCharIcon>(L"SkillAmpRatioImage");
	shared_ptr<CStatusCharIcon> spSkillDamageReducitonIcon = spLevel->CreateUI<CStatusCharIcon>(L"SkillDamageReductionImage");
	shared_ptr<CStatusCharIcon> spMoveSpeedIcon = spLevel->CreateUI<CStatusCharIcon>(L"MoveSpeedImage");
	shared_ptr<CStatusCharIcon> spAttackSpeedIcon = spLevel->CreateUI<CStatusCharIcon>(L"AttackSpeedImage");

	spAttackPowerIcon->SetPriority(10);
	spDefenseIcon->SetPriority(10);
	spIncreaseAttackDamageIcon->SetPriority(10);
	spAttackDamageReductionIcon->SetPriority(10);
	spSkillAmpRatioIcon->SetPriority(10);
	spSkillDamageReducitonIcon->SetPriority(10);
	spMoveSpeedIcon->SetPriority(10);
	spAttackSpeedIcon->SetPriority(10);

	spAttackPowerIcon->SetCharacterStatusType(ECharacterStatusType::ATTACK_POWER);
	spDefenseIcon->SetCharacterStatusType(ECharacterStatusType::DEFENSE);
	spIncreaseAttackDamageIcon->SetCharacterStatusType(ECharacterStatusType::INCREASE_BASIC_ATTACK_DAMAGE_RATIO);
	spAttackDamageReductionIcon->SetCharacterStatusType(ECharacterStatusType::NORMAL_ATTACK_DAMAGE_REDUCTION);
	spSkillAmpRatioIcon->SetCharacterStatusType(ECharacterStatusType::SKILL_AMP_RATIO);
	spSkillDamageReducitonIcon->SetCharacterStatusType(ECharacterStatusType::SKILL_DAMAGE_REDUCTION);
	spMoveSpeedIcon->SetCharacterStatusType(ECharacterStatusType::MOVE_SPEED_RATIO);
	spAttackSpeedIcon->SetCharacterStatusType(ECharacterStatusType::ATTACK_SPEED_RATIO);

	AddUI(L"AttackPowerImage", spAttackPowerIcon);
	AddUI(L"DefenseImage", spDefenseIcon);
	AddUI(L"IncreaseAttackDamageImage", spIncreaseAttackDamageIcon);
	AddUI(L"AttackDamageReductionImage", spAttackDamageReductionIcon);
	AddUI(L"SkillAmpRatioImage", spSkillAmpRatioIcon);
	AddUI(L"SkillDamageReductionImage", spSkillDamageReducitonIcon);
	AddUI(L"MoveSpeedImage", spMoveSpeedIcon);
	AddUI(L"AttackSpeedImage", spAttackSpeedIcon);

	// 스텟 텍스트 8개
	shared_ptr<CStatusCharValues> spAttackPowerText = spLevel->CreateUI<CStatusCharValues>(L"AttackPowerText");
	shared_ptr<CStatusCharValues> spDefenseText = spLevel->CreateUI<CStatusCharValues>(L"DefenseText");
	shared_ptr<CStatusCharValues> spIncreaseAttackDamageText = spLevel->CreateUI<CStatusCharValues>(L"IncreaseAttackDamageText");
	shared_ptr<CStatusCharValues> spAttackDamageReductionText = spLevel->CreateUI<CStatusCharValues>(L"AttackDamageReductionText");
	shared_ptr<CStatusCharValues> spSkillAmpRatioText = spLevel->CreateUI<CStatusCharValues>(L"SkillAmpRatioText");
	shared_ptr<CStatusCharValues> spSkillDamageReducitonText = spLevel->CreateUI<CStatusCharValues>(L"SkillDamageReducitonText");
	shared_ptr<CStatusCharValues> spMoveSpeedText = spLevel->CreateUI<CStatusCharValues>(L"MoveSpeedText");
	shared_ptr<CStatusCharValues> spAttackSpeedText = spLevel->CreateUI<CStatusCharValues>(L"AttackSpeedText");

	spAttackPowerText->SetFontName(L"EternalReturn");
	spDefenseText->SetFontName(L"EternalReturn");
	spIncreaseAttackDamageText->SetFontName(L"EternalReturn");
	spAttackDamageReductionText->SetFontName(L"EternalReturn");
	spSkillAmpRatioText->SetFontName(L"EternalReturn");
	spSkillDamageReducitonText->SetFontName(L"EternalReturn");
	spMoveSpeedText->SetFontName(L"EternalReturn");
	spAttackSpeedText->SetFontName(L"EternalReturn");

	spAttackPowerText->SetPriority(7);
	spDefenseText->SetPriority(7);
	spIncreaseAttackDamageText->SetPriority(7);
	spAttackDamageReductionText->SetPriority(7);
	spSkillAmpRatioText->SetPriority(7);
	spSkillDamageReducitonText->SetPriority(7);
	spMoveSpeedText->SetPriority(7);
	spAttackSpeedText->SetPriority(7);

	spAttackPowerText->SetCharacterStatusType(ECharacterStatusType::ATTACK_POWER);
	spDefenseText->SetCharacterStatusType(ECharacterStatusType::DEFENSE);
	spIncreaseAttackDamageText->SetCharacterStatusType(ECharacterStatusType::INCREASE_BASIC_ATTACK_DAMAGE_RATIO);
	spAttackDamageReductionText->SetCharacterStatusType(ECharacterStatusType::NORMAL_ATTACK_DAMAGE_REDUCTION);
	spSkillAmpRatioText->SetCharacterStatusType(ECharacterStatusType::SKILL_AMP_RATIO);
	spSkillDamageReducitonText->SetCharacterStatusType(ECharacterStatusType::SKILL_DAMAGE_REDUCTION);
	spMoveSpeedText->SetCharacterStatusType(ECharacterStatusType::MOVE_SPEED_RATIO);
	spAttackSpeedText->SetCharacterStatusType(ECharacterStatusType::ATTACK_SPEED_RATIO);

	AddUI(L"AttackPowerText", spAttackPowerText);
	AddUI(L"spDefenseText", spDefenseText);
	AddUI(L"IncreaseAttackDamageText", spIncreaseAttackDamageText);
	AddUI(L"AttackDamageReductionText", spAttackDamageReductionText);
	AddUI(L"SkillAmpRatioText", spSkillAmpRatioText);
	AddUI(L"SkillDamageReducitonText", spSkillDamageReducitonText);
	AddUI(L"MoveSpeedText", spMoveSpeedText);
	AddUI(L"AttackSpeedText", spAttackSpeedText);

	// 장비 이미지 6장
	shared_ptr<CEquipSlotImage> spWeaponSlotImage = spLevel->CreateUI<CEquipSlotImage>(L"WeaponSlotImage");
	shared_ptr<CEquipSlotImage> spArmorSlotImage = spLevel->CreateUI<CEquipSlotImage>(L"ArmorSlotImage");
	shared_ptr<CEquipSlotImage> spHeadSlotImage = spLevel->CreateUI<CEquipSlotImage>(L"HeadSlotImage");
	shared_ptr<CEquipSlotImage> spArmSlotImage = spLevel->CreateUI<CEquipSlotImage>(L"ArmSlotImage");
	shared_ptr<CEquipSlotImage> spLegSlotImage = spLevel->CreateUI<CEquipSlotImage>(L"LegSlotImage");
	shared_ptr<CEquipSlotImage> spDecoSlotImage = spLevel->CreateUI<CEquipSlotImage>(L"DecoSlotImage");

	spWeaponSlotImage->SetPriority(10);
	spArmorSlotImage->SetPriority(10);
	spHeadSlotImage->SetPriority(10);
	spArmSlotImage->SetPriority(10);
	spLegSlotImage->SetPriority(10);
	spDecoSlotImage->SetPriority(10);

	spWeaponSlotImage->SetEquipSlotType(EEquipSlotType::WEAPON);
	spArmorSlotImage->SetEquipSlotType(EEquipSlotType::ARMOR);
	spHeadSlotImage->SetEquipSlotType(EEquipSlotType::HEAD);
	spArmSlotImage->SetEquipSlotType(EEquipSlotType::ARM);
	spLegSlotImage->SetEquipSlotType(EEquipSlotType::LEG);
	spDecoSlotImage->SetEquipSlotType(EEquipSlotType::DECO);

	AddUI(L"WeaponSlotImage", spWeaponSlotImage);
	AddUI(L"ArmorSlotImage", spArmorSlotImage);
	AddUI(L"HeadSlotImage", spHeadSlotImage);
	AddUI(L"ArmSlotImage", spArmSlotImage);
	AddUI(L"LegSlotImage", spLegSlotImage);
	AddUI(L"DecoSlotImage", spDecoSlotImage);

	m_arrEquipImages[(int32)EEquipSlotType::WEAPON] = spWeaponSlotImage;
	m_arrEquipImages[(int32)EEquipSlotType::ARMOR] = spArmorSlotImage;
	m_arrEquipImages[(int32)EEquipSlotType::HEAD] = spHeadSlotImage;
	m_arrEquipImages[(int32)EEquipSlotType::ARM] = spArmSlotImage;
	m_arrEquipImages[(int32)EEquipSlotType::LEG] = spLegSlotImage;
	m_arrEquipImages[(int32)EEquipSlotType::DECO] = spDecoSlotImage;

	// 아이템 버튼 6개
	shared_ptr<CItemButton> spFirstEquipButton = spLevel->CreateUI<CItemButton>(L"FirstEquipButton");
	shared_ptr<CItemButton> spSecondEquipButton = spLevel->CreateUI<CItemButton>(L"SecondEquipButton");
	shared_ptr<CItemButton> spThirdEquipButton = spLevel->CreateUI<CItemButton>(L"ThirdEquipButton");
	shared_ptr<CItemButton> spFourthEquipButton = spLevel->CreateUI<CItemButton>(L"FourthEquipButton");
	shared_ptr<CItemButton> spFifthEquipButton = spLevel->CreateUI<CItemButton>(L"FifthEquipButton");
	shared_ptr<CItemButton> spSixthEquipButton = spLevel->CreateUI<CItemButton>(L"SixthEquipButton");

	spFirstEquipButton->SetPriority(5);
	spSecondEquipButton->SetPriority(5);
	spThirdEquipButton->SetPriority(5);
	spFourthEquipButton->SetPriority(5);
	spFifthEquipButton->SetPriority(5);
	spSixthEquipButton->SetPriority(5);

	spFirstEquipButton->SetItemBelongType(EItemBelongType::EQUIPMENT);
	spSecondEquipButton->SetItemBelongType(EItemBelongType::EQUIPMENT);
	spThirdEquipButton->SetItemBelongType(EItemBelongType::EQUIPMENT);
	spFourthEquipButton->SetItemBelongType(EItemBelongType::EQUIPMENT);
	spFifthEquipButton->SetItemBelongType(EItemBelongType::EQUIPMENT);
	spSixthEquipButton->SetItemBelongType(EItemBelongType::EQUIPMENT);

	spFirstEquipButton->SetItemSlotType(EItemSlotType::FIRST);
	spSecondEquipButton->SetItemSlotType(EItemSlotType::SECOND);
	spThirdEquipButton->SetItemSlotType(EItemSlotType::THIRD);
	spFourthEquipButton->SetItemSlotType(EItemSlotType::FOURTH);
	spFifthEquipButton->SetItemSlotType(EItemSlotType::FIFTH);
	spSixthEquipButton->SetItemSlotType(EItemSlotType::SIXTH);

	m_arrEquipButtons[(int32)EItemSlotType::FIRST] = spFirstEquipButton;
	m_arrEquipButtons[(int32)EItemSlotType::SECOND] = spSecondEquipButton;
	m_arrEquipButtons[(int32)EItemSlotType::THIRD] = spThirdEquipButton;
	m_arrEquipButtons[(int32)EItemSlotType::FOURTH] = spFourthEquipButton;
	m_arrEquipButtons[(int32)EItemSlotType::FIFTH] = spFifthEquipButton;
	m_arrEquipButtons[(int32)EItemSlotType::SIXTH] = spSixthEquipButton;

	AddUI(L"FirstEquipButton", spFirstEquipButton);
	AddUI(L"SecondEquipButton", spSecondEquipButton);
	AddUI(L"ThirdEquipButton", spThirdEquipButton);
	AddUI(L"FourthEquipButton", spFourthEquipButton);
	AddUI(L"FifthEquipButton", spFifthEquipButton);
	AddUI(L"SixthEquipButton", spSixthEquipButton);

	return S_OK;
}

HRESULT Client::CStatusPanel::BeginPlay()
{
	if (FAILED(CPanel::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Client::CStatusPanel::PreTick(float _fDeltaSeconds)
{
	switch (CPanel::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CStatusPanel::Tick(float _fDeltaSeconds)
{
	switch (CPanel::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CStatusPanel::PostTick(float _fDeltaSeconds)
{
	switch (CPanel::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Client::CStatusPanel::EndPlay()
{
	if (FAILED(CPanel::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Client::CStatusPanel::Render()
{
	CPanel::Render();
}

void Client::CStatusPanel::Release()
{
	CPanel::Release();
}

void Client::CStatusPanel::SetEquipment(const std::shared_ptr<CItem>& _spItem, int32 _iSlot)
{
	if (_iSlot < 0 || _iSlot >= m_arrEquipImages.size()) { return; }

	m_arrEquipImages[_iSlot].lock()->SetItem(_spItem);
	m_arrEquipButtons[_iSlot].lock()->SetItem(_spItem);
}
