#pragma once
#include "Actor.h"

namespace Engine
{
	class CSoundComponent;
	class CEffectComponent;
	class CSkeletalMeshComponent;
	class CStaticMeshComponent;
	class CSphereComponent;
	class COBBComponent;
}

namespace Client
{
	enum class EProjectileState
	{
		STAY,
		MOVE,
		TRACE,
		EXPLODE,
		DIE,
		ENUM_END
	};

    class CProjectile : public CActor
    {
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CProjectile() = default;

		virtual ~CProjectile() = default;
		
	/********************
		Events
	********************/
	public:
		template<typename T>
		static shared_ptr<T> Create
		(
			const Vector3& _vSpawnPosition,
			const Vector3& _vSpawnDirection,
			float _fLifeSeconds,
			float _fProjectileSpeed,
			float _fProjectileDamage,
			const std::shared_ptr<CActor>& _spTargetActor,
			const std::shared_ptr<CActor>& _spOwnerActor,
			EProjectileType _eProjectileType,
			EProjectileState _eProjectileState,
			int32 _iProjectileIndex
		)
		{
			shared_ptr<T> spProjectile = make_shared<T>();
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
				_eProjectileState,
				_iProjectileIndex
			);

			spProjectile->PreInitialize();
			spProjectile->Initialize();
			spProjectile->PostInitialize();
			spProjectile->BeginPlay();
			return spProjectile;
		}

		void InitializeProjectile
		(
			const Vector3& _vSpawnPosition,
			const Vector3& _vSpawnDirection,
			float _fLifeSeconds,
			float _fProjectileSpeed,
			float _fProjectileDamage,
			const std::shared_ptr<CActor>& _spTargetActor,
			const std::shared_ptr<CActor>& _spOwnerActor,
			EProjectileType _eProjectileType,
			EProjectileState _eProjectileState,
			int32 _iProjectileIndex
		);

		virtual HRESULT PreInitialize() override;

		virtual HRESULT Initialize() override;

		virtual HRESULT PostInitialize() override;

		virtual HRESULT BeginPlay() override;

		virtual int32 PreTick(float _fDeltaSeconds) override;

		virtual int32 Tick(float _fDeltaSeconds) override;

		virtual int32 PostTick(float _fDeltaSeconds) override;

		virtual HRESULT EndPlay() override;

		virtual void Render() override;

		virtual void Release() override;
		
	/********************
		Methods
	********************/
	public:
		// Actor overrides
		virtual void OnCollisionEnter(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst) override;

		virtual void OnCollisionStay(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst) override;

		virtual void OnCollisionExit(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst) override;
		
	public:
		void Revive
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
		);

		void MoveTo(const Vector3& _vDirection);

		void TraceTo(const std::shared_ptr<CActor> _spTargetActor);

		bool IsDead() { return m_eProjectileState == EProjectileState::DIE; }

		EProjectileType GetProjectileType() const { return m_eProjectileType; }

	/********************
		Data Members
	********************/
	protected:
		std::weak_ptr<CStaticMeshComponent> m_wpStaticMeshComponent;

		std::weak_ptr<CSkeletalMeshComponent> m_wpSkeletalMeshComponent;

		std::weak_ptr<CEffectComponent> m_wpEffectComponent;

		std::weak_ptr<CEffectComponent> m_wpSecondEffectComponent;

		std::weak_ptr<CSphereComponent> m_wpSphereComponent;

		std::weak_ptr<COBBComponent> m_wpOBBComponent;

		std::weak_ptr<CSoundComponent> m_wpSoundComponent;

	protected:
		// 스폰 위치
		Vector3 m_vSpawnPosition = Vector3::Zero;

		// 스폰 방향
		Vector3 m_vSpawnDirection = Vector3::UnitZ;

		// 투사체 최대 지속 시간
		float m_fMaxLifeSeconds = 0.0f;
		
		// 투사체 누적 지속 시간
		float m_fSumLifeSeconds = 0.0f;

		// 투사체 속도
		float m_fProjectileSpeed = 0.1f;

		// 투사체 대미지
		float m_fProjectileDamage = 0.0f;

		// 투사체 반지름
		float m_fProjectileRadius = 1.0f;

		// 투사체 가로, 세로, 높이
		Vector3 m_vProjectileExtents = Vector3::Zero;

		// 투사체가 목표로 하는 액터
		std::weak_ptr<CActor> m_wpTargetActor;

		// 투사체를 발사한 액터
		std::weak_ptr<CActor> m_wpOwnerActor;

		int32 m_iProjectileIndex = 0;

		EProjectileType m_eProjectileType = EProjectileType::ENUM_END;

		EProjectileState m_eProjectileState = EProjectileState::ENUM_END;

		bool m_bSkillApply = false;

		bool m_bSoundApply = false;

		bool m_bAlphaThirdSkillApply = false;
    };
}
