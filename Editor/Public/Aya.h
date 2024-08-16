#pragma once
#include "Survivor.h"

namespace Engine
{
	class COBBComponent;
	class CSphereComponent;
	class CSocket;
}

namespace Editor
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
		// 일반 공격 여부
		bool m_bAttackApply = false;

		bool m_bFirstSkillFirstFire = false;

		bool m_bFirstSkillSecondFire = false;

		// 두 번째 스킬 최대 발사 횟수
		int32 m_iMaxSecondSkillFire = 6;

		// 두 번째 스킬 누적 발사 횟수
		int32 m_iSumSecondSkillFire = 0;

		// 두 번째 스킬이 사용 중인지 여부
		bool m_bSecondSkillApplying = false;

		// 세번째 스킬 이동 속도 배율
		float m_fThirdSkillSpeedOffset = 2.0f;

	private:
		// sockets
		std::array<std::shared_ptr<CSocket>, 1> m_arrSockets;

		std::shared_ptr<CWeapon> m_spPistol;

	private:
		std::vector<shared_ptr<CProjectile>> m_vecAyaProjectiles;
	};
}
