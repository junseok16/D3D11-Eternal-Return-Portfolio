#include "pch.h"
#include "InItemBoxBackground.h"

#include "ItemBox.h"

HRESULT Client::CInItemBoxBackground::PreInitialize()
{
    SetActorRenderType(ERenderType::TRANSLUCENT_OBJECT);
    SetPrimitiveType(EPrimitiveType::POINT);
    SetImageNames({ L"Btn_Ping_Basic_02" });

    m_wstrGeometryShaderName = L"GS_InGameSlider";
    m_wstrPixelShaderName = L"PS_InItemBox";

    return CImage::PreInitialize();
}

HRESULT Client::CInItemBoxBackground::Initialize()
{
    SetWidth(20.0f);
    SetHeight(20.0);
    SetMaxWidth(20.0);
    SetMaxHeight(20.0);
    return CImage::Initialize();
}

HRESULT Client::CInItemBoxBackground::PostInitialize()
{
    if (FAILED(CImage::PostInitialize())) { return E_FAIL; }

    return S_OK;
}

HRESULT Client::CInItemBoxBackground::BeginPlay()
{
    if (FAILED(CImage::BeginPlay())) { return E_FAIL; }

    Vector4 v4Position = m_wpItemBox.lock()->GetItemBoxWorldPosition();
    Vector3 v3Position = { v4Position.x, v4Position.y + 1.0f, v4Position.z };

    SetActorLocalPosition(v3Position);
    return S_OK;
}

int32 Client::CInItemBoxBackground::PreTick(float _fDeltaSeconds)
{
    switch (CImage::PreTick(_fDeltaSeconds))
    {
    case -1:	return -1;
    default:	break;
    }

    return 0;
}

int32 Client::CInItemBoxBackground::Tick(float _fDeltaSeconds)
{
    switch (CImage::Tick(_fDeltaSeconds))
    {
    case -1:	return -1;
    default:	break;
    }

    return 0;
}

int32 Client::CInItemBoxBackground::PostTick(float _fDeltaSeconds)
{
    switch (CImage::PostTick(_fDeltaSeconds))
    {
    case -1:	return -1;
    default:	break;
    }

    return 0;
}

HRESULT Client::CInItemBoxBackground::EndPlay()
{
    if (FAILED(CImage::EndPlay())) { return E_FAIL; }

    return S_OK;
}

void Client::CInItemBoxBackground::Render()
{
    CImage::Render();
}

void Client::CInItemBoxBackground::Release()
{
    CImage::Release();
}
