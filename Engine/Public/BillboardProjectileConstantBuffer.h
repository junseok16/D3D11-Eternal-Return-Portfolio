#pragma once
#include "ConstantBuffer.h"

namespace Engine
{
	class CWorld;
	class CCameraManager;

	class CBillboardProjectileConstantBuffer : public CConstantBuffer
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CBillboardProjectileConstantBuffer() = default;

		virtual ~CBillboardProjectileConstantBuffer() = default;
		
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
		std::weak_ptr<CWorld> m_wpWorld;

		std::weak_ptr<CCameraManager> m_wpCameraManager;

		float m_fSumDeltaSeconds = 0.0f;

	private:
		FBillboardProjectileConstantBuffer m_tBillboardProjectileConstantBuffer;
	};
}
