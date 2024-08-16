#include "pch.h"
#include "Cell.h"

std::shared_ptr<CCell> Engine::CCell::Create(const std::array<Vector3, (int8)ECellPoint::ENUM_END>& _arrPoints, int32 _iCellIndex)
{
	const std::shared_ptr<CCell> spCell = make_shared<CCell>();
	ENSURE(spCell->Initialize(_arrPoints, _iCellIndex));
	return spCell;
}

HRESULT Engine::CCell::Initialize(const std::array<Vector3, (int8)ECellPoint::ENUM_END>& _arrPoints, int32 _iCellIndex)
{
	// 세 점의 좌표를 저장합니다.
	m_arrPoints = _arrPoints;

	// 평면의 방정식을 저장합니다.
	m_tPlane = Plane(_arrPoints[0], _arrPoints[1], _arrPoints[2]);

	// 셀의 중심을 저장합니다.
	m_vCentroid = (_arrPoints[0] + _arrPoints[1] + _arrPoints[2]) / 3.0f;

	// 셀 번호를 저장합니다.
	m_iCellIndex = _iCellIndex;

	// 정사영된 세 점의 좌표를 구합니다.
	m_arrOrthogonalPoints = _arrPoints;
	m_arrOrthogonalPoints[(int8)ECellPoint::A].y = 0.0f;
	m_arrOrthogonalPoints[(int8)ECellPoint::B].y = 0.0f;
	m_arrOrthogonalPoints[(int8)ECellPoint::C].y = 0.0f;

	// 세 변의 법선 벡터를 저장합니다.
	m_arrNormals[(int8)ECellLine::AB] = m_arrOrthogonalPoints[(int8)ECellPoint::B] - m_arrOrthogonalPoints[(int8)ECellPoint::A];
	m_arrNormals[(int8)ECellLine::AB] = { -1.0f * m_arrNormals[(int8)ECellLine::AB].z, 0.0f, m_arrNormals[(int8)ECellLine::AB].x };
	m_arrNormals[(int8)ECellLine::AB].Normalize();

	m_arrNormals[(int8)ECellLine::BC] = m_arrOrthogonalPoints[(int8)ECellPoint::C] - m_arrOrthogonalPoints[(int8)ECellPoint::B];
	m_arrNormals[(int8)ECellLine::BC] = { -1.0f * m_arrNormals[(int8)ECellLine::BC].z, 0.0f, m_arrNormals[(int8)ECellLine::BC].x };
	m_arrNormals[(int8)ECellLine::BC].Normalize();

	m_arrNormals[(int8)ECellLine::CA] = m_arrOrthogonalPoints[(int8)ECellPoint::A] - m_arrOrthogonalPoints[(int8)ECellPoint::C];
	m_arrNormals[(int8)ECellLine::CA] = { -1.0f * m_arrNormals[(int8)ECellLine::CA].z, 0.0f, m_arrNormals[(int8)ECellLine::CA].x };
	m_arrNormals[(int8)ECellLine::CA].Normalize();
	return S_OK;
}

void Engine::CCell::Release()
{
}

bool Engine::CCell::IsNeighborLine(const Vector3& _vSrcPoint, const Vector3& _vDstPoint)
{
	if (m_arrOrthogonalPoints[(int8)ECellPoint::A] == _vSrcPoint)
	{
		if (m_arrOrthogonalPoints[(int8)ECellPoint::B] == _vDstPoint) { return true; }

		if (m_arrOrthogonalPoints[(int8)ECellPoint::C] == _vDstPoint) { return true; }
	}

	if (m_arrOrthogonalPoints[(int8)ECellPoint::B] == _vSrcPoint)
	{
		if (m_arrOrthogonalPoints[(int8)ECellPoint::C] == _vDstPoint) { return true; }

		if (m_arrOrthogonalPoints[(int8)ECellPoint::A] ==  _vDstPoint) { return true; }
	}

	if (m_arrOrthogonalPoints[(int8)ECellPoint::C] == _vSrcPoint)
	{
		if (m_arrOrthogonalPoints[(int8)ECellPoint::A] == _vDstPoint) { return true; }

		if (m_arrOrthogonalPoints[(int8)ECellPoint::B] == _vDstPoint) { return true; }
	}

	return false;
}


bool Engine::CCell::IsInCell(Vector3& _vInLocalPosition, Vector3& _vOutLocalPosition, int32& _iNeighborCellIndex)
{
	for (int8 iIndex = 0; iIndex < (int8)ECellLine::ENUM_END; iIndex++)
	{
		Vector3 vDirection = _vInLocalPosition - m_arrOrthogonalPoints[iIndex];
		vDirection.Normalize();

		// 셀 밖에 있는 경우
		if (m_arrNormals[iIndex].Dot(vDirection) > 0)
		{
			_iNeighborCellIndex = m_arrNeighborCellIndices[iIndex];
			return false;
		}
	}

	float fY = -(m_tPlane.x * _vInLocalPosition.x + m_tPlane.z * _vInLocalPosition.z + m_tPlane.w) / m_tPlane.y;
	_vOutLocalPosition = { _vInLocalPosition.x, fY, _vInLocalPosition.z };
	return true;
}
