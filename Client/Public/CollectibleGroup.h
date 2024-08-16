#pragma once
#include "Actor.h"

namespace Engine
{
	class CStaticMeshComponent;
}

namespace Client
{
	class CCollectible;

	class CCollectibleGroup final : public CActor
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CCollectibleGroup() = default;

		virtual ~CCollectibleGroup() = default;

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
		void AddCollectible(const shared_ptr<CCollectible>& _spCollectible);

	/********************
		Getter/Setter
	********************/
	public:
		void SetLocationType(ELocationType _eLocationType) { m_eLocationType = _eLocationType; }

		ELocationType GetLocationType() const { return m_eLocationType; }

		void SetCollectibleType(ECollectibleType _eCollectibleType) { m_eCollectibleType = _eCollectibleType; }

		ECollectibleType GetCollectibleType() const { return m_eCollectibleType; }

		std::vector<std::weak_ptr<CCollectible>>& GetCollectibles() { return m_vecCollectibles; }

	/********************
		Data Members
	********************/
	protected:
		ELocationType m_eLocationType = ELocationType::ENUM_END;

		ECollectibleType m_eCollectibleType = ECollectibleType::ENUM_END;

		std::weak_ptr<CStaticMeshComponent> m_wpStaticMeshComponent;

		std::vector<std::weak_ptr<CCollectible>> m_vecCollectibles;
	};
}
