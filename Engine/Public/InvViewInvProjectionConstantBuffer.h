#pragma once
#include "ConstantBuffer.h"

namespace Engine
{
	class CCameraManager;

	class CInvViewInvProjectionConstantBuffer final : public CConstantBuffer
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CInvViewInvProjectionConstantBuffer() = default;

		virtual ~CInvViewInvProjectionConstantBuffer() = default;
		
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
		std::weak_ptr<CCameraManager> m_wpCameraManager;

	private:
		FInvViewInvProjConstantBuffer m_tInvViewInvProjectionConstantBuffer;
	};
}
