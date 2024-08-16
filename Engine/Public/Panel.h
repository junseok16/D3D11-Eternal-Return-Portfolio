#pragma once
// #include "UI.h"
#include "Actor.h"

namespace Engine
{
	class CUI;

	class ENGINE_DLL CPanel : public CActor
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CPanel() = default;

		virtual ~CPanel() = default;
		
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
		void SetActive(bool _bActive);

		HRESULT AddUI(const std::wstring& _wstrUIName, const std::shared_ptr<CUI>& _spUI);

		HRESULT RemoveUI(const std::wstring& _wstrUIName);

	/********************
		Data Members
	********************/
	protected:
		bool m_bActive = true;

		// 이 패널이 갖고 있는 사용자 인터페이스들
		std::unordered_map<std::wstring, std::weak_ptr<CUI>> m_umapUIs;
	};
}
