#pragma once
#include "Panel.h"

namespace Client
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
		Data Members
	********************/
	private:
		EEnemyType m_eEnemyType = EEnemyType::ENUM_END;

		std::weak_ptr<CActor> m_wpPanelOwner;

	private:
		std::weak_ptr<CInHPBarSlider> m_wpInHPBarSlider;

		std::weak_ptr<CInRetreatBarSlider> m_wpInRetreatBarSlider;

		std::weak_ptr<CInLevelImage> m_wpInLevelImage;
	};
}
