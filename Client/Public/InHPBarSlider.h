#pragma once
#include "Slider.h"

namespace Client
{
	class CWildAnimal;
	class CBoss;

	class CInHPBarSlider final : public CSlider
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CInHPBarSlider() = default;

		virtual ~CInHPBarSlider() = default;
		
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
