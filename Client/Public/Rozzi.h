#pragma once
#include "Survivor.h"

namespace Engine
{
	class COBBComponent;
	class CSphereComponent;
}

namespace Client
{
	class CRozzi : public CSurvivor
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CRozzi() = default;

		virtual ~CRozzi() = default;
		
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
		
	/********************
		Data Members
	********************/
	private:
		// 첫 번째 스킬
		std::weak_ptr<COBBComponent> m_wpFirstSkillOBBComponent;
		
		// 두 번째 스킬
		std::weak_ptr<CSphereComponent> m_wpSecondSkillSphereComponent;

		// 세 번째 스킬
		std::weak_ptr<COBBComponent> m_wpThirdSkillOBBComponent;

		// 세 번째 스킬 이동 속도 배율
		float m_fThirdSkillSpeedOffset = 1.3f;
	};
}
