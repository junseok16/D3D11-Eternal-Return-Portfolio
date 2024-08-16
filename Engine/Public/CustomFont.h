#pragma once

namespace Engine
{
	class CDeviceManager;

	class CFont final
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CFont() = default;

		virtual ~CFont() = default;
		
	/********************
		Events
	********************/
	public:
		static std::shared_ptr<CFont> Create
		(
			const std::shared_ptr<CDeviceManager>& _spDeviceManager,
			const std::wstring& _wstrFontPath
		);

		HRESULT Initialize
		(
			const std::shared_ptr<CDeviceManager>& _spDeviceManager,
			const std::wstring& _wstrFontPath
		);

		int32 Tick();

		void Render
		(
			const wstring& _strText,
			const Vector2& _vPosition,
			const Vector4& _vColor,
			float _fRadian = 0.0f,
			const Vector2& _vOrigin = Vector2::Zero,
			float _fScale = 1.0f,
			int32 _iOption = 0
		);

		void Release();
		
	/********************
		Data Members
	********************/
	private:
		ComPtr<ID3D11Device> m_cpDevice = nullptr;

		ComPtr<ID3D11DeviceContext> m_cpDeviceContext = nullptr;

		std::shared_ptr<SpriteBatch> m_spSpriteBatch = nullptr;

		std::shared_ptr<SpriteFont> m_spSpriteFont = nullptr;
	};
}
