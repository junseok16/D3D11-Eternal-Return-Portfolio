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

		// 이 애니메이션 상태 이름
		std::wstring m_wstrAnimStateName = L"";

	private:
		// 이 애니메이션 상태에서 재생할 애니메이션 이름들
		std::vector<std::string> m_vecAnimationNames;

		// 현재 재생 중인 애니메이션 이름
		std::string m_wstrCurAnimationName = "";

		// 현재 재생 중인 애니메이션 인덱스
		uint32 m_iCurAnimationIndex = 0;

	private:
		// 애니메이션을 반복할지 여부
		bool m_bLoop = false;
	};
}
