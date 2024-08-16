#pragma once
#include "ConstantBuffer.h"

namespace Engine
{
	class CDeferredWorldViewProjectionConstantBuffer : public CConstantBuffer
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CDeferredWorldViewProjectionConstantBuffer() = default;

		virtual ~CDeferredWorldViewProjectionConstantBuffer() = default;
		
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
		void SetWorldMatrix(const Matrix& _matWorld) { m_tWorldViewProjectionConstantBuffer.m_matWorld = _matWorld; }

		void SetViewMatrix(const Matrix& _matView) { m_tWorldViewProjectionConstantBuffer.m_matView = _matView; }

		void SetProjectionMatix(const Matrix& _matProjection) { m_tWorldViewProjectionConstantBuffer.m_matProjection = _matProjection; }
		
	/********************
		Methods
	********************/
	public:
		virtual void TickConstantBuffer(uint32 _iIndex) override;

		virtual void CopyConstantBuffer(uint32 _iIndex) override;
		
	private:
		FWorldViewProjectionConstantBuffer m_tWorldViewProjectionConstantBuffer;
	};
}
