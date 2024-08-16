#include "pch.h"
#include "Frame.h"

shared_ptr<CFrame> Engine::CFrame::Create(const std::wstring& _wstrTimerName)
{
	const shared_ptr<CFrame> spTimer = make_shared<CFrame>();
	ENSUREF(spTimer->Initialize(_wstrTimerName), L"Failed to initialize frame.");
	return spTimer;
}

HRESULT Engine::CFrame::Initialize(const std::wstring& _wstrFrameName)
{
	m_wstrFrameName = _wstrFrameName;
	QueryPerformanceCounter(&m_llCurTime);
	QueryPerformanceCounter(&m_llFixTime);
	QueryPerformanceCounter(&m_llLastTime);

	// 1�ʴ� ƽ ���� ���մϴ�.
	QueryPerformanceFrequency(&m_llTickPerSecond);
	return S_OK;
}

float Engine::CFrame::Tick()
{
	// ���� ƽ ���� ���մϴ�.
	QueryPerformanceCounter(&m_llCurTime);

	if (m_llCurTime.QuadPart - m_llFixTime.QuadPart >= m_llTickPerSecond.QuadPart)
	{
		// 1�ʴ� ƽ ���� �ٽ� ���մϴ�.
		QueryPerformanceFrequency(&m_llTickPerSecond);
		m_llFixTime = m_llCurTime;
	}

	// ���� ƽ ������ ���� ƽ ���� �� ƽ�� ���ϰ�, �� ƽ��ŭ�� ��(second)�� ���մϴ�.
	m_fDeltaSeconds = static_cast<float>(m_llCurTime.QuadPart - m_llLastTime.QuadPart) / m_llTickPerSecond.QuadPart;

	// ���� ƽ ���� ���� ƽ ���� �����մϴ�.
	m_llLastTime = m_llCurTime;

	return m_fDeltaSeconds;
}

void Engine::CFrame::Release()
{
}
