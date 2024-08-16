#pragma once
#include "Manager.h"

namespace Engine
{
	class CCameraManager;
	class CLightManager;
	class CLevel;
	class CController;
	class CSoundHandler;
}

namespace Client
{
	class CBoss;
	class CAlpha;
	class COmega;
	class CWickline;
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

		float GetDayToNightLerpRatio() const { return (m_fMaxDayDeltaSeconds - m_fSumDayDeltaSeconds) / 10.0f; }

		float GetNightToDayLerpRatio() const { return (m_fMaxNightDeltaSeconds - m_fSumNightDeltaSeconds) / 10.0f; }

		float GetDayTime() const { return m_fMaxDayDeltaSeconds - m_fSumDayDeltaSeconds; }

		float GetNightTime() const { return m_fMaxNightDeltaSeconds - m_fSumNightDeltaSeconds; }

		int32 GetSumDay() const { return m_iSumDay; }

		int32 GetSumNight() const { return m_iSumNight; }

	/********************
		Methods
	********************/
	private:
		void TickDay(float _fDeltaSeconds);

	public:
		void ChangeSurvivor(const wstring& _wstrSurvivorName);

		void AddSurvivor(const wstring& _wstrSurvivorName, const std::shared_ptr<CSurvivor>& _spSurvivor);

	public:
		shared_ptr<CBoss> CreateBoss(EBossType _eBossType);

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
		float m_fMaxDayDeltaSeconds = 180.0f;

		// ¹ã Áö¼Ó ½Ã°£
		float m_fMaxNightDeltaSeconds = 180.0f;

		float m_fDeltaSeconds = 0.0f;

		int32 m_iSumDay = 1;

		int32 m_iSumNight = 0;

	private:
		std::weak_ptr<CLightManager> m_wpLightManager;

		std::weak_ptr<CCameraManager> m_wpCameraManager;

		std::weak_ptr<CSoundHandler> m_wpSoundHandler;

		std::weak_ptr<CController> m_wpController;

		std::unordered_map<std::wstring, std::weak_ptr<CSurvivor>> m_umapSurvivors;

		std::weak_ptr<CSurvivor> m_wpCurSurvivor;

	private:
		std::weak_ptr<CLevel> m_wpCurLevel;

		std::weak_ptr<CWickline> m_wpWickline;

		std::weak_ptr<CAlpha> m_wpAlpha;

		std::weak_ptr<COmega> m_wpOmega;

	private:
		std::array<std::string, 10> m_arrAreaSounds
		{
			"BSER_AreaBGM_Alley",
			"BSER_AreaBGM_Cemetery",
			"BSER_AreaBGM_Church",
			"BSER_AreaBGM_Downtown",
			"BSER_AreaBGM_Factory",
			"BSER_AreaBGM_Forest",
			"BSER_AreaBGM_Harbor",
			"BSER_AreaBGM_Hospital",
			"BSER_AreaBGM_Hotel",
			"BSER_AreaBGM_Laboratory",
		};

	private:
		float m_fCameraDelay = 0.0f;

		bool m_bAlphaCamera = true;

		bool m_bWicklineCamera = true;
	};
}
