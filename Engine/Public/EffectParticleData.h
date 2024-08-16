#pragma once

namespace Engine
{
	class CSceneComponent;
	class CPrimitiveBuffer;
	class CPrimitiveShader;

	enum class EEffectParticleDataState
	{
		ON,		// 이펙트를 켠 상태
		PLAY,	// 이펙트를 켜고 재생하는 상태
		STOP,	// 이펙트를 켜고 재생하다 멈춘 상태
		RESET,	// 이펙트를 처음으로 되돌린 상태
		OFF,	// 이펙트를 끈 상태
		ENUM_END
	};

	class ENGINE_DLL CEffectParticleData final : public enable_shared_from_this<CEffectParticleData>
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CEffectParticleData() = default;

		virtual ~CEffectParticleData() = default;

	/********************
		Events
	********************/
	public:
		static std::shared_ptr<CEffectParticleData> Create
		(
			const std::shared_ptr<CSceneComponent>& _spOwnerComponent,
			int32 _iNumInstances,
			const std::vector<std::wstring>& _vecTextureNames,
			const std::wstring& _wstrEffectParticleDesc = L"",
			const std::wstring& _wstrVertexShaderDesc = L"",
			const std::wstring& _wstrPixelShaderDesc = L"",
			const std::wstring& _wstrGeometryShaderDesc = L""
		);

		HRESULT Initialize
		(
			const std::shared_ptr<CSceneComponent>& _spOwnerComponent,
			int32 _iNumInstances,
			const std::vector<std::wstring>& _vecTextureNames,
			const std::wstring& _wstrEffectParticleDesc = L"",
			const std::wstring& _wstrVertexShaderDesc = L"",
			const std::wstring& _wstrPixelShaderDesc = L"",
			const std::wstring& _wstrGeometryShaderDesc = L""
		);

		int32 Tick(float _fDeltaSeconds);

		void Render();

		void Release();
		
		void Clear();
		
	/********************
		Getter/Setter
	********************/
	public:
		void SetEffectParticleDataState(EEffectParticleDataState _eEffectParticleDataState) { m_eEffectParticleDataState = _eEffectParticleDataState; }
		
		void SetPlayProperty(FParticlePlayEffectProperty _tParticlePlayProperty) { m_tParticlePlayProperty = _tParticlePlayProperty; }

		void SetTransformProperty(FParticleTransformEffectProperty _tParticleTransformProperty) { m_tParticleTransformProperty = _tParticleTransformProperty; }

		void SetSizeProperty(FParticleSizeEffectProperty _tParticleSizeProperty) { m_tParticleSizeProperty = _tParticleSizeProperty; }

		void SetMaskProperty(FParticleMaskEffectProperty _tParticleMaskProperty) { m_tParticleMaskProperty = _tParticleMaskProperty; }

		void SetColorProperty(FParticleColorEffectProperty _tParticleColorProperty) { m_tParticleColorProperty = _tParticleColorProperty; }

	/********************
		Data Members
	********************/
	private:
		// 이 데이터를 소유한 컴포넌트
		std::weak_ptr<CSceneComponent> m_wpOwnerComponent;

	private:
		std::wstring m_wstrEffectParticleDesc = L"";

		std::wstring m_wstrVertexShaderDesc = L"";

		std::wstring m_wstrPixelShaderDesc = L"";

		std::wstring m_wstrGeomteryShaderDesc = L"";

	private:
		// 이 파티클을 표현하는 메시의 개수
		uint16 m_iNumMeshes = 1;

		// 이 파티클을 표현하는 메시
		std::shared_ptr<CPrimitiveBuffer> m_spPrimitiveBuffer = nullptr;

		// 이 파티클을 표현하는 셰이더
		std::shared_ptr<CPrimitiveShader> m_spPrimitiveShader = nullptr;

	private:
		// 이펙트 원본 데이터들 모음
		FParticlePlayEffectProperty m_tParticlePlayProperty;

		FParticleTransformEffectProperty m_tParticleTransformProperty;

		FParticleSizeEffectProperty m_tParticleSizeProperty;

		FParticleMaskEffectProperty m_tParticleMaskProperty;

		FParticleColorEffectProperty m_tParticleColorProperty;

	private:
		// 이펙트 현재 데이터들 모음
		float m_fCurPlaySeconds = 0.0f;

		float m_fCurLifeSeconds = 0.0f;

		Vector4 m_vCurColor{ 0.0f, 0.0f, 0.0f, 1.0f };

	private:
		EEffectParticleDataState m_eEffectParticleDataState = EEffectParticleDataState::ON;
	};
}
