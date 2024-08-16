#pragma once
#include "Manager.h"

namespace Engine
{
	// buffer
	class CVertexBuffer;
	class CIndexBuffer;
	class CConstantBuffer;

	// texture
	class CTexture;

	// state
	class CSampler;
	class CDepthStencil;
	class CBlend;

	// shader
	class CVertexShader;
	class CPixelShader;

	// manager
	class CDeviceManager;
	class CLightManager;

	// handler
	class CViewHandler;
	class CStateHandler;
	class CShaderHandler;

	class ENGINE_DLL CPostProcessManager : public CManager
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CPostProcessManager() = default;

		virtual ~CPostProcessManager() = default;

	/********************
		Events
	********************/
	public:
		HRESULT PreInitialize(const std::shared_ptr<CLightManager>& _spLightManager);

		HRESULT Initialize();

		int32 Tick();

		void Render();

		virtual void Release() override;
		
	public:
		void RenderLight();

		void RenderPostProcess();

		void RenderDebug();

	/********************
		Methods
	********************/
	public:
		HRESULT BeginViewGroup(const std::wstring& _wstrViewGroupName);

		HRESULT EndViewGroup();

	/********************
		Data Members
	********************/
	private:
		std::weak_ptr<CDeviceManager> m_wpDeviceManager;

		std::weak_ptr<CLightManager> m_wpLightManager;

		std::weak_ptr<CViewHandler> m_wpViewHandler;

		std::weak_ptr<CStateHandler> m_wpStateHandler;

		std::weak_ptr<CShaderHandler> m_wpShaderHandler;

	private:
		Matrix m_matDeferredWorld = Matrix::Identity;

		Matrix m_matDeferredView = Matrix::Identity;

		Matrix m_matDeferredOrthogonalProjection = Matrix::Identity;

	private:
		// 버텍스 버퍼
		std::shared_ptr<CVertexBuffer> m_spVertexBuffer = nullptr;

		// 인덱스 버퍼
		std::shared_ptr<CIndexBuffer> m_spIndexBuffer = nullptr;

	private:
		// 버텍스 셰이더
		std::shared_ptr<CVertexShader> m_spVertexShader = nullptr;

		// 상수 버퍼
		std::shared_ptr<CConstantBuffer> m_spVSConstantBuffers;

	private:
		// 픽셀 셰이더
		std::shared_ptr<CPixelShader> m_spPostProcessPixelShader = nullptr;

		// 상수 버퍼
		std::shared_ptr<CConstantBuffer> m_spPSConstantBuffers[2]{ nullptr };

		// 텍스처들
		std::vector<std::shared_ptr<CTexture>> m_vecPostProcessPixelShaderTextures;

		// 샘플러
		std::shared_ptr<CSampler> m_spPSSampler[3]{ nullptr };
	};
}
