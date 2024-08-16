#include "pch.h"
#include "Socket.h"

#include "SkeletalMeshComponent.h"
#include "Bone.h"

HRESULT Engine::CSocket::PreInitialize()
{
	if (FAILED(CActor::PreInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Engine::CSocket::Initialize()
{
	if (FAILED(CActor::Initialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Engine::CSocket::PostInitialize()
{
	if (FAILED(CActor::PostInitialize())) { return E_FAIL; }

	// �θ� ���Ϳ��� ���̷�Ż �޽� ������Ʈ�� �ҷ��ɴϴ�.
	m_wpSkeletalMeshComponent = CActor::GetOwnerActor()->FindActorComponent<CSkeletalMeshComponent>(L"SkeletalMeshComponent");
	m_wpBone = m_wpSkeletalMeshComponent.lock()->FindBone(m_strBoneName);

	return S_OK;
}

HRESULT Engine::CSocket::BeginPlay()
{
	if (FAILED(CActor::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Engine::CSocket::PreTick(float _fDeltaSeconds)
{
	switch (CActor::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Engine::CSocket::Tick(float _fDeltaSeconds)
{
	// ���� ����� �����մϴ�.
	XMMATRIX matSocket = m_wpBone.lock()->GetWorldMatrix();

	for (int32 iIndex = 0; iIndex < 3; iIndex++)
	{
		matSocket.r[iIndex] = XMVector3Normalize(matSocket.r[iIndex]);
	}

	m_matSocket = matSocket;
	SetSocketMatrix(matSocket);

	switch (CActor::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Engine::CSocket::PostTick(float _fDeltaSeconds)
{
	switch (CActor::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Engine::CSocket::EndPlay()
{
	if (FAILED(CActor::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Engine::CSocket::Render()
{
	CActor::Render();
}

void Engine::CSocket::Release()
{
	CActor::Release();
}
