#pragma once
#include "Manager.h"

namespace Engine
{
	class CFrame;

	class CFrameManager final : public Engine::CManager
	{
	/********************
		Events
	********************/
	public:
		HRESULT PreInitialize();

		HRESULT Initialize();

		float Tick(const std::wstring& _wstrFrameName);

		virtual void Release() override;
		
	/********************
		Methods
	********************/
	public:
		std::shared_ptr<CFrame> CreateFrame(const std::wstring& _wstrFrameName);

		void AddFrame(const std::wstring& _wstrFrameName, std::shared_ptr<CFrame> _spFrame);

		void RemoveFrame(const std::wstring& _wstrFrameName);

		std::shared_ptr<CFrame> FindFrame(const std::wstring& _wstrFrameName);

	/********************
		Getter/Setter
	********************/
		std::optional<float> GetDeltaSeconds(const std::wstring& _wstrFrameName);

	/********************
		Data Members
	********************/
	private:
		std::unordered_map<std::wstring, std::shared_ptr<CFrame>> m_umapFrames;
	};
}
