#pragma once
#include "ConstantBuffer.h"

namespace Engine
{
	class CUI;

    class CSize2DConstantBuffer final : public CConstantBuffer
    {
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CSize2DConstantBuffer() = default;

		virtual ~CSize2DConstantBuffer() = default;
		
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
		void SetWidth(float _fWidth) { m_tSize2D.m_fWidth = _fWidth; }

		void SetHeight(float _fHeight) { m_tSize2D.m_fHeight = _fHeight; }

		void SetMaxWidth(float _fMaxWidth) { m_tSize2D.m_fMaxWidth = _fMaxWidth; }

		void SetMaxHeight(float _fMaxHeight) { m_tSize2D.m_fMaxHeight = _fMaxHeight; }

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
		std::weak_ptr<CUI> m_wpUI;

		FSize2D m_tSize2D;
    };
}
