#pragma once
#include "Text.h"

namespace Client
{
	enum class EItemInfoType
	{
		NAME,
		LEVEL,
		CATEGORY,
		EFFECT,
		EXPLANATION,
		ENUM_END
	};

	class CItem;

    class CItemInfoText : public CText
    {
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CItemInfoText() = default;

		virtual ~CItemInfoText() = default;
		
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

	public:
		void SetItemInfoType(EItemInfoType _eItemInfoType) { m_eItemInfoType = _eItemInfoType; }

	private:
		EItemInfoType m_eItemInfoType = EItemInfoType::ENUM_END;

		std::weak_ptr<CItem> m_wpItem;
    };
}
