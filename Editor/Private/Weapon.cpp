#include "pch.h"
#include "Weapon.h"

#include "StaticMeshComponent.h"

#include "Survivor.h"

shared_ptr<CWeapon> Editor::CWeapon::Create(const std::shared_ptr<CActor>& _spWeaponOwner, const std::string& _strBoneName, EWeaponType _eWeaponType)
{
	const shared_ptr<CWeapon> spWeapon = make_shared<CWeapon>();
	spWeapon->Initialize(_spWeaponOwner, _strBoneName, _eWeaponType);
	return spWeapon;
}

void Editor::CWeapon::Initialize(const std::shared_ptr<CActor>& _spWeaponOwner, const std::string& _strBoneName, EWeaponType _eWeaponType)
{
	m_wpOwnerActor = _spWeaponOwner;
	m_strBoneName = _strBoneName;
	m_eWeaponType = _eWeaponType;
}

HRESULT Editor::CWeapon::PreInitialize()
{
	{
		m_wpStaticMeshComponent = CreateActorComponent<CStaticMeshComponent>(L"StaticMeshComponent", EComponentType::STATIC_MESH);
		SetRootComponent(m_wpStaticMeshComponent.lock());

		wstring wstrWeaponType = L"";
		switch (m_eWeaponType)
		{
		case Editor::EWeaponType::GLOVE:        wstrWeaponType = L"Glove";			break;
		case Editor::EWeaponType::TONFA:		wstrWeaponType = L"Tonfa";			break;
		case Editor::EWeaponType::PISTOL:		wstrWeaponType = L"Pistol";			break;
		case Editor::EWeaponType::ASSAULT_RIFLE:wstrWeaponType = L"AssaultRifle";	break;
		case Editor::EWeaponType::SNIPER_RIFLE:	wstrWeaponType = L"SniperRifle";	break;
		default: CHECKF(false, L"Weapon type is not designated.");					break;
		}

		m_wpStaticMeshComponent.lock()->SetModelDesc(wstrWeaponType);
		m_wpStaticMeshComponent.lock()->SetVertexShaderDesc(L"VS_StaticMesh");
		m_wpStaticMeshComponent.lock()->SetPixelShaderDesc(L"PS_StaticMesh");
	}

	m_wpSurvivor = dynamic_pointer_cast<CSurvivor>(m_wpOwnerActor.lock());

	return CSocket::PreInitialize();
}

HRESULT Editor::CWeapon::Initialize()
{
	if (FAILED(CSocket::Initialize())) { return E_FAIL; }

	switch (m_eWeaponType)
	{
	case Editor::EWeaponType::GLOVE:
	{
		// SetActorLocalRotate(Vector3::UnitX, -5.0f);
		// SetActorLocalPosition({ 0.22f, -0.39f, 0.6f });
	}
	break;

	case Editor::EWeaponType::TONFA:
	{
		// SetActorLocalRotate(Vector3::UnitX, 10.0f);
		// SetActorLocalRotate(Vector3::UnitY, +10.0f);
		// SetActorLocalRotate(Vector3::UnitZ, -3.0f);
		SetActorLocalPosition({ -0.35f, 0.05f, 0.08f });
	}
	break;
	
	case Editor::EWeaponType::PISTOL:
	{
		SetActorLocalPosition({ 0.0f, 0.0f, 0.07f });
	}
	break;

	case Editor::EWeaponType::ASSAULT_RIFLE:break;
	case Editor::EWeaponType::SNIPER_RIFLE:	break;
	default: CHECKF(false, L"Weapon type is not designated."); break;
	}

	return S_OK;
}

HRESULT Editor::CWeapon::PostInitialize()
{
	if (FAILED(CSocket::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Editor::CWeapon::BeginPlay()
{
	if (FAILED(CSocket::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Editor::CWeapon::PreTick(float _fDeltaSeconds)
{
	switch (CSocket::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	m_eSurvivorState = m_wpSurvivor.lock()->GetSurvivorState();
	return 0;
}

int32 Editor::CWeapon::Tick(float _fDeltaSeconds)
{
	switch (m_eWeaponType)
	{
	case Editor::EWeaponType::GLOVE:
	{
		// SetActorLocalRotate(Vector3::UnitX, -5.3f);
		// SetActorLocalPosition({ 0.19f, -0.412f, 0.54f });
	}
	break;

	case Editor::EWeaponType::TONFA:
	{

	}
	break;

	case Editor::EWeaponType::PISTOL:
	{
		SetActorLocalPosition({ 0.0f, 0.0f, 0.07f });
	}
	break;

	case Editor::EWeaponType::ASSAULT_RIFLE:break;
	case Editor::EWeaponType::SNIPER_RIFLE:	break;
	default: CHECKF(false, L"Weapon type is not designated."); break;
	}

	switch (CSocket::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Editor::CWeapon::PostTick(float _fDeltaSeconds)
{
	switch (CSocket::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Editor::CWeapon::EndPlay()
{
	if (FAILED(CSocket::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Editor::CWeapon::Render()
{
	CSocket::Render();
}

void Editor::CWeapon::Release()
{
	CSocket::Release();
}
