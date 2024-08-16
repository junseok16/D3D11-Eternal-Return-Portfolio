#pragma once

namespace Engine
{
	class CAnimGraph;
	class CBoneOffset;
	class CVertexBuffer;
	class CIndexBuffer;

	class CMeshBuffer final
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CMeshBuffer() = default;

		virtual ~CMeshBuffer() = default;
		
	/********************
		Events
	********************/
	public:
		static std::shared_ptr<CMeshBuffer> Create(const std::wstring& _wstrModelDesc = L"");

		HRESULT Initialize(const std::wstring& _wstrModelDesc = L"");

		void Release();
		
	/********************
		Getter/Setter
	********************/
	public:
		std::shared_ptr<CVertexBuffer> GetVertexBuffer(uint16 _iMeshIndex) const { return m_vecVertexBuffers[_iMeshIndex]; }

		std::shared_ptr<CIndexBuffer> GetIndexBuffer(uint16 _iMeshIndex) const { return m_vecIndexBuffers[_iMeshIndex]; }
		
		void SetVertexBuffer(uint16 _iMeshIndex, std::shared_ptr<CVertexBuffer> _spVertexBuffer);

		void SetIndexBuffer(uint16 _iMeshIndex, std::shared_ptr<CIndexBuffer> _spIndexBuffer);

		const std::vector<std::shared_ptr<CBoneOffset>>& GetBoneOffsets() const { return m_vecBoneOffsets; }

	/********************
		Methods
	********************/
	public:
		// 입력 조립기
		void IASetVertexBuffer(uint16 _iMeshIndex);

		void IASetIndexBuffer(uint16 _iMeshIndex);

		void IASetPrimitiveTopology(uint16 _iMeshIndex);

		// 그리기
		void DrawIndexed(uint16 _iMeshIndex);
		
	/********************
		Data Members
	********************/
	private:
		std::vector<std::shared_ptr<CBoneOffset>> m_vecBoneOffsets;

		std::vector<std::shared_ptr<CVertexBuffer>> m_vecVertexBuffers;

		std::vector<std::shared_ptr<CIndexBuffer>> m_vecIndexBuffers;
	};
}
