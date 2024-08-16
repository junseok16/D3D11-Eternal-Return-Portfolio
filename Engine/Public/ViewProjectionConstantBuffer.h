#pragma once
#include "ConstantBuffer.h"

namespace Engine
{
    class CCameraManager;

    class CViewProjectionConstantBuffer final : public CConstantBuffer
    {
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CViewProjectionConstantBuffer() = default;

		virtual ~CViewProjectionConstantBuffer() = default;
		
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
		void SetViewMatrix(const Matrix& _matView) { m_tViewProjectionConstantBuffer.m_matView = _matView; }

		void SetProjectionMatix(const Matrix& _matProjection) { m_tViewProjectionConstantBuffer.m_matProjection = _matProjection; }
		
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
		FViewProjectionConstantBuffer m_tViewProjectionConstantBuffer;
    };
}
