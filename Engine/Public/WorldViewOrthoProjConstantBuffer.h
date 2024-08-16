#pragma once
#include "ConstantBuffer.h"

namespace Engine
{
	class CCameraManager;

	class CWorldViewOrthoProjConstantBuffer : public CConstantBuffer
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CWorldViewOrthoProjConstantBuffer() = default;

		virtual ~CWorldViewOrthoProjConstantBuffer() = default;
		
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
		void SetWorldMatrix(const Matrix& _matWorld) { m_tWorldViewOrthoProjConstantBuffer.m_matWorld = _matWorld; }

		void SetViewMatrix(const Matrix& _matView) { m_tWorldViewOrthoProjConstantBuffer.m_matView = _matView; }

		void SetOrthoProjMatix(const Matrix& _matProjection) { m_tWorldViewOrthoProjConstantBuffer.m_matOrthoProj = _matProjection; }
		
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
		FWorldViewOrthoProjConstantBuffer m_tWorldViewOrthoProjConstantBuffer;
    };
}
