#pragma once
#include "BossStateComponent.h"

namespace Editor
{
	class COmegaStateComponent final : public CBossStateComponent
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit COmegaStateComponent() = default;

		virtual ~COmegaStateComponent() = default;

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
		Overrides
	********************/
	public:
		virtual void UpdateBossState(float _fDeltaSeconds) override;

		virtual void UpdateBossBehavior(float _fDeltaSeconds) override;

	public:
		virtual void OnAnimEnter(uint32 _iAnimState, float _fRatio) override;

		virtual void OnAnimStay(uint32 _iAnimState, float _fRatio) override;

		virtual void OnAnimExit(uint32 _iAnimState, float _fRatio) override;

	private:
		EBossState m_ePreAttackState = EBossState::ATTACK_01;

		EBossState m_ePreSkillState = EBossState::SKILL_01;
	};
}
