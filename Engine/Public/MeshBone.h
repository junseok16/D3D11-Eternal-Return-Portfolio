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
		// �ִϸ��̼� ��ȯ ����
		EAnimChangeState m_eAnimChangeState = EAnimChangeState::PLAY;

		// �ϵ� �ִϸ��̼� ���� �ð�
		float m_fHardInterplateSeconds = 0.1f;

		// ����Ʈ �ִϸ��̼� ���� �ð�
		float m_fSoftInterpolateSeconds = 0.05f;

		// �ִϸ��̼� ���� �ð�
		float m_fCurSeconds = 0.0f;

		// �ִϸ��̼� ��
		uint32 m_iNumAnimations = 0;

		// �ִϸ��̼� �ݺ� ����
		bool m_bLoop = true;

		// ��� ����
		std::vector<std::shared_ptr<CBone>> m_vecBones;

		// ��� �ִϸ��̼ǵ�
		std::unordered_map<std::string, std::shared_ptr<CAnimation>> m_umapAnimtaions;

		// �ִϸ��̼� ��� �ӵ�
		float m_fPlayRate = 1.0f;

	private:
		// �ִϸ��̼� 
		std::weak_ptr<CAnimData> m_wpAnimData;

		// ���� �ִϸ��̼� ����
		std::weak_ptr<CAnimState> m_wpCurAnimState;

		// ���� �ִϸ��̼� ����
		uint32 m_iAfterAnimState = 0;

		// ���� �ִϸ��̼� ����
		int32 m_iCurAnimState = -1;

		// ���� �ִϸ��̼� �̸�
		string m_strCurAnimationName = "";

		// ���� �ִϸ��̼� �̸�
		string m_strAfterAnimationName = "";

		bool m_bLastAnim = false;

	private:
		// �� ���� ������ ��Ʈ ������Ʈ
		std::weak_ptr<CSceneComponent> m_wpOwnerComponent;

		// �� ���� ������ ����
		std::weak_ptr<CActor> m_wpOwnerActor;

		// ���� ������Ʈ
		std::weak_ptr<CStateComponent> m_wpStateComponent;
	};
}
