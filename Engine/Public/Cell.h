#pragma once

namespace Engine
{
	class CCell final
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CCell() = default;

		virtual ~CCell() = default;
		
	/********************
		Events
	********************/
	public:
		static std::shared_ptr<CCell> Create(const std::array<Vector3, (int8)ECellPoint::ENUM_END>& _arrPoints, int32 _iCellIndex);

		HRESULT Initialize(const std::array<Vector3, (int8)ECellPoint::ENUM_END>& _arrPoints, int32 _iCellIndex);

		void Release();

	/********************
		Getter/Setter
	********************/
	public:
		Vector3 GetOrthogonalPoint(ECellPoint _eCellPoint) { return m_arrOrthogonalPoints[(int8)_eCellPoint]; }

		void SetNeighborCell(ECellLine _eCellLine, const std::shared_ptr<CCell>& _spNeighborCell)
		{
			m_arrNeighborCellIndices[(int8)_eCellLine] = _spNeighborCell->m_iCellIndex;
		}

		Vector3 GetCentroidPosition() const { return m_vCentroid; }

		int32 GetCellIndex() const { return m_iCellIndex; }

		const std::array<Vector3, (int8)ECellPoint::ENUM_END>& GetThreePoints() { return m_arrPoints; }

	/********************
		Methods
	********************/
	public:
		bool IsNeighborLine(const Vector3& _vSrcPoint, const Vector3& _vDstPoint);

		bool IsInCell(Vector3& _vInLocalPosition, Vector3& _vOutLocalPosition, int32& iNeighborCellIndex);
		
	/********************
		Data Members
	********************/
	private:
		// 이 셀이 갖고 있는 세 점의 좌표들
		std::array<Vector3, (int8)ECellPoint::ENUM_END> m_arrPoints;

		// 세 점의 좌표로 만든 평면의 방정식
		Plane m_tPlane{};

		// xz평면으로 정사영된 세 점의 좌표들
		std::array<Vector3, (int8)ECellPoint::ENUM_END> m_arrOrthogonalPoints;
		
		// 이 셀이 갖고 있는 세 변의 법선 벡터들
		std::array<Vector3, (int8)ECellLine::ENUM_END> m_arrNormals;

		// 이 셀의 번호
		int32 m_iCellIndex = 0;

		// 셀의 중심
		Vector3 m_vCentroid = Vector3::Zero;

		// 이 셀에 이웃한 다른 셀들의 번호
		std::array<int32, (int8)ECellLine::ENUM_END> m_arrNeighborCellIndices{ -1, -1, -1 };
	};
}

