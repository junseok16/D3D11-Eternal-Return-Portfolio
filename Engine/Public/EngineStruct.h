#pragma once

/********************
	Input Layouts
********************/
namespace Engine
{
	struct ENGINE_DLL TPosition final
	{
		XMFLOAT3 m_vPosition;

		const static UINT iNumInputElementDescs = 1;
		const static D3D11_INPUT_ELEMENT_DESC m_vecInputElementDescs[1];
	};

	struct ENGINE_DLL TPositionSize final
	{
		XMFLOAT3 m_vPosition;
		XMFLOAT2 m_vPSize;

		const static UINT iNumInputElementDescs = 2;
		const static D3D11_INPUT_ELEMENT_DESC m_vecInputElementDescs[2];
	};

	struct ENGINE_DLL TPositionColor final
	{
		XMFLOAT3 m_vPosition;
		XMFLOAT3 m_vColor;

		const static UINT iNumInputElementDescs = 2;
		const static D3D11_INPUT_ELEMENT_DESC m_vecInputElementDescs[2];
	};

	struct ENGINE_DLL TPositionTexCoord2 final
	{
		XMFLOAT3 m_vPosition;
		XMFLOAT2 m_vTexCoord2;

		const static UINT iNumInputElementDescs = 2;
		const static D3D11_INPUT_ELEMENT_DESC m_vecInputElementDescs[2];
	};

	struct ENGINE_DLL TPositionTexCoord3 final
	{
		XMFLOAT3 m_vPosition;
		XMFLOAT3 m_vTexCoord3;

		const static UINT iNumInputElementDescs = 2;
		const static D3D11_INPUT_ELEMENT_DESC m_vecInputElementDescs[2];
	};

	struct ENGINE_DLL TPositionColorTexCoord final
	{
		XMFLOAT3 m_vPosition;
		XMFLOAT3 m_vColor;
		XMFLOAT2 m_vTexCoord;

		const static UINT iNumInputElementDescs = 3;
		const static D3D11_INPUT_ELEMENT_DESC m_vecInputElementDescs[3];
	};

	struct ENGINE_DLL TPositionNormalTexCoord final
	{
		XMFLOAT3 m_vPosition;
		XMFLOAT3 m_vNormal;
		XMFLOAT2 m_vTexCoord;

		const static UINT iNumInputElementDescs = 3;
		const static D3D11_INPUT_ELEMENT_DESC m_vecInputElementDescs[3];
	};

	struct ENGINE_DLL TPositionNormalTexCoordTangent final
	{
		XMFLOAT3 m_vPosition;
		XMFLOAT3 m_vNormal;
		XMFLOAT2 m_vTexCoord;
		XMFLOAT3 m_vTangent;

		const static UINT iNumInputElementDescs = 4;
		const static D3D11_INPUT_ELEMENT_DESC m_vecInputElementDescs[4];
	};

	struct ENGINE_DLL TPositionNormalTexCoordTangentBlend final
	{
		XMFLOAT3 m_vPosition;
		XMFLOAT3 m_vNormal;
		XMFLOAT2 m_vTexCoord;
		XMFLOAT3 m_vTangent;
		XMUINT4 m_vBlendIndices;
		XMFLOAT4 m_vBlendWeights;

		const static UINT iNumInputElementDescs = 6;
		const static D3D11_INPUT_ELEMENT_DESC m_vecInputElementDescs[6];
	};

	struct ENGINE_DLL TInstanceTransform final
	{
		XMFLOAT4 m_vRight;
		XMFLOAT4 m_vUp;
		XMFLOAT4 m_vLook;
		XMFLOAT4 m_vPosition;

		XMFLOAT4 m_vColor;
	};

	struct ENGINE_DLL TInstancePoint final
	{
		const static UINT iNumInputElementDescs = 7;
		const static D3D11_INPUT_ELEMENT_DESC m_vecInputElementDescs[7];
	};
}

/********************
	Aninmation
********************/
namespace Engine
{
	struct FKeyFrame final
	{
		// 현재 틱에 해당하는 크기, 이동, 회전 정보
		Vector3 m_vScale = Vector3::One;
		Vector4 m_vRotate = Vector4::Zero;
		Vector3 m_vTranslate = Vector3::Zero;
		double m_dTime = 0.0;
	};
}

/********************
	Particle Effect
********************/
namespace Engine
{
	struct FParticlePlayEffectProperty final
	{
		float m_fStartPlaySeconds = 0.0f;
		float m_fFinishPlaySeconds = 0.0f;
		float m_fMinLifeSeconds = 0.0f;
		float m_fMaxLifeSeconds = 0.0f;
		bool m_bLoop = false;
	};

	struct FParticleTransformEffectProperty
	{
		int32 m_iNumInstances = 0;
		int32 m_iEffectShapeType = 0;
		Vector3 m_vPivot = Vector3::Zero;
		Vector3 m_vCenter = Vector3::Zero;
		Vector3 m_vRange = Vector3::One;
	};

