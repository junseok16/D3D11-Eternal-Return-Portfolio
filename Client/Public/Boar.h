#pragma once
#include "WildAnimal.h"

namespace Engine
{
	class CEffectComponent;
}

namespace Client
{
	class CBoar final : public CWildAnimal
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CBoar() = default;

		virtual ~CBoar() = default;
		
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
		Methods
	********************/
	public:
		// Actor overrides
		virtual void OnCollisionEnter(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst);

		virtual void OnCollisionStay(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst);

		virtual void OnCollisionExit(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst);

	public:
		// Actor overrides
		virtual void OnAnimEnter(uint32 _iAnimState, uint32 _iAnimIndex, float _fRatio) override;

		virtual void OnAnimStay(uint32 _iAnimState, uint32 _iAnimIndex, float _fRatio) override;

		virtual void OnAnimExit(uint32 _iAnimState, uint32 _iAnimIndex, float _fRatio) override;
		
	/********************
		Data Members
	********************/
	private:
		// Ω∫≈≥ ¿Ã∆Â∆Æ
		std::weak_ptr<CEffectComponent> m_wpSkillEffectComponent;

		int32 m_iSumSkillFire = 0;

		int32 m_iMaxSkillFire = 2;

		bool m_bSkillApply = false;
	};
}
