#include "pch.h"
#include "Projectile.h"

#include "SphereComponent.h"
#include "OBBComponent.h"

#include "WildAnimal.h"
#include "Boss.h"
#include "Pawn.h"

shared_ptr<CProjectile> Editor::CProjectile::Create
(
	const Vector3& _vSpawnPosition,
	const Vector3& _vSpawnDirection,
	float _fLifeSeconds,
	float _fProjectileSpeed,
	float _fProjectileDamage,
	const std::shared_ptr<CActor>& _spTargetActor,
	const std::shared_ptr<CActor>& _spOwnerActor,
	EProjectileType _eProjectileType,
	EProjectileState _eProjectileState
)
{
	shared_ptr<CProjectile> spProjectile = make_shared<CProjectile>();
	spProjectile->InitializeProjectile
	(
		_vSpawnPosition,
		_vSpawnDirection,
		_fLifeSeconds,
		_fProjectileSpeed,
		_fProjectileDamage,
		_spTargetActor,
		_spOwnerActor,
		_eProjectileType,
		_eProjectileState
	);

	spProjectile->PreInitialize();
	spProjectile->Initialize();
	spProjectile->PostInitialize();
	spProjectile->BeginPlay();
	return spProjectile;
}

void Editor::CProjectile::InitializeProjectile
(
	const Vector3& _vSpawnPosition,
	const Vector3& _vSpawnDirection,
	float _fLifeSeconds,
	float _fProjectileSpeed,
	float _fProjectileDamage,
	const std::shared_ptr<CActor>& _spTargetActor,
	const std::shared_ptr<CActor>& _spOwnerActor,
	EProjectileType _eProjectileType,
	EProjectileState _eProjectileState
)
{
	m_vSpawnPosition = _vSpawnPosition;
	m_vSpawnDirection = _vSpawnDirection;
	m_fMaxLifeSeconds = _fLifeSeconds;
	m_fProjectileSpeed = _fProjectileSpeed,
	m_fProjectileDamage = _fProjectileDamage,
	m_wpTargetActor = _spTargetActor;
	m_wpOwnerActor = _spOwnerActor;
	m_eProjectileType = _eProjectileType;
	m_eProjectileState = _eProjectileState;
}

HRESULT Editor::CProjectile::PreInitialize()
{
	switch (m_eProjectileType)
	{
	case Editor::EProjectileType::AYA:
	case Editor::EProjectileType::ROZZI:
	case Editor::EProjectileType::WICKLINE_SKILL_01:
	case Editor::EProjectileType::ALPHA_SKILL_02:
	case Editor::EProjectileType::OMEGA_SKILL_02:
		m_wpSphereComponent = CreateActorComponent<CSphereComponent>(L"SphereComponent", EComponentType::SPHERE);
		SetRootComponent(m_wpSphereComponent.lock());
		break;

	case Editor::EProjectileType::WICKLINE_SKILL_02:
		m_wpSphereComponent = CreateActorComponent<CSphereComponent>(L"SphereComponent", EComponentType::SPHERE);
		SetRootComponent(m_wpSphereComponent.lock());
		break;

	default:
		CHECKF(false, L"Projectile type is not designated.");
		break;
	}

	return CActor::PreInitialize();
}

HRESULT Editor::CProjectile::Initialize()
{
	if (FAILED(CActor::Initialize())) { return E_FAIL; }

	SetActorLocalPosition(m_vSpawnPosition);
	LookAt(m_vSpawnPosition + m_vSpawnDirection);

	{
		m_wpSphereComponent.lock()->SetCenter({ 0.0f, 0.0f, 0.0f });
		m_wpSphereComponent.lock()->SetRadius(0.2f);
		m_wpSphereComponent.lock()->SetActive(true);
		m_wpSphereComponent.lock()->SetCollisionLayer(ECollisionLayer::PLAYER_PROJECTILE);
		m_wpSphereComponent.lock()->AddCollisionFlag(ECollisionLayer::MONSTER);
	}

	return S_OK;
}

