#pragma once

namespace Engine
{
	class CBoneOffset final
	{
	public:
		explicit CBoneOffset() = default;

		virtual ~CBoneOffset() = default;

	public:
		static std::shared_ptr<CBoneOffset> Create(uint32 _iNumBones, const vector<uint32>& _vecBoneIndices, const vector<Matrix>& _vecOffsetMatrices);

		HRESULT Initialize(uint32 _iNumBones, const vector<uint32>& _vecBoneIndices, const vector<Matrix>& _vecOffsetMatrices);

		void Release();

	public:
		uint32 GetNumBones() const { return m_iNumBones; }

		const std::vector<uint32>& GetBoneIndices() const { return m_vecBoneIndices; }

		const std::vector<Matrix>& GetOffsetMatrices() const { return m_vecOffsetMatrices; }

	private:
		uint32 m_iNumBones = 0;

		std::vector<uint32> m_vecBoneIndices;

		std::vector<Matrix> m_vecOffsetMatrices;
	};
}
