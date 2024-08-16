#pragma once
#include "Buffer.h"

namespace Engine
{
	class CVertexBuffer final : public IBuffer
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CVertexBuffer() = default;

		virtual ~CVertexBuffer() = default;
		
	/********************
		Events
	********************/
	public:
		virtual HRESULT Initialize(std::shared_ptr<FModelDesc> _spModelDesc = nullptr, int32 _iMeshIndex = -1, EPrimitiveType _ePrimitiveType = EPrimitiveType::ENUM_END) override;

		virtual void Release() override;

	/********************
		Methods
	********************/
	public:
        void IASetVertexBuffer();

		void IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY _ePrimitiveTopology);

		void Draw();

	/********************
		Data Members
	********************/
    protected:
        uint32 m_iOffset = 0;

        uint32 m_iStride = 0;

        uint32 m_iNumVertices = 0;
	};
}