HRESULT Editor::CProjectile::PostInitialize()
{
	if (FAILED(CActor::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Editor::CProjectile::BeginPlay()
{
	if (FAILED(CActor::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Editor::CProjectile::PreTick(float _fDeltaSeconds)
{
	switch (CActor::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Editor::CProjectile::Tick(float _fDeltaSeconds)
{
	switch (CActor::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	switch (m_eProjectileState)
	{
	case Editor::EProjectileState::MOVE:
	{
		m_fSumLifeSeconds += _fDeltaSeconds;

		if (m_fSumLifeSeconds >= m_fMaxLifeSeconds)
		{
			m_fSumLifeSeconds = 0.0f;
			m_wpSphereComponent.lock()->SetActive(false);
			SetActorLocalPosition(m_vSpawnPosition);
			m_eProjectileState = EProjectileState::DIE;
			break;
		}

		m_wpSphereComponent.lock()->SetActive(true);
		Vector3 vWorldPosition = GetActorWorldPosition().value();
		Vector3 vTargetPosition = vWorldPosition + m_vSpawnDirection * m_fProjectileSpeed;
		SetActorLocalPosition(vTargetPosition);
	}
	break;

	case Editor::EProjectileState::TRACE:
		break;

	case Editor::EProjectileState::DIE:
		break;

	default:
		CHECKF(false, L"Projectile type is not designated.");
		break;
	}

	return 0;
}

int32 Editor::CProjectile::PostTick(float _fDeltaSeconds)
{
	if (m_eProjectileState == EProjectileState::DIE) { return 0; }

	switch (CActor::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Editor::CProjectile::EndPlay()
{
	if (FAILED(CActor::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Editor::CProjectile::Render()
{
	if (m_eProjectileState == EProjectileState::DIE) { return; }

	CActor::Render();
}

void Editor::CProjectile::Release()
{
	CActor::Release();
}

void Editor::CProjectile::OnCollisionEnter(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
	CActor::OnCollisionEnter(_spSrc, _spDst);

	switch (_spDst->GetCollisionLayer())
	{
	case ECollisionLayer::MONSTER:
	{
		shared_ptr<CWildAnimal> spWildAnimal = dynamic_pointer_cast<CWildAnimal>(_spDst->GetOwnerActor());
		if (spWildAnimal && spWildAnimal->IsDead()) { break; }

		shared_ptr<CBoss> spBoss = dynamic_pointer_cast<CBoss>(_spDst->GetOwnerActor());
		if (spBoss && spBoss->IsDead()) { break; }

		_spDst->GetOwnerActor()->TakeDamage(m_fProjectileDamage, nullptr, static_pointer_cast<CPawn>(m_wpOwnerActor.lock()));

		m_fSumLifeSeconds = 0.0f;
		m_wpSphereComponent.lock()->SetActive(false);
		SetActorLocalPosition(m_vSpawnPosition);
		m_eProjectileState = EProjectileState::DIE;
	}
	break;

	default:
		break;
	}

}

void Editor::CProjectile::OnCollisionStay(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
	CActor::OnCollisionStay(_spSrc, _spDst);
}

void Editor::CProjectile::OnCollisionExit(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
	CActor::OnCollisionExit(_spSrc, _spDst);
}

void Editor::CProjectile::Revive
(
	const Vector3& _vSpawnPosition,
	const Vector3& _vSpawnDirection,
	float _fLifeSeconds,
	float _fProjectileSpeed,
	float _fProjectileDamage,
	const std::shared_ptr<CActor>& _spTargetActor,
	const std::shared_ptr<CActor>& _spOwnerActor,
	EProjectileType _eProjectileType,
	EProjectileState _eProjectileState)
{
	m_vSpawnPosition = _vSpawnPosition;
	m_vSpawnDirection = _vSpawnDirection;
	m_fMaxLifeSeconds = _fLifeSeconds;
	m_fProjectileSpeed = _fProjectileSpeed,
	m_fProjectileDamage = _fProjectileDamage;
	m_wpTargetActor = _spTargetActor;
	m_wpOwnerActor = _spOwnerActor;
	m_eProjectileType = _eProjectileType;
	m_eProjectileState = _eProjectileState;

	SetActorLocalPosition(m_vSpawnPosition);
	LookAt(m_vSpawnPosition + m_vSpawnDirection);
}

void Editor::CProjectile::MoveTo(const Vector3& _vDirection)
{
	m_eProjectileState = EProjectileState::MOVE;

	Vector3 vPosition = GetActorLocalPosition().value();
	LookAt(vPosition + _vDirection);
}

void Editor::CProjectile::TraceTo(const std::shared_ptr<CActor> _spTargetActor)
{

}
