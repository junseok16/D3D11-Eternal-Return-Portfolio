#pragma once
#include "Actor.h"

namespace Engine
{
	class CStaticMeshComponent;
	class CEffectComponent;
}

namespace Editor
{
	class CEffectTester : public CActor
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CEffectTester() = default;

		virtual ~CEffectTester() = default;
		
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
		Data Members
	********************/
	private:
		std::weak_ptr<CEffectComponent> m_wpEffectComponent;

		std::weak_ptr<CStaticMeshComponent> m_wpStaticMeshComponent;
	};
}
