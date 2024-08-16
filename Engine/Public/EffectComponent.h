#pragma once
#include "MeshComponent.h"

namespace Engine
{
	class CStateHandler;
	class CEffectMeshData;
	class CEffectParticleData;

	class ENGINE_DLL CEffectComponent final : public CMeshComponent
	{
	/******************
		Ctor/Dtor
	******************/
	public:
		explicit CEffectComponent() = default;

		virtual ~CEffectComponent() = default;

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
		Methods
	********************/
	public:
		HRESULT AddMeshEffect(const std::wstring& _wstrMeshEffectDataName, const std::shared_ptr<CEffectMeshData>& _spEffectMeshData);

		HRESULT RemoveMeshEffect(const std::wstring& _wstrMeshEffectDataName);

		HRESULT CreateMeshEffectDataGroup(const std::wstring& _wstrMeshEffectDataGroupName);

	public:
		void PlayMeshEffect();

		void StopMeshEffect();

		void ResetMeshEffect();

		void OffMeshEffect();

	public:
		HRESULT AddParticleEffect(const std::wstring& _wstrParticleEffectName, const std::shared_ptr<CEffectParticleData>& _spEffectParticleData);

		HRESULT RemoveParticleEffect(const std::wstring& _wstrParticleEffectName);

		HRESULT CreateParticleEffectDataGroup
		(
			const std::wstring& _wstrParticleEffectGroupName,
			FParticlePlayEffectProperty _tParticlePlayProperty,
			FParticleTransformEffectProperty _tParticleTransformProperty,
			FParticleSizeEffectProperty _tParticleSizeProperty,
			FParticleMaskEffectProperty _tParticleMaskProperty,
			FParticleColorEffectProperty _tParticleColorProperty
		);

	public:
		void PlayParticleEffect();

		void StopParticleEffect();

		void ResetParticleEffect();

		void OffParticleEffect();

	/********************
		Data Members
	********************/
	private:
		std::weak_ptr<CStateHandler> m_wpStateHandler;

		ComPtr<ID3D11RasterizerState> m_cpCullNoneState = nullptr;

		ComPtr<ID3D11RasterizerState> m_cpCullBackState = nullptr;

		ComPtr<ID3D11BlendState> m_cpBlendEnableState = nullptr;

		ComPtr<ID3D11BlendState> m_cpBlendDisableState = nullptr;

	private:
		std::unordered_map<std::wstring, std::shared_ptr<CEffectMeshData>> m_umapEffectMeshData;

		std::unordered_map<std::wstring, std::shared_ptr<CEffectParticleData>> m_umapEffectParticleData;
	};
}
