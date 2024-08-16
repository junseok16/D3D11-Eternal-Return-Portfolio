#pragma once
#include "ShapeComponent.h"

namespace Engine
{
	class ENGINE_DLL COBBComponent : public CShapeComponent
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit COBBComponent() = default;

		virtual ~COBBComponent() = default;

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
		std::shared_ptr<BoundingOrientedBox> GetOBB() const { return m_spWorldOBB; }
		
		void SetCenter(const Vector3& _vCenter);

		void SetExtent(const Vector3& _vExtents);

		void SetOrientation(const Vector3& _vOrientation);
		
	/********************
		Methods
	********************/
	public:
		virtual bool IsCollided(const std::shared_ptr<CShapeComponent>& _spShapeComponent) override;

	/********************
		Data Members
	********************/
	private:
		std::shared_ptr<BoundingOrientedBox> m_spLocalOBB = nullptr;

		std::shared_ptr<BoundingOrientedBox> m_spWorldOBB = nullptr;
	};
}
