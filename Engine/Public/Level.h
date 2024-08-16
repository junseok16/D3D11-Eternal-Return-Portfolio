#pragma once
#include "Object.h"

namespace Engine
{
	class CWorld;
	class CUI;
	class CActor;
	class CController;

	class ENGINE_DLL CLevel : public CObject
	{
	/******************
		Ctor/Dtor
	******************/
	public:
		explicit CLevel() = default;

		virtual ~CLevel() = default;

	/******************
		Events
	******************/
	public:
		virtual HRESULT PreInitialize();

		virtual HRESULT Initialize();

		virtual HRESULT PostInitialize();

	/******************
		Methods
	******************/
	public:
		/**
		* @detail		새로운 액터를 생성하고 이 레벨에 액터를 추가합니다.
		* @param[in]	const std::wstring& _wstrActorName: 생성할 액터의 이름
		* @return		std::shared_ptr<T>: 생성한 액터의 셰어드 포인터
		*/
		template<typename T, typename = std::enable_if_t<std::is_base_of_v<CActor, T>>>
		std::shared_ptr<T> CreateActor(const std::wstring& _wstrActorName, const std::wstring& _wstrLayer = L"")
		{
			if (m_umapActors.find(_wstrActorName) != m_umapActors.end()) { return nullptr; }

			std::shared_ptr<T> spActor = std::make_shared<T>();
			spActor->SetOwnerWorld(m_wpOwnerWorld.lock());
			spActor->SetOwnerLevel(std::dynamic_pointer_cast<CLevel>(shared_from_this()));
			spActor->SetActorName(_wstrActorName);

			AddActorToWorld(_wstrActorName, spActor);
			return spActor;
		}

		void AddActorToWorld(const std::wstring& _wstrActorName, std::shared_ptr<CActor> _spActor);

		/**
		* @detail		이 레벨에서 액터를 찾습니다.
		* @param[in]	const std::wstring& _wstrActorName: 찾을 액터의 이름
		* @return		액터가 있는 경우, 그 액터의 셰어드 포인터
		*				액터가 없는 경우, 널포인터
		*/
		template<typename T, typename = std::enable_if_t<std::is_base_of_v<CActor, T>>>
		std::shared_ptr<T> FindActor(const std::wstring& _wstrActorName)
		{
			if (m_umapActors.find(_wstrActorName) == m_umapActors.end()) { return nullptr; }
			return std::dynamic_pointer_cast<T>(m_umapActors[_wstrActorName].lock());
		}



		template<typename T, typename = std::enable_if_t<std::is_base_of_v<CUI, T>>>
		std::shared_ptr<T> CreateUI(const std::wstring& _wstrUIName, const std::wstring& _wstrLayer = L"")
		{
			if (m_umapUIs.find(_wstrUIName) != m_umapUIs.end()) { return nullptr; }

			std::shared_ptr<T> spUI = std::make_shared<T>();
			spUI->SetOwnerWorld(m_wpOwnerWorld.lock());
			spUI->SetOwnerLevel(std::dynamic_pointer_cast<CLevel>(shared_from_this()));
			spUI->SetActorName(_wstrUIName);

			AddUIToWorld(_wstrUIName, spUI);
			return spUI;
		}

		void AddUIToWorld(const std::wstring& _wstrUIName, std::shared_ptr<CUI> _spUI);

		template<typename T, typename = std::enable_if_t<std::is_base_of_v<CUI, T>>>
		std::shared_ptr<T> FindUI(const std::wstring& _wstrUIName)
		{
			if (m_umapUIs.find(_wstrUIName) == m_umapUIs.end()) { return nullptr; }
			return std::dynamic_pointer_cast<T>(m_umapUIs[_wstrUIName].lock());
		}

	/******************
		Getter/Setter
	******************/
	public:
		std::shared_ptr<CWorld> GetOwnerWorld() const;

		void SetOwnerWorld(std::shared_ptr<CWorld> _spOwnerWorld) { m_wpOwnerWorld = _spOwnerWorld; }

		void SetLevelName(const std::wstring& _wstrLevelName) { m_wstrLevelName = _wstrLevelName; }

		const std::wstring& GetLevelName() const { return m_wstrLevelName; }

		const std::unordered_map<std::wstring, std::weak_ptr<CActor>>& GetActors() const { return m_umapActors; }

		const shared_ptr<CController> GetController() { return m_wpController.expired() ? nullptr : m_wpController.lock(); }

		void SetPossessedPawnName(const std::wstring& _wstrPossessedPawnName) { m_wstrPossessedPawnName = _wstrPossessedPawnName; }

	/******************
		Data Members
	******************/
	private:
		// 이 레벨에 있는 핵심 액터들(게임 스테이트, 컨트롤러 등)
		std::unordered_map<std::wstring, std::weak_ptr<CActor>> m_umapCoreActors;

		// 이 레벨에 있는 모든 액터들
		std::unordered_map<std::wstring, std::weak_ptr<CActor>> m_umapActors;

		// 이 레벨에 있는 모든 사용자 인터페이스들
		std::unordered_map<std::wstring, std::weak_ptr<CUI>> m_umapUIs;

		// 이 레벨을 갖고 있는 월드
		std::weak_ptr<CWorld> m_wpOwnerWorld;

		// 이 레벨의 이름
		std::wstring m_wstrLevelName = L"";

		// 이 레벨에서 빙의할 폰
		std::wstring m_wstrPossessedPawnName = L"";

	private:
		// 컨트롤러
		std::weak_ptr<CController> m_wpController;
	};
}
