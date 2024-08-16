#pragma once
#include "UI.h"

namespace Engine
{
	class CDeviceManager;
	class CGeometryComponent;

	class ENGINE_DLL CImage : public CUI
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CImage() = default;

		virtual ~CImage() = default;
		
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
		void SetPrimitiveType(EPrimitiveType _ePrimitiveType) { m_ePrimitiveType = _ePrimitiveType; }

		void SetImageNames(const std::vector<std::wstring>& _vecImageNames) { m_vecImageNames = _vecImageNames; }

		void SetTextureIndex(uint32 _iTextureIndex);

		float GetCurRatio() const { return m_fCurRatio; }

	/********************
		Data Members
	********************/
	protected:
		std::weak_ptr<CGeometryComponent> m_wpGeometryComponent;

		EPrimitiveType m_ePrimitiveType = EPrimitiveType::ENUM_END;

		std::vector<std::wstring> m_vecImageNames;

		float m_fCurRatio = 0.0f;
	};
}
