#pragma once
#include "Slider.h"

namespace Editor
{
	class CWildAnimal;
	class CBoss;

	class CInRetreatBarSlider final : public CSlider
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CInRetreatBarSlider() = default;

		virtual ~CInRetreatBarSlider() = default;
		
	/********************
		Events
	********************/
	public:
		virtual HRESULT PreInitialize();

		virtual HRESULT Initialize();

		virtual HRESULT PostInitialize();

		virtual HRESULT BeginPlay();

		virtual int32 PreTick(float _fDeltaSeconds);

		virtual int32 Tick(float _fDeltaSeconds);
		
		virtual int32 PostTick(float _fDeltaSeconds);

		virtual HRESULT EndPlay();

		virtual void Render();

		virtual void Release();
		
	/********************
		Methods
	********************/
	private:
		virtual void TickSlider() override;
		
	/********************
		Data Memebers
	********************/
	private:
		std::weak_ptr<CWildAnimal> m_wpWildAnimal;

		std::weak_ptr<CBoss> m_wpBoss;

		Vector3 m_fSliderOffset = Vector3::Zero;

		EEnemyType m_eEnemyType = EEnemyType::ENUM_END;
	};
}

