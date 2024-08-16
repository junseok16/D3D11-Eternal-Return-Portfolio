#pragma once
#include "UI.h"

namespace Engine
{
	class CFontHandler;
	class CFont;

	class ENGINE_DLL CText : public CUI
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CText() = default;

		virtual ~CText() = default;
		
	/********************
		Events
	********************/
	public:
		virtual HRESULT PreInitialize();

		virtual HRESULT Initialize();

		virtual HRESULT PostInitialize();

		virtual HRESULT BeginPlay();

		virtual int32 PreTick(float _fDeltaSeconds);

		virtual int32 Tick(float _fDeltaSeconds);
		
		virtual int32 PostTick(float _fDeltaSeconds);

		virtual HRESULT EndPlay();

		virtual void Render();

		virtual void Release();
		
	/********************
		Getter/Setter
	********************/
	public:
		void SetFontName(const wstring& _wstrFontName) { m_wstrFontName = _wstrFontName; }

		void SetText(const wstring& _wstrText) { m_wstrText = _wstrText; }

		void SetTextColor(const Vector4& _vTextColor) { m_vTextColor = _vTextColor; }

		void SetTextPosition(const Vector2& _vTextPosition) { m_vTextPosition = _vTextPosition; }

		void SetTextScale(float _fScale) { m_fScale = _fScale; }

		void SetOption(int32 _iOption) { m_iOption = _iOption; }

	/********************
		Data Members
	********************/
	protected:
		std::wstring m_wstrText = L"";

		std::wstring m_wstrFontName = L"";

		Vector4 m_vTextColor = Vector4::One;

		Vector2 m_vTextPosition = Vector2::Zero;

		Vector2 m_vOrigin = Vector2::Zero;

		float m_fRadian = 0.0f;

		float m_fScale = 1.0f;

		int32 m_iOption = 0;

	private:
		std::weak_ptr<CFontHandler> m_wpFontHandler;

		std::weak_ptr<CFont> m_wpFont;
	};
}
