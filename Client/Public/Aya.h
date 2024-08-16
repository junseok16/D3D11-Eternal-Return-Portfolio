#pragma once
#include "Survivor.h"

namespace Engine
{
	class COBBComponent;
	class CSphereComponent;
	class CSocket;
}

namespace Client
{
	class CWeapon;
	class CCraftTool;
	class CProjectile;

	class CAya final : public CSurvivor
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CAya() = default;

		virtual ~CAya() = default;
		
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

		// Actor overrides
		virtual void OnAnimEnter(uint32 _iAnimState, uint32 _iAnimIndex, float _fRatio) override;

		virtual void OnAnimStay(uint32 _iAnimState, uint32 _iAnimIndex, float _fRatio) override;

		virtual void OnAnimExit(uint32 _iAnimState, uint32 _iAnimIndex, float _fRatio) override;

		// Survivor overrides
		virtual void MoveForward(int32 _iValue) override;

		virtual void MoveBackward(int32 _iValue) override;

		virtual void MoveRight(int32 _iValue) override;

		virtual void MoveLeft(int32 _iValue) override;
		
	public:
		bool IsSecondSkillApplying() const { return m_bSecondSkillApplying; }
		
	/********************
		Data Members
	********************/
	private:
		std::weak_ptr<CSphereComponent> m_wpFourthSkillSphereComponent;

	private:
		std::weak_ptr<CEffectComponent> m_wpFirstSkillEffectComponent;
		
		std::weak_ptr<CEffectComponent> m_wpSecondSkillEffectComponent;

		std::weak_ptr<CEffectComponent> m_wpThirdSkillEffectComponent;

		std::weak_ptr<CEffectComponent> m_wpFourthSkillEffectComponent;

	private:
		// �Ϲ� ���� ����
		bool m_bAttackApply = false;

		bool m_bFirstSkillFirstFire = false;

		bool m_bFirstSkillSecondFire = false;

		// ù ��° ��ų �Ҹ�
		string m_strFirstSkillFirstSound = "";

		string m_strFirstSkillSecondSound = "";

		// �� ��° ��ų �ִ� �߻� Ƚ��
		int32 m_iMaxSecondSkillFire = 6;

		// �� ��° ��ų ���� �߻� Ƚ��
		int32 m_iSumSecondSkillFire = 0;

		// �� ��° ��ų�� ��� ������ ����
		bool m_bSecondSkillApplying = false;

		bool m_bSecondSkillFire = false;

		// �� ��° ��ų �̵� �ӵ� ����
		float m_fThirdSkillSpeedOffset = 2.0f;

		// �� ��° ��ų�� ��� ������ ����
		bool m_bFourthSkillApplying = false;

	private:
		// sockets
		std::array<std::shared_ptr<CSocket>, 2> m_arrSockets;

		std::shared_ptr<CWeapon> m_spPistol;

		std::weak_ptr<CCraftTool> m_wpHammer;

	private:
		std::vector<shared_ptr<CProjectile>> m_vecAyaProjectiles;
	};
}
