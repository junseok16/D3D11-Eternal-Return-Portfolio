// default
#include "pch.h"
#include "ClientLevel.h"

// location
#include "Location.h"

// spawn point
#include "ItemBox.h"

// survivor
#include "Hyunwoo.h"
#include "Aya.h"

// light
#include "Sun.h"
#include "Sky.h"

// wild animal
#include "Bear.h"
#include "Boar.h"
#include "Chicken.h"
#include "Dog.h"
#include "Wolf.h"

// manager
#include "GameManager.h"
#include "UIManager.h"

// panel
#include "InItemBoxPanel.h"
#include "InGamePanel.h"

HRESULT Client::CClientLevel::PreInitialize()
{
	if (FAILED(CLevel::PreInitialize())) { return E_FAIL; }

	LoadLevelFromFile();
	return S_OK;
}

HRESULT Client::CClientLevel::Initialize()
{
	if (FAILED(CLevel::Initialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CClientLevel::PostInitialize()
{
	if (FAILED(CLevel::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CClientLevel::LoadLevelFromFile()
{
	/******************
		User Interface
	******************/
	CUIManager::GetInstance()->LoadUserInterface();
	shared_ptr<CItemBoxPanel> spItemBoxPanel = CUIManager::GetInstance()->GetItemBoxPanel();
	shared_ptr<CItemPanel> spItemPanel = CUIManager::GetInstance()->GetItemPanel();
	shared_ptr<CStatusPanel> spStatusPanel = CUIManager::GetInstance()->GetStatusPanel();

	/******************
		Light
	******************/
	{
		std::shared_ptr<CSun> spSun = CreateActor<CSun>(L"Sun");
		std::shared_ptr<CSky> spSky = CreateActor<CSky>(L"Sky");
	}

	/******************
		Location
	******************/
	{
		// Alley
		{
			std::shared_ptr<CLocation> spAlley1x1 = CreateActor<CLocation>(L"AlleyLocation1x1");
			spAlley1x1->SetLocationType(ELocationType::ALLEY1x1);

			std::shared_ptr<CLocation> spAlley10x10 = CreateActor<CLocation>(L"AlleyLocation10x10");
			spAlley10x10->SetLocationType(ELocationType::ALLEY10x10);

			std::shared_ptr<CLocation> spAlleyGreen = CreateActor<CLocation>(L"AlleyGreen");
			spAlleyGreen->SetLocationType(ELocationType::ALLEY_GREEN);

			for (int32 iIndex = 0; iIndex <= 30; ++iIndex)
			{
				shared_ptr<CItemBox> spItemBox = CreateActor<CItemBox>(L"AlleyItemSpot" + to_wstring(iIndex) + L"_");
				spItemBox->SetItemBoxPanel(spItemBoxPanel);

				// shared_ptr<CInItemBoxPanel> spInItemBoxPanel = CInItemBoxPanel::Create(spItemBox);
				// spItemBox->SetInItemBoxPanel(spInItemBoxPanel);
			}
		}

		// School
		{
			std::shared_ptr<CLocation> spSchool1x1 = CreateActor<CLocation>(L"SchoolLocation1x1");
			spSchool1x1->SetLocationType(ELocationType::SCHOOL1x1);

			std::shared_ptr<CLocation> spSchool10x10 = CreateActor<CLocation>(L"SchoolLocation10x10");
			spSchool10x10->SetLocationType(ELocationType::SCHOOL10x10);

			std::shared_ptr<CLocation> spSchoolGreen = CreateActor<CLocation>(L"SchoolGreen");
			spSchoolGreen->SetLocationType(ELocationType::SCHOOL_GREEN);

			for (int32 iIndex = 0; iIndex <= 30; ++iIndex)
			{
				shared_ptr<CItemBox> spItemBox = CreateActor<CItemBox>(L"SchoolItemSpot" + to_wstring(iIndex) + L"_");
				spItemBox->SetItemBoxPanel(spItemBoxPanel);

				// shared_ptr<CInItemBoxPanel> spInItemBoxPanel = CInItemBoxPanel::Create(spItemBox);
				// spItemBox->SetInItemBoxPanel(spInItemBoxPanel);
			}
		}

		// Hotel
		{
			std::shared_ptr<CLocation> spHotel = CreateActor<CLocation>(L"HotelLocation");
			spHotel->SetLocationType(ELocationType::HOTEL);

			std::shared_ptr<CLocation> spHotelGreen = CreateActor<CLocation>(L"HotelGreen");
			spHotelGreen->SetLocationType(ELocationType::HOTEL_GREEN);

			for (int32 iIndex = 0; iIndex <= 29; ++iIndex)
			{
				shared_ptr<CItemBox> spItemBox = CreateActor<CItemBox>(L"HotelItemSpot" + to_wstring(iIndex) + L"_");
				spItemBox->SetItemBoxPanel(spItemBoxPanel);

				// shared_ptr<CInItemBoxPanel> spInItemBoxPanel = CInItemBoxPanel::Create(spItemBox);
				// spItemBox->SetInItemBoxPanel(spInItemBoxPanel);
			}
		}

		// Forest
		{
			std::shared_ptr<CLocation> spForest1x1 = CreateActor<CLocation>(L"ForestLocation1x1");
			spForest1x1->SetLocationType(ELocationType::FOREST1x1);

			std::shared_ptr<CLocation> spForest10x10 = CreateActor<CLocation>(L"ForestLocation10x10");
			spForest10x10->SetLocationType(ELocationType::FOREST10x10);

			std::shared_ptr<CLocation> spForestGreen = CreateActor<CLocation>(L"ForestGreen");
			spForestGreen->SetLocationType(ELocationType::FOREST_GREEN);

			for (int32 iIndex = 0; iIndex <= 30; ++iIndex)
			{
				shared_ptr<CItemBox> spItemBox = CreateActor<CItemBox>(L"ForestItemSpot" + to_wstring(iIndex) + L"_");
				spItemBox->SetItemBoxPanel(spItemBoxPanel);

				// shared_ptr<CInItemBoxPanel> spInItemBoxPanel = CInItemBoxPanel::Create(spItemBox);
				// spItemBox->SetInItemBoxPanel(spInItemBoxPanel);
			}
		}

		// Loboratory
		{
			std::shared_ptr<CLocation> spLaboratory = CreateActor<CLocation>(L"LaboratoryLocation");
			spLaboratory->SetLocationType(ELocationType::LABORATORY);
		}
		
		// Archery
		{
			std::shared_ptr<CLocation> spArchery1x1 = CreateActor<CLocation>(L"ArcheryLocation1x1");
			spArchery1x1->SetLocationType(ELocationType::ARCHERY1x1);

			std::shared_ptr<CLocation> spArchery10x10 = CreateActor<CLocation>(L"ArcheryLocation10x10");
			spArchery10x10->SetLocationType(ELocationType::ARCHERY10x10);

			std::shared_ptr<CLocation> spArcheryGreen = CreateActor<CLocation>(L"ArcheryGreen");
			spArcheryGreen->SetLocationType(ELocationType::ARCHERY_GREEN);
		}

		// Downtown
		{
			std::shared_ptr<CLocation> spDowntownLocation = CreateActor<CLocation>(L"DowntownLocation");
			spDowntownLocation->SetLocationType(ELocationType::DOWNTOWN);

			std::shared_ptr<CLocation> spDowntownGreen = CreateActor<CLocation>(L"DowntownGreen");
			spDowntownGreen->SetLocationType(ELocationType::DOWNTOWN_GREEN);
		}

		/*
		// Temple
		{
			std::shared_ptr<CLocation> spTemple = CreateActor<CLocation>(L"TempleLocation");
			spTemple->SetLocationType(ELocationType::TEMPLE);
		}

		// Uptown
		{
			std::shared_ptr<CLocation> spUptown = CreateActor<CLocation>(L"UptownLocation");
			spUptown->SetLocationType(ELocationType::UPTOWN);
		}
		*/
	}

	/******************
		Survivor
	******************/
	{
		SetPossessedPawnName(L"Hyunwoo");
		m_wpHyunwoo = CreateActor<CHyunwoo>(L"Hyunwoo");
		m_wpHyunwoo.lock()->CreateInventory(spItemPanel, spStatusPanel);
		CGameManager::GetInstance()->AddSurvivor(L"FirstSurvivor", m_wpHyunwoo.lock());

		m_wpAya = CreateActor<CAya>(L"Aya");
		m_wpAya.lock()->CreateInventory(spItemPanel, spStatusPanel);
		CGameManager::GetInstance()->AddSurvivor(L"SecondSurvivor", m_wpAya.lock());
	}
	
	/******************
		Wild Animal
	******************/
	{
		LoadWildAnimalFromFile(EWildAnimalType::BEAR);
		LoadWildAnimalFromFile(EWildAnimalType::BOAR);
		LoadWildAnimalFromFile(EWildAnimalType::CHICKEN);
		LoadWildAnimalFromFile(EWildAnimalType::DOG);
		LoadWildAnimalFromFile(EWildAnimalType::WOLF);
	}
	return S_OK;
}

HRESULT Client::CClientLevel::LoadWildAnimalFromFile(EWildAnimalType _eWildAnimalType)
{
	shared_ptr<CItemBoxPanel> spItemBoxPanel = CUIManager::GetInstance()->GetItemBoxPanel();

	wstring wstrFilePath = L"../../Resource/Editor/WildAnimal/";

	switch (_eWildAnimalType)
	{
	case Client::EWildAnimalType::BEAR:
		wstrFilePath += L"Bear.dat";
		break;

	case Client::EWildAnimalType::BOAR:
		wstrFilePath += L"Boar.dat";
		break;

	case Client::EWildAnimalType::CHICKEN:
		wstrFilePath += L"Chicken.dat";
		break;

	case Client::EWildAnimalType::DOG:
		wstrFilePath += L"Dog.dat";
		break;

	case Client::EWildAnimalType::WOLF:
		wstrFilePath += L"Wolf.dat";
		break;

	default:
		CHECKF(false, L"Wild animal type is not designated.");
		break;
	}

	std::ifstream inFile;
	inFile.open(wstrFilePath.c_str(), ios_base::in | ios_base::binary);

	// 파일이 열리지 않은 경우
	if (!inFile.is_open()) { return E_FAIL; }

	// 야생 동물의 마릿수를 읽습니다.
	uint32 iNumWildAnimals = 0;
	inFile.read(reinterpret_cast<char*>(&iNumWildAnimals), sizeof(uint32));

	for (uint32 iIndex = 0; iIndex < iNumWildAnimals; ++iIndex)
	{
		// 스폰 위치
		Vector3 vSpawnPosition = Vector3::Zero;
		inFile.read(reinterpret_cast<char*>(&vSpawnPosition), sizeof(Vector3));

		// 스폰 인덱스
		int32 iSpawnCellIndex = -1;
		inFile.read(reinterpret_cast<char*>(&iSpawnCellIndex), sizeof(int32));

		// Y축 회전 각도
		float fYDegree = 0.0f;
		inFile.read(reinterpret_cast<char*>(&fYDegree), sizeof(float));


		switch (_eWildAnimalType)
		{
		case Client::EWildAnimalType::BEAR:
		{
			shared_ptr<CBear> spBear = CreateActor<CBear>(L"Bear" + to_wstring(iIndex));
			spBear->SetItemBoxPanel(spItemBoxPanel);
			spBear->SetSpawnPosition(vSpawnPosition);
			spBear->SetSpawnCellIndex(iSpawnCellIndex);
			spBear->SetSpawnYDegree(fYDegree);

			shared_ptr<CInGamePanel> spInGamePanel = CInGamePanel::Create(spBear, EEnemyType::WILD_ANIMAL);
		}
		break;

		case Client::EWildAnimalType::BOAR:
		{
			shared_ptr<CBoar> spBoar = CreateActor<CBoar>(L"Boar" + to_wstring(iIndex));
			spBoar->SetItemBoxPanel(spItemBoxPanel);
			spBoar->SetSpawnPosition(vSpawnPosition);
			spBoar->SetSpawnCellIndex(iSpawnCellIndex);
			spBoar->SetSpawnYDegree(fYDegree);

			shared_ptr<CInGamePanel> spInGamePanel = CInGamePanel::Create(spBoar, EEnemyType::WILD_ANIMAL);
		}
		break;

		case Client::EWildAnimalType::CHICKEN:
		{
			shared_ptr<CChicken> spChicken = CreateActor<CChicken>(L"Chicken" + to_wstring(iIndex));
			spChicken->SetItemBoxPanel(spItemBoxPanel);
			spChicken->SetSpawnPosition(vSpawnPosition);
			spChicken->SetSpawnCellIndex(iSpawnCellIndex);
			spChicken->SetSpawnYDegree(fYDegree);

			shared_ptr<CInGamePanel> spInGamePanel = CInGamePanel::Create(spChicken, EEnemyType::WILD_ANIMAL);
		}
		break;

		case Client::EWildAnimalType::DOG:
		{
			shared_ptr<CDog> spDog = CreateActor<CDog>(L"Dog" + to_wstring(iIndex));
			spDog->SetItemBoxPanel(spItemBoxPanel);
			spDog->SetSpawnPosition(vSpawnPosition);
			spDog->SetSpawnCellIndex(iSpawnCellIndex);
			spDog->SetSpawnYDegree(fYDegree);

			shared_ptr<CInGamePanel> spInGamePanel = CInGamePanel::Create(spDog, EEnemyType::WILD_ANIMAL);
		}
		break;

		case Client::EWildAnimalType::WOLF:
		{
			shared_ptr<CWolf> spWolf = CreateActor<CWolf>(L"Wolf" + to_wstring(iIndex));
			spWolf->SetItemBoxPanel(spItemBoxPanel);
			spWolf->SetSpawnPosition(vSpawnPosition);
			spWolf->SetSpawnCellIndex(iSpawnCellIndex);
			spWolf->SetSpawnYDegree(fYDegree);

			shared_ptr<CInGamePanel> spInGamePanel = CInGamePanel::Create(spWolf, EEnemyType::WILD_ANIMAL);
		}
		break;

		default:
			CHECKF(false, L"Wild animal type is not designated.");
			break;
		}
	}

	return S_OK;
}
