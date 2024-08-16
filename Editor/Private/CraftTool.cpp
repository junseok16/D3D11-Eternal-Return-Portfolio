#include "pch.h"
#include "CraftTool.h"

#include "StaticMeshComponent.h"

#include "Survivor.h"

shared_ptr<CCraftTool> Editor::CCraftTool::Create(const std::shared_ptr<CActor>& _spWeaponOwner, const std::string& _strBoneName, ECraftToolType _eCraftToolType)
{
	const shared_ptr<CCraftTool> spCraftTool = make_shared<CCraftTool>();
	spCraftTool->Initialize(_spWeaponOwner, _strBoneName, _eCraftToolType);
	return spCraftTool;
}

void Editor::CCraftTool::Initialize(const std::shared_ptr<CActor>& _spWeaponOwner, const std::string& _strBoneName, ECraftToolType _eCraftToolType)
{
	m_wpOwnerActor = _spWeaponOwner;
	m_strBoneName = _strBoneName;
	m_eCraftToolType = _eCraftToolType;
}

HRESULT Editor::CCraftTool::PreInitialize()
{
	{
		m_wpStaticMeshComponent = CreateActorComponent<CStaticMeshComponent>(L"StaticMeshComponent", EComponentType::STATIC_MESH);
		SetRootComponent(m_wpStaticMeshComponent.lock());

		wstring wstrCraftToolType = L"";
		switch (m_eCraftToolType)
		{
		case Editor::ECraftToolType::HAMMER:	wstrCraftToolType = L"CraftHammer";		break;
		case Editor::ECraftToolType::DRIVER:	wstrCraftToolType = L"CraftDriver";		break;
		case Editor::ECraftToolType::FRYING_PAN:wstrCraftToolType = L"CraftFryingPan";	break;
		default: CHECKF(false, L"Craft tool type is not designated.");					break;
		}

		m_wpStaticMeshComponent.lock()->SetModelDesc(wstrCraftToolType);
		m_wpStaticMeshComponent.lock()->SetVertexShaderDesc(L"VS_StaticMesh");
		m_wpStaticMeshComponent.lock()->SetPixelShaderDesc(L"PS_StaticMesh");
	}

	m_wpSurvivor = dynamic_pointer_cast<CSurvivor>(m_wpOwnerActor.lock());

	return CSocket::PreInitialize();
}

HRESULT Editor::CCraftTool::Initialize()
{
	if (FAILED(CSocket::Initialize())) { return E_FAIL; }

	switch (m_eCraftToolType)
	{
	case Editor::ECraftToolType::HAMMER:
		SetActorLocalRotate(Vector3::UnitX, 90.0f);
		break;

	case Editor::ECraftToolType::DRIVER:
		break;

	case Editor::ECraftToolType::FRYING_PAN:
		break;

	default:
		CHECKF(false, L"Craft tool type is not designated.");
		break;
	}

	return S_OK;
}

HRESULT Editor::CCraftTool::PostInitialize()
{
	if (FAILED(CSocket::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Editor::CCraftTool::BeginPlay()
{
	if (FAILED(CSocket::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Editor::CCraftTool::PreTick(float _fDeltaSeconds)
{
	m_eSurvivorState = m_wpSurvivor.lock()->GetSurvivorState();

	switch (m_eCraftToolType)
	{
	case Editor::ECraftToolType::HAMMER:
		if (m_eSurvivorState != ESurvivorState::CRAFT_METAL) { return 0; }
		break;

	case Editor::ECraftToolType::DRIVER:
		if (m_eSurvivorState != ESurvivorState::CRAFT_METAL) { return 0; }
		break;

	case Editor::ECraftToolType::FRYING_PAN:
		if (m_eSurvivorState != ESurvivorState::CRAFT_FOOD) { return 0; }
		break;

	default:
		CHECKF(false, L"Craft tool type is not designated.");
		break;
	}

	switch (CSocket::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Editor::CCraftTool::Tick(float _fDeltaSeconds)
{
	switch (m_eCraftToolType)
	{
	case Editor::ECraftToolType::HAMMER:
		if (m_eSurvivorState != ESurvivorState::CRAFT_METAL) { return 0; }
		break;

	case Editor::ECraftToolType::DRIVER:
		if (m_eSurvivorState != ESurvivorState::CRAFT_METAL) { return 0; }
		break;

	case Editor::ECraftToolType::FRYING_PAN:
		if (m_eSurvivorState != ESurvivorState::CRAFT_FOOD) { return 0; }
		break;

	default:
		CHECKF(false, L"Craft tool type is not designated.");
		break;
	}

	switch (CSocket::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Editor::CCraftTool::PostTick(float _fDeltaSeconds)
{
	switch (m_eCraftToolType)
	{
	case Editor::ECraftToolType::HAMMER:
		if (m_eSurvivorState != ESurvivorState::CRAFT_METAL) { return 0; }
		break;

	case Editor::ECraftToolType::DRIVER:
		if (m_eSurvivorState != ESurvivorState::CRAFT_METAL) { return 0; }
		break;

	case Editor::ECraftToolType::FRYING_PAN:
		if (m_eSurvivorState != ESurvivorState::CRAFT_FOOD) { return 0; }
		break;

	default:
		CHECKF(false, L"Craft tool type is not designated.");
		break;
	}

	switch (CSocket::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Editor::CCraftTool::EndPlay()
{
	if (FAILED(CSocket::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Editor::CCraftTool::Render()
{
	switch (m_eCraftToolType)
	{
	case Editor::ECraftToolType::HAMMER:
		if (m_eSurvivorState != ESurvivorState::CRAFT_METAL) { return; }
		break;

	case Editor::ECraftToolType::DRIVER:
		if (m_eSurvivorState != ESurvivorState::CRAFT_METAL) { return; }
		break;

	case Editor::ECraftToolType::FRYING_PAN:
		if (m_eSurvivorState != ESurvivorState::CRAFT_FOOD) { return; }
		break;

	default:
		CHECKF(false, L"Craft tool type is not designated.");
		break;
	}

	CSocket::Render();
}

void Editor::CCraftTool::Release()
{
	CSocket::Release();
}
