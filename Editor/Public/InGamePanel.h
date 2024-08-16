#pragma once
#include "Panel.h"

namespace Editor
{
	class CInHPBarSlider;
	class CInRetreatBarSlider;
	class CInLevelImage;

	class CInGamePanel : public CPanel
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CInGamePanel() = default;

		virtual ~CInGamePanel() = default;
		
	/********************
		Events
	********************/
	public:
		static std::shared_ptr<CInGamePanel> Create
		(
			const std::shared_ptr<CActor>& _spPanelOwner,
			EEnemyType _eEnemyType
		);

		void Initialize(const std::shared_ptr<CActor>& _spPanelOwner, EEnemyType _eEnemyType);

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

	private:
		EEnemyType m_eEnemyType = EEnemyType::ENUM_END;

		std::weak_ptr<CActor> m_wpPanelOwner;

	private:
		std::weak_ptr<CInHPBarSlider> m_wpInHPBarSlider;

		std::weak_ptr<CInRetreatBarSlider> m_wpInRetreatBarSlider;

		std::weak_ptr<CInLevelImage> m_wpInLevelImage;
	};
}
