#pragma once
#include "ConstantBuffer.h"

namespace Engine
{
    class CColorConstantBuffer : public CConstantBuffer
    {
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CColorConstantBuffer() = default;

		virtual ~CColorConstantBuffer() = default;
		
	/********************
		Events
	********************/
	public:
		virtual HRESULT Initialize(const std::shared_ptr<CActor>& _spOwnerActor, const std::wstring& _wstrConstantBufferName, uint8 _iBindPoint) override;

		virtual void Release() override;
		
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
		FColorConstantBuffer m_tColorConstantBuffer;
    };
}
