#pragma once
#include "WildAnimalStateComponent.h"

namespace Client
{
	class CDogStateComponent final : public CWildAnimalStateComponent
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CDogStateComponent() = default;

		virtual ~CDogStateComponent() = default;

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
		virtual void UpdateWildAnimalState(float _fDeltaSeconds) override;

		virtual void UpdateWildAnimalBehavior(float _fDeltaSeconds) override;

	public:
		virtual void OnAnimEnter(uint32 _iAnimState, float _fRatio) override;

		virtual void OnAnimStay(uint32 _iAnimState, float _fRatio) override;

		virtual void OnAnimExit(uint32 _iAnimState, float _fRatio) override;
		
	/********************
		Data Members
	********************/
	private:
		EWildAnimalState m_ePreAttackState = EWildAnimalState::ATTACK_01;
	};
}
