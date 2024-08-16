#include "pch.h"
#include "CollisionManager.h"

// component
#include "ShapeComponent.h"
#include "SphereComponent.h"
#include "AABBComponent.h"
#include "OBBComponent.h"

// actor
#include "Actor.h"

HRESULT Engine::CCollisionManager::PreInitialize()
{
	return S_OK;
}

HRESULT Engine::CCollisionManager::Initialize()
{
	return S_OK;
}

int32 Engine::CCollisionManager::Tick()
{
	size_t iSize = m_vecShapeComponents.size();

	for (size_t iOuterloopIndex = 0; iOuterloopIndex < iSize; ++iOuterloopIndex)
	{
		for (size_t iInnerloopIndex = iOuterloopIndex + 1; iInnerloopIndex < iSize; ++iInnerloopIndex)
		{
			shared_ptr<CShapeComponent> spSrc = m_vecShapeComponents[iOuterloopIndex];
			shared_ptr<CShapeComponent> spDst = m_vecShapeComponents[iInnerloopIndex];
			
			// 콜라이더가 비활성화된 경우
			if (!spSrc->IsActive() || !spDst->IsActive())
			{
				std::unordered_set<std::shared_ptr<CShapeComponent>>& usetSrcShapeComponents = spSrc->GetShapeComponents();
				std::unordered_set<std::shared_ptr<CShapeComponent>>& usetDstShapeComponents = spDst->GetShapeComponents();

				if (usetSrcShapeComponents.find(spDst) != usetSrcShapeComponents.end())
				{
					usetSrcShapeComponents.erase(spDst);
					usetDstShapeComponents.erase(spSrc);
				}
				continue;
			}

			// 두 콜라이더가 충돌한 경우
			if (spSrc->IsCollided(spDst) == true)
			{
				// 이전에 충돌하지 않고 방금 충돌한 경우
				std::unordered_set<std::shared_ptr<CShapeComponent>>& usetSrcShapeComponents = spSrc->GetShapeComponents();
				std::unordered_set<std::shared_ptr<CShapeComponent>>& usetDstShapeComponents = spDst->GetShapeComponents();

				if (usetSrcShapeComponents.find(spDst) == usetSrcShapeComponents.end())
				{
					spSrc->GetOwnerActor()->OnCollisionEnter(spSrc, spDst);
					spDst->GetOwnerActor()->OnCollisionEnter(spDst, spSrc);

					usetDstShapeComponents.insert(spSrc);
					usetSrcShapeComponents.insert(spDst);
				}
				// 이전에 이미 충돌한 경우
				else
				{
					spSrc->GetOwnerActor()->OnCollisionStay(spSrc, spDst);
					spDst->GetOwnerActor()->OnCollisionStay(spDst, spSrc);
				}
			}
			// 두 콜라이더가 충돌하지 않은 경우
			else
			{
				// 이전에 충돌했다가 방금 충돌하지 않은 경우
				std::unordered_set<std::shared_ptr<CShapeComponent>>& usetSrcShapeComponents = spSrc->GetShapeComponents();
				std::unordered_set<std::shared_ptr<CShapeComponent>>& usetDstShapeComponents = spDst->GetShapeComponents();

				if (usetSrcShapeComponents.find(spDst) != usetSrcShapeComponents.end())
				{
					spSrc->GetOwnerActor()->OnCollisionExit(spSrc, spDst);
					spDst->GetOwnerActor()->OnCollisionExit(spDst, spSrc);

					usetDstShapeComponents.erase(spSrc);
					usetSrcShapeComponents.erase(spDst);
				}
			}
		}
	}

	return 0;
}

void Engine::CCollisionManager::Release()
{
	for (auto& spShapeComponent : m_vecShapeComponents)
	{
		spShapeComponent = nullptr;
	}
	m_vecShapeComponents.clear();
}

HRESULT Engine::CCollisionManager::AddShapeComponent(const std::shared_ptr<CShapeComponent>& _spShapeComponent)
{
	auto iter = find(m_vecShapeComponents.begin(), m_vecShapeComponents.end(), _spShapeComponent);

	// 이미 컴포넌트가 있는 경우
	if (iter != m_vecShapeComponents.end()) { return E_FAIL; }
	m_vecShapeComponents.push_back(_spShapeComponent);

	return S_OK;
}

HRESULT Engine::CCollisionManager::RemoveShapeComponent(const std::shared_ptr<CShapeComponent>& _spShapeComponent)
{
	auto iter = find(m_vecShapeComponents.begin(), m_vecShapeComponents.end(), _spShapeComponent);

	// 컴포넌트가 없는 경우
	if (iter == m_vecShapeComponents.end()) { return E_FAIL; }
	m_vecShapeComponents.erase(iter);

	return S_OK;
}
