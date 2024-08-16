#include "pch.h"
#include "RectComponent.h"

#include "PrimitiveMeshData.h"

shared_ptr<CRectComponent> Engine::CRectComponent::Create(const std::wstring& _wstrPrimitiveDesc, const std::wstring& _wstrVertexShader, const std::wstring& _wstrPixelShader)
{
	const shared_ptr<CRectComponent> spRectComponent = make_shared<CRectComponent>();
	spRectComponent->SetPrimitiveDesc(_wstrPrimitiveDesc);
	spRectComponent->SetVertexShaderDesc(_wstrVertexShader);
	spRectComponent->SetPixelShaderDesc(_wstrPixelShader);

	spRectComponent->SetComponentType(EComponentType::RECT);
	spRectComponent->SetComponentName(_wstrPrimitiveDesc);

	spRectComponent->PreInitializeComponent();
	spRectComponent->InitializeComponent();
	spRectComponent->PostInitializeComponent();
	spRectComponent->BeginPlay();

	return spRectComponent;
}

HRESULT Engine::CRectComponent::PreInitializeComponent()
{
	if (FAILED(CMeshComponent::PreInitializeComponent())) { return E_FAIL; }
	m_spPrimitiveMeshData = CPrimitiveMeshData::Create(static_pointer_cast<CSceneComponent>(shared_from_this()), EPrimitiveType::RECT, { m_wstrPrimitiveDesc }, m_wstrVertexShaderDesc, m_wstrPixelShaderDesc);

	return S_OK;
}

HRESULT Engine::CRectComponent::InitializeComponent()
{
	if (FAILED(CMeshComponent::InitializeComponent())) { return E_FAIL; }

	return S_OK;
}

HRESULT Engine::CRectComponent::PostInitializeComponent()
{
	if (FAILED(CMeshComponent::PostInitializeComponent())) { return E_FAIL; }

	return S_OK;
}

HRESULT Engine::CRectComponent::BeginPlay()
{
	if (FAILED(CMeshComponent::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Engine::CRectComponent::PreTickComponent(float _fDeltaSeconds)
{
	switch (CMeshComponent::PreTickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Engine::CRectComponent::TickComponent(float _fDeltaSeconds)
{
	switch (CMeshComponent::TickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Engine::CRectComponent::PostTickComponent(float _fDeltaSeconds)
{
	switch (CMeshComponent::PostTickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	m_spPrimitiveMeshData->Tick();
	return 0;
}

HRESULT Engine::CRectComponent::EndPlay()
{
	if (FAILED(CMeshComponent::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Engine::CRectComponent::Render()
{
	CMeshComponent::Render();

	m_spPrimitiveMeshData->Render(0);
}

void Engine::CRectComponent::Release()
{
	m_spPrimitiveMeshData->Release();
	m_spPrimitiveMeshData = nullptr;

	CMeshComponent::Release();
}
