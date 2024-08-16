#pragma once
#include "Socket.h"

namespace Engine
{
	class CStaticMeshComponent;
	class CSkeletalMeshComponent;
}

namespace Client
{
	class CCraftStateComponent;

	class CCraft : public CSocket
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CCraft() = default;

		virtual ~CCraft() = default;
		
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
		void SetCraftType(ECraftType _eCraftType) { m_eCraftType = _eCraftType; }

	/********************
		Data Members
	********************/
	private:
		std::weak_ptr<CSkeletalMeshComponent> m_wpSkeletalMeshComponent;

		std::weak_ptr<CCraftStateComponent> m_wpCraftStateComponent;

		ECraftType m_eCraftType = ECraftType::ENUM_END;
	};
}
