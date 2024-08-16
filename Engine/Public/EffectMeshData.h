#pragma once

namespace Engine
{
	class CSceneComponent;
	class CMeshBuffer;
	class CMeshShader;

	enum class EEffectMeshDataState
	{
		ON,		// 이펙트를 켠 상태
		PLAY,	// 이펙트를 켜고 재생하는 상태
		STOP,	// 이펙트를 켜고 재생하다 멈춘 상태
		RESET,	// 이펙트를 처음으로 되돌린 상태
		OFF,	// 이펙트를 끈 상태
		ENUM_END
	};

	class ENGINE_DLL CEffectMeshData final : public enable_shared_from_this<CEffectMeshData>
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CEffectMeshData() = default;

		virtual ~CEffectMeshData() = default;

	/********************
		Events
	********************/
	public:
		static std::shared_ptr<CEffectMeshData> Create
		(
			const std::shared_ptr<CSceneComponent>& _spOwnerComponent,
			const std::wstring& _wstrEffectModelDesc = L"",
			const std::wstring& _wstrVertexShaderDesc = L"",
			const std::wstring& _wstrPixelShaderDesc = L""
		);

		HRESULT Initialize
		(
			const std::shared_ptr<CSceneComponent>& _spOwnerComponent,
			const std::wstring& _wstrEffectModelDesc = L"",
			const std::wstring& _wstrVertexShaderDesc = L"",
			const std::wstring& _wstrPixelShaderDesc = L""
		);

		int32 Tick(float _fDeltaSeconds);

		void Render();

		void Release();
		
		void Clear();

	/********************
		Getter/Setter
	********************/
	public:
		void SetMeshBuffer(std::shared_ptr<CMeshBuffer> _spMeshBuffer) { m_spMeshBuffer = _spMeshBuffer; }

		std::shared_ptr<CMeshBuffer> GetMeshBuffer() const { return m_spMeshBuffer; }
		
		void SetMeshShader(std::shared_ptr<CMeshShader> _spMeshShader) { m_spMeshShader = _spMeshShader; }

		std::shared_ptr<CMeshShader> GetMeshShader() const { return m_spMeshShader; }

		const std::wstring& GetEffectModelDesc() { return m_wstrEffectModelDesc; }
		
	/********************
		Methods
	********************/
	public:
		void RecalcEffectMeshData(float _fDeltaSeconds);

	/********************
		Editor
	********************/
	public:
		HRESULT ChangeEffectModelDesc(const std::wstring& _wstrEffectModelDesc);

		HRESULT ChangeShaders(const std::shared_ptr<CSceneComponent>& _spOwnerComponent, const std::wstring& _wstrVertexShaderDesc, const std::wstring& _wstrPixelShaderDesc);

	public:
		void SetEffectMeshDataName(const std::wstring& _wstrEffectMeshDataName) { m_wstrEffectMeshDataName = _wstrEffectMeshDataName; }

		void SetEffectMeshDataState(EEffectMeshDataState _eEffectMeshDataState) { m_eEffectMeshDataState = _eEffectMeshDataState; }

		FPlayEffectProperty GetPlayProperty() const { return m_tPlayProperty; }

		void SetPlayProperty(float _fStartPlaySeconds, float _fFinishPlaySeconds, bool _bLoop)
		{
			m_tPlayProperty.m_fStartPlaySeconds = _fStartPlaySeconds;
			m_tPlayProperty.m_fFinishPlaySeconds = _fFinishPlaySeconds;
			m_tPlayProperty.m_bLoop = _bLoop;
		}

		FMaskEffectProperty GetMaskProperty() const { return m_tMaskProperty; }

		void SetMaskProperty
		(
			bool _bUseMask,
			bool _bUseColorMask,
			int32 _iNumRow,
			int32 _iNumColumn,
			const Vector2& _vMaskUVSpeed,
			const Vector2& _vMaskMaxUV)
		{
			m_tMaskProperty.m_bUseMask = _bUseMask;
			m_tMaskProperty.m_bUseColorMask = _bUseColorMask;
			m_tMaskProperty.m_iMaskRowColume[0] = _iNumRow;
			m_tMaskProperty.m_iMaskRowColume[1] = _iNumColumn;
			m_tMaskProperty.m_vMaskUVSpeed = _vMaskUVSpeed;
			m_tMaskProperty.m_vMaskMaxUV = _vMaskMaxUV;
		}

		FNoiseEffectProperty GetNoiseProperty() const { return m_tNoiseProperty; }

		void SetNoiseProperty(bool _bUseNoise, int32 _iNumRow, int32 _iNumColumn, const Vector2& _vNoiseUVSpeed, const Vector2& _vNoiseMaxUV)
		{
			m_tNoiseProperty.m_bUseNoise = _bUseNoise;
			m_tNoiseProperty.m_iNoiseRowColume[0] = _iNumRow;
			m_tNoiseProperty.m_iNoiseRowColume[1] = _iNumColumn;
			m_tNoiseProperty.m_vNoiseUVSpeed = _vNoiseUVSpeed;
			m_tNoiseProperty.m_vNoiseMaxUV = _vNoiseMaxUV;
		}

