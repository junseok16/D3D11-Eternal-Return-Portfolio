#pragma once
#include "MeshComponent.h"

namespace Engine
{
	class CStaticMeshData;

	class ENGINE_DLL CStaticMeshComponent : public CMeshComponent
	{
	/******************
		Ctor/Dtor
	******************/
	public:
		explicit CStaticMeshComponent() = default;

		virtual ~CStaticMeshComponent() = default;

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
		
	public:
		HRESULT ChangeModelDesc(const std::wstring& _wstrModelDesc);

	/********************
		Getter/Setter
	********************/
	public:
		void SetModelDesc(const std::wstring& _wstrStaticModelDesc) { m_wstrStaticModelDesc = _wstrStaticModelDesc; }

		const std::wstring& GetModelDesc() const { return m_wstrStaticModelDesc; }

	/********************
		Data Members
	********************/
	private:
		std::wstring m_wstrStaticModelDesc = L"";

		std::shared_ptr<CStaticMeshData> m_spStaticMeshData = nullptr;
	};
}
