#pragma once
#include "Text.h"

namespace Client
{
	class CGameManager;
	class CSurvivor;

    class CSkillCoolDownText final : public CText
    {
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CSkillCoolDownText() = default;

		virtual ~CSkillCoolDownText() = default;
		
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
		void SetSkillType(ESkillType _eSkillType) { m_eSkillType = _eSkillType; }

	/********************
		Data Members
	********************/
	private:
		ESkillType m_eSkillType = ESkillType::ENUM_END;

		std::weak_ptr<CGameManager> m_wpGameManager;

		std::weak_ptr<CSurvivor> m_wpSurvivor;
    };
}
