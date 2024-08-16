#pragma once
#include "ShapeComponent.h"

namespace Engine
{
	class ENGINE_DLL CAABBComponent : public CShapeComponent
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CAABBComponent() = default;

		virtual ~CAABBComponent() = default;

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
		
	/********************
		Getter/Setter
	********************/
	public:
		std::shared_ptr<BoundingBox> GetAABB() const { return m_spWorldAABB; }

		void SetCenter(const Vector3& _vCenter)
		{
			m_spLocalAABB->Center = _vCenter;
			m_spWorldAABB->Center = _vCenter;
		}

		void SetExtent(const Vector3& _vExtents)
		{
			m_spLocalAABB->Extents = _vExtents;
			m_spWorldAABB->Extents = _vExtents;
		}
		
	/********************
		Methods
	********************/
	public:
		virtual bool IsCollided(const std::shared_ptr<CShapeComponent>& _spShapeComponent) override;

	/********************
		Data Members
	********************/
	private:
		std::shared_ptr<BoundingBox> m_spLocalAABB = nullptr;

		std::shared_ptr<BoundingBox> m_spWorldAABB = nullptr;
	};
}
