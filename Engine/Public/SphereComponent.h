#pragma once
#include "ShapeComponent.h"

namespace Engine
{
	class ENGINE_DLL CSphereComponent : public CShapeComponent
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CSphereComponent() = default;

		virtual ~CSphereComponent() = default;

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
		std::shared_ptr<BoundingSphere> GetSphere() const { return m_spWorldSphere; }
		
		void SetCenter(const Vector3& _vCenter) { m_spLocalSphere->Center = _vCenter; }
		
		float GetRadius() const { return m_spLocalSphere->Radius; }

		void SetRadius(const float _fRadius) { m_spLocalSphere->Radius = _fRadius; }
		
	/********************
		Methods
	********************/
	public:
		virtual bool IsCollided(const std::shared_ptr<CShapeComponent>& _spShapeComponent) override;

	/********************
		Data Members
	********************/
	private:
		std::shared_ptr<BoundingSphere> m_spLocalSphere = nullptr;

		std::shared_ptr<BoundingSphere> m_spWorldSphere = nullptr;
	};
}
