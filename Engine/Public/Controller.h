#pragma once
#include "Actor.h"

namespace Engine
{
	class CInputComponent;
	class CPawn;

    class ENGINE_DLL CController : public CActor
    {
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CController() = default;

		virtual ~CController() = default;

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
	public:
		void AddPitchInput(float _fValue);

		void AddRollInput(float _fValue);

		void AddYawInput(float _fValue);

		bool Possess(const std::shared_ptr<CPawn> _spPawn);

		bool UnPossess();
		
	/********************
		Getter/Setter
	********************/
	public:
		const std::shared_ptr<CInputComponent> GetInputComponent() { return m_wpInputComponent.expired() ? nullptr : m_wpInputComponent.lock(); }

		std::shared_ptr<CPawn> GetPawn() { return m_wpPawn.expired() ? nullptr : m_wpPawn.lock(); }

		void EnableInput();

		void DisableInput();

	/********************
		Data Members
	********************/
	protected:
		std::weak_ptr<CInputComponent> m_wpInputComponent;

	protected:
		std::weak_ptr<CPawn> m_wpPawn;

		Vector3 m_fSpawnPosition = Vector3::Zero;
	};
}
