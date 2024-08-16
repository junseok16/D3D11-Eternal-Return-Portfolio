#pragma once
#include "Actor.h"

namespace Engine
{
	class CStaticMeshComponent;
	class CSphereComponent;
}

namespace Editor
{
	class CCollectible : public CActor
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CCollectible() = default;

		virtual ~CCollectible() = default;

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
		// actor overrides
		virtual void OnCollisionEnter(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst);

		virtual void OnCollisionStay(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst);

		virtual void OnCollisionExit(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst);
		
	/********************
		Getter/Setter
	********************/
	public:
		void SetInstancableActorType(EInstancableActorType _eInstancableActorType) { m_eInstancableActorType = _eInstancableActorType; }

		EInstancableActorType GetInstancableActorType() const { return m_eInstancableActorType; }

		void SetLocationType(ELocationType _eLocationType) { m_eLocationType = _eLocationType; }

		ELocationType GetLocationType() const { return m_eLocationType; }

		void SetCollectibleType(ECollectibleType _eCollectibleType) { m_eCollectibleType = _eCollectibleType; }

		ECollectibleType GetCollectibleType() const { return m_eCollectibleType; }

	/********************
		Data Members
	********************/
	protected:
		EInstancableActorType m_eInstancableActorType = EInstancableActorType::COLLECTIBLE;

		ELocationType m_eLocationType = ELocationType::ENUM_END;

		ECollectibleType m_eCollectibleType = ECollectibleType::ENUM_END;

		std::weak_ptr<CSphereComponent> m_wpSphereComponents;
	};
}
