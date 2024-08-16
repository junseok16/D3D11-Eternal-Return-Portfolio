#pragma once
#include "ConstantBuffer.h"

namespace Engine
{
	class CWorldConstantBuffer final : public CConstantBuffer
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CWorldConstantBuffer() = default;

		virtual ~CWorldConstantBuffer() = default;
		
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
		void SetWorldMatrix(const Matrix& _matWorld) { m_tWorldConstantBuffer.m_matWorld = _matWorld; }

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
		FWorldConstantBuffer m_tWorldConstantBuffer;
	};
}
