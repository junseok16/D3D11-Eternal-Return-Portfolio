#pragma once
#include "SceneComponent.h"

namespace Engine
{
	class CLightConstantBuffer;
	class CInvViewInvProjectionConstantBuffer;

	struct TLightDesc final
	{
		ELightType m_eLightType = ELightType::ENUM_END;

		Vector3 m_vAmbient = Vector3::One;
		float m_fRange = 10.0f;

		Vector3 m_vDiffuse = Vector3::One;
		float m_fFallOffBegin = 0.0;

		Vector3 m_vSpecular = Vector3::Zero;
		float m_fFallOffEnd = 10.0;

		Vector3 m_vPosition = Vector3::Zero;
		float m_fPower = 1.0f;

		Vector3 m_vDirection = Vector3::Down;

		Vector3 m_vStrength = Vector3::One;
	};

    class ENGINE_DLL CLightComponent : public CSceneComponent
    {
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CLightComponent() = default;

		virtual ~CLightComponent() = default;

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
		TLightDesc GetLightDesc() const { return m_tLightDesc; }

		void SetLightDesc(TLightDesc _tLightDesc) { m_tLightDesc = _tLightDesc; }

		void SetLightDiffuse(const Vector3& _vDiffuse) { m_tLightDesc.m_vDiffuse = _vDiffuse; }

		void SetLightAmbient(const Vector3& _vAmbient) { m_tLightDesc.m_vAmbient = _vAmbient; }

	/********************
		Data Members
	********************/
	private:
		TLightDesc m_tLightDesc;

		std::shared_ptr<CLightConstantBuffer> m_spLightPSConstantBuffers = nullptr;

		std::shared_ptr<CInvViewInvProjectionConstantBuffer> m_spInvViewInvProjectionConstantBuffer = nullptr;
    };
}
