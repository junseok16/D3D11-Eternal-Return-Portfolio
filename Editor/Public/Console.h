#pragma once
#include "Actor.h"

namespace Engine
{
	class CStaticMeshComponent;
	class CSphereComponent;
}

namespace Editor
{
	class CConsole : public CActor
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CConsole() = default;

		virtual ~CConsole() = default;

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
		// actor overrides
		virtual void OnCollisionEnter(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst);

		virtual void OnCollisionStay(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst);

		virtual void OnCollisionExit(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst);
		
	/********************
		Getter/Setter
	********************/
	public:
		void SetInstancableActorType(EInstancableActorType _eInstancableActorType) { m_eInstancableActorType = _eInstancableActorType; }

		EInstancableActorType GetInstancableActorType() const { return m_eInstancableActorType; }

		void SetConsoleType(EConsoleType _eConsoleType) { m_eConsoleType = _eConsoleType; }

		EConsoleType GetConsoleType() const { return m_eConsoleType; }

	/********************
		Data Members
	********************/
	protected:
		EInstancableActorType m_eInstancableActorType = EInstancableActorType::CONSOLE;

		EConsoleType m_eConsoleType = EConsoleType::ENUM_END;

		std::weak_ptr<CSphereComponent> m_wpSphereComponents;
	};
}
