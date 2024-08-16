#pragma once

namespace Parser
{
	struct TPosition final
	{
		XMFLOAT3 m_vPosition;
	};

	struct TPositionNormalTexCoordTangent final
	{
		XMFLOAT3 m_vPosition;
		XMFLOAT3 m_vNormal;
		XMFLOAT2 m_vTexCoord;
		XMFLOAT3 m_vTangent;
	};

	struct TPositionNormalTexCoordTangentBlend final
	{
		XMFLOAT3 m_vPosition;
		XMFLOAT3 m_vNormal;
		XMFLOAT2 m_vTexCoord;
		XMFLOAT3 m_vTangent;
		XMUINT4  m_vBlendIndices;
		XMFLOAT4 m_vBlendWeights;
	};
}