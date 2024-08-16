#include "pch.h"
#include "EditorLevel.h"

// manager
#include "GameManager.h"

// location
#include "Location.h"

// spawn point
#include "ItemBox.h"
#include "Console.h"
#include "Collectible.h"

// wild animal
#include "Bear.h"
#include "Boar.h"
#include "Chicken.h"
#include "Dog.h"
#include "Wolf.h"

// boss
#include "Wickline.h"
#include "Alpha.h"
#include "Omega.h"

// boudary
#include "Boundary.h"

// survivor
#include "Hyunwoo.h"
#include "Yuki.h"
#include "Aya.h"
#include "Rozzi.h"

// light
#include "Sun.h"
#include "Sky.h"

// tester
#include "EffectTester.h"

HRESULT Editor::CEditorLevel::PreInitialize()
{
	if (FAILED(CLevel::PreInitialize())) { return E_FAIL; }

	// 0. 사용자 인터페이스
	/*
	{
		m_wpSkillPanel		= CreateActor<CSkillPanel>(L"SkillPanel");
		m_wpStatusPanel		= CreateActor<CStatusPanel>(L"StatusPanel");
		m_wpItemPanel		= CreateActor<CItemPanel>(L"ItemPanel");
		m_wpItemBoxPanel	= CreateActor<CItemBoxPanel>(L"ItemBoxPanel");
		m_wpGamePlayPanel	= CreateActor<CGamePlayPanel>(L"GamePlayPanel");
	}
	*/

	// 1. 빛
	{
		std::shared_ptr<CSun> spSun = CreateActor<CSun>(L"Sun");
		// std::shared_ptr<CSky> spSky = CreateActor<CSky>(L"Sky");
	}
	/*
	// Alley
	{
		std::shared_ptr<CLocation> spAlley1x1 = CreateActor<CLocation>(L"AlleyLocation1x1");
		spAlley1x1->SetLocationType(ELocationType::ALLEY1x1);
	}

	// School
	{
		std::shared_ptr<CLocation> spSchool1x1 = CreateActor<CLocation>(L"SchoolLocation1x1");
		spSchool1x1->SetLocationType(ELocationType::SCHOOL1x1);
	}

	// Hotel
	{
		std::shared_ptr<CLocation> spHotel = CreateActor<CLocation>(L"HotelLocation");
		spHotel->SetLocationType(ELocationType::HOTEL);
	}

	// Forest
	{
		std::shared_ptr<CLocation> spForest1x1 = CreateActor<CLocation>(L"ForestLocation1x1");
		spForest1x1->SetLocationType(ELocationType::FOREST1x1);
	}

	// Loboratory
	{
		std::shared_ptr<CLocation> spLaboratory = CreateActor<CLocation>(L"LaboratoryLocation");
		spLaboratory->SetLocationType(ELocationType::LABORATORY);
	}
	*/
	// 3. 플레이어
	{
		// SetPossessedPawnName(L"Hyunwoo");
		// m_wpHyunwoo = CreateActor<CHyunwoo>(L"Hyunwoo");
		// m_wpHyunwoo.lock()->CreateInventory(m_wpItemPanel.lock(), m_wpStatusPanel.lock());
		// CGameManager::GetInstance()->AddSurvivor(L"FirstSurvivor", m_wpHyunwoo.lock());
		
		// SetPossessedPawnName(L"Aya");
		// m_wpAya = CreateActor<CAya>(L"Aya");
		// m_wpAya.lock()->CreateInventory(m_wpItemPanel.lock(), m_wpStatusPanel.lock());
		// CGameManager::GetInstance()->AddSurvivor(L"SecondSurvivor", m_wpAya.lock());
	}

	// 6. 이펙트
	
	{
		m_wpEffectTester = CreateActor<CEffectTester>(L"EffectTester");
	}
	
	return S_OK;
}

