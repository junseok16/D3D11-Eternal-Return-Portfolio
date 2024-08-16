#pragma once

namespace Engine
{
	class CAnimState final : public enable_shared_from_this<CAnimState>
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CAnimState() = default;

		virtual ~CAnimState() = default;

	/********************
		Events
	********************/
	public:
		static std::shared_ptr<CAnimState> Create
		(
			uint32 _iAnimState,
			const std::wstring& _wstrAnimStateName,
			const std::vector<std::string>& _vecAnimationNames,
			bool _bLoop
		);

		HRESULT Initialize
		(
			uint32 _iAnimState,
			const std::wstring& _wstrAnimStateName,
			const std::vector<std::string>& _vecAnimationNames,
			bool _bLoop
		);

		int32 Tick(float _fDeltaSeconds);

		void Release();
		
	/********************
		Getter/Setter
	********************/
	public:
		uint32 GetAnimState() const { return m_iAnimState; }

		string GetCurAnimationName() const { return m_vecAnimationNames[m_iCurAnimationIndex]; }

		uint32 GetCurAnimIndex() const { return m_iCurAnimationIndex; }

		bool IsLoop() const { return m_bLoop; }

		bool HasAnotherAnimation();
		
	/********************
		Data Members
	********************/
	private:
		uint32 m_iAnimState = 0;

		// �� �ִϸ��̼� ���� �̸�
		std::wstring m_wstrAnimStateName = L"";

	private:
		// �� �ִϸ��̼� ���¿��� ����� �ִϸ��̼� �̸���
		std::vector<std::string> m_vecAnimationNames;

		// ���� ��� ���� �ִϸ��̼� �̸�
		std::string m_wstrCurAnimationName = "";

		// ���� ��� ���� �ִϸ��̼� �ε���
		uint32 m_iCurAnimationIndex = 0;

	private:
		// �ִϸ��̼��� �ݺ����� ����
		bool m_bLoop = false;
	};
}
