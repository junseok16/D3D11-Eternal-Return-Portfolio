#include "pch.h"
#include "Survivor.h"

// component
#include "StateComponent.h"
#include "CameraComponent.h"
#include "InputComponent.h"
#include "NavigationComponent.h"
#include "SurvivorStateComponent.h"
#include "SphereComponent.h"
#include "LightComponent.h"

// controller
#include "Controller.h"

#include "Inventory.h"
#include "ItemBox.h"
#include "Collectible.h"
#include "Console.h"

// manager
#include "GameManager.h"

// wild animal
#include "WildAnimal.h"

HRESULT Editor::CSurvivor::PreInitialize()
{
	return CCharacter::PreInitialize();
}

HRESULT Editor::CSurvivor::Initialize()
{
	if (FAILED(CCharacter::Initialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Editor::CSurvivor::PostInitialize()
{
	if (FAILED(CCharacter::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Editor::CSurvivor::BeginPlay()
{
	if (!m_bPosessed) { return S_OK; }

	if (FAILED(CCharacter::BeginPlay())) { return E_FAIL; }

	shared_ptr<CInputComponent> spInputComponent = m_wpController.lock()->GetInputComponent();

	// 키보드
	spInputComponent->MapKeyAxis(L"MoveForward", DIK_W, 1);
	spInputComponent->BindKeyAxis(L"MoveForward", static_pointer_cast<CSurvivor>(shared_from_this()), &CSurvivor::MoveForward);

	spInputComponent->MapKeyAxis(L"MoveBackward", DIK_S, -1);
	spInputComponent->BindKeyAxis(L"MoveBackward", static_pointer_cast<CSurvivor>(shared_from_this()), &CSurvivor::MoveBackward);

	spInputComponent->MapKeyAxis(L"MoveRight", DIK_D, 1);
	spInputComponent->BindKeyAxis(L"MoveRight", static_pointer_cast<CSurvivor>(shared_from_this()), &CSurvivor::MoveRight);

	spInputComponent->MapKeyAxis(L"MoveLeft", DIK_A, -1);
	spInputComponent->BindKeyAxis(L"MoveLeft", static_pointer_cast<CSurvivor>(shared_from_this()), &CSurvivor::MoveLeft);

	spInputComponent->MapKeyAction(L"ChangeToFirstSurvivor", DIK_F1);
	spInputComponent->BindKeyAction(L"ChangeToFirstSurvivor", static_pointer_cast<CSurvivor>(shared_from_this()), &CSurvivor::ChangeToFirstSurvivor);

	spInputComponent->MapKeyAction(L"ChangeToSecondSurvivor", DIK_F2);
	spInputComponent->BindKeyAction(L"ChangeToSecondSurvivor", static_pointer_cast<CSurvivor>(shared_from_this()), &CSurvivor::ChangeToSecondSurvivor);

	spInputComponent->MapKeyAction(L"ChangeToThirdSurvivor", DIK_F3);
	spInputComponent->BindKeyAction(L"ChangeToThirdSurvivor", static_pointer_cast<CSurvivor>(shared_from_this()), &CSurvivor::ChangeToThirdSurvivor);

	return S_OK;
}

int32 Editor::CSurvivor::PreTick(float _fDeltaSeconds)
{
	if (!m_bPosessed) { return 0; }

	switch (CCharacter::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	m_vCurDirection = Vector3::Zero;
	m_iDirectionFlag = 0;
	m_fDeltaSeconds = _fDeltaSeconds;

	// 쿨다운 시간을 감소시킵니다.
	for (size_t iIndex = 0; iIndex < m_vecCurSkillCoolDown.size(); ++iIndex)
	{
		if (0.0f < m_vecCurSkillCoolDown[iIndex])
		{
			m_vecCurSkillCoolDown[iIndex] -= _fDeltaSeconds;

			if (m_vecCurSkillCoolDown[iIndex] < 0.0f)
			{
				m_vecCurSkillCoolDown[iIndex] = 0.0f;
			}
		}
	}
	
	return 0;
}

int32 Editor::CSurvivor::Tick(float _fDeltaSeconds)
{
	// 기본 체력 재생
	m_fSumHPRegeneration += _fDeltaSeconds;
	
	if (m_fSumHPRegeneration >= 0.5f)
	{
		m_fSumHPRegeneration = 0.0f;
		m_fCurHP += m_arrHPRegenerations[m_iCurSurvivorLevel];

		if (m_arrMaxHPs[m_iCurSurvivorLevel] < m_fCurHP)
		{
			m_fCurHP = m_arrMaxHPs[m_iCurSurvivorLevel];
		}
	}

	// 기본 스태미나 재생
	m_fSumSPRegeneration += _fDeltaSeconds;

	if (m_fSumSPRegeneration >= 0.5f)
	{
		m_fSumSPRegeneration = 0.0f;
		m_fCurSP += m_arrSPRegenerations[m_iCurSurvivorLevel];

		if (m_arrMaxSPs[m_iCurSurvivorLevel] < m_fCurSP)
		{
			m_fCurSP = m_arrMaxSPs[m_iCurSurvivorLevel];
		}
	}

	// 음료 스태미나 재생
	if (m_fCurLerpHP)
	{
		m_fSumLerpHPSeconds += _fDeltaSeconds;

		if (m_fSumLerpHPSeconds >= 0.5f)
		{
			m_fSumLerpHPSeconds = 0.0f;
			m_fCurLerpHP -= 30.0f;

			if (m_fCurLerpHP <= 0.0f)
			{
				AddCurSP(m_fCurLerpHP + 15.0f);
				m_fCurLerpHP = 0.0f;
			}
			else
			{
				AddCurHP(15.0f);
			}
		}
	}

	// 음식 체력 재생
	if (m_fCurLerpSP)
	{
		m_fSumLerpSPSeconds += _fDeltaSeconds;

		if (m_fSumLerpSPSeconds >= 0.5f)
		{
			m_fSumLerpSPSeconds = 0.0f;
			m_fCurLerpSP -= 15.0f;

			if (m_fCurLerpSP <= 0.0f)
			{
				AddCurSP(m_fCurLerpSP + 15.0f);
				m_fCurLerpSP = 0.0f;
			}
			else
			{
				AddCurSP(15.0f);
			}
		}
	}

	if (!m_bPosessed) { return 0; }

	switch (CCharacter::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Editor::CSurvivor::PostTick(float _fDeltaSeconds)
{
	if (!m_bPosessed) { return 0; }

	switch (CCharacter::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	MoveSurvivor(_fDeltaSeconds);
	return 0;
}

HRESULT Editor::CSurvivor::EndPlay()
{
	if (FAILED(CCharacter::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Editor::CSurvivor::Render()
{
	if (!m_bPosessed) { return; }

	CCharacter::Render();
}

void Editor::CSurvivor::Release()
{
	if (m_spInventory)
	{
		m_spInventory->Release();
		m_spInventory = nullptr;
	}
	
	CCharacter::Release();
}

HRESULT Editor::CSurvivor::CreateInventory(const std::shared_ptr<CItemPanel>& _spItemPanel, const std::shared_ptr<CStatusPanel>& _spStatusPanel)
{
	// 인벤토리를 생성합니다.
	m_spInventory = CInventory::Create();
	m_spInventory->SetItemPanel(_spItemPanel);
	m_spInventory->SetStatusPanel(_spStatusPanel);
	return S_OK;
}

void Editor::CSurvivor::MoveSurvivor(float _fDeltaSeconds)
{
	if (m_wpCameraComponent.lock()->GetCameraType() == ECameraType::FIRST_PERSON)
	{
		Vector3 vCameraForward = m_wpCameraComponent.lock()->GetCameraForwardVector();
		vCameraForward.y = 0.0f;
		vCameraForward.Normalize();

		Vector3 vPosition = GetActorLocalPosition().value();
		LookAt(vPosition + vCameraForward);
	}

	if (m_vCurDirection == Vector3::Zero)
	{
		m_fSumLerpSeconds = 0.0f;
		return;
	}

	switch (m_wpCameraComponent.lock()->GetCameraType())
	{
	case ECameraType::THIRD_PERSON:
		MoveAsTPS(_fDeltaSeconds);
		break;

	case ECameraType::FIRST_PERSON:
		MoveAsFPS(_fDeltaSeconds);
		break;

	default:
		CHECKF(false, L"Camera type is not designated.")
		break;
	}
}

void Editor::CSurvivor::MoveForward(int32 _iValue)
{
	m_vCurDirection.x = 1;
}

void Editor::CSurvivor::MoveBackward(int32 _iValue)
{
	m_vCurDirection.x = -1;
}

void Editor::CSurvivor::MoveRight(int32 _iValue)
{
	m_vCurDirection.z = 1;
}

void Editor::CSurvivor::MoveLeft(int32 _iValue)
{
	m_vCurDirection.z = -1;
}

bool Editor::CSurvivor::ChangeToFirstSurvivor()
{
	CGameManager::GetInstance()->ChangeSurvivor(L"FirstSurvivor");
	return false;
}

bool Editor::CSurvivor::ChangeToSecondSurvivor()
{
	CGameManager::GetInstance()->ChangeSurvivor(L"SecondSurvivor");
	return false;
}

bool Editor::CSurvivor::ChangeToThirdSurvivor()
{
	CGameManager::GetInstance()->ChangeSurvivor(L"ThirdSurvivor");
	return false;
}

void Editor::CSurvivor::OnCollisionEnter(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
	switch (_spDst->GetCollisionLayer())
	{
	case ECollisionLayer::MONSTER:
		m_wpCurWildAnimal = dynamic_pointer_cast<CWildAnimal>(_spDst->GetOwnerActor());
		break;

	case ECollisionLayer::ITEM:
		m_wpCurItemBox = dynamic_pointer_cast<CItemBox>(_spDst->GetOwnerActor());
		break;

	case ECollisionLayer::ENVIRONMENT:
	{
		// m_wpCurCollectible = dynamic_pointer_cast<CCollectible>(_spDst->GetOwnerActor());
		// m_eCurCollectibleType = m_wpCurCollectible.lock()->GetCollectibleType();
	}
	break;

	case ECollisionLayer::STRUCTURE:
	{
		// m_wpCurConsole = dynamic_pointer_cast<CConsole>(_spDst->GetOwnerActor());
		// m_eCurConsoleType = m_wpCurConsole.lock()->GetConsoleType();
	}
	break;

	case ECollisionLayer::BOUNDARY:
		break;

	default:
		break;
	}
}

void Editor::CSurvivor::OnCollisionStay(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
	
}

void Editor::CSurvivor::OnCollisionExit(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
	switch (_spDst->GetCollisionLayer())
	{
	case ECollisionLayer::MONSTER:
	{
		if (m_wpCurWildAnimal.expired()) { break; }

		if (m_wpCurWildAnimal.lock() == dynamic_pointer_cast<CWildAnimal>(_spDst->GetOwnerActor()))
		{
			if (m_wpCurWildAnimal.lock()->IsOpened())
			{
				m_wpCurWildAnimal.lock()->CloseItemBox();
			}
			m_wpCurWildAnimal.reset();
		}
	}
	break;

	case ECollisionLayer::ITEM:
		if (m_wpCurItemBox.lock() == dynamic_pointer_cast<CItemBox>(_spDst->GetOwnerActor()))
		{
			if (m_wpCurItemBox.lock()->IsOpened())
			{
				m_wpCurItemBox.lock()->CloseItemBox();
			}
			m_wpCurItemBox.reset();
		}
		break;

	case ECollisionLayer::ENVIRONMENT:
		if (m_wpCurCollectible.lock() == dynamic_pointer_cast<CCollectible>(_spDst->GetOwnerActor()))
		{
			m_wpCurCollectible.reset();
			m_eCurCollectibleType = ECollectibleType::ENUM_END;
		}
		break;

	case ECollisionLayer::STRUCTURE:
		if (m_wpCurConsole.lock() == dynamic_pointer_cast<CConsole>(_spDst->GetOwnerActor()))
		{
			m_wpCurConsole.reset();
			m_eCurConsoleType = EConsoleType::ENUM_END;
		}
		break;
		
	case ECollisionLayer::BOUNDARY:
		break;

	default:
		break;
	}
}

bool Editor::CSurvivor::IsSkillValid(ESkillType _eSkillType)
{
	if (m_arrCurSkillLevels[(int32)_eSkillType] == -1) { return false; }

	float fStaminaConsumption = GetStaminaConsumption(_eSkillType);
	if (m_fCurSP < fStaminaConsumption) { return false; }

	if (0.0f < m_vecCurSkillCoolDown[(int32)_eSkillType]) { return false; }

	m_vecCurSkillCoolDown[(int32)_eSkillType] = m_vecMaxSkillCoolDown[(int32)_eSkillType][m_arrCurSkillLevels[(int32)_eSkillType]];
	m_fCurSP -= fStaminaConsumption;
	return true;
}

ESurvivorState Editor::CSurvivor::GetSurvivorState() const
{
	return m_wpSurvivorStateComponent.lock()->GetSurvivorState();
}

void Editor::CSurvivor::AddLerpHP(float _fHP)
{
	m_fCurLerpHP = _fHP;
}

void Editor::CSurvivor::AddLerpSP(float _fSP)
{
	m_fCurLerpSP = _fSP;
}

void Editor::CSurvivor::AddCurHP(float _fHP)
{
	m_fCurHP += _fHP;
	if (m_arrMaxHPs[m_iCurSurvivorLevel] < m_fCurHP)
	{
		m_fCurHP = m_arrMaxHPs[m_iCurSurvivorLevel];
	}
}

void Editor::CSurvivor::AddCurSP(float _fSP)
{
	m_fCurSP += _fSP;
	if (m_arrMaxSPs[m_iCurSurvivorLevel] < m_fCurSP)
	{
		m_fCurSP = m_arrMaxSPs[m_iCurSurvivorLevel];
	}
}

void Editor::CSurvivor::AddCurExp(float _fExp)
{
	// 최대 레벨인 경우
	if (m_iCurSurvivorLevel == m_iMaxSurvivorLevel)
	{
		return;
	}

	m_fCurExp += _fExp;
	if (m_arrMaxExps[m_iCurSurvivorLevel] < m_fCurExp)
	{
		m_fCurExp = m_fCurExp - m_arrMaxExps[m_iCurSurvivorLevel];

		m_iCurSurvivorLevel++;
		if (m_iMaxSurvivorLevel < m_iCurSurvivorLevel)
		{
			m_iCurSurvivorLevel = m_iMaxSurvivorLevel;
			m_fCurExp = m_arrMaxHPs[m_iCurSurvivorLevel];
		}
		else
		{
			m_fCurHP = m_arrMaxHPs[m_iCurSurvivorLevel];
			m_iCurSkillPoint += 1;
		}
	}
}

float Editor::CSurvivor::GetStaminaConsumption(ESkillType _eSkillType) const
{
	int32 iSkillLevel = m_arrCurSkillLevels[(uint32)_eSkillType];

	if (iSkillLevel < 0) { return 0.0f; }

	return m_arrSkillInfos[(uint32)_eSkillType].m_vecStamina[iSkillLevel];
}

void Editor::CSurvivor::SetSurvivorState(ESurvivorState _eSurvivorState)
{
	m_wpSurvivorStateComponent.lock()->SetServivorState(_eSurvivorState);
}

void Editor::CSurvivor::MoveAsTPS(float _fDeltaSeconds)
{
	Vector3 vCameraForward = m_wpCameraComponent.lock()->GetCameraForwardVector();
	vCameraForward.y = 0.0f;
	vCameraForward.Normalize();

	Vector3 vCameraRight = m_wpCameraComponent.lock()->GetCameraRightVector();
	vCameraRight.y = 0.0f;
	vCameraRight.Normalize();

	m_vCurDirection.Normalize();
	vCameraForward *= m_vCurDirection.x;
	vCameraRight *= m_vCurDirection.z;

	Vector3 vDirection = vCameraForward + vCameraRight;
	vDirection.Normalize();

	if (m_vPreDirection != m_vCurDirection)
	{
		Vector3 vForward = GetActorWorldForwardVector().value();
		vForward.Normalize();

		if (0 <= vForward.Dot(vDirection))
		{
			m_fSumLerpSeconds += _fDeltaSeconds;
			if (m_fMaxLerpSeconds <= m_fSumLerpSeconds)
			{
				m_vPreDirection = m_vCurDirection;
				m_fSumLerpSeconds = 0.0f;
			}

			float fRatio = m_fSumLerpSeconds / m_fMaxLerpSeconds;
			vDirection = Vector3::Lerp(vForward, vDirection, fRatio);
		}
	}

	Vector3 vPosition = GetActorLocalPosition().value();
	LookAt(vPosition + vDirection);

	// 플레이어의 로컬 좌표는 월드 좌표와 같으므로 로컬 좌표를 전달합니다.
	Vector3 vTargetPosition = vPosition + vDirection * _fDeltaSeconds * m_fCurMoveSpeed;
	
	Vector3 vWorldPosition = Vector3::Zero;
	if (!m_wpNavigationComponent.lock()->IsValidCell(vTargetPosition, vWorldPosition))
	{
		return;
	}

	SetActorLocalPosition(vWorldPosition);
}

void Editor::CSurvivor::MoveAsFPS(float _fDeltaSeconds)
{
	Vector3 vCameraForward = m_wpCameraComponent.lock()->GetCameraForwardVector();
	vCameraForward.y = 0.0f;
	vCameraForward.Normalize();

	Vector3 vCameraRight = m_wpCameraComponent.lock()->GetCameraRightVector();
	vCameraRight.y = 0.0f;
	vCameraRight.Normalize();

	m_vCurDirection.Normalize();
	vCameraForward *= m_vCurDirection.x;
	vCameraRight *= m_vCurDirection.z;

	Vector3 vDirection = vCameraForward + vCameraRight;
	vDirection.Normalize();

	Vector3 vPosition = GetActorLocalPosition().value();
	// 플레이어의 로컬 좌표는 월드 좌표와 같으므로 로컬 좌표를 전달합니다.
	Vector3 vTargetPosition = vPosition + vDirection * _fDeltaSeconds * m_fCurMoveSpeed;
	Vector3 vWorldPosition = Vector3::Zero;
	if (!m_wpNavigationComponent.lock()->IsValidCell(vTargetPosition, vWorldPosition)) { return; }

	SetActorLocalPosition(vWorldPosition);
}

const Vector3& Editor::CSurvivor::GetCameraCenter()
{
	return m_wpCameraComponent.lock()->GetCurCameraCenter();
}

void Editor::CSurvivor::SetCameraCenter(const Vector3& _vCenter)
{
	m_wpCameraComponent.lock()->SetCurCameraCenter(_vCenter);
}

int32 Editor::CSurvivor::GetCurCellIndex()
{
	return m_wpNavigationComponent.lock()->GetCurCellIndex();
}

Vector3 Editor::CSurvivor::GetCurCentroidPosition()
{
	int32 iCellIndex = GetCurCellIndex();
	return m_wpNavigationComponent.lock()->GetCentroidPosition(iCellIndex);
}

void Editor::CSurvivor::SetCurCellIndex(int32 _iCellIndex)
{
	m_wpNavigationComponent.lock()->SetCurCellIndex(_iCellIndex);
}

void Editor::CSurvivor::SetCentroidPosition(const Vector3& _vCentroidPosition)
{
	SetActorLocalPosition(_vCentroidPosition);
}

float Editor::CSurvivor::GetCurAzimuthRadian() const
{
	return m_wpCameraComponent.lock()->GetCurAzimuthRadian();
}

void Editor::CSurvivor::SetCurAzimuthRadian(float _fAzimuthRadian)
{
	m_wpCameraComponent.lock()->SetCurAzimuthRadian(_fAzimuthRadian);
}

float Editor::CSurvivor::GetCurElevationRadian() const
{
	return m_wpCameraComponent.lock()->GetCurElevationRadian();
}

void Editor::CSurvivor::SetCurElevationRadian(float _fElevationRadian)
{
	m_wpCameraComponent.lock()->SetCurElevationRadian(_fElevationRadian);
}
