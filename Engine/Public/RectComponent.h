#pragma once
#include "MeshComponent.h"

namespace Engine
{
	class CPrimitiveMeshData;

	class ENGINE_DLL CRectComponent : public CMeshComponent
	{
	/******************
		Ctor/Dtor
	******************/
	public:
		explicit CRectComponent() = default;

		virtual ~CRectComponent() = default;

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

		virtual void Release() override;
		
	public:
		static shared_ptr<CRectComponent> Create
		(
			const std::wstring& _wstrPrimitiveDesc,
			const std::wstring& _wstrVertexShader,
			const std::wstring& _wstrPixelShader
		);

	/********************
		Getter/Setter
	********************/
	public:
		void SetPrimitiveDesc(const std::wstring& _wstrPrimitiveDesc) { m_wstrPrimitiveDesc = _wstrPrimitiveDesc; }

		const std::wstring& GetPrimitiveDesc() const { return m_wstrPrimitiveDesc; }

	/********************
		Data Members
	********************/
	private:
		std::wstring m_wstrPrimitiveDesc = L"";

		std::shared_ptr<CPrimitiveMeshData> m_spPrimitiveMeshData = nullptr;
	};
}
