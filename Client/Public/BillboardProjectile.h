#pragma once
#include "Projectile.h"

namespace Engine
{
	class CGeometryComponent;
}

namespace Client
{
	class CBillboardProjectile final : public CProjectile
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CBillboardProjectile() = default;

		virtual ~CBillboardProjectile() = default;
		
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
	protected:
		std::weak_ptr<CGeometryComponent> m_wpGeometryComponent;
	};
}
