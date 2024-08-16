#include "pch.h"
#include "FrameManager.h"
#include "Frame.h"

HRESULT Engine::CFrameManager::PreInitialize()
{
	CHECKF(CreateFrame(L"OuterLoop"), L"Failed to create the outer frame.");
	CHECKF(CreateFrame(L"InnerLoop"), L"Failed to create the inner frame.");
	return S_OK;
}

HRESULT Engine::CFrameManager::Initialize()
{
	return S_OK;
}

float Engine::CFrameManager::Tick(const std::wstring& _wstrFrameName)
{
	return m_umapFrames[_wstrFrameName]->Tick();
}

void Engine::CFrameManager::Release()
{
	for (auto& spTimer : m_umapFrames)
	{
		spTimer.second->Release();
		spTimer.second = nullptr;
	}
	m_umapFrames.clear();
}

shared_ptr<CFrame> Engine::CFrameManager::CreateFrame(const wstring& _wstrFrameName)
{
	if (m_umapFrames.find(_wstrFrameName) != m_umapFrames.end()) { return nullptr; }

	const shared_ptr<CFrame> spFrame = CFrame::Create(_wstrFrameName);
	AddFrame(_wstrFrameName, spFrame);
	return spFrame;
}

void Engine::CFrameManager::AddFrame(const wstring& _wstrFrameName, shared_ptr<CFrame> _spTimer)
{
	m_umapFrames.emplace(_wstrFrameName, _spTimer);
}

void Engine::CFrameManager::RemoveFrame(const wstring& _wstrFrameName)
{
	if (shared_ptr<CFrame> spFrame = FindFrame(_wstrFrameName))
	{
		m_umapFrames.erase(_wstrFrameName);
		spFrame->Release();
		spFrame = nullptr;
	}
}

shared_ptr<CFrame> Engine::CFrameManager::FindFrame(const wstring& _wstrFrameName)
{
	if (m_umapFrames.find(_wstrFrameName) == m_umapFrames.end()) { return nullptr; }
	return m_umapFrames[_wstrFrameName];
}

optional<float> Engine::CFrameManager::GetDeltaSeconds(const std::wstring& _wstrFrameName)
{
	if (shared_ptr<CFrame> spFrame = FindFrame(_wstrFrameName))
	{
		return spFrame->GetDeltaSeconds();
	}
	return nullopt;
}
