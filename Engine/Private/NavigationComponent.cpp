#include "pch.h"
#include "NavigationComponent.h"

#include "Cell.h"
#include "Actor.h"

#include "NavHandler.h"

HRESULT Engine::CNavigationComponent::PreInitializeComponent()
{
	if (FAILED(CSceneComponent::PreInitializeComponent())) { return E_FAIL; }
	m_vecCells = CNavHandler::GetInstance()->FindNavigation(m_wstrNavigationName);

	return S_OK;
}

HRESULT Engine::CNavigationComponent::InitializeComponent()
{
	if (FAILED(CSceneComponent::InitializeComponent())) { return E_FAIL; }

	return S_OK;
}

HRESULT Engine::CNavigationComponent::PostInitializeComponent()
{
	if (FAILED(CSceneComponent::PostInitializeComponent())) { return E_FAIL; }

	// ��̾� �� ��� ������ ���� ����� �׵� ����Դϴ�.
	m_matWorld = Matrix::Identity;
	return S_OK;
}

HRESULT Engine::CNavigationComponent::BeginPlay()
{
	if (FAILED(CSceneComponent::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Engine::CNavigationComponent::PreTickComponent(float _fDeltaSeconds)
{
	switch (CSceneComponent::PreTickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return S_OK;
}

int32 Engine::CNavigationComponent::TickComponent(float _fDeltaSeconds)
{
	switch (CSceneComponent::TickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return S_OK;
}

int32 Engine::CNavigationComponent::PostTickComponent(float _fDeltaSeconds)
{
	switch (CSceneComponent::PostTickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return S_OK;
}

HRESULT Engine::CNavigationComponent::EndPlay()
{
	if (FAILED(CSceneComponent::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Engine::CNavigationComponent::Render()
{
	CSceneComponent::Render();
}

void Engine::CNavigationComponent::Release()
{
	for (auto& spCell : m_vecCells)
	{
		spCell = nullptr;
	}
	m_vecCells.clear();

	CSceneComponent::Release();
}

bool Engine::CNavigationComponent::IsValidCell(Vector3& _vInWorldPosition, Vector3& _vOutWorldPosition)
{
	int32 iNeighborCellIndex = -1;
	Matrix matInverseWorld = m_matWorld.Invert();


	Vector3 vInWorldPosition = _vInWorldPosition;

	// �÷��̾��� ���� ��ǥ�� ���翵�� ��, ���� ���� ��ǥ�� �����ϴ�.
	_vInWorldPosition.y = 0.0f;
	Vector3 vInLocalPosition = _vInWorldPosition.Transform(_vInWorldPosition, matInverseWorld);

	// ���� �� �ȿ��� �̵��� ���
	if (m_vecCells[m_iCurCellIndex]->IsInCell(vInLocalPosition, _vOutWorldPosition, iNeighborCellIndex) == true)
	{
		_vOutWorldPosition = _vOutWorldPosition.Transform(_vOutWorldPosition, m_matWorld);
		return true;
	}
	// ���� �� ������ �̵��� ���, �̿��� �� ��ȣ�� Ȯ���մϴ�.
	else
	{
		if (iNeighborCellIndex == -1)
		{
			_vOutWorldPosition = vInWorldPosition;
			return false;
		}

		else
		{
			while (true)
			{
				if (iNeighborCellIndex == -1)
				{
					_vOutWorldPosition = vInWorldPosition;
					return false;
				}
				
				if (m_vecCells[iNeighborCellIndex]->IsInCell(vInLocalPosition, _vOutWorldPosition, iNeighborCellIndex) == true)
				{
					_vOutWorldPosition = _vOutWorldPosition.Transform(_vOutWorldPosition, m_matWorld);
					m_iCurCellIndex = iNeighborCellIndex;
					return true;
				}
			}
		}
	}
}

bool Engine::CNavigationComponent::FindValidCell(Vector3& _vInWorldPosition, Vector3& _vOutWorldPosition)
{
	return false;
}

Vector3 Engine::CNavigationComponent::GetCentroidPosition(uint32 _iCellIndex)
{
	return m_vecCells[_iCellIndex]->GetCentroidPosition();
}
