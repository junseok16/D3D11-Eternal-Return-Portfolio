#pragma once
#include "Actor.h"

namespace Engine
{
	class CLightComponent;
	class CCubeComponent;
}

namespace Editor
{
	class CSky : public CActor
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CSky() = default;

		virtual ~CSky() = default;

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
		std::weak_ptr<CLightComponent> m_wpDayLightComponent;

		std::weak_ptr<CLightComponent> m_wpNightLightComponent;

		std::weak_ptr<CCubeComponent> m_wpSkyboxCubeComponent;

		std::weak_ptr<CPawn> m_wpPosessedPawn;
	};
}