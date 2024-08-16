#pragma once
#include "Manager.h"

namespace Client
{
	class CItemInfoPanel;
	class CSkillPanel;
	class CStatusPanel;
	class CItemPanel;
	class CItemBoxPanel;
	class CGamePlayPanel;
	class CInItemBoxPanel;
	class CInGamePanel;

	class CUIManager : public CManager
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		DECLARE_SINGLETON(CUIManager)

	/********************
		Events
	********************/
	public:
		HRESULT Initialize();

		int32 Tick(float _fDeltaSeconds);

		void Release();
		
	/********************
		Events
	********************/
	public:
		void LoadUserInterface();
		
	/********************
		Getter/Setter
	********************/
	public:
		std::shared_ptr<CItemBoxPanel> GetItemBoxPanel() const { return m_wpItemBoxPanel.expired() ? nullptr : m_wpItemBoxPanel.lock(); }

		std::shared_ptr<CItemPanel> GetItemPanel() const { return m_wpItemPanel.expired() ? nullptr : m_wpItemPanel.lock(); }

		std::shared_ptr<CStatusPanel> GetStatusPanel() const { return m_wpStatusPanel.expired() ? nullptr : m_wpStatusPanel.lock(); }

		std::shared_ptr<CItemInfoPanel> GetItemInfoPanel() const { return m_wpItemInfoPanel.expired() ? nullptr : m_wpItemInfoPanel.lock(); }

		void AddInItemBoxPanel(const std::shared_ptr<CInItemBoxPanel>& _spInItemBoxPanel) { m_vecInItemBoxPanels.push_back(_spInItemBoxPanel); }
		
		void AddInGamePanel(const std::shared_ptr<CInGamePanel>& _spInGamePanel) { m_vecInGamePanels.push_back(_spInGamePanel); }

	/******************
		Data Members
	******************/
	private:
		std::weak_ptr<CSkillPanel> m_wpSkillPanel;

		std::weak_ptr<CStatusPanel> m_wpStatusPanel;

		std::weak_ptr<CItemPanel> m_wpItemPanel;

		std::weak_ptr<CItemBoxPanel> m_wpItemBoxPanel;

		std::weak_ptr<CGamePlayPanel> m_wpGamePlayPanel;

		std::weak_ptr<CItemInfoPanel> m_wpItemInfoPanel;

	private:
		std::vector<std::shared_ptr<CInItemBoxPanel>> m_vecInItemBoxPanels;

		std::vector<std::shared_ptr<CInGamePanel>> m_vecInGamePanels;
	};
}
