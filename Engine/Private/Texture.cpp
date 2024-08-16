#include "pch.h"
#include "Texture.h"

#include "ModelHandler.h"
#include "ViewHandler.h"
#include "EffectHandler.h"

std::shared_ptr<CTexture> Engine::CTexture::Create(const std::wstring& _wstrTextureName, uint8 _iBindPoint, bool _bModel)
{
	const shared_ptr<CTexture> spTexture = make_shared<CTexture>();
	if (FAILED(spTexture->Initialize(_wstrTextureName, _iBindPoint, _bModel))) { return nullptr; }
	return spTexture;
}

HRESULT Engine::CTexture::Initialize(const std::wstring& _wstrTextureName, uint8 _iBindPoint, bool _bModel)
{
	m_wpModelHandler = CModelHandler::GetInstance();
	m_wpViewHandler = CViewHandler::GetInstance();
	m_wpEffectHandler = CEffectHandler::GetInstance();

	CHECK(!m_wpModelHandler.expired());
	CHECK(!m_wpViewHandler.expired());
	CHECK(!m_wpEffectHandler.expired());

	ComPtr<ID3D11ShaderResourceView> cpShaderResourceView = nullptr;
	if (_bModel) { cpShaderResourceView = m_wpModelHandler.lock()->FindShaderResourceView(_wstrTextureName); }

	if (!cpShaderResourceView) { cpShaderResourceView = m_wpViewHandler.lock()->FindShaderResourceView(_wstrTextureName); }
	if (!cpShaderResourceView) { cpShaderResourceView = m_wpEffectHandler.lock()->FindMaskShaderResourceView(_wstrTextureName); }
	if (!cpShaderResourceView) { cpShaderResourceView = m_wpEffectHandler.lock()->FindNoiseShaderResourceView(_wstrTextureName); }

	// 리소스 뷰가 없는 경우, 바인드 포인트만 저장합니다.
	m_iBindPoint = _iBindPoint;

	if (!cpShaderResourceView) { return E_FAIL; }
	m_cpShaderResourceView = cpShaderResourceView;
	m_wstrTextureName = _wstrTextureName;
	return S_OK;
}

void Engine::CTexture::Release()
{
	if (m_cpShaderResourceView)
	{
		m_cpShaderResourceView = nullptr;
	}
}

void Engine::CTexture::PSSetShaderResources()
{
	if (!m_cpShaderResourceView || m_iBindPoint < 0) { return; }
	m_wpViewHandler.lock()->PSSetShaderResources(m_iBindPoint, 1, m_cpShaderResourceView.GetAddressOf());
}

void Engine::CTexture::PSUnsetShaderResources()
{
	ComPtr<ID3D11ShaderResourceView> cpShaderResourceView = nullptr;
	m_wpViewHandler.lock()->PSSetShaderResources(m_iBindPoint, 1, cpShaderResourceView.GetAddressOf());
}

void Engine::CTexture::VSSetShaderResources()
{
	if (!m_cpShaderResourceView || m_iBindPoint < 0) { return; }
	m_wpViewHandler.lock()->VSSetShaderResources(m_iBindPoint, 1, m_cpShaderResourceView.GetAddressOf());
}

void Engine::CTexture::GSSetShaderResources()
{
	if (!m_cpShaderResourceView || m_iBindPoint < 0) { return; }
	m_wpViewHandler.lock()->GSSetShaderResources(m_iBindPoint, 1, m_cpShaderResourceView.GetAddressOf());
}

HRESULT Engine::CTexture::SetShaderResourceView(const std::wstring& _wstrTextureName)
{
	ComPtr<ID3D11ShaderResourceView> cpShaderResourceView = nullptr;

	if (!cpShaderResourceView) { cpShaderResourceView = m_wpModelHandler.lock()->FindShaderResourceView(_wstrTextureName); }
	if (!cpShaderResourceView) { cpShaderResourceView = m_wpViewHandler.lock()->FindShaderResourceView(_wstrTextureName); }
	if (!cpShaderResourceView) { cpShaderResourceView = m_wpEffectHandler.lock()->FindMaskShaderResourceView(_wstrTextureName); }
	if (!cpShaderResourceView) { cpShaderResourceView = m_wpEffectHandler.lock()->FindNoiseShaderResourceView(_wstrTextureName); }
	
	if (!cpShaderResourceView) { return E_FAIL; }

	m_cpShaderResourceView = cpShaderResourceView;
	m_wstrTextureName = _wstrTextureName;
	return S_OK;
}
