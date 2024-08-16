#pragma once
#include "Manager.h"

namespace Engine
{
	class CLightComponent;
	
	class CShaderHandler;
	
	class CVertexBuffer;
	class CIndexBuffer;
	class CVertexShader;
	class CPixelShader;
	class CTexture;
	class CSampler;
	class CConstantBuffer;

	class CLightManager final : public Engine::CManager
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CLightManager() = default;

		virtual ~CLightManager() = default;

	/********************
		Events
	********************/
	public:
		HRESULT PreInitialize();

		HRESULT Initialize();

		int32 Tick();

		void Render();

		virtual void Release() override;

	/********************
		Methods
	********************/
	public:
		HRESULT AddLightComponent(const std::wstring& _wstrLightComponentName, const std::shared_ptr<CLightComponent>& _spLightComponent, ELightType _eLightType);
		
		HRESULT RemoveLightComponent(const std::wstring& _wstrLightComponentName, ELightType _eLightType);

		std::shared_ptr<CLightComponent> FindLightComponent(const std::wstring& _wstrLightComponentName, ELightType _eLightType);
		
	/********************
		Getter/Setter
	********************/
	public:
		void SetVertexBuffer(const std::shared_ptr<CVertexBuffer>& _spVertexBuffer) { m_spVertexBuffer = _spVertexBuffer; }

		void SetIndexBuffer(const std::shared_ptr<CIndexBuffer>& _spIndexBuffer) { m_spIndexBuffer = _spIndexBuffer; }

		void SetVertexShader(const std::shared_ptr<CVertexShader> _spVertexShader) { m_spVertexShader = _spVertexShader; }

		void SetVertexConstantBuffer(const std::shared_ptr<CConstantBuffer>& _spVSConstantBuffers) { m_spVSConstantBuffers = _spVSConstantBuffers; }

	/********************
		Data Members
	********************/
	private:
		// ����Ʈ ������Ʈ��
		std::unordered_map<std::wstring, std::weak_ptr<CLightComponent>> m_umapDirectionalLightComponents;

		std::unordered_map<std::wstring, std::weak_ptr<CLightComponent>> m_umapPointLightComponents;

		std::unordered_map<std::wstring, std::weak_ptr<CLightComponent>> m_umapSpotLightComponents;

		// ���� ����Ʈ ������Ʈ
		std::weak_ptr<CLightComponent> m_wpLightComponent;

	private:
		// ���ؽ� ����
		std::shared_ptr<CVertexBuffer> m_spVertexBuffer = nullptr;

		// �ε��� ����
		std::shared_ptr<CIndexBuffer> m_spIndexBuffer = nullptr;

	private:
		// ���ؽ� ���̴�
		std::shared_ptr<CVertexShader> m_spVertexShader = nullptr;

		// ��� ����
		std::shared_ptr<CConstantBuffer> m_spVSConstantBuffers = nullptr;

	private:
		// �ȼ� ���̴�
		std::shared_ptr<CPixelShader> m_spDirectionalLightPixelShader = nullptr;

		std::shared_ptr<CPixelShader> m_spPointLightPixelShader = nullptr;

		// ��� ����
		// std::shared_ptr<CConstantBuffer> m_spDirectionalLightPSConstantBuffers = nullptr;

		// std::shared_ptr<CConstantBuffer> m_spPointLightPSConstantBuffers[2]{ nullptr };

	private:
		// �ؽ�ó
		std::shared_ptr<CTexture> m_spNormalTexture = nullptr;
		
		std::shared_ptr<CTexture> m_spDepthTexture = nullptr;

		// ���÷�
		std::shared_ptr<CSampler> m_spPSSampler[2]{ nullptr };

	private:
		std::weak_ptr<CShaderHandler> m_wpShaderHandler;
	};
}
