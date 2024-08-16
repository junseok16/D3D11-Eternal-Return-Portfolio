#pragma once
#include "Buffer.h"

namespace Engine
{
	class CIndexBuffer final : public IBuffer
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CIndexBuffer() = default;

		virtual ~CIndexBuffer() = default;
		
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
		void IASetIndexBuffer();

		void IASetPrimitiveTopology();

		void DrawIndexed();
		
	/********************
		Data Members
	********************/
	protected:
		DXGI_FORMAT m_eIndexFormat = DXGI_FORMAT::DXGI_FORMAT_R32_UINT;

		D3D11_PRIMITIVE_TOPOLOGY m_ePrimitiveTopology = D3D11_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

		uint32 m_iStride = 0;

		uint32 m_iNumIndices = 0;
	};
}
