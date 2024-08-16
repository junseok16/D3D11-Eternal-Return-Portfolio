#pragma once
#include "ConstantBuffer.h"

namespace Engine
{
	class CLightManager;
	class CLightComponent;

	class CLightConstantBuffer : public CConstantBuffer
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CLightConstantBuffer() = default;

		virtual ~CLightConstantBuffer() = default;
		
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
		void SetLightDesc(const std::shared_ptr<CLightComponent>& _spLightComponent, ELightType _eLightType);

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
		std::weak_ptr<CLightManager> m_wpLightManager;

		std::weak_ptr<CLightComponent> m_wpLightComponent;

	private:
		FLightConstantBuffer m_tLightConstantBuffer;

		std::wstring m_wstrLightComponentName = L"";
			
		ELightType m_eLightType = ELightType::ENUM_END;
	};
}
