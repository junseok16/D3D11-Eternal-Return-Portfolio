#pragma once
#include "UI.h"

namespace Engine
{
    class CGeometryComponent;
	class CActor;

    class ENGINE_DLL CSlider : public CUI
    {
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CSlider() = default;

		virtual ~CSlider() = default;
		
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
		
	private:
		virtual void TickSlider();

	/********************
		Getter/Setter
	********************/
	public:
		void SetPrimitiveType(EPrimitiveType _ePrimitiveType) { m_ePrimitiveType = _ePrimitiveType; }

		void SetFrontSliderName(const std::wstring& _wstrFrontSliderName) { m_wstrFrontSliderName = _wstrFrontSliderName; }
		
		void SetActor(const std::shared_ptr<CActor>& _spActor) { m_wpActor = _spActor; }

	/********************
		Data Members
	********************/
	protected:
		std::weak_ptr<CGeometryComponent> m_wpFrontSliderComponent;

		std::wstring m_wstrFrontSliderName = L"";

		EPrimitiveType m_ePrimitiveType = EPrimitiveType::ENUM_END;

	protected:
		std::weak_ptr<CActor> m_wpActor;

		float m_fPercentage = 0.0f;
    };
}
