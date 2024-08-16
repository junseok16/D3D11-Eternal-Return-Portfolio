#pragma once
#include "StateComponent.h"

namespace Editor
{
	class CSurvivor;
	class CCraft;

	class CCraftStateComponent : public CStateComponent
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CCraftStateComponent() = default;

		virtual ~CCraftStateComponent() = default;

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
		// craft metal
		bool IsCraftNoneEnterCondition();

		bool IsCraftMetalBeginEnterCondition();

		bool IsCraftMetalEnterCondition();

		bool IsCraftMetalBeginExitCondition();

		bool IsCraftMetalExitCondition();

		// craft food
		bool IsCraftNoneExitCondition();

		bool IsCraftFoodBeginEnterCondition();

		bool IsCraftFoodEnterCondition();

		bool IsCraftFoodBeginExitCondition();

		bool IsCraftFoodExitCondition();
		
	private:
		void UpdateCraftState(float _fDeltaSeconds);

	public:
		virtual void OnAnimEnter(uint32 _iAnimState, float _fRatio) override;

		virtual void OnAnimStay(uint32 _iAnimState, float _fRatio) override;

		virtual void OnAnimExit(uint32 _iAnimState, float _fRatio) override;

	/********************
		Data Members
	********************/
	protected:
		ECraftState m_eCraftState = ECraftState::ENUM_END;

		std::weak_ptr<CSurvivor> m_wpSurvivor;
	};
}
