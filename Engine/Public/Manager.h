#pragma once

namespace Engine
{
	class CEngineModule;

	class ENGINE_DLL CManager : public enable_shared_from_this<CManager>
	{
	public:
		template<typename T>
		static std::shared_ptr<T> Create(const std::shared_ptr<CEngineModule>& _spEngineModule)
		{
			const std::shared_ptr<T> spManager = make_shared<T>();
			spManager->SetEngineModule(_spEngineModule);
			return spManager;
		}

		virtual void Release();

	public:
		void SetEngineModule(const std::shared_ptr<CEngineModule>& _spEngineModule) { m_wpEngineModule = _spEngineModule; }

		std::shared_ptr<CEngineModule> GetEngineModule() const { return m_wpEngineModule.expired() ? nullptr : m_wpEngineModule.lock(); }

	protected:
		std::weak_ptr<CEngineModule> m_wpEngineModule;
	};
}
