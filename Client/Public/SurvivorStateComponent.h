#pragma once
#include "StateComponent.h"

namespace Engine
{
	class CInputComponent;
	class CCameraComponent;
	class CSoundComponent;
}

namespace Client
{
	class CSurvivor;

	class CSurvivorStateComponent : public CStateComponent
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CSurvivorStateComponent() = default;

		virtual ~CSurvivorStateComponent() = default;

	/********************
		Framework
	********************/
	public:
		virtual HRESULT PreInitializeComponent();

		virtual HRESULT InitializeComponent();

		virtual HRESULT PostInitializeComponent();

		virtual HRESULT BeginPlay();

		virtual int32 PreTickComponent(float _fDeltaSeconds);

		virtual int32 TickComponent(float _fDeltaSeconds);

		virtual int32 PostTickComponent(float _fDeltaSeconds);

		virtual HRESULT EndPlay();

		virtual void Render();

		virtual void Release();
		
	/********************
		Methods
	********************/
	private:
		// common
		bool IsWaitEnterCondition();

		bool IsRunEnterCondition();

		bool IsArriveEnterCondition();

		// attack
		bool IsFirstAttackEnterCondition();

		bool IsSecondAttackEnterCondition();

		// 1st skill
		bool IsFirstSkillEnterCondition();

		// 2nd skill
		bool IsSecondSkillBeginEnterCondition();

		bool IsSecondSkillEnterCondition();

		bool IsSecondSkillEndEnterCondition();

		// 3rd skill
		bool IsThirdSkillBeginEnterCondition();

		bool IsThirdSkillEnterCondition();

		bool IsThirdSkillEndEnterCondition();

		// 4th skill
		bool IsFourthSkillBeginEnterCondition();

		bool IsFourthSkillEnterCondition();

		bool IsFourthSkillEndEnterCondition();

		// collect
		bool IsCollectStoneEnterCondition();

		bool IsCollectWaterEnterCondition();

		bool IsCollectWoodEnterCondition();

		// craft
		bool IsCraftFoodEnterCondition();

		bool IsCraftMetalEnterCondition();

		// rest
		bool IsRestBeginEnterCondition();

		bool IsRestEnterCondition();

		bool IsRestEndEnterCondition();

		// operate
		bool IsOperateEnterCondition();

		// death
		bool IsDeathEnterCondition();

	private:
		// common
		bool IsWaitExitCondition();

		bool IsRunExitCondition();

		bool IsArriveExitCondition();

		// attack
		bool IsFirstAttackExitCondition();

		bool IsSecondAttackExitCondition();

		// skill
		bool IsFirstSkillExitCondition();

		// 2nd skill
		bool IsSecondSkillBeginExitCondition();

		bool IsSecondSkillExitCondition();

		bool IsSecondSkillEndExitCondition();

		// 3rd skill
		bool IsThirdSkillBeginExitCondition();

		bool IsThirdSkillExitCondition();
		
		bool IsThirdSkillEndExitCondition();

		// 4th skill
		bool IsFourthSkillBeginExitCondition();

		bool IsFourthSkillExitCondition();

		bool IsFourthSkillEndExitCondition();

		// collect
		bool IsCollectStoneExitCondition();

		bool IsCollectWaterExitCondition();

		bool IsCollectWoodExitCondition();

		// craft
		bool IsCraftFoodExitCondition();

		bool IsCraftMetalExitCondition();

		// rest
		bool IsRestBeginExitCondition();

		bool IsRestExitCondition();
		
		bool IsRestEndExitCondition();

		// operate
		bool IsOperateExitCondition();

		// death
		bool IsDeathExitCondition();

	private:
		virtual void UpdateSurvivorState(float _fDeltaSeconds);
		
	/********************
		Getter/Setter
	********************/
	public:
		void SetServivorState(ESurvivorState _eSurvivorState) { m_eSurvivorState = _eSurvivorState; }

		ESurvivorState GetSurvivorState() const { return m_eSurvivorState; }

	public:
		bool IsBoxOpened() const { return m_bItemBoxOpen; }

	/********************
		Data Members
	********************/
	protected:
		std::weak_ptr<CInputComponent> m_wpInputComponent;

		std::weak_ptr<CCameraComponent> m_wpCameraComponent;

		std::weak_ptr<CSoundComponent> m_wpSoundComponent;

	protected:
		// 현재 플레이어 상태
		ESurvivorState m_eSurvivorState = ESurvivorState::ENUM_END;

		// 이 컴포넌트를 갖고 있는 플레이어
		std::weak_ptr<CSurvivor> m_wpSurvivor;

		float m_fDeltaSeconds = 0.0f;

		float m_fSumCraftMetalSeconds = 0.0f;

		float m_fSumCraftFoodSeconds = 0.0f;

		float m_fSumRestSeconds = 0.0f;

		float m_fSumCollectStoneSeconds = 0.0f;
		
		float m_fSumCollectBranchSeconds = 0.0f;
		
		float m_fSumCollectWaterSeconds = 0.0f;

		float m_fSumOperateSeconds = 0.0f;

		bool m_bItemBoxOpen = false;
	};
}
