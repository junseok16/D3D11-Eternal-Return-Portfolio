#pragma once
#include "Slider.h"

namespace Client
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
		virtual HRESULT PreInitialize() override;

		virtual HRESULT Initialize() override;

		virtual HRESULT PostInitialize() override;

		virtual HRESULT BeginPlay() override;

		virtual int32 PreTick(float _fDeltaSeconds) override;

		virtual int32 Tick(float _fDeltaSeconds) override;
		
		virtual int32 PostTick(float _fDeltaSeconds) override;

		virtual HRESULT EndPlay() override;

		virtual void Render() override;

		virtual void Release() override;
		
	/********************
		Getter/Setter
	********************/
	public:
		void SetEnemyType(EEnemyType _eEnemyType) { m_eEnemyType = _eEnemyType; }

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

		Vector3 m_vSliderOffset = Vector3::Zero;

		EEnemyType m_eEnemyType = EEnemyType::ENUM_END;
	};
}

