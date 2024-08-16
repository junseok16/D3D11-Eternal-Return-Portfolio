#pragma once
#include "MeshComponent.h"

namespace Engine
{
	class CPrimitiveMeshData;

	class ENGINE_DLL CGeometryComponent : public CMeshComponent
	{
	/******************
		Ctor/Dtor
	******************/
	public:
		explicit CGeometryComponent() = default;

		virtual ~CGeometryComponent() = default;

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
		void SetPrimitiveType(EPrimitiveType _ePrimitiveType) { m_ePrimitiveType = _ePrimitiveType; }

		void SetProjectionType(EProjectionType _eProjectionType) { m_eProjectionType = _eProjectionType; }

		void SetTextureNames(const std::vector<std::wstring>& _vecTextureNames) { m_vecTextureNames = _vecTextureNames; }

		void SetTextureIndex(uint32 _iTextureIndex);

	/********************
		Data Members
	********************/
	private:
		EPrimitiveType m_ePrimitiveType = EPrimitiveType::ENUM_END;

		EProjectionType m_eProjectionType = EProjectionType::ENUM_END;

		std::vector<std::wstring> m_vecTextureNames;

		uint32 m_iTextureIndex = 0;

		std::shared_ptr<CPrimitiveMeshData> m_spPrimitiveMeshData = nullptr;
	};
}
