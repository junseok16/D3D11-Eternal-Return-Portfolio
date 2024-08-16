#pragma once
#include "ConstantBuffer.h"

namespace Engine
{
	class CCameraManager;

	class CWorldInvTransWorldViewProjectionConstantBuffer final : public CConstantBuffer
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CWorldInvTransWorldViewProjectionConstantBuffer() = default;

		virtual ~CWorldInvTransWorldViewProjectionConstantBuffer() = default;
		
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
		void SetWorldMatrix(const Matrix& _matWorld) { m_tWorldInvTransWorldViewProjectionConstantBuffer.m_matWorld = _matWorld; }

		void SetInverseTransposeWorldMatrix(const Matrix& _matInverseTransposeWorld) { m_tWorldInvTransWorldViewProjectionConstantBuffer.m_matInverseTransposeWorld = _matInverseTransposeWorld; }

		void SetViewMatrix(const Matrix& _matView) { m_tWorldInvTransWorldViewProjectionConstantBuffer.m_matView = _matView; }

		void SetProjectionMatix(const Matrix& _matProjection) { m_tWorldInvTransWorldViewProjectionConstantBuffer.m_matProjection = _matProjection; }
		
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
		FWorldInvTransWorldViewProjectionConstantBuffer m_tWorldInvTransWorldViewProjectionConstantBuffer;
	};
}
