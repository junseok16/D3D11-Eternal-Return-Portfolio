#pragma once

namespace Engine
{
	class CVertexBuffer;
	class CIndexBuffer;

	class CInstanceVertexBuffer;
	class CInstanceIndexBuffer;

	class CPrimitiveBuffer final
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CPrimitiveBuffer() = default;

		virtual ~CPrimitiveBuffer() = default;
		
	/********************
		Events
	********************/
	public:
		static std::shared_ptr<CPrimitiveBuffer> Create(EPrimitiveType _ePrimitiveType, uint32 _iNumInstances = 0);

		HRESULT Initialize(EPrimitiveType _ePrimitiveType, uint32 _iNumInstances = 0);

		int32 Tick(EEffectShapeType _eEffectShapeType, float _fDeltaSeconds);

		void Release();
		
	/********************
		Getter/Setter
	********************/
	public:
		std::shared_ptr<CVertexBuffer> GetVertexBuffer() const { return m_spVertexBuffer; }

		std::shared_ptr<CIndexBuffer> GetIndexBuffer() const { return m_spIndexBuffer; }
		
		void SetVertexBuffer(std::shared_ptr<CVertexBuffer> _spVertexBuffer);

		void SetIndexBuffer(std::shared_ptr<CIndexBuffer> _spIndexBuffer);

	/********************
		Methods
	********************/
	public:
		// �Է� ������
		void IASetVertexBuffer();

		void IASetIndexBuffer();

		void IASetPrimitiveTopology();

		void IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY _ePrimitiveTopology);

		// �׸���
		void DrawIndexed();

		void Draw();
		
		void DrawIndexedInstanced();

	/********************
		Data Members
	********************/
	private:
		EPrimitiveType m_ePrimitiveType = EPrimitiveType::ENUM_END;

	private:
		// ���ؽ� ����
		std::shared_ptr<CVertexBuffer> m_spVertexBuffer = nullptr;

		// �ε��� ����
		std::shared_ptr<CIndexBuffer> m_spIndexBuffer = nullptr;

	private:
		// �ν��Ͻ� ���ؽ� ����
		std::shared_ptr<CInstanceVertexBuffer> m_spInstanceVertexBuffer = nullptr;

		// �ν��Ͻ� �ε��� ����
		std::shared_ptr<CInstanceIndexBuffer> m_spInstanceIndexBuffer = nullptr;
	};
}