		FColorEffectProperty GetColorProperty() const { return m_tColorProperty; }

		void SetColorProperty(const Vector4& _vStartColor, const Vector4& _vFinishColor)
		{
			m_tColorProperty.m_vStartColor = _vStartColor;
			m_tColorProperty.m_vFinishColor = _vFinishColor;
		}

		FTransformEffectProperty GetTransformProperty() const { return m_tTransformProperty; }

		void SetTransformProperty
		(
			const Vector3& _vStartScale, const Vector3& _vStartRotate, const Vector3& _vStartTranslate,
			const Vector3& _vFinishScale, const Vector3& _vFinishRotate, const Vector3& _vFinishTranslate
		)
		{
			m_tTransformProperty.m_vStartScale = _vStartScale;
			m_tTransformProperty.m_vStartRotate = _vStartRotate;
			m_tTransformProperty.m_vStartTranslate = _vStartTranslate;

			m_tTransformProperty.m_vFinishScale = _vFinishScale;
			m_tTransformProperty.m_vFinishRotate = _vFinishRotate;
			m_tTransformProperty.m_vFinishTranslate = _vFinishTranslate;
		}

		FUVEffectProperty GetUVProperty() const { return m_tUVProperty; }

		void SetUVProperty(bool _bUseUV, const Vector2& _vStartUV, const Vector2& _vFinishUV)
		{
			m_tUVProperty.m_bUseEffectUV = _bUseUV;
			m_tUVProperty.m_vEffectStartUV = _vStartUV;
			m_tUVProperty.m_vEffectFinishUV = _vFinishUV;
		}

		const Matrix& GetEffectMatrix() const { return m_matEffect; }

		int32 GetCurMaskIndex() const { return m_iCurMaskIndex; }

		const wstring& GetVertexShaderDescName() const { return m_wstrVertexShaderDesc; }

		const wstring& GetPixelShaderDescName() const { return m_wstrPixelShaderDesc; }

	public:
		void ModifyPixelShaderTexture(int32 _iMeshIndex, int32 _iTextureIndex, const std::wstring& _wstrTextureName);

		const Vector2& GetCurEffectUV() const { return m_vCurEffectUV; }

		const Vector4& GetCurColor() const { return m_vCurColor; }

		const Vector2& GetCurMaskUV() const { return m_vCurMaskUV; }

		const Vector2& GetCurNoiseUV() const { return m_vCurNoiseUV; }

		float GetCurRatio() const { return m_fCurRatio; }

	/********************
		Data Members
	********************/
	private:
		// 이 데이터를 소유한 컴포넌트
		std::weak_ptr<CSceneComponent> m_wpOwnerComponent;

		std::wstring m_wstrEffectMeshDataName = L"";

	private:
		// 모델의 이름
		std::wstring m_wstrEffectModelDesc = L"";

		std::wstring m_wstrVertexShaderDesc = L"";

		std::wstring m_wstrPixelShaderDesc = L"";

		// 이 모델을 표현하는 메시의 개수
		uint16 m_iNumMeshes = 0;

		// 이 모델을 표현하는 메시
		std::shared_ptr<CMeshBuffer> m_spMeshBuffer = nullptr;

		// 이 모델을 표현하는 셰이더
		std::shared_ptr<CMeshShader> m_spMeshShader = nullptr;

	private:
		// 이펙트 원본 데이터들 모음
		FPlayEffectProperty m_tPlayProperty;

		FMaskEffectProperty m_tMaskProperty;

		FNoiseEffectProperty m_tNoiseProperty;

		FColorEffectProperty m_tColorProperty;

		FTransformEffectProperty m_tTransformProperty;

		FUVEffectProperty m_tUVProperty;

	private:
		// 이펙트 현재 데이터들 모음
		float m_fCurPlaySeconds = 0.0f;

		Vector4 m_vCurColor{ 0.0f, 0.0f, 0.0f, 1.0f };

		Vector2 m_vCurEffectUV = Vector2::Zero;

		Vector2 m_vCurMaskUV = Vector2::One;

		Vector2 m_vCurNoiseUV = Vector2::One;

		Matrix m_matEffect = Matrix::Identity;

		Vector3 m_vCurScale = Vector3::One;

		Vector3 m_vCurRotate = Vector3::Zero;

		Vector3 m_vCurTranslate = Vector3::Zero;

		int32 m_iCurMaskIndex = 0;

		float m_fCurRatio = 0.0f;

	private:
		EEffectMeshDataState m_eEffectMeshDataState = EEffectMeshDataState::ON;
	};
}
