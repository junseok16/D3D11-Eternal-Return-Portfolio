#pragma once
#include "Character.h"

namespace Engine
{
	class CLightComponent;
	class CSphereComponent;
	class CNavigationComponent;
}

namespace Editor
{
	// user interface
	class CStatusPanel;
	class CItemPanel;
	class CInventory;

	// component
	class CSurvivorStateComponent;

	class CWildAnimal;
	class CConsole;
	class CCollectible;
	class CItemBox;
	
	class CSurvivor : public CCharacter
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CSurvivor() = default;

		virtual ~CSurvivor() = default;
		
	/********************
		Events
	********************/
	public:
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
		
	public:
		HRESULT CreateInventory(const std::shared_ptr<CItemPanel>& _spItemPanel, const std::shared_ptr<CStatusPanel>& _spStatusPanel);

	/********************
		Methods
	********************/
	public:
		void MoveSurvivor(float _fDeltaSeconds);

		virtual void MoveForward(int32 _iValue);

		virtual void MoveBackward(int32 _iValue);

		virtual void MoveRight(int32 _iValue);

		virtual void MoveLeft(int32 _iValue);

		virtual bool ChangeToFirstSurvivor();

		virtual bool ChangeToSecondSurvivor();

		virtual bool ChangeToThirdSurvivor();

	public:
		virtual void OnCollisionEnter(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst) override;

		virtual void OnCollisionStay(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst) override;

		virtual void OnCollisionExit(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst) override;

	public:
		virtual bool IsSkillValid(ESkillType _eSkillType);

	/********************
		Getter/Setter
	********************/
	public:
		float GetCurHP() const { return m_fCurHP; }

		float GetCurSP() const { return m_fCurSP; }

		float GetMaxHP() const { return m_arrMaxHPs[m_iCurSurvivorLevel]; }

		float GetMaxSP() const { return m_arrMaxSPs[m_iCurSurvivorLevel]; }

		float GetCurExp() const { return m_fCurExp; }

		float GetMaxExp() const { return m_arrMaxExps[m_iCurSurvivorLevel]; }

		int32 GetCurLevel() const { return m_iCurSurvivorLevel; }

		float GetHPRegeneration() const { return m_arrHPRegenerations[m_iCurSurvivorLevel]; }

		float GetSPRegeneration() const { return m_arrSPRegenerations[m_iCurSurvivorLevel]; }

		float GetCurCoolDown(ESkillType _eSkillType) const { return m_vecCurSkillCoolDown[(int32)_eSkillType]; }

		float GetCurAttackPower() const { return m_arrAttackPower[m_iCurSurvivorLevel]; }

		float GetCurDefensePower() const { return m_arrDefensePower[m_iCurSurvivorLevel]; }

		float GetCurMoveSpeed() const { return m_fCurMoveSpeed; }

	public:
		void AddLerpHP(float _fHP);

		void AddLerpSP(float _fSP);

	public:
		void AddCurHP(float _fHP);

		void AddCurSP(float _fSP);

		void AddCurExp(float _fExp);

		void AddSkillLevel(ESkillType _eSkillType, int32 _iSkillPoint) { m_arrCurSkillLevels[(uint32)_eSkillType] += _iSkillPoint; }

		void AddSkillPoint(uint32 _iSkillPoint) { m_iCurSkillPoint += _iSkillPoint; }

	public:
		uint32 GetCurSkillPoint() const { return m_iCurSkillPoint; }

		int32 GetCurSkillLevel(ESkillType _eSkillType) { return m_arrCurSkillLevels[(uint32)_eSkillType]; }

		int32 GetMaxSkillLevel(ESkillType _eSkillType) { return m_arrMaxSkillLevels[(uint32)_eSkillType]; }

		float GetStaminaConsumption(ESkillType _eSkillType) const;

	public:
		float GetCollectSeconds() const { return m_fCollectSeconds; }

		float GetConsoleSeconds() const { return m_fConsoleSeconds; }

		ECollectibleType GetCurCollectibleType() const { return m_eCurCollectibleType; }

		EConsoleType GetCurConsoleType() const { return m_eCurConsoleType; }

		ESurvivorType GetSurvivorType() const { return m_eSurvivorType; }

		std::shared_ptr<CWildAnimal> GetWildAnimal() const { return m_wpCurWildAnimal.expired() ? nullptr : m_wpCurWildAnimal.lock(); }

		std::shared_ptr<CItemBox> GetItemBox() const { return m_wpCurItemBox.expired() ? nullptr : m_wpCurItemBox.lock(); }

		std::shared_ptr<CInventory> GetInventory() const { return m_spInventory; }

	public:
		void SetSurvivorState(ESurvivorState _eSurvivorState);

		ESurvivorState GetSurvivorState() const;

	private:
		void MoveAsTPS(float _fDeltaSeconds);

		void MoveAsFPS(float _fDeltaSeconds);

	public:
		const Vector3& GetCameraCenter();

