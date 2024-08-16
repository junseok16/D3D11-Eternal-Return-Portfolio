#pragma once
#include "Survivor.h"

namespace Engine
{
	class CEffectComponent;
	class COBBComponent;
	class CSphereComponent;
	class CSocket;
}

namespace Client
{
	class CWeapon;
	class CCraftTool;

	class CHyunwoo final : public CSurvivor
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CHyunwoo() = default;

		virtual ~CHyunwoo() = default;
		
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
		virtual void OnCollisionEnter(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst) override;

		virtual void OnCollisionStay(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst) override;

		virtual void OnCollisionExit(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst) override;
		
	public:
		// Actor overrides
		virtual void OnAnimEnter(uint32 _iAnimState, uint32 _iAnimIndex, float _fRatio) override;

		virtual void OnAnimStay(uint32 _iAnimState, uint32 _iAnimIndex, float _fRatio) override;

		virtual void OnAnimExit(uint32 _iAnimState, uint32 _iAnimIndex, float _fRatio) override;

	public:
		// Survivor overrides
		virtual void MoveForward(int32 _iValue) override;

		virtual void MoveBackward(int32 _iValue) override;

		virtual void MoveRight(int32 _iValue) override;

		virtual void MoveLeft(int32 _iValue) override;

		virtual float TakeDamage(float _fDamageAmount, std::shared_ptr<CController> _spInstigatorController, std::shared_ptr<CPawn> _spInstigatorPawn) override;

	public:
		void SetSecondSkillApply(bool _bSecondSkillApply) { m_bSecondSkillApply = _bSecondSkillApply; }

	/********************
		Data Members
	********************/
	private:
		std::weak_ptr<CSphereComponent> m_wpAttackSphereComponent;

		std::weak_ptr<COBBComponent> m_wpFirstSkillOBBComponent;

		std::weak_ptr<COBBComponent> m_wpThirdSkillOBBComponent;

		std::weak_ptr<COBBComponent> m_wpFourthSkillOBBComponent;

	private:
		std::weak_ptr<CEffectComponent> m_wpLeftAttackEffectComponent;

		std::weak_ptr<CEffectComponent> m_wpRightAttackEffectComponent;

		std::weak_ptr<CEffectComponent> m_wpFirstSkillEffectComponent;

		std::weak_ptr<CEffectComponent> m_wpSecondSkillEffectComponent;

		std::weak_ptr<CEffectComponent> m_wpThirdSkillEffectComponent;

		std::weak_ptr<CEffectComponent> m_wpFourthSkillEffectComponent;

		std::weak_ptr<CEffectComponent> m_wpFourthSkillSlashEffectComponent;

	private:
		// �����ߴ��� ����
		bool m_bAttackApply = false;

		// ù ��° ��ų�� ���ƴ��� ����
		bool m_bFirstSkillApply = false;

		bool m_bSecondSkillApply = false;

		float m_fSumSecondSkillDeltaSeconds = 0.0f;

		// �� ��° ��ų�� ���ƴ��� ����
		bool m_bThirdSkillApply = false;

		// �� ��° ��ų �̵� �ӵ� ����
		float m_fThirdSkillSpeedOffset = 5.0f;

		// �� ��° ��ų�� �浹�� ����
		std::vector<std::weak_ptr<CActor>> m_vecThirdSkillActors;

		// �� ��° ��ų�� ���ƴ��� ����
		bool m_bFourthSkillApply = false;

		// �� ��° ��ų ����
		float m_fFourthSkillCurDepth = 0.0f;

		// �� ��° ��ų �ּ� ����
		float m_fFourthSkillMinDepth = 0.1f;

		// �� ��° ��ų �ִ� ����
		float m_fFourthSkillMaxDepth = 2.0f;

	private:
		std::array<std::shared_ptr<CSocket>, 1> m_arrSockets;

		std::weak_ptr<CWeapon> m_wpHyunwooGlove;

		std::weak_ptr<CCraftTool> m_wpHammer;
	};
}
