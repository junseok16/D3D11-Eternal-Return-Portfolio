#include "pch.h"
#include "GameManager.h"

#include "World.h"
#include "Level.h"
#include "Controller.h"
#include "Inventory.h"
#include "Survivor.h"
#include "StateComponent.h"

IMPLEMENT_SINGLETON(CGameManager)

HRESULT Editor::CGameManager::Initialize()
{
	return S_OK;
}

HRESULT Editor::CGameManager::PostInitialize()
{
	m_wpController = CWorld::GetInstance()->GetCurLevel()->GetController();
	m_wpCurSurvivor = dynamic_pointer_cast<CSurvivor>(m_wpController.lock()->GetPawn());
	return S_OK;
}

int32 Editor::CGameManager::Tick(float _fDeltaSeconds)
{
	m_fDeltaSeconds = _fDeltaSeconds;
	TickDay(_fDeltaSeconds);
	return 0;
}

void Editor::CGameManager::Release()
{
	// 싱글턴 매니저를 메모리에서 해제합니다.
	m_spInstance = nullptr;
}

void Editor::CGameManager::TickDay(float _fDeltaSeconds)
{
	switch (m_eDayType)
	{
	case Editor::EDayType::DAY:
	{
		m_fSumDayDeltaSeconds += _fDeltaSeconds;

		if (m_fSumDayDeltaSeconds >= m_fMaxDayDeltaSeconds)
		{
			m_fSumDayDeltaSeconds = 0.0f;
			m_eDayType = EDayType::NIGHT;
		}
	}
	break;

	case Editor::EDayType::NIGHT:
	{
		m_fSumNightDeltaSeconds += _fDeltaSeconds;

		if (m_fSumNightDeltaSeconds >= m_fMaxNightDeltaSeconds)
		{
			m_fSumNightDeltaSeconds = 0.0f;
			m_eDayType = EDayType::DAY;
		}
	}
	break;
	}
}

void Editor::CGameManager::ChangeSurvivor(const wstring& _wstrSurvivorName)
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
}

void Editor::CGameManager::AddSurvivor(const wstring& _wstrSurvivorName, const std::shared_ptr<CSurvivor>& _spSurvivor)
{
	if (m_umapSurvivors.find(_wstrSurvivorName) != m_umapSurvivors.end()) { return; }

	m_umapSurvivors.insert({ _wstrSurvivorName, _spSurvivor });
}
