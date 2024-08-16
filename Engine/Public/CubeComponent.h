#pragma once
#include "MeshComponent.h"

namespace Engine
{
	class CConstantBuffer;
	class CPrimitiveMeshData;

	class ENGINE_DLL CCubeComponent final : public CMeshComponent
	{
	/******************
		Ctor/Dtor
	******************/
	public:
		explicit CCubeComponent() = default;

		virtual ~CCubeComponent() = default;

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
		void SetPrimitiveDesc(const std::vector<std::wstring>& _vecPrimitiveDescs) { m_vecPrimitiveDescs = _vecPrimitiveDescs; }

		const std::vector<std::wstring>& GetPrimitiveDesc() const { return m_vecPrimitiveDescs; }

		void SetConstantBuffer(const shared_ptr<CConstantBuffer>& _spConstantBuffer);

	/********************
		Data Members
	********************/
	private:
		std::vector<std::wstring> m_vecPrimitiveDescs;

		std::shared_ptr<CPrimitiveMeshData> m_spPrimitiveMeshData = nullptr;
	};
}
