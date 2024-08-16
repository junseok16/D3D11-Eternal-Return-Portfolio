#pragma once

namespace Engine
{
	class CStateComponent;
	class CSkeletalMeshData;
	class CActor;
	class CAnimState;

	class CAnimData : public enable_shared_from_this<CAnimData>
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CAnimData() = default;

		virtual ~CAnimData() = default;

	/********************
		Events
	********************/
	public:
		static std::shared_ptr<CAnimData> Create(const std::shared_ptr<CActor>& _spOwnerActor);

		HRESULT Initialize(const std::shared_ptr<CActor>& _spOwnerActor);

		int32 Tick(float _fDeltaSeconds);

		void Render();

		void Release();
		
	/********************
		Methods
	********************/
	public:
		HRESULT AddAnimState
		(
			uint32 _iAnimState,
			const std::wstring& _wstrAnimStateName,
			const std::vector<std::string>& _vecAnimationNames,
			bool _bLoop
		);
		
	/********************
		Getter/Setter
	********************/
	public:
		void SetSkeletalMeshData(const std::shared_ptr<CSkeletalMeshData>& _spSkeletalMeshData);

		std::shared_ptr<CAnimState> GetCurAnimState() const;

	/********************
		Data Members
	********************/
	private:
		// �� �ִϸ��̼� �׷����� ���� �ִ� ����
		std::weak_ptr<CActor> m_wpOwnerActor;

		// �� ������ ���� ������Ʈ
		std::weak_ptr<CStateComponent> m_wpStateComponent;

		std::weak_ptr<CSkeletalMeshData> m_wpSkeletalMeshData;

	private:
		// �ִϸ��̼� ���µ�
		std::unordered_map<uint32, std::shared_ptr<CAnimState>> m_umapAnimStates;

		// ���� �ִϸ��̼� ����
		std::wstring m_wstrCurAnimState = L"";

		// ���� �÷��̾� �ִϸ��̼� ����
		uint32 m_iCurAnimState = 0;
	};
}
