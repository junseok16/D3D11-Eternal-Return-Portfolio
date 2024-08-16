#pragma once
#include "PrimitiveComponent.h"

namespace Engine
{
	class ENGINE_DLL CMeshComponent : public CPrimitiveComponent
	{
	/******************
		Ctor/Dtor
	******************/
	public:
		explicit CMeshComponent() = default;

		virtual ~CMeshComponent() = default;

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
		
	/********************
		Getter/Setter
	********************/
	public:
		void SetVertexShaderDesc(const std::wstring& _wstrVertexShaderDesc) { m_wstrVertexShaderDesc = _wstrVertexShaderDesc; }

		void SetGeometryShaderDesc(const std::wstring& _wstrGeometryShaderDesc) { m_wstrGeometryShaderDesc = _wstrGeometryShaderDesc; }

		void SetPixelShaderDesc(const std::wstring& _wstrPixelShaderDesc) { m_wstrPixelShaderDesc = _wstrPixelShaderDesc; }

		const std::wstring& GetVertexShaderDesc() { return m_wstrVertexShaderDesc; }

		const std::wstring& GetGeometryShaderDesc() { return m_wstrGeometryShaderDesc; }

		const std::wstring& GetPixelShaderDesc() { return m_wstrPixelShaderDesc; }

	/********************
		Data Members
	********************/
	protected:
		std::wstring m_wstrVertexShaderDesc = L"";

		std::wstring m_wstrGeometryShaderDesc = L"";

		std::wstring m_wstrPixelShaderDesc = L"";
	};
}
