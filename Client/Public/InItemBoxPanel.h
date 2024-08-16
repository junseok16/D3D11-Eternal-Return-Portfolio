#pragma once
#include "Panel.h"

namespace Client
{
	class CInItemBoxBackground;
	class CInItemBoxImage;
	class CItemBox;

	class CInItemBoxPanel : public CPanel
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CInItemBoxPanel() = default;

		virtual ~CInItemBoxPanel() = default;
		
	/********************
		Events
	********************/
	public:
		static std::shared_ptr<CInItemBoxPanel> Create(const std::shared_ptr<CItemBox>& _spPanelOwner);

		void Initialize(const std::shared_ptr<CItemBox>& _spPanelOwner);

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
		std::weak_ptr<CItemBox> m_wpPanelOwner;

	private:
		std::weak_ptr<CInItemBoxBackground> m_wpInItemBoxBackground;

		std::weak_ptr<CInItemBoxImage> m_wpInItemBoxImage;
	};
}