	struct FParticleSizeEffectProperty final
	{
		float m_fMinSpeed = 0.0f;
		float m_fMaxSpeed = 0.0f;
		float m_fMinSize = 0.0f;
		float m_fMaxSize = 0.0f;
	};

	struct FParticleMaskEffectProperty final
	{
		bool m_bUseParticleMask = false;
		std::wstring m_wstrParticleMaskTextureName = L"";
		int32 m_iParticleMaskRowColume[2]{ 1, 1 };
		Vector2 m_vParticleMaskUVSpeed{ 0.0f, 0.0f };
		Vector2 m_vParticleMaskMaxUV{ 1.0f, 1.0f };
	};

	struct FParticleColorEffectProperty final
	{
		Vector4 m_vStartColor{ 0.0f, 0.0f, 0.0f, 1.0f };
		Vector4 m_vFinishColor = Vector4::One;
	};
}

/********************
	Mesh Effect
********************/
namespace Engine
{
	struct FPlayEffectProperty final
	{
		float m_fStartPlaySeconds = 0.0f;
		float m_fFinishPlaySeconds = 0.0f;
		bool m_bLoop = false;
	};

	struct FMaskEffectProperty final
	{
		bool m_bUseMask = false;
		bool m_bUseColorMask = false;
		std::wstring m_wstrMaskTextureName = L"";
		int32 m_iMaskRowColume[2]{ 1, 1 };
		Vector2 m_vMaskUVSpeed{ 0.0f, 0.0f };
		Vector2 m_vMaskMaxUV{ 1.0f, 1.0f };
	};

	struct FNoiseEffectProperty final
	{
		bool m_bUseNoise = false;
		std::wstring m_wstrNoiseTextureName = L"";
		int32 m_iNoiseRowColume[2]{ 1, 1 };
		Vector2 m_vNoiseUVSpeed{ 0.0f, 0.0f };
		Vector2 m_vNoiseMaxUV{ 1.0f, 1.0f };
	};

	struct FColorEffectProperty final
	{
		Vector4 m_vStartColor{ 0.0f, 0.0f, 0.0f, 1.0f };
		Vector4 m_vFinishColor = Vector4::One;
	};

	struct FTransformEffectProperty final
	{
		Vector3 m_vStartScale = Vector3::One;
		Vector3 m_vStartRotate = Vector3::Zero;
		Vector3 m_vStartTranslate = Vector3::Zero;

		Vector3 m_vFinishScale = Vector3::One;
		Vector3 m_vFinishRotate = Vector3::Zero;
		Vector3 m_vFinishTranslate = Vector3::Zero;
	};

	struct FUVEffectProperty final
	{
		bool m_bUseEffectUV = false;
		Vector2 m_vEffectStartUV{ 0.0f, 0.0f };
		Vector2 m_vEffectFinishUV{ 1.0f, 1.0f };
	};

	struct FMeshEffectDataGroupProperty
	{
		std::wstring m_wstrMeshEffectGroupName = L"";

		std::vector<std::wstring> m_vecMeshEffectDataNames;
		std::vector<std::wstring> m_vecEffectModelDescNames;
		std::vector<std::wstring> m_vecVSDescNames;
		std::vector<std::wstring> m_vecPSDescNames;

		std::vector<FPlayEffectProperty> m_vecPlayProperties;
		std::vector<FMaskEffectProperty> m_vecMaskProperties;
		std::vector<FNoiseEffectProperty> m_vecNoiseProperties;
		std::vector<FColorEffectProperty> m_vecColorProperties;
		std::vector<FTransformEffectProperty> m_vecTransformProperties;
		std::vector<FUVEffectProperty> m_vecUVProperties;
	};

}

/********************
	Constant Buffer
********************/
namespace Engine
{
	struct FRimConstantBuffer final
	{
		Vector3 m_vCameraWorldPosition = Vector3::Zero;
		float m_fPadding = 0.0f;
		Vector3 m_vRimColor = Vector3(0.0f, 1.0f, 0.0f);
		float m_fRimStrength = 0.5f;
	};

	struct FBoneConstantBuffer final
	{
		Matrix m_matBone[256]{ Matrix::Identity };
	};

	struct FWorldViewProjectionConstantBuffer final
	{
		Matrix m_matWorld = Matrix::Identity;
		Matrix m_matView = Matrix::Identity;
		Matrix m_matProjection = Matrix::Identity;
	};

	struct FWorldViewOrthoProjConstantBuffer final
	{
		Matrix m_matWorld = Matrix::Identity;
		Matrix m_matView = Matrix::Identity;
		Matrix m_matOrthoProj = Matrix::Identity;
	};

	struct FWorldConstantBuffer final
	{
		Matrix m_matWorld = Matrix::Identity;
	};

