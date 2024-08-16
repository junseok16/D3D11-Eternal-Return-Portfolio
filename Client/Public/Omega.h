#pragma once
#include "Boss.h"

namespace Engine
{
	class CEffectComponent;
	class CSphereComponent;
	class COBBComponent;
}

namespace Client
{
	class CProjectile;

	class COmega final : public CBoss
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit COmega() = default;

		virtual ~COmega() = default;
		
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
		std::weak_ptr<COBBComponent> m_wpFirstSkillOBBComponent;

	private:
		std::weak_ptr<CEffectComponent> m_wpRightAttackEffectComponent;

		std::weak_ptr<CEffectComponent> m_wpLeftAttackEffectComponent;

		std::weak_ptr<CEffectComponent> m_wpFirstSkillEffectComponent;

	private:
		std::vector<std::shared_ptr<CProjectile>> m_vecOmegaProjectiles;

		bool m_bFirstSkillApply = false;
	};
}
