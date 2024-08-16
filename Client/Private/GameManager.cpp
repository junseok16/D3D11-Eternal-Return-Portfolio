#include "pch.h"
#include "GameManager.h"

#include "CameraManager.h"
#include "LightManager.h"
#include "CameraManager.h"
#include "EngineModule.h"

#include "World.h"
#include "Level.h"
#include "Controller.h"
#include "Inventory.h"
#include "Survivor.h"

#include "StateComponent.h"
#include "CameraComponent.h"

#include "Wickline.h"
#include "Alpha.h"
#include "Omega.h"

#include "MathUtility.h"

#include "SoundHandler.h"

IMPLEMENT_SINGLETON(CGameManager)

HRESULT Client::CGameManager::Initialize()
{
	return S_OK;
}

HRESULT Client::CGameManager::PostInitialize()
{
	m_wpCurLevel = CWorld::GetInstance()->GetCurLevel();

	m_wpLightManager = CWorld::GetInstance()->GetEngineModule()->GetLightManager();
	m_wpCameraManager = CWorld::GetInstance()->GetEngineModule()->GetCameraManager();

	m_wpController = m_wpCurLevel.lock()->GetController();
	m_wpCurSurvivor = dynamic_pointer_cast<CSurvivor>(m_wpController.lock()->GetPawn());

	m_wpSoundHandler = CSoundHandler::GetInstance();

	int32 iIndex = CMathUtility::GetRandomInteger(0, 9);
	m_wpSoundHandler.lock()->PlaySoundEx(m_arrAreaSounds[iIndex], ESoundType::BGM_01, 1.0f, false);
	return S_OK;
}

int32 Client::CGameManager::Tick(float _fDeltaSeconds)
{
	m_fDeltaSeconds = _fDeltaSeconds;
	TickDay(_fDeltaSeconds);


	if (!m_wpAlpha.expired())
	{
		if (m_bAlphaCamera)
		{
			if (m_wpAlpha.lock()->GetCameraComponent()->IsCameraWalkFinished())
			{
				m_fCameraDelay += _fDeltaSeconds;

				if (2.0f <= m_fCameraDelay)
				{
					m_bAlphaCamera = false;
					m_fCameraDelay = 0.0f;
					m_wpCurSurvivor.lock()->GetCameraComponent()->SetThisCameraOnAir();
				}
			}
		}
	}



	if (!m_wpWickline.expired())
	{
		if (m_bWicklineCamera)
		{
			if (m_wpWickline.lock()->GetCameraComponent()->IsCameraWalkFinished())
			{
				m_fCameraDelay += _fDeltaSeconds;

				if (2.0f <= m_fCameraDelay)
				{
					m_fCameraDelay = 0.0f;
					m_wpCurSurvivor.lock()->GetCameraComponent()->SetThisCameraOnAir();
				}
			}
		}
	}
	return 0;
}

void Client::CGameManager::Release()
{
	// 싱글턴 매니저를 메모리에서 해제합니다.
	m_spInstance = nullptr;
}

void Client::CGameManager::TickDay(float _fDeltaSeconds)
{
	switch (m_eDayType)
	{
	case Client::EDayType::DAY:
	{
		m_fSumDayDeltaSeconds += _fDeltaSeconds;

		if (m_fSumDayDeltaSeconds >= m_fMaxDayDeltaSeconds)
		{
			m_fSumDayDeltaSeconds = 0.0f;
			m_eDayType = EDayType::NIGHT;
			m_iSumNight++;

			int32 iIndex = CMathUtility::GetRandomInteger(0, 9);
			m_wpSoundHandler.lock()->PlaySoundEx(m_arrAreaSounds[iIndex], ESoundType::BGM_01, 1.0f, false);

			if (m_iSumNight == 1)
			{
				CreateBoss(EBossType::ALPHA);
			}
			if (m_iSumNight == 2)
			{
				CreateBoss(EBossType::WICKLINE);
			}
		}
	}
	break;

	case Client::EDayType::NIGHT:
	{
		m_fSumNightDeltaSeconds += _fDeltaSeconds;

		if (m_fSumNightDeltaSeconds >= m_fMaxNightDeltaSeconds)
		{
			m_fSumNightDeltaSeconds = 0.0f;
			m_eDayType = EDayType::DAY;
			m_iSumDay++;

			int32 iIndex = CMathUtility::GetRandomInteger(0, 9);
			m_wpSoundHandler.lock()->PlaySoundEx(m_arrAreaSounds[iIndex], ESoundType::BGM_01, 1.0f, false);
		}
	}
	break;
	}
}

