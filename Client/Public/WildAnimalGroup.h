#pragma once
#include "Actor.h"

namespace Client
{
	class CWildAnimal;

	class CWildAnimalGroup final : public CActor
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CWildAnimalGroup() = default;

		virtual ~CWildAnimalGroup() = default;

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
		void AddWildAnimal(const std::shared_ptr<CWildAnimal>& _spWildAnimal);
		
	/********************
		Getter/Setter
	********************/
	public:
		std::vector<std::weak_ptr<CWildAnimal>>& GetConsoles() { return m_vecWildAnimals; }

	/********************
		Data Members
	********************/
	protected:
		std::vector<std::weak_ptr<CWildAnimal>> m_vecWildAnimals;
	};
}
