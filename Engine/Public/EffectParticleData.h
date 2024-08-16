#pragma once

namespace Engine
{
	class CSceneComponent;
	class CPrimitiveBuffer;
	class CPrimitiveShader;

	enum class EEffectParticleDataState
	{
		ON,		// ����Ʈ�� �� ����
		PLAY,	// ����Ʈ�� �Ѱ� ����ϴ� ����
		STOP,	// ����Ʈ�� �Ѱ� ����ϴ� ���� ����
		RESET,	// ����Ʈ�� ó������ �ǵ��� ����
		OFF,	// ����Ʈ�� �� ����
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
		// �� �����͸� ������ ������Ʈ
		std::weak_ptr<CSceneComponent> m_wpOwnerComponent;

	private:
		std::wstring m_wstrEffectParticleDesc = L"";

		std::wstring m_wstrVertexShaderDesc = L"";

		std::wstring m_wstrPixelShaderDesc = L"";

		std::wstring m_wstrGeomteryShaderDesc = L"";

	private:
		// �� ��ƼŬ�� ǥ���ϴ� �޽��� ����
		uint16 m_iNumMeshes = 1;

		// �� ��ƼŬ�� ǥ���ϴ� �޽�
		std::shared_ptr<CPrimitiveBuffer> m_spPrimitiveBuffer = nullptr;

		// �� ��ƼŬ�� ǥ���ϴ� ���̴�
		std::shared_ptr<CPrimitiveShader> m_spPrimitiveShader = nullptr;

	private:
		// ����Ʈ ���� �����͵� ����
		FParticlePlayEffectProperty m_tParticlePlayProperty;

		FParticleTransformEffectProperty m_tParticleTransformProperty;

		FParticleSizeEffectProperty m_tParticleSizeProperty;

		FParticleMaskEffectProperty m_tParticleMaskProperty;

		FParticleColorEffectProperty m_tParticleColorProperty;

	private:
		// ����Ʈ ���� �����͵� ����
		float m_fCurPlaySeconds = 0.0f;

		float m_fCurLifeSeconds = 0.0f;

		Vector4 m_vCurColor{ 0.0f, 0.0f, 0.0f, 1.0f };

	private:
		EEffectParticleDataState m_eEffectParticleDataState = EEffectParticleDataState::ON;
	};
}
