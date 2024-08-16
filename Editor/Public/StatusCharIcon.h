#pragma once
#include "Image.h"

namespace Editor
{
	class CStatusCharIcon : public CImage
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CStatusCharIcon() = default;

		virtual ~CStatusCharIcon() = default;

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
	};
}
