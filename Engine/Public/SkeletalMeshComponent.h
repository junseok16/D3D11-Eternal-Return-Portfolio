#pragma once
#include "MeshComponent.h"

namespace Engine
{
	class CSkeletalMeshData;
	class CAnimData;
	class CBone;

	class ENGINE_DLL CSkeletalMeshComponent : public CMeshComponent
	{
	/******************
		Ctor/Dtor
	******************/
	public:
		explicit CSkeletalMeshComponent() = default;

		virtual ~CSkeletalMeshComponent() = default;

	/********************
		Events
	********************/
	public:
		virtual HRESULT PreInitializeComponent() override;

		virtual HRESULT InitializeComponent() override;

		virtual HRESULT PostInitializeComponent() override;

		virtual HRESULT BeginPlay() override;

		virtual int32 PreTickComponent(float _fDeltaSeconds) override;

		virtual int32 TickComponent(float _fDeltaSeconds) override;

		virtual int32 PostTickComponent(float _fDeltaSeconds) override;

		virtual HRESULT EndPlay() override;

		virtual void Render() override;

		virtual void RenderShadow() override;

		virtual void Release() override;
		
	/********************
		Events
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
		void SetModelDesc(const std::wstring& _wstrSkeletalModelDesc) { m_wstrSkeletalModelDesc = _wstrSkeletalModelDesc; }

		const std::wstring& GetModelDesc() const { return m_wstrSkeletalModelDesc; }

		const shared_ptr<CAnimData>& GetAnimData() { return m_spAnimData; }
		
	/********************
		Methods
	********************/
	public:
		std::shared_ptr<CBone> FindBone(const std::string& _strBoneName);

		void SetPlayRate(float _fPlayRate);

		void PlayAnimation();

		void StopAnimation();

	/********************
		Data Members
	********************/
	private:
		std::wstring m_wstrSkeletalModelDesc = L"";

		std::shared_ptr<CSkeletalMeshData> m_spSkeletalMeshData = nullptr;

		std::shared_ptr<CAnimData> m_spAnimData = nullptr;

		bool m_bPlayAnimation = true;
	};
}
