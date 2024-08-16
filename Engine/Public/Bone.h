#pragma once

namespace Engine
{
	class CBone final
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CBone() = default;

		virtual ~CBone() = default;
		
		explicit CBone(const CBone& _rhs);

	/********************
		Events
	********************/
	public:
		static shared_ptr<CBone> Create(const std::string& _strBoneName, const Matrix& _matLocal, int32 _iParentBone);

		HRESULT Initialize(const std::string& _strBoneName, const Matrix& _matLocal, int32 _iParentBone);

		void Release();

	/********************
		Getter/Setter
	********************/
	public:
		void SetLocalMatrix(const Matrix& _matLocal) { m_matLocal = _matLocal; }

		const Matrix& GetLocalMatrix() const { return m_matLocal; }

		const Matrix& GetWorldMatrix() const { return m_matWorld; }
		
		const std::string& GetBoneName() const { return m_strBoneName; }

	public:
		void RecalcBone(const std::vector<std::shared_ptr<CBone>>& _vecBones);

	/********************
		Data Members
	********************/
	private:
		string m_strBoneName = "";

		Matrix m_matLocal = Matrix::Identity;

		Matrix m_matWorld = Matrix::Identity;

		int32 m_iParentBone = 0;
	};
}