HRESULT Editor::CEditorLevel::Initialize()
{
	if (FAILED(CLevel::Initialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Editor::CEditorLevel::PostInitialize()
{
	if (FAILED(CLevel::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Editor::CEditorLevel::AddLocations(const std::wstring& _wstrLocationName, const std::shared_ptr<CLocation>& _spLocation)
{
	if (m_umapLocations.find(_wstrLocationName) != m_umapLocations.end()) { return E_FAIL; }

	m_umapLocations.emplace(_wstrLocationName, _spLocation);
	return S_OK;
}

HRESULT Editor::CEditorLevel::AddWildAnimal(EWildAnimalType _eWildAnimalType, const std::wstring& _wstrWildAnimalName, const std::shared_ptr<CWildAnimal>& _spWildAnimal)
{
	switch (_eWildAnimalType)
	{
	case Editor::EWildAnimalType::BEAR:
		m_umapBears.insert({ _wstrWildAnimalName, dynamic_pointer_cast<CBear>(_spWildAnimal) });
		break;

	case Editor::EWildAnimalType::BOAR:
		m_umapBoars.insert({ _wstrWildAnimalName, dynamic_pointer_cast<CBoar>(_spWildAnimal) });
		break;

	case Editor::EWildAnimalType::CHICKEN:
		m_umapChickens.insert({ _wstrWildAnimalName, dynamic_pointer_cast<CChicken>(_spWildAnimal) });
		break;

	case Editor::EWildAnimalType::DOG:
		m_umapDogs.insert({ _wstrWildAnimalName, dynamic_pointer_cast<CDog>(_spWildAnimal) });
		break;

	case Editor::EWildAnimalType::WOLF:
		m_umapWolfs.insert({ _wstrWildAnimalName, dynamic_pointer_cast<CWolf>(_spWildAnimal) });
		break;

	default:
		CHECKF(false, L"Wild animal type is not designated.");
		break;
	}
	return S_OK;
}

int32 Editor::CEditorLevel::GetWildAnimalSize(EWildAnimalType _eWildAnimalType)
{
	size_t iWildAnimalSize = 0;

	switch (_eWildAnimalType)
	{
	case Editor::EWildAnimalType::BEAR:
		iWildAnimalSize = m_umapBears.size();
		break;

	case Editor::EWildAnimalType::BOAR:
		iWildAnimalSize = m_umapBoars.size();
		break;

	case Editor::EWildAnimalType::CHICKEN:
		iWildAnimalSize = m_umapChickens.size();
		break;

	case Editor::EWildAnimalType::DOG:
		iWildAnimalSize = m_umapDogs.size();
		break;

	case Editor::EWildAnimalType::WOLF:
		iWildAnimalSize = m_umapWolfs.size();
		break;

	default:
		CHECKF(false, L"Wild animal type is not designated.");
		break;
	}

	return (int32)iWildAnimalSize;
}

HRESULT Editor::CEditorLevel::RemoveLocations(const std::wstring& _wstrLocationName)
{
	if (m_umapLocations.find(_wstrLocationName) == m_umapLocations.end()) { return E_FAIL; }

	m_umapLocations.erase(_wstrLocationName);
	return S_OK;
}

HRESULT Editor::CEditorLevel::RemoveWildAnimal(EWildAnimalType _eWildAnimalType, const std::wstring& _wstrWildAnimalName)
{
	switch (_eWildAnimalType)
	{
	case Editor::EWildAnimalType::BEAR:
	{
		if (m_umapBears.find(_wstrWildAnimalName) == m_umapBears.end()) { return E_FAIL; }
		m_umapBears.erase(_wstrWildAnimalName);
	}
	break;

	case Editor::EWildAnimalType::BOAR:
	{
		if (m_umapBoars.find(_wstrWildAnimalName) == m_umapBoars.end()) { return E_FAIL; }
		m_umapBoars.erase(_wstrWildAnimalName);
	}
	break;

	case Editor::EWildAnimalType::CHICKEN:
	{
		if (m_umapChickens.find(_wstrWildAnimalName) == m_umapChickens.end()) { return E_FAIL; }
		m_umapChickens.erase(_wstrWildAnimalName);
	}
	break;

	case Editor::EWildAnimalType::DOG:
	{
		if (m_umapDogs.find(_wstrWildAnimalName) == m_umapDogs.end()) { return E_FAIL; }
		m_umapDogs.erase(_wstrWildAnimalName);
	}
	break;

	case Editor::EWildAnimalType::WOLF:
	{
		if (m_umapWolfs.find(_wstrWildAnimalName) == m_umapWolfs.end()) { return E_FAIL; }
		m_umapWolfs.erase(_wstrWildAnimalName);
	}
	break;

	default:
		CHECKF(false, L"Wild animal type is not designated.")
		break;
	}

	return S_OK;
}
