#pragma once
#include "Actor.h"

namespace Engine
{
	class CCameraManager;

	class ENGINE_DLL CUI abstract : public CActor
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CUI() = default;

		virtual ~CUI() = default;
		
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
		void SetActive(bool _bActive) { m_bActive = _bActive; }

		void SetPriority(uint32 _iPriority) { m_iPriority = _iPriority; }

		uint32 GetPriority() const { return m_iPriority; }

		void SetPivot(Vector2 _vPivot) { m_vPivot = _vPivot; }

		Vector2 GetPivot() const { return m_vPivot; }

		void SetWidth(float _fWidth) { m_fWidth = _fWidth; }

		void SetHeight(float _fHeight) { m_fHeight = _fHeight; }

		float GetWidth() const { return m_fWidth; }

		float GetHeight() const { return m_fHeight; }

		void SetMaxWidth(float _fMaxWidth) { m_fMaxWidth = _fMaxWidth; }

		void SetMaxHeight(float _fMaxHeight) { m_fMaxHeight = _fMaxHeight; }

		float GetMaxWidth() const { return m_fMaxWidth; }

		float GetMaxHeight() const { return m_fMaxHeight; }

	public:
		void SetVertexShader(const std::wstring& _wstrVertexShaderName) { m_wstrVertexShaderName = _wstrVertexShaderName; }

		void SetPixelShader(const std::wstring& _wstrPixelShaderName) { m_wstrPixelShaderName = _wstrPixelShaderName; }

		void SetGeometryShader(const std::wstring& _wstrGeometryShaderName) { m_wstrGeometryShaderName = _wstrGeometryShaderName; }

	/********************
		Data Members
	********************/
	protected:
		bool m_bActive = true;

		uint32 m_iPriority = 0;
		
		Vector2 m_vPivot = Vector2::Zero;

		float m_fMaxWidth = 1.0f;

		float m_fMaxHeight = 1.0f;

		float m_fWidth = 1.0f;

		float m_fHeight = 1.0f;

	protected:
		std::wstring m_wstrVertexShaderName = L"";

		std::wstring m_wstrPixelShaderName = L"";

		std::wstring m_wstrGeometryShaderName = L"";
	};
}
