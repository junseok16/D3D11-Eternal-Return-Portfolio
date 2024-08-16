#pragma once
#include "ConstantBuffer.h"

namespace Engine
{
    class CBoneConstantBuffer : public CConstantBuffer
    {
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CBoneConstantBuffer() = default;

		virtual ~CBoneConstantBuffer() = default;
		
	/********************
		Events
	********************/
	public:
		virtual HRESULT Initialize(const std::shared_ptr<CActor>& _spOwnerActor, const std::wstring& _wstrConstantBufferName, uint8 _iBindPoint) override;

		virtual void Release() override;

	/********************
		Getter/Setter
	********************/
	public:

	/********************
		Methods
	********************/
	public:
		virtual void TickConstantBuffer(uint32 _iIndex) override;

		virtual void CopyConstantBuffer(uint32 _iIndex) override;
		
	/********************
		Data Members
	********************/
	private:
		FBoneConstantBuffer m_tBoneConstantBuffer;
    };
}
