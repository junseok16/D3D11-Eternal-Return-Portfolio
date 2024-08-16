#pragma once
#include "Text.h"

namespace Client
{
	class CGameManager;
	class CSurvivor;

	class CStatusCharValues final : public CText
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CStatusCharValues() = default;

		virtual ~CStatusCharValues() = default;
		
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
		void SetCharacterStatusType(ECharacterStatusType _eCharacterStatusType) { m_eCharacterStatusType = _eCharacterStatusType; }

	/********************
		Data Members
	********************/
	private:
		ECharacterStatusType m_eCharacterStatusType = ECharacterStatusType::ENUM_END;

		std::weak_ptr<CGameManager> m_wpGameManager;

		std::weak_ptr<CSurvivor> m_wpSurvivor;
	};
}