void Client::CGameManager::ChangeSurvivor(const wstring& _wstrSurvivorName)
{
	// 현재 생존자가 있는 셀 인덱스
	int32 iCellIndex = m_wpCurSurvivor.lock()->GetCurCellIndex();

	// 현재 생존자가 있는 위치
	Matrix vWorldMatrix = m_wpCurSurvivor.lock()->GetActorWorldMatrix().value();

	float fAzimuthRadian = m_wpCurSurvivor.lock()->GetCurAzimuthRadian();
	float fElevationRadian = m_wpCurSurvivor.lock()->GetCurElevationRadian();
	Vector3 vCenter = m_wpCurSurvivor.lock()->GetCameraCenter();

	m_wpController.lock()->UnPossess();
	m_wpController.lock()->Possess(m_umapSurvivors[_wstrSurvivorName].lock());

	m_wpCurSurvivor = m_umapSurvivors[_wstrSurvivorName].lock();
	m_wpCurSurvivor.lock()->BeginPlay();
	m_wpCurSurvivor.lock()->SetCurCellIndex(iCellIndex);

	m_wpCurSurvivor.lock()->SetActorLocalMatrix(vWorldMatrix);

	// 인벤토리를 초기화합니다.
	m_wpCurSurvivor.lock()->GetInventory()->RefreshItemPanel();
	m_wpCurSurvivor.lock()->GetInventory()->RefreshStatusPanel();

	m_wpCurSurvivor.lock()->SetCurAzimuthRadian(fAzimuthRadian);
	m_wpCurSurvivor.lock()->SetCurElevationRadian(fElevationRadian);
	m_wpCurSurvivor.lock()->SetCameraCenter(vCenter);

	m_wpCurSurvivor.lock()->SetSurvivorState(ESurvivorState::ARRIVE);
	m_wpCurSurvivor.lock()->SetOnAir(true);
	m_wpCurSurvivor.lock()->PreTick(m_fDeltaSeconds);
	
	string strIndex = to_string(CMathUtility::GetRandomInteger(1, 3));

	switch (m_wpCurSurvivor.lock()->GetSurvivorType())
	{
	case ESurvivorType::HYUNWOO:
		m_wpCurSurvivor.lock()->PlaySoundEx("Hyunwoo_firstMove_" + strIndex + "_ko", ESoundType::TALK_01);
		break;

	case ESurvivorType::AYA:
		m_wpCurSurvivor.lock()->PlaySoundEx("Aya_firstMove_"+ strIndex +"_ko", ESoundType::TALK_01);
		break;

	default:
		break;
	}
	
}

void Client::CGameManager::AddSurvivor(const wstring& _wstrSurvivorName, const std::shared_ptr<CSurvivor>& _spSurvivor)
{
	if (m_umapSurvivors.find(_wstrSurvivorName) != m_umapSurvivors.end()) { return; }

	m_umapSurvivors.insert({ _wstrSurvivorName, _spSurvivor });
}

shared_ptr<CBoss> Client::CGameManager::CreateBoss(EBossType _eBossType)
{
	switch (_eBossType)
	{
	case Client::EBossType::WICKLINE:
		m_wpWickline = m_wpCurLevel.lock()->CreateActor<CWickline>(L"Wickline");
		m_wpWickline.lock()->PreInitialize();
		m_wpWickline.lock()->Initialize();
		m_wpWickline.lock()->PostInitialize();
		m_wpWickline.lock()->BeginPlay();
		return m_wpWickline.lock();

	case Client::EBossType::ALPHA:
		m_wpAlpha = m_wpCurLevel.lock()->CreateActor<CAlpha>(L"Alpha");
		m_wpAlpha.lock()->PreInitialize();
		m_wpAlpha.lock()->Initialize();
		m_wpAlpha.lock()->PostInitialize();
		m_wpAlpha.lock()->BeginPlay();
		return m_wpAlpha.lock();

	case Client::EBossType::OMEGA:
		m_wpOmega = m_wpCurLevel.lock()->CreateActor<COmega>(L"Omega");
		m_wpOmega.lock()->PreInitialize();
		m_wpOmega.lock()->Initialize();
		m_wpOmega.lock()->PostInitialize();
		m_wpOmega.lock()->BeginPlay();
		return m_wpOmega.lock();

	default:
		break;
	}
	return nullptr;
}
