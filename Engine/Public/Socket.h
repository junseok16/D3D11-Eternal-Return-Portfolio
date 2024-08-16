#pragma once
#include "Actor.h"

namespace Engine
{
	class CSkeletalMeshComponent;
	class CBone;

	class ENGINE_DLL CSocket : public CActor
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CSocket() = default;

		virtual ~CSocket() = default;
		
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
		
	/********************
		Getter/Setter
	********************/
	public:
		void SetBoneName(const std::string& _strBoneName) { m_strBoneName = _strBoneName; }

	/********************
		Data Members
	********************/
	protected:
		// 부모 액터 스켈레탈 메시 컴포넌트
		std::weak_ptr<CSkeletalMeshComponent> m_wpSkeletalMeshComponent;

		// 부모 액터 본
		std::weak_ptr<CBone> m_wpBone;

		// 본 행렬
		Matrix m_matSocket = Matrix::Identity;

		// 본 이름
		std::string m_strBoneName = "";
	};
}
