#pragma once
#include "Buffer.h"

namespace Engine
{
    class CInstanceIndexBuffer final : public IBuffer
    {
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CInstanceIndexBuffer() = default;

		virtual ~CInstanceIndexBuffer() = default;
		
	/********************
		Events
	********************/
	public:
		virtual HRESULT Initialize(std::shared_ptr<FModelDesc> _spModelDesc = nullptr, int32 _iNumInstances = -1, EPrimitiveType _ePrimitiveType = EPrimitiveType::ENUM_END) override;

		virtual void Release() override;

	/********************
		Methods
	********************/
	public:
		void IASetIndexBuffer();

		void IASetPrimitiveTopology();

		void DrawIndexedInstanced();

	/********************
		Data Members
	********************/
	protected:
		// ÀÎµ¦½º ¹öÆÛ
		DXGI_FORMAT m_eIndexFormat = DXGI_FORMAT::DXGI_FORMAT_R32_UINT;

		D3D11_PRIMITIVE_TOPOLOGY m_ePrimitiveTopology = D3D11_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

		uint32 m_iStride = 0;

		uint32 m_iNumIndices = 0;

		uint32 m_iNumInstances = 0;
    };
}
