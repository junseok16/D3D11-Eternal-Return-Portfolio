#pragma once
#include "ConstantBuffer.h"

namespace Engine
{
	class CTextureConstantBuffer : public CConstantBuffer
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CTextureConstantBuffer() = default;

		virtual ~CTextureConstantBuffer() = default;
		
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
		void SetDiffuseTexture(int32 _iDiffuseTexture) { m_tTextureConstantBuffer.m_iDiffuseTexture = _iDiffuseTexture; }

		void SetNormalTexture(int32 _iNormalTexture) { m_tTextureConstantBuffer.m_iNormalTexture = _iNormalTexture; }

		void SetBaseColor(const Vector4& _vBaseColor) { m_tTextureConstantBuffer.m_vBaseColor = _vBaseColor; }

		bool IsDiffuseTexture() const { return m_tTextureConstantBuffer.m_iDiffuseTexture; }

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
		FTextureConstantBuffer m_tTextureConstantBuffer;
	};
}
