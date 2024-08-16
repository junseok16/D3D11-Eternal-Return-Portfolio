#pragma once

namespace Client
{
	class CClientModule;

	class CManager : public enable_shared_from_this<CManager>
	{
	public:
		template<typename T>
		static std::shared_ptr<T> Create(const std::shared_ptr<CClientModule>& _spClientModule)
		{
			const std::shared_ptr<T> spManager = make_shared<T>();
			spManager->SetClientModule(_spClientModule);
			return spManager;
		}

		virtual void Release();

	public:
		void SetClientModule(const std::shared_ptr<CClientModule>& _spClientModule) { m_wpClientModule = _spClientModule; }

		std::shared_ptr<CClientModule> GetClientModule() const { return m_wpClientModule.expired() ? nullptr : m_wpClientModule.lock(); }

	protected:
		std::weak_ptr<CClientModule> m_wpClientModule;
	};
}
