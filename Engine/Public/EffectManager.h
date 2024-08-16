#pragma once
#include "Manager.h"

namespace Engine
{
	class CEffectComponent;

	class ENGINE_DLL CEffectManager final : public CManager
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CEffectManager() = default;

		virtual ~CEffectManager() = default;

	/********************
		Events
	********************/
	public:
		HRESULT PreInitialize();

		HRESULT Initialize();

		virtual void Release() override;

		void Render();
		
	/********************
		Methods
	********************/
	public:
		HRESULT AddEffectComponent(const std::wstring& _wstrEffectComponentName, const std::shared_ptr<CEffectComponent>& _spEffectComponent);

		HRESULT RemoveEffectComponent(const std::wstring& _wstrEffectComponentName);

	/********************
		Events
	********************/
	private:
		std::unordered_map<std::wstring, std::weak_ptr<CEffectComponent>> m_umapEffectComponents;
	};
}
