#pragma once
#include "Socket.h"

namespace Engine
{
	class CStaticMeshComponent;
}

namespace Client
{
	class CSurvivor;

	class CCraftTool : public CSocket
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CCraftTool() = default;

		virtual ~CCraftTool() = default;
		
	/********************
		Events
	********************/
	public:
		static shared_ptr<CCraftTool> Create(const std::shared_ptr<CActor>& _spWeaponOwner, const std::string& _strBoneName, ECraftToolType _eCraftToolType);

		void Initialize(const std::shared_ptr<CActor>& _spWeaponOwner, const std::string& _strBoneName, ECraftToolType _eCraftToolType);

		virtual HRESULT PreInitialize() override;

		virtual HRESULT Initialize() override;

		virtual HRESULT PostInitialize() override;

		virtual HRESULT BeginPlay() override;

		virtual int32 PreTick(float _fDeltaSeconds) override;

		virtual int32 Tick(float _fDeltaSeconds) override;
		
		virtual int32 PostTick(float _fDeltaSeconds) override;

		virtual HRESULT EndPlay() override;

		virtual void Render() override;

		virtual void Release() override;
		
	/********************
		Getter/Setter
	********************/
	public:
		void SeCraftToolType(ECraftToolType _eCraftToolType) { m_eCraftToolType = _eCraftToolType; }

	/********************
		Data Members
	********************/
	private:
		std::weak_ptr<CStaticMeshComponent> m_wpStaticMeshComponent;

		std::weak_ptr<CSurvivor> m_wpSurvivor;

		ESurvivorState m_eSurvivorState = ESurvivorState::ENUM_END;

		ECraftToolType m_eCraftToolType = ECraftToolType::ENUM_END;
	};
}

