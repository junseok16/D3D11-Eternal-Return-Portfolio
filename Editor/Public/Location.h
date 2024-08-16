#pragma once
#include "Actor.h"

namespace Engine
{
	class CStaticMeshComponent;
}

namespace Editor
{
	class CLocation : public CActor
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CLocation() = default;

		virtual ~CLocation() = default;

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
		void SetLocationType(ELocationType _eLocationType) { m_eLocationType = _eLocationType; }

		ELocationType GetLocationType() const { return m_eLocationType; }

		void SetInstancableActorType(EInstancableActorType _eInstancableActorType) { m_eInstancableActorType = _eInstancableActorType; }

		EInstancableActorType GetInstancableActorType() const { return m_eInstancableActorType; }

	/********************
		Data Members
	********************/
	private:
		EInstancableActorType m_eInstancableActorType = EInstancableActorType::LOCATION;

		ELocationType m_eLocationType = ELocationType::ENUM_END;

		std::weak_ptr<CStaticMeshComponent> m_wpStaticMeshComponent;
	};
}
