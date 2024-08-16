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
		// �θ� ���� ���̷�Ż �޽� ������Ʈ
		std::weak_ptr<CSkeletalMeshComponent> m_wpSkeletalMeshComponent;

		// �θ� ���� ��
		std::weak_ptr<CBone> m_wpBone;

		// �� ���
		Matrix m_matSocket = Matrix::Identity;

		// �� �̸�
		std::string m_strBoneName = "";
	};
}
