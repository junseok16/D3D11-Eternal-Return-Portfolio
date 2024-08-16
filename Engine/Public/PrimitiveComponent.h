#pragma once
#include "SceneComponent.h"

namespace Engine
{
	class ENGINE_DLL CPrimitiveComponent : public CSceneComponent
	{
	/******************
		Ctor/Dtor
	******************/
	public:
		explicit CPrimitiveComponent() = default;

		virtual ~CPrimitiveComponent() = default;

	/********************
		Events
	********************/
	public:
		virtual HRESULT PreInitializeComponent() override;

		virtual HRESULT InitializeComponent() override;

		virtual HRESULT PostInitializeComponent() override;

		virtual HRESULT BeginPlay() override;

		virtual int32 PreTickComponent(float _fDeltaSeconds) override;

		virtual int32 TickComponent(float _fDeltaSeconds) override;

		virtual int32 PostTickComponent(float _fDeltaSeconds) override;

		virtual HRESULT EndPlay() override;

		virtual void Render() override;

		virtual void Release() override;
	};
}