		void SetCameraCenter(const Vector3& _vCenter);

		int32 GetCurCellIndex();

		Vector3 GetCurCentroidPosition();

		void SetCurCellIndex(int32 _iCellIndex);

		void SetCentroidPosition(const Vector3& _vCentroidPosition);

		float GetCurAzimuthRadian() const;

		void SetCurAzimuthRadian(float _fAzimuthRadian);

		float GetCurElevationRadian() const;

		void SetCurElevationRadian(float _fElevationRadian);

	/********************
		Data Members
	********************/
	protected:
		std::weak_ptr<CSurvivorStateComponent> m_wpSurvivorStateComponent;

		std::weak_ptr<CNavigationComponent> m_wpNavigationComponent;

		std::weak_ptr<CSphereComponent> m_wpBodySphereComponent;

		std::weak_ptr<CLightComponent> m_wpLightComponent;

	protected:
		uint32 m_iDirectionFlag = 0;

		float m_fDeltaSeconds = 0.0f;

	protected:
		// 생존자 인벤토리
		std::shared_ptr<CInventory> m_spInventory = nullptr;

		// 현재 생존자와 충돌한 채집
		std::weak_ptr<CCollectible> m_wpCurCollectible;

		// 현재 생존자와 충돌한 채집의 타입
		ECollectibleType m_eCurCollectibleType = ECollectibleType::ENUM_END;

		// 현재 생존자와 충돌한 콘솔
		std::weak_ptr<CConsole> m_wpCurConsole;

		// 현재 생존자와 충돌한 콘솔 타입
		EConsoleType m_eCurConsoleType = EConsoleType::ENUM_END;

		// 생존자와 충돌한 아이템 박스
		std::weak_ptr<CItemBox> m_wpCurItemBox;

		// 생존자와 충돌한 야생 동물
		std::weak_ptr<CWildAnimal> m_wpCurWildAnimal;

	protected:
		// 채집에 걸리는 시간
		float m_fCollectSeconds = 3.0f;

		// 콘솔에 걸리는 시간
		float m_fConsoleSeconds = 3.0f;

		// 누적 보간 체력 회복 시간
		float m_fSumLerpHPSeconds = 0.0f;

		// 누적 보간 스태미나 회복 시간
		float m_fSumLerpSPSeconds = 0.0f;

		float m_fCurLerpHP = 0.0f;

		float m_fCurLerpSP = 0.0f;

		// 누적 체력 재생 시간
		float m_fSumHPRegeneration = 0.0f;

		// 누적 스태미나 재생 시간
		float m_fSumSPRegeneration = 0.0f;

	protected:
		// 현재 스킬 포인트
		uint32 m_iCurSkillPoint = 0;

		// 현재 경험치
		float m_fCurExp = 0.0f;

		// 최대 경험치
		std::array<float, 10> m_arrMaxExps{};

		// 생존자 타입
		ESurvivorType m_eSurvivorType = ESurvivorType::ENUM_END;

		// 생존자 현재 레벨
		int32 m_iCurSurvivorLevel = 0;

		// 생존자 최대 레벨
		int32 m_iMaxSurvivorLevel = 9;

		// 공격력
		std::array<float, 10> m_arrAttackPower{};

		// 방어력
		std::array<float, 10> m_arrDefensePower{};

		// 현재 체력
		float m_fCurHP = 100.0f;

		// 체력 회복량
		std::array<float, 10> m_arrHPRegenerations{};

		// 최대 체력
		std::array<float, 10> m_arrMaxHPs{};

		// 현재 스테미나
		float m_fCurSP = 100.0f;

		// 스테미나 회복량
		std::array<float, 10> m_arrSPRegenerations{};

		// 최대 스테미나
		std::array<float, 10> m_arrMaxSPs{};

		// 시야 범위
		float m_fSightRange = 10.0f;

		// 현재 이동 속력
		float m_fCurMoveSpeed = 4.0f;

		// 현재 스킬 레벨
		std::array<int32, 5> m_arrCurSkillLevels{ -1, -1, -1, -1, -1 };

		// 최대 스킬 레벨
		std::array<int32, 5> m_arrMaxSkillLevels{ 0, 0, 0, 0, 0 };

		// 최대 스킬 쿨다운 시간
		std::vector<vector<float>> m_vecMaxSkillCoolDown;

		// 누적 스킬 쿨다운 시간
		std::vector<float> m_vecCurSkillCoolDown;

		// 스킬 정보들
		std::array<TSkillInfo, 5> m_arrSkillInfos;

		// 현재 이동 방향
		Vector3 m_vCurDirection = Vector3::Zero;

		// 이전 이동 방향
		Vector3 m_vPreDirection = Vector3::Zero;

		// 최대 보간 시간
		float m_fMaxLerpSeconds = 0.2f;

		// 누적 보간 시간
		float m_fSumLerpSeconds = 0.0f;
	};
}
