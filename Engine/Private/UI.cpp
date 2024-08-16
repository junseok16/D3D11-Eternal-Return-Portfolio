#include "pch.h"
#include "UI.h"

HRESULT Engine::CUI::PreInitialize()
{
	if (FAILED(CActor::PreInitialize())) { return E_FAIL; }
	
	return S_OK;
}

HRESULT Engine::CUI::Initialize()
{
	if (FAILED(CActor::Initialize())) { return E_FAIL; }

	// 스크린 좌표계에서 NDC 좌표계로 변환합니다.
	float fX = (2.0f * m_vPivot.x / 1280.0f) - 1.0f;
	float fY = (-2.0f * m_vPivot.y / 720.0f) + 1.0f;
	float fZ = 0.0f;

	Vector3 vNDCPosition = Vector3(fX, fY, fZ);

	Matrix matOrthogonalProjection = XMMatrixOrthographicLH(1280.0f, 720.0f, 1.0f, 1000.0f);
	matOrthogonalProjection = matOrthogonalProjection.Invert();

	Vector3 vViewPosition = XMVector3TransformCoord(vNDCPosition, matOrthogonalProjection);
	SetActorLocalPosition(vViewPosition);

	return S_OK;
}

HRESULT Engine::CUI::PostInitialize()
{
	if (FAILED(CActor::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Engine::CUI::BeginPlay()
{
	if (FAILED(CActor::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Engine::CUI::PreTick(float _fDeltaSeconds)
{
	switch (CActor::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Engine::CUI::Tick(float _fDeltaSeconds)
{
	switch (CActor::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Engine::CUI::PostTick(float _fDeltaSeconds)
{
	switch (CActor::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Engine::CUI::EndPlay()
{
	if (FAILED(CActor::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Engine::CUI::Render()
{
	CActor::Render();
}

void Engine::CUI::Release()
{
	CActor::Release();
}
