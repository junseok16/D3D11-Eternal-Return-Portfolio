#pragma once
#include "Actor.h"

namespace Engine
{
	class CStaticMeshComponent;
}

namespace Editor
{
	class CConsole;

	class CConsoleGroup final : public CActor
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CConsoleGroup() = default;

		virtual ~CConsoleGroup() = default;

	/********************
		Events
	********************/
	public:
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
		Methods
	********************/
	public:
		void AddConsole(const shared_ptr<CConsole>& _spConsole);

	/********************
		Getter/Setter
	********************/
	public:
		void SetConsoleType(EConsoleType _eConsoleType) { m_eConsoleType = _eConsoleType; }

		EConsoleType GetConsoleType() const { return m_eConsoleType; }

		std::vector<std::weak_ptr<CConsole>>& GetConsoles() { return m_vecConsoles; }

	/********************
		Data Members
	********************/
	protected:
		EInstancableActorType m_eInstancableActorType = EInstancableActorType::CONSOLE_GROUP;

		EConsoleType m_eConsoleType = EConsoleType::ENUM_END;

		std::weak_ptr<CStaticMeshComponent> m_wpStaticMeshComponent;

		std::vector<std::weak_ptr<CConsole>> m_vecConsoles;
	};
}
