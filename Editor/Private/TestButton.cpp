#include "pch.h"
#include "TestButton.h"

HRESULT Editor::CTestButton::PreInitialize()
{
	// 델리게이트를 추가합니다.
	// AddOnClickDelegate(static_pointer_cast<CTestButton>(shared_from_this()), &CTestButton::OnButtonClick);

	SetActorRenderType(ERenderType::OPAQUE_USER_INTERFACE);
	SetPrimitiveType(EPrimitiveType::POINT);
	SetButtonNames({ L"Btn_LevelUp_Disabled" });
	return CButton::PreInitialize();
}

HRESULT Editor::CTestButton::Initialize()
{
	SetPivot({ 460.0f, 600.0f });
	SetWidth(54.0f);
	SetHeight(58.0f);
	return CButton::Initialize();
}

HRESULT Editor::CTestButton::PostInitialize()
{
	if (FAILED(CButton::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Editor::CTestButton::BeginPlay()
{
	if (FAILED(CButton::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Editor::CTestButton::PreTick(float _fDeltaSeconds)
{
	switch (CButton::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Editor::CTestButton::Tick(float _fDeltaSeconds)
{
	switch (CButton::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Editor::CTestButton::PostTick(float _fDeltaSeconds)
{
	switch (CButton::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Editor::CTestButton::EndPlay()
{
	if (FAILED(CButton::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Editor::CTestButton::Render()
{
	CButton::Render();
}

void Editor::CTestButton::Release()
{
	CButton::Release();
}
