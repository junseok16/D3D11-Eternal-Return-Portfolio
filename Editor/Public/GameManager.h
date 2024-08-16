#pragma once
#include "Manager.h"

namespace Engine
{
	class CController;
}

namespace Editor
{
	class CSurvivor;

	class CGameManager final
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		DECLARE_SINGLETON(CGameManager)

	/********************
		Events
	********************/
	public:
		HRESULT Initialize();

		HRESULT PostInitialize();

		int32 Tick(float _fDeltaSeconds);

		void Release();
		
	/********************
		Events
	********************/
	public:
		EDayType GetDayType() const { return m_eDayType; }

		std::shared_ptr<CSurvivor> GetSurvivor() const { return m_wpCurSurvivor.expired() ? nullptr : m_wpCurSurvivor.lock(); }

		std::shared_ptr<CController> GetController() const { return m_wpController.expired() ? nullptr : m_wpController.lock(); }

		float GetDayTime() const { return m_fMaxDayDeltaSeconds - m_fSumDayDeltaSeconds; }

		float GetNightTime() const { return m_fMaxNightDeltaSeconds - m_fSumNightDeltaSeconds; }

	/********************
		Methods
	********************/
	private:
		void TickDay(float _fDeltaSeconds);

	public:
		void ChangeSurvivor(const wstring& _wstrSurvivorName);

		void AddSurvivor(const wstring& _wstrSurvivorName, const std::shared_ptr<CSurvivor>& _spSurvivor);

	/********************
		Data Members
	********************/
	private:
		// ¹ã³· Å¸ÀÔ
		EDayType m_eDayType = EDayType::DAY;

		// ´©ÀûµÈ ³· ½Ã°£
		float m_fSumDayDeltaSeconds = 0.0f;

		// ´©ÀûµÈ ¹ã ½Ã°£
		float m_fSumNightDeltaSeconds = 0.0f;

		// ³· Áö¼Ó ½Ã°£
		float m_fMaxDayDeltaSeconds = 90.0f;

		// ¹ã Áö¼Ó ½Ã°£
		float m_fMaxNightDeltaSeconds = 90.0f;

		float m_fDeltaSeconds = 0.0f;

	private:
		std::weak_ptr<CController> m_wpController;

		std::unordered_map<std::wstring, std::weak_ptr<CSurvivor>> m_umapSurvivors;

		std::weak_ptr<CSurvivor> m_wpCurSurvivor;
	};
}