	struct FInvViewInvProjConstantBuffer final
	{
		Matrix m_matInvView = Matrix::Identity;
		Matrix m_matInvProj = Matrix::Identity;
	};

	struct FViewOrthoProjConstantBuffer final
	{
		Matrix m_matView = Matrix::Identity;
		Matrix m_matOrthoProj = Matrix::Identity;
	};

	struct FViewProjectionConstantBuffer final
	{
		Matrix m_matView = Matrix::Identity;
		Matrix m_matProjection = Matrix::Identity;
	};

	struct FWorldInvTransWorldViewProjectionConstantBuffer final
	{
		Matrix m_matWorld = Matrix::Identity;
		Matrix m_matInverseTransposeWorld = Matrix::Identity;
		Matrix m_matView = Matrix::Identity;
		Matrix m_matProjection = Matrix::Identity;
	};

	struct FSize2D final
	{
		float m_fWidth			= 1.0f;
		float m_fHeight			= 1.0f;
		float m_fMaxWidth		= 1.0f;
		float m_fMaxHeight		= 1.0f;
	};

	struct FCameraPosition final
	{
		Vector4 m_vCameraPosition = Vector4::Zero;
		Vector4 m_vCameraForward = Vector4::UnitX;
	};

	struct FMaterialConstantBuffer final
	{
		Vector3	m_vAmbient		= { 0.5f, 0.5f, 0.5f };
		float	m_fShininess	= 1.0f;

		Vector3 m_vDiffuse		= { 0.5f, 0.5f, 0.5f };
		float	m_fPadding0		= 0.0f;

		Vector3 m_vSpecular		= { 0.5f, 0.5f, 0.5f };
		float	m_fPadding1		= 0.0f;
	};

	struct FLightConstantBuffer final
	{
		Vector3	m_vAmbient		= Vector3::One;
		float m_fRange			= 10.0f;

		Vector3 m_vDiffuse		= Vector3::One;
		float m_fFallOffBegin	= 0.0f;

		Vector3 m_vSpecular		= Vector3::One;
		float m_fFallOffEnd		= 10.0f;

		Vector3 m_vPosition		= Vector3::Zero;
		float m_fPower			= 1.0f;

		Vector3 m_vDirection	= Vector3::Down;
		float	m_fPadding0		= 0.0f;

		Vector3 m_vStrength		= Vector3::One;
		float	m_fPadding1		= 0.0f;
	};

	struct FMeshEffectTransformConstantBuffer final
	{
		Matrix m_matWorld = Matrix::Identity;
		Matrix m_matView = Matrix::Identity;
		Matrix m_matProjection = Matrix::Identity;
	};

	struct FMeshEffectConstantBuffer final
	{
		int32 m_iUseEffectUV = false;

		Vector2 m_vCurEffectUV{ 0.0f, 0.0f };

		int32 m_iUseColorMask = false;


		int32 m_iUseMask = false;

		int32 m_iMaskNumRow = 1;

		int32 m_iMaskNumColumn = 1;

		int32 m_iCurMaskIndex = 0;

		Vector2 m_vCurMaskUV{ 1.0f, 1.0f };


		int32 m_iUseNoise = false;

		int32 m_iNoiseNumRow = 1;

		int32 m_iNoiseNumColumn = 1;

		float m_fRatio = 0.0f;

		Vector2 m_vCurNoiseUV{ 1.0f, 1.0f };


		Vector4 m_vCurColor{ 0.0f, 0.0f, 0.0f, 1.0f };
	};

	struct FBillboardProjectileConstantBuffer final
	{
		Vector3 m_vCameraPosition = Vector3::Zero;
		float	m_fWidth = 1.0f;
		Matrix	m_matView = Matrix::Identity;
		Matrix	m_matProjection = Matrix::Identity;
		float	m_fDeltaSeconds = 0.0f;
		Vector3 m_vPadding = Vector3::Zero;
	};

	struct FTextureConstantBuffer final
	{
		Vector4 m_vBaseColor = Vector4::One;
		int32 m_iDiffuseTexture = 0;
		int32 m_iNormalTexture = 0;
		float m_fPadding0 = 0.0f;
		float m_fPadding1 = 0.0f;
	};

	struct FRatioConstantBuffer final
	{
		float m_fRatio = 0.0f;
		int m_iPadding0 = 0;
		float m_fPadding1 = 0.0f;
		float m_fPadding2 = 0.0f;
	};

	struct FLightViewLightProjectionConstantBuffer final
	{
		Matrix m_matLightView = Matrix::Identity;
		Matrix m_matLightProjection = Matrix::Identity;
	};

	struct FColorConstantBuffer final
	{
		Vector4 m_vColor = Vector4::One;
	};

	struct FLerpConstantBuffer final
	{
		float m_fRatio = 0.0f;
		int m_iDayType = 1;
		float m_fDayTime = 0.0f;
		float m_fNightTime = 0.0f;
	};
}