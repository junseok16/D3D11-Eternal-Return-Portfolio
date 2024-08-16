#pragma once
#include "Object.h"

namespace Engine
{
	class CEngineModule;
	class CLevel;
	class CLayer;
	class CActor;
	class CUI;
	
	class ENGINE_DLL CWorld : public CObject
	{
	/******************
		Ctor/Dtor
	******************/
	public:
		DECLARE_SINGLETON(CWorld)

	/******************
		Events
	******************/
	public:
		HRESULT PreInitialize(std::function<std::shared_ptr<CLevel>()> _fnLevelFactory, const std::shared_ptr<CEngineModule>& _spEngineModule);

		HRESULT Initialize();

		HRESULT PostInitialize();

		HRESULT BeginPlay();

		HRESULT Tick(float _fDeltaSeconds);

		HRESULT EndPlay();

		void Release();

	/******************
		Getter/Setter
	******************/
	public:
		std::shared_ptr<CEngineModule> GetEngineModule() const { return m_wpEngineModule.expired() ? nullptr : m_wpEngineModule.lock(); }

		std::shared_ptr<CLevel> GetCurLevel() const;

	public:
		std::shared_ptr<CLevel> GetLevel(const std::wstring& _wstrLevelName) const;

		const std::unordered_map<std::wstring, std::shared_ptr<CLevel>>& GetLevels() { return m_umapLevels; }

		std::shared_ptr<CActor> GetActor(const std::wstring& _wstrActorName) const;

		const std::unordered_map<std::wstring, std::shared_ptr<CActor>>& GetActors() { return m_umapActors; }

		// const std::unordered_map<std::wstring, std::shared_ptr<CUI>>& GetUIs() { return m_umapUIs; }
		
		const std::vector<std::shared_ptr<CUI>>& GetUIs() { return m_vecUIs; }

		float GetCurDeltaSeconds() const { return m_fCurDeltaSeconds; }

	/******************
		Methods
	******************/
	public:
		template<typename T, typename = std::enable_if_t<std::is_base_of_v<CLevel, T>>>
		std::shared_ptr<T> CreateLevel(const std::wstring& _wstrLevelName)
		{
			if (m_umapLevels.find(_wstrLevelName) != m_umapLevels.end()) { return nullptr; }

			std::shared_ptr<CLevel> spLevel = std::make_shared<T>(_wstrLevelName);
			spLevel->SetOwnerWorld(static_pointer_cast<CWorld>(shared_from_this()));
			AddLevelToWorld(_wstrLevelName, spLevel);
			return spLevel;
		}

		std::shared_ptr<CLevel> CreateLevel(std::function<std::shared_ptr<CLevel>()> _fnLevel);

		template<typename T, typename = std::enable_if_t<std::is_base_of_v<CLevel, T>>>
		std::shared_ptr<T> FindLevel(const std::wstring& _wstrLevelName)
		{
			if (m_umapLevels.find(_wstrLevelName) == m_umapLevels.end()) { return nullptr; }
			return std::dynamic_pointer_cast<T>(m_umapLevels[_wstrLevelName]);
		}

		void AddActorToWorld(const std::wstring& _wstrActorName, std::shared_ptr<CActor> _spActor);

		void AddUIToWorld(const std::wstring& _wstrUIName, std::shared_ptr<CUI> _spUI);

	private:
		void AddLevelToWorld(const std::wstring& _wstrLevelName, std::shared_ptr<CLevel> _spLevel);

	/******************
		Data Members
	******************/
	private:
		std::weak_ptr<CEngineModule> m_wpEngineModule;

	private:
		// 현재 레벨
		std::weak_ptr<CLevel> m_wpCurLevel;

	private:
		// 이 월드에 있는 모든 레벨들
		std::unordered_map<std::wstring, std::shared_ptr<CLevel>> m_umapLevels;

		// 이 월드에 있는 모든 레이어들
		std::unordered_map<std::wstring, std::shared_ptr<CLayer>> m_umapLayers;

		// 이 월드에 있는 모든 액터들
		std::unordered_map<std::wstring, std::shared_ptr<CActor>> m_umapActors;

		// 이 월드에 있는 모든 사용자 인터페이스들
		std::unordered_map<std::wstring, std::shared_ptr<CUI>> m_umapUIs;

		// 이 월드에 있는 모든 사용자 인터페이스들
		std::vector<std::shared_ptr<CUI>> m_vecUIs;

		float m_fCurDeltaSeconds = 0.0f;
	};
}
