#pragma once
#include "Actor.h"

namespace Engine
{
	class CAABBComponent;
}

namespace Client
{
	class CBoundary final : public CActor
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CBoundary() = default;

		virtual ~CBoundary() = default;

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
		virtual void OnCollisionEnter(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst) override;

		virtual void OnCollisionStay(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst) override;

		virtual void OnCollisionExit(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst) override;
		
	/********************
		Getter/Setter
	********************/
	public:
		void SetSpawnPosition(const Vector3& _vSpawnPosition) { m_vSpawnPosition = _vSpawnPosition; }

		void SetFromLocationType(ELocationType _eFromLocationType) { m_eFromLocationType = _eFromLocationType; }

		void SetToLocationType(ELocationType _eToLocationType) { m_eToLocationType = _eToLocationType; }

	/********************
		Data Members
	********************/
	private:
		std::weak_ptr<CAABBComponent> m_wpAABBComponent;

		Vector3 m_vSpawnPosition = Vector3::Zero;

		ELocationType m_eFromLocationType = ELocationType::ENUM_END;

		ELocationType m_eToLocationType = ELocationType::ENUM_END;
	};
}
