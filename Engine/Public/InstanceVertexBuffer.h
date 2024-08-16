#pragma once
#include "Buffer.h"

namespace Engine
{
    class CInstanceVertexBuffer final : public IBuffer
    {
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CInstanceVertexBuffer() = default;

		virtual ~CInstanceVertexBuffer() = default;
		
	/********************
		Events
	********************/
	public:
		virtual HRESULT Initialize(std::shared_ptr<FModelDesc> _spModelDesc = nullptr, int32 _iNumInstances = -1, EPrimitiveType _ePrimitiveType = EPrimitiveType::ENUM_END) override;

		virtual void Release() override;

		int32 Tick(float _fDeltaSeconds);

	/********************
		Methods
	********************/
	public:
        void IASetVertexBuffer();

		void IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY _ePrimitiveTopology);
		
	/********************
		Data Members
	********************/
    protected:
		// 버텍스 버퍼
		uint32 m_iOffset = 0;

		uint32 m_iStride = 0;

		uint32 m_iNumVertices = 0;

		uint32 m_iNumVertexBuffers = 0;
		
	protected:
		// 인스턴스 버퍼
		ComPtr<ID3D11Buffer> m_cpInstanceBuffer = nullptr;

		uint32 m_iInstanceOffset = 0;

		uint32 m_iInstanceStride = 0;

		uint32 m_iNumInstances = 0;
    };
}
