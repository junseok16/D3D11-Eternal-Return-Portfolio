#pragma once
#include "Actor.h"

namespace Engine
{
	class CController;
	// class CPlayerState;

	class CCameraComponent;
	class CInputComponent;
	class CSkeletalMeshComponent;
	// class CPawnMovementComponent;
	// class CSpringArmComponent;	

	class ENGINE_DLL CPawn : public CActor
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CPawn() = default;

		virtual ~CPawn() = default;

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
		std::shared_ptr<CController> GetController() const { return m_wpController.expired() ? nullptr : m_wpController.lock(); }
		
		void SetController(const std::shared_ptr<CController>& _spContoller) { m_wpController = _spContoller; }
		
		void SetPossessed(bool _bPossessed) { m_bPosessed = _bPossessed; }

		std::shared_ptr<CCameraComponent> GetCameraComponent() const { return m_wpCameraComponent.expired() ? nullptr : m_wpCameraComponent.lock(); }

	/******************
		Data Members
	******************/
	protected:
		std::weak_ptr<CController> m_wpController;

	protected:
		std::weak_ptr<CCameraComponent> m_wpCameraComponent;

		std::weak_ptr<CInputComponent> m_wpInputComponent;

		std::weak_ptr<CSkeletalMeshComponent> m_wpSkeletalMeshComponent;

	protected:
		bool m_bPosessed = false;
	};
}
