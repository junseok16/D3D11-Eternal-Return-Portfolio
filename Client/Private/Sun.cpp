#include "pch.h"
#include "Sun.h"

#include "LightComponent.h"

#include "GameManager.h"

HRESULT Client::CSun::PreInitialize()
{
	m_wpLightComponent = CreateActorComponent<CLightComponent>(L"SunLightComponent", EComponentType::DIRECTIONAL_LIGHT);
	SetRootComponent(m_wpLightComponent.lock());

	Vector3 vLightDirection = { -20.0f, -100.0f, 0.0f };
	vLightDirection.Normalize();

	TLightDesc tLightDesc
	{
		ELightType::DIRECTIONAL,
		{ 0.8f, 0.8f, 0.8f },
		10.0f,
		Vector3::One,
		0.0f,
		Vector3::Zero,
		10.0f,
		{ 0.0f, 100.0f, 0.0f },
		1.0f,
		vLightDirection,
		Vector3::One,
	};

	m_wpLightComponent.lock()->SetLightDesc(tLightDesc);

	SetActorRenderType(ERenderType::NOT_RENDER);
	return CActor::PreInitialize();
}

HRESULT Client::CSun::Initialize()
{
	if (FAILED(CActor::Initialize())) { return E_FAIL; }


	return S_OK;
}

HRESULT Client::CSun::PostInitialize()
{
	if (FAILED(CActor::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CSun::BeginPlay()
{
	if (FAILED(CActor::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Client::CSun::PreTick(float _fDeltaSeconds)
{
	switch (CActor::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}
	return 0;
}

int32 Client::CSun::Tick(float _fDeltaSeconds)
{
	switch (CActor::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	EDayType eDayType = CGameManager::GetInstance()->GetDayType();
	float fDayTime = CGameManager::GetInstance()->GetDayTime();
	float fNightTime = CGameManager::GetInstance()->GetNightTime();

	Vector3 vNightAmbient = { 0.2f, 0.2f, 0.3f };
	Vector3 vDayAmbient = { 0.8f, 0.8f, 0.8f };

	switch (eDayType)
	{
	case Client::EDayType::DAY:
	{
		if (fDayTime <= 10.0f)
		{
			Vector3 vLerpAmbient = Vector3::Lerp(vDayAmbient, vNightAmbient, 1.0f - (fDayTime / 10.0f));
			m_wpLightComponent.lock()->SetLightAmbient(vLerpAmbient);
		}
		else if (fDayTime == 0.0f)
		{
			m_wpLightComponent.lock()->SetLightAmbient(vNightAmbient);
		}
	}
	break;

	case Client::EDayType::NIGHT:
	{
		if (fNightTime <= 10.0f)
		{
			Vector3 vLerpAmbient = Vector3::Lerp(vNightAmbient, vDayAmbient, 1.0f - (fNightTime / 10.0f));
			m_wpLightComponent.lock()->SetLightAmbient(vLerpAmbient);
		}
		else if (fNightTime == 0.0f)
		{
			m_wpLightComponent.lock()->SetLightAmbient(vDayAmbient);
		}
	}
	break;

	default:
		break;
	}

	return 0;
}

int32 Client::CSun::PostTick(float _fDeltaSeconds)
{
	switch (CActor::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Client::CSun::EndPlay()
{
	if (FAILED(CActor::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Client::CSun::Render()
{
	CActor::Render();
}

void Client::CSun::Release()
{
	CActor::Release();
}
