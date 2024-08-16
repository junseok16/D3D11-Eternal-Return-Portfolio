#include "pch.h"
#include "CustomFont.h"

#include "DeviceManager.h"

std::shared_ptr<CFont> Engine::CFont::Create
(
	const std::shared_ptr<CDeviceManager>& _spDeviceManager,
	const std::wstring& _wstrFontPath
)
{
	const std::shared_ptr<CFont> spFont = make_shared<CFont>();
	spFont->Initialize(_spDeviceManager, _wstrFontPath);
	return spFont;
}

HRESULT Engine::CFont::Initialize
(
	const std::shared_ptr<CDeviceManager>& _spDeviceManager,
	const std::wstring& _wstrFontPath
)
{
	m_cpDevice = _spDeviceManager->GetDevice();
	m_cpDeviceContext = _spDeviceManager->GetDeviceContext();

	m_spSpriteBatch = make_shared<SpriteBatch>(m_cpDeviceContext.Get());
	m_spSpriteFont = make_shared<SpriteFont>(m_cpDevice.Get(), _wstrFontPath.c_str());
	return S_OK;
}

int32 Engine::CFont::Tick()
{
	return 0;
}

void Engine::CFont::Render(const wstring& _strText, const Vector2& _vPosition, const Vector4& _vColor, float _fRadian, const Vector2& _vOrigin, float _fScale, int32 _iOption)
{
	m_spSpriteBatch->Begin();
	
	if (_iOption == 0x1)
	{
		m_spSpriteFont->DrawString(m_spSpriteBatch.get(), _strText.c_str(), _vPosition + Vector2(+0.3f, +0.3f), Colors::Black, _fRadian, _vOrigin, _fScale);
		m_spSpriteFont->DrawString(m_spSpriteBatch.get(), _strText.c_str(), _vPosition + Vector2(+0.3f, -0.3f), Colors::Black, _fRadian, _vOrigin, _fScale);
		m_spSpriteFont->DrawString(m_spSpriteBatch.get(), _strText.c_str(), _vPosition + Vector2(-0.3f, +0.3f), Colors::Black, _fRadian, _vOrigin, _fScale);
		m_spSpriteFont->DrawString(m_spSpriteBatch.get(), _strText.c_str(), _vPosition + Vector2(-0.3f, -0.3f), Colors::Black, _fRadian, _vOrigin, _fScale);
	}
	
	m_spSpriteFont->DrawString(m_spSpriteBatch.get(), _strText.c_str(), _vPosition, _vColor, _fRadian, _vOrigin, _fScale);

	m_spSpriteBatch->End();
}

void Engine::CFont::Release()
{
	m_spSpriteBatch.reset();
	m_spSpriteFont.reset();

	m_cpDeviceContext = nullptr;
	m_cpDevice = nullptr;
}
