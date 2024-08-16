#pragma once
#include "Socket.h"

namespace Engine
{
	class CStaticMeshComponent;
	class CSkeletalMeshComponent;
}

namespace Client
{
	class CSurvivor;

    class CWeapon : public CSocket
    {
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CWeapon() = default;

		virtual ~CWeapon() = default;
		
	/********************
		Events
	********************/
	public:
		static shared_ptr<CWeapon> Create(const std::shared_ptr<CActor>& _spWeaponOwner, const std::string& _wstrBoneName, EWeaponType _eWeaponType);

		void Initialize(const std::shared_ptr<CActor>& _spWeaponOwner, const std::string& _wstrBoneName, EWeaponType _eWeaponType);

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
		void SetWeaponType(EWeaponType _eWeaponType) { m_eWeaponType = _eWeaponType; }

	/********************
		Data Members
	********************/
	private:
		std::weak_ptr<CStaticMeshComponent> m_wpStaticMeshComponent;

		std::weak_ptr<CSurvivor> m_wpSurvivor;

		ESurvivorState m_eSurvivorState = ESurvivorState::ENUM_END;

		EWeaponType m_eWeaponType = EWeaponType::ENUM_END;
    };
}
