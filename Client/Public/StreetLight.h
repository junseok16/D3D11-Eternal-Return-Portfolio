#pragma once
#include "Actor.h"

namespace Engine
{
    class CLightComponent;
}

namespace Client
{
    class CStreetLight final : public CActor
    {
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CStreetLight() = default;

		virtual ~CStreetLight() = default;

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
		std::weak_ptr<CLightComponent> m_wpLightComponent;
    };
}
