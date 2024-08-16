#pragma once
#include "Pawn.h"

namespace Engine
{
	class ENGINE_DLL CCharacter : public CPawn
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CCharacter() = default;

		virtual ~CCharacter() = default;
		
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
	};
}
