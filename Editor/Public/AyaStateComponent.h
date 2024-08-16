#pragma once
#include "SurvivorStateComponent.h"

namespace Editor
{
	class CAya;

	class CAyaStateComponent final : public CSurvivorStateComponent
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CAyaStateComponent() = default;

		virtual ~CAyaStateComponent() = default;

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
		virtual void UpdateSurvivorState(float _fDeltaSeconds);

	public:
		virtual void OnAnimEnter(uint32 _iAnimState, float _fRatio) override;

		virtual void OnAnimStay(uint32 _iAnimState, float _fRatio) override;

		virtual void OnAnimExit(uint32 _iAnimState, float _fRatio) override;

		void EatItem();

	/********************
		Data Members
	********************/
	private:
		bool m_bZoomOut = true;

		ESurvivorState m_ePreAttackState = ESurvivorState::ATTACK_01;

		std::weak_ptr<CAya> m_wpAya;

		bool m_bItemBoxOpen = false;
	};
}