#pragma once

namespace Engine
{
	class ENGINE_DLL CFrame final
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CFrame() = default;

		virtual ~CFrame() = default;

	/********************
		Events
	********************/
	public:
		static std::shared_ptr<CFrame> Create(const std::wstring& _wstrTimerName);

		HRESULT Initialize(const std::wstring& _wstrFrameName);

		float Tick();

		void Release();

	/**********************
		Getter/Setter
	**********************/
	public:
		float GetDeltaSeconds() const { return m_fDeltaSeconds; }

	/********************
		Data Members
	********************/
	private:
		LARGE_INTEGER m_llCurTime{};

		LARGE_INTEGER m_llFixTime{};

		LARGE_INTEGER m_llLastTime{};

		LARGE_INTEGER m_llTickPerSecond{};

	private:
		// 프레임의 이름
		std::wstring m_wstrFrameName = L"";

		// 현재 델타 세컨드
		float m_fDeltaSeconds = 0.0f;
	};
}
