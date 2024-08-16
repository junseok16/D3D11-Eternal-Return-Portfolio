#include "pch.h"
#include "InHPBarSlider.h"

#include "WildAnimal.h"
#include "Boss.h"

HRESULT Editor::CInHPBarSlider::PreInitialize()
{
	SetActorRenderType(ERenderType::TRANSLUCENT_OBJECT);
	SetPrimitiveType(EPrimitiveType::POINT);
	SetFrontSliderName(L"Img_Main_Gage_04");
	m_vSliderOffset = { 0.0f, 3.5f, 0.0f };

	m_wstrGeometryShaderName = L"GS_InGameSlider";
	m_wstrPixelShaderName = L"PS_InGameSlider";

	switch (m_eEnemyType)
	{
	case EEnemyType::WILD_ANIMAL:
		m_wpWildAnimal = dynamic_pointer_cast<CWildAnimal>(m_wpActor.lock());
		break;

	case EEnemyType::BOSS:
		m_wpBoss = dynamic_pointer_cast<CBoss>(m_wpActor.lock());
		break;
	}

	return CSlider::PreInitialize();
}

HRESULT Editor::CInHPBarSlider::Initialize()
{
	SetWidth(2.0f);
	SetHeight(0.25f);
	SetMaxWidth(2.0f);
	SetMaxHeight(0.25f);
	return CSlider::Initialize();
}

HRESULT Editor::CInHPBarSlider::PostInitialize()
{
	if (FAILED(CSlider::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Editor::CInHPBarSlider::BeginPlay()
{
	if (FAILED(CSlider::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Editor::CInHPBarSlider::PreTick(float _fDeltaSeconds)
{
	switch (CSlider::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	Vector3 vPosition = m_wpActor.lock()->GetActorWorldPosition().value();

	SetActorLocalPosition(vPosition + m_vSliderOffset);
	return 0;
}

int32 Editor::CInHPBarSlider::Tick(float _fDeltaSeconds)
{
	switch (CSlider::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}
	
	return 0;
}

int32 Editor::CInHPBarSlider::PostTick(float _fDeltaSeconds)
{
	switch (CSlider::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	TickSlider();
	return 0;
}

HRESULT Editor::CInHPBarSlider::EndPlay()
{
	if (FAILED(CSlider::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Editor::CInHPBarSlider::Render()
{
	CSlider::Render();
}

void Editor::CInHPBarSlider::Release()
{
	CSlider::Release();
}

void Editor::CInHPBarSlider::TickSlider()
{
	float fCurHP = 0.0f;
	float fMaxHP = 0.0f;

	switch (m_eEnemyType)
	{
	case Editor::EEnemyType::WILD_ANIMAL:
		fCurHP = m_wpWildAnimal.lock()->GetCurHP();
		fMaxHP = m_wpWildAnimal.lock()->GetMaxHP();
		break;

	case Editor::EEnemyType::SURVIVOR:
		break;

	case Editor::EEnemyType::BOSS:
		fCurHP = m_wpBoss.lock()->GetCurHP();
		fMaxHP = m_wpBoss.lock()->GetMaxHP();
		break;

	default:
		CHECKF(false, L"Enemy type is not designated.")
			break;
	}

	if (fCurHP <= 0.0f) { fCurHP = 0.0f; }

	m_fWidth = m_fMaxWidth * fCurHP / fMaxHP;
}
