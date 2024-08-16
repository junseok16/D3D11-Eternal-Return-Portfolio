#pragma once
#include "Image.h"

namespace Client
{
	class CGameManager;

    class CStatusProfile final : public CImage
    {
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CStatusProfile() = default;

		virtual ~CStatusProfile() = default;
		
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
		void SetSurvivorType(ESurvivorType _eSurvivorType) { m_eSurvivorType = _eSurvivorType; }
		
	/********************
		Data Members
	********************/
	private:
		std::weak_ptr<CGameManager> m_wpGameManager;

		ESurvivorType m_eSurvivorType = ESurvivorType::ENUM_END;
    };
}
