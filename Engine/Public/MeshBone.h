#pragma once

namespace Engine
{
	enum class EAnimChangeState
	{
		PLAY,
		SOFT_INTERPOLATE,
		HARD_INTERPOLATE,
	};

	class CActor;
	class CStateComponent;
	class CSceneComponent;
	class CAnimState;
	class CAnimData;
	class CBone;
	class CAnimation;

	class CMeshBone final : public enable_shared_from_this<CMeshBone>
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CMeshBone() = default;

		virtual ~CMeshBone() = default;
		
	/********************
		Events
	********************/
	public:
		static std::shared_ptr<CMeshBone> Create
		(
			const std::shared_ptr<CSceneComponent>& _spOwnerComponent,
			const std::wstring& _wstrModelDesc = L""
		);

		HRESULT Initialize
		(
			const std::shared_ptr<CSceneComponent>& _spOwnerComponent,
			const std::wstring& _wstrModelDesc = L""
		);

		int32 Tick(float _fDeltaSeconds);

		void Release();
		
	/********************
		Getter/Setter
	********************/
	public:
		const std::vector<std::shared_ptr<CBone>>& GetBones() { return m_vecBones; }

		void SetAnimData(const std::shared_ptr<CAnimData> _spAnimData) { m_wpAnimData = _spAnimData; }

	/********************
		Methods
	********************/
	public:
		std::shared_ptr<CBone> FindBone(const std::string& _strBoneName);

		void SetPlayRate(float _fPlayRate);

	private:
		void UpdateAnimState();

		void RecalcAnimation(float _fDeltaSeconds);

		bool InterpolateAnimation(float _fDeltaSeconds, float _fInterpolateSeconds);

	/********************
		Data Members
	********************/
	private:
		// 애니메이션 전환 상태
		EAnimChangeState m_eAnimChangeState = EAnimChangeState::PLAY;

		// 하드 애니메이션 보간 시간
		float m_fHardInterplateSeconds = 0.1f;

		// 소프트 애니메이션 보간 시간
		float m_fSoftInterpolateSeconds = 0.05f;

		// 애니메이션 보간 시각
		float m_fCurSeconds = 0.0f;

		// 애니메이션 수
		uint32 m_iNumAnimations = 0;

		// 애니메이션 반복 여부
		bool m_bLoop = true;

		// 모든 본들
		std::vector<std::shared_ptr<CBone>> m_vecBones;

		// 모든 애니메이션들
		std::unordered_map<std::string, std::shared_ptr<CAnimation>> m_umapAnimtaions;

		// 애니메이션 재생 속도
		float m_fPlayRate = 1.0f;

	private:
		// 애니메이션 
		std::weak_ptr<CAnimData> m_wpAnimData;

		// 현재 애니메이션 상태
		std::weak_ptr<CAnimState> m_wpCurAnimState;

		// 다음 애니메이션 상태
		uint32 m_iAfterAnimState = 0;

		// 현재 애니메이션 상태
		int32 m_iCurAnimState = -1;

		// 현재 애니메이션 이름
		string m_strCurAnimationName = "";

		// 다음 애니메이션 이름
		string m_strAfterAnimationName = "";

		bool m_bLastAnim = false;

	private:
		// 이 본을 소유한 루트 컴포넌트
		std::weak_ptr<CSceneComponent> m_wpOwnerComponent;

		// 이 본을 소유한 액터
		std::weak_ptr<CActor> m_wpOwnerActor;

		// 상태 컴포넌트
		std::weak_ptr<CStateComponent> m_wpStateComponent;
	};
}
