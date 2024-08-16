#pragma once

namespace Editor
{
	class CEditorModule;

	class CManager : public enable_shared_from_this<CManager>
	{
	public:
		template<typename T>
		static std::shared_ptr<T> Create(const std::shared_ptr<CEditorModule>& _spEditorModule)
		{
			const std::shared_ptr<T> spManager = make_shared<T>();
			spManager->SetEditorModule(_spEditorModule);
			return spManager;
		}

		virtual void Release();

	public:
		void SetEditorModule(const std::shared_ptr<CEditorModule>& _spEditorModule) { m_wpEditorModule = _spEditorModule; }

		std::shared_ptr<CEditorModule> GetEditorModule() const { return m_wpEditorModule.expired() ? nullptr : m_wpEditorModule.lock(); }

	protected:
		std::weak_ptr<CEditorModule> m_wpEditorModule;
	};
}
