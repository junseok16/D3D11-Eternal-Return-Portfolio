// default
#include "pch.h"
#include "TabWindow.h"

// manager
#include "IMGUIManager.h"

// engine
#include "World.h"
#include "Level.h"
#include "Actor.h"
#include "Pawn.h"
#include "Controller.h"

#include "Bear.h"
#include "Boar.h"
#include "Chicken.h"
#include "Dog.h"
#include "Wolf.h"

// component
#include "StaticMeshComponent.h"
#include "SphereComponent.h"

// editor
#include "EditorCamera.h"
#include "EditorLevel.h"

#include "Location.h"
#include "ConsoleGroup.h"
#include "Console.h"
#include "CollectibleGroup.h"
#include "Collectible.h"

std::shared_ptr<CTabWindow> Editor::CTabWindow::Create(const std::shared_ptr<CIMGUIManager>& _spIMGUIManager)
{
	const shared_ptr<CTabWindow> spWindow = make_shared<CTabWindow>();
	ENSURE(spWindow->Initialize(_spIMGUIManager));
	return spWindow;
}

HRESULT Editor::CTabWindow::Initialize(const std::shared_ptr<CIMGUIManager>& _spIMGUIManager)
{
	m_wpIMGUIManager = _spIMGUIManager;
	m_wpEditorLevel = dynamic_pointer_cast<CEditorLevel>(CWorld::GetInstance()->GetCurLevel());
	m_wpController = m_wpEditorLevel.lock()->GetController();
	return S_OK;
}

int32 Editor::CTabWindow::Tick()
{
	TickPlayButton();
	TickStopButton();
	TickSaveButton();
	TickLoadButton();
	return 0;
}

void Editor::CTabWindow::Release()
{
}



void Editor::CTabWindow::TickPlayButton()
{
	if (ImGui::Button("Play", ImVec2(120, 30)))
	{
		m_wpController.lock()->EnableInput();
		m_wpController.lock()->GetPawn()->SetOnAir(true);
		m_wpIMGUIManager.lock()->GetEditorCamera()->SetOnAir(true);
		m_bOnAir = true;
	}
	ImGui::SameLine();
}



void Editor::CTabWindow::TickStopButton()
{
	if (ImGui::Button("Stop", ImVec2(120, 30)))
	{
		m_wpController.lock()->DisableInput();
		m_wpController.lock()->GetPawn()->SetOnAir(false);
		m_wpIMGUIManager.lock()->GetEditorCamera()->SetOnAir(false);
		m_bOnAir = false;
	}
}



void Editor::CTabWindow::TickSaveButton()
{
	ImGui::SeparatorText("Save");

	ImGui::InputTextWithHint("Save File", "Lumia", m_chSaveFileName, IM_ARRAYSIZE(m_chSaveFileName));

	if (ImGui::Button("Save", ImVec2(-FLT_MIN, 0.0f)))
	{
		{
			string strPath = m_strFilePath + "/" + "WildAnimal.dat";

			std::ofstream outFile;
			outFile.open(strPath.c_str(), ios_base::out | ios_base::binary | ios_base::trunc);

			ZeroMemory(m_chSaveFileName, MAX_PATH);

			// ������ ������ ���� ���
			if (!outFile.is_open()) { return; }

			// SaveWildAnimal(outFile);
		}
		
		{

		}
		// SaveLocations(outFile);
		// SaveNavigations(outFile);
		// SaveCollectibleGroups(outFile);
		// SaveConsoleGroups(outFile);
	}
}

void Editor::CTabWindow::SaveLocations(std::ofstream& _outFile)
{
	/*
	* ���� Ÿ��: ����			uint32
	* ���� ����					uint32
	* {
	*	���� �̸�				wstring
	*	���� Ÿ��				uint32
	*	����ƽ ������Ʈ �̸�	wstring
	*	���ؽ� ���̴� �̸�		wstring
	*	�ȼ� ���̴� �̸�		wstring
	* }
	*/
	
	// ������ �ҷ��ɴϴ�.
	const std::unordered_map<std::wstring, std::weak_ptr<CLocation>>& umapLocations = m_wpEditorLevel.lock()->GetLocations();

	// ���� Ÿ��
	uint32 iInstancableActorType = static_cast<uint32>(EInstancableActorType::LOCATION);
	_outFile.write(reinterpret_cast<char*>(&iInstancableActorType), sizeof(uint32));

	// ���� ����
	uint32 iNumLocations = static_cast<uint32>(umapLocations.size());
	_outFile.write(reinterpret_cast<char*>(&iNumLocations), sizeof(uint32));
	
	for (const auto& pair : umapLocations)
	{
		// ���� �̸�
		wstring wstrLocationName = pair.second.lock()->GetActorName();
		uint32 iLocationNameLength = static_cast<uint32>(wstrLocationName.length());

		string strLocationName = "";
		strLocationName.assign(wstrLocationName.begin(), wstrLocationName.end());

		_outFile.write(reinterpret_cast<char*>(&iLocationNameLength), sizeof(uint32));
		_outFile.write(strLocationName.c_str(), iLocationNameLength);

		// ���� Ÿ��
		uint32 iLocationType = static_cast<uint32>(pair.second.lock()->GetLocationType());
		_outFile.write(reinterpret_cast<char*>(&iLocationType), sizeof(uint32));

		// ����ƽ ������Ʈ �̸�
		const vector<shared_ptr<CStaticMeshComponent>>& vecStaticMeshComponents = pair.second.lock()->FindActorComponent<CStaticMeshComponent>(EComponentType::STATIC_MESH);
		wstring wstrComponentName = vecStaticMeshComponents.front()->GetComponentName();
		uint32 iComponentNameLength = static_cast<uint32>(wstrComponentName.length());

		string strComponentName = "";
		strComponentName.assign(wstrComponentName.begin(), wstrComponentName.end());

		_outFile.write(reinterpret_cast<char*>(&iComponentNameLength), sizeof(uint32));
		_outFile.write(strComponentName.c_str(), iComponentNameLength);

		// ���ؽ� ���̴� �̸�
		wstring wstrVertexShaderDescName = vecStaticMeshComponents.front()->GetVertexShaderDesc();
		uint32 iVertexShaderDescLength = static_cast<uint32>(wstrVertexShaderDescName.length());

		string strVertexShaderDescName = "";
		strVertexShaderDescName.assign(wstrVertexShaderDescName.begin(), wstrVertexShaderDescName.end());

		_outFile.write(reinterpret_cast<char*>(&iVertexShaderDescLength), sizeof(uint32));
		_outFile.write(strVertexShaderDescName.c_str(), iVertexShaderDescLength);

		// �ȼ� ���̴� �̸�
		wstring wstrPixelShaderDescName = vecStaticMeshComponents.front()->GetPixelShaderDesc();
		uint32 iPixelShaderDescNameLength = static_cast<uint32>(wstrPixelShaderDescName.length());

		string strPixelShaderDescName = "";
		strPixelShaderDescName.assign(wstrPixelShaderDescName.begin(), wstrPixelShaderDescName.end());

		_outFile.write(reinterpret_cast<char*>(&iPixelShaderDescNameLength), sizeof(uint32));
		_outFile.write(strPixelShaderDescName.c_str(), iPixelShaderDescNameLength);
	}
}

void Editor::CTabWindow::SaveNavigations(std::ofstream& _outFile)
{
	// ������, �߻� ������ �־�� �� ������̼� �޽ø�...
	// �÷��̾��� ������̼� ������Ʈ�� ������ �� �־�� �Ѵ�.
}

void Editor::CTabWindow::SaveCollectibleGroups(std::ofstream& _outFile)
{
	/*
	* ���� Ÿ��: ä�� �׷�		uint32
	* ä�� �׷��� ����			uint32
	* {
	*	ä�� �׷��� �̸�		wstring
	*	���� Ÿ��				uint32
	*	ä�� Ÿ��				uint32
	*	����ƽ ������Ʈ �̸�	wstring
	*	�� �̸�				wstring
	*	���ؽ� ���̴� �̸�		wstring
	*	�ȼ� ���̴� �̸�		wstring
	*	ä���� ����
	*	{
	*		ä���� �̸�
	*		�� ������Ʈ�� ��ġ
	*		�� ������Ʈ�� ������
	*	}
	* }
	*/

	/*
	const std::unordered_map<std::wstring, std::weak_ptr<CCollectibleGroup>>& umapCollectibleGroups = m_wpEditorLevel.lock()->GetCollectibleGroups();

	// ���� Ÿ��
	uint32 iInstancableActorType = static_cast<uint32>(EInstancableActorType::COLLECTIBLE_GROUP);
	_outFile.write(reinterpret_cast<char*>(&iInstancableActorType), sizeof(uint32));

	// ä�� �׷� ����
	uint32 iNumCollectibleGroups = static_cast<uint32>(umapCollectibleGroups.size());
	_outFile.write(reinterpret_cast<char*>(&iNumCollectibleGroups), sizeof(uint32));

	for (const auto& pair : umapCollectibleGroups)
	{
		// ä�� �׷� �̸�
		wstring wstrCollectibleGroupName = pair.second.lock()->GetActorName();
		uint32 iCollectibleGroupNameLength = static_cast<uint32>(wstrCollectibleGroupName.length());

		string strCollectibleGroupName = "";
		strCollectibleGroupName.assign(wstrCollectibleGroupName.begin(), wstrCollectibleGroupName.end());

		_outFile.write(reinterpret_cast<char*>(&iCollectibleGroupNameLength), sizeof(uint32));
		_outFile.write(strCollectibleGroupName.c_str(), iCollectibleGroupNameLength);

		// ���� Ÿ��(�б�, ȣ�� ��)
		uint32 iLocationType = static_cast<uint32>(pair.second.lock()->GetLocationType());
		_outFile.write(reinterpret_cast<char*>(&iLocationType), sizeof(uint32));

		// ä�� Ÿ��(��������, ��, ����, ��)
		uint32 iCollectibleType = static_cast<uint32>(pair.second.lock()->GetCollectibleType());
		_outFile.write(reinterpret_cast<char*>(&iCollectibleType), sizeof(uint32));

		// ����ƽ ������Ʈ �̸�
		const vector<shared_ptr<CStaticMeshComponent>>& vecStaticMeshComponents = pair.second.lock()->FindActorComponent<CStaticMeshComponent>(EComponentType::STATIC_MESH);
		wstring wstrComponentName = vecStaticMeshComponents.front()->GetComponentName();
		uint32 iComponentNameLength = static_cast<uint32>(wstrComponentName.length());

		string strComponentName = "";
		strComponentName.assign(wstrComponentName.begin(), wstrComponentName.end());

		_outFile.write(reinterpret_cast<char*>(&iComponentNameLength), sizeof(uint32));
		_outFile.write(strComponentName.c_str(), iComponentNameLength);

		// �� �̸�
		wstring wstrModelDescName = vecStaticMeshComponents.front()->GetModelDesc();
		uint32 iModelDescLength = static_cast<uint32>(wstrModelDescName.length());

		string strModelDescName = "";
		strModelDescName.assign(wstrModelDescName.begin(), wstrModelDescName.end());

		_outFile.write(reinterpret_cast<char*>(&iModelDescLength), sizeof(uint32));
		_outFile.write(strModelDescName.c_str(), iModelDescLength);

		// ���ؽ� ���̴� �̸�
		wstring wstrVertexShaderDescName = vecStaticMeshComponents.front()->GetVertexShaderDesc();
		uint32 iVertexShaderDescLength = static_cast<uint32>(wstrVertexShaderDescName.length());

		string strVertexShaderDescName = "";
		strVertexShaderDescName.assign(wstrVertexShaderDescName.begin(), wstrVertexShaderDescName.end());

		_outFile.write(reinterpret_cast<char*>(&iVertexShaderDescLength), sizeof(uint32));
		_outFile.write(strVertexShaderDescName.c_str(), iVertexShaderDescLength);

		// �ȼ� ���̴� �̸�
		wstring wstrPixelShaderDescName = vecStaticMeshComponents.front()->GetPixelShaderDesc();
		uint32 iPixelShaderDescNameLength = static_cast<uint32>(wstrPixelShaderDescName.length());

		string strPixelShaderDescName = "";
		strPixelShaderDescName.assign(wstrPixelShaderDescName.begin(), wstrPixelShaderDescName.end());

		_outFile.write(reinterpret_cast<char*>(&iPixelShaderDescNameLength), sizeof(uint32));
		_outFile.write(strPixelShaderDescName.c_str(), iPixelShaderDescNameLength);

		std::vector<std::weak_ptr<CCollectible>>& vecCollectibles = pair.second.lock()->GetCollectibles();
		
		// ä���� ����
		uint32 iNumCollectibles = static_cast<uint32>(vecCollectibles.size());
		_outFile.write(reinterpret_cast<char*>(&iNumCollectibles), sizeof(uint32));
		
		for (const auto& wpCollectible : vecCollectibles)
		{
			// ä�� �̸�
			wstring wstrCollectibleName = wpCollectible.lock()->GetActorName();
			uint32 iCollectibleNameLength = static_cast<uint32>(wstrCollectibleName.length());

			string strCollectibleName = "";
			strCollectibleName.assign(wstrCollectibleName.begin(), wstrCollectibleName.end());

			_outFile.write(reinterpret_cast<char*>(&iCollectibleNameLength), sizeof(uint32));
			_outFile.write(strCollectibleName.c_str(), iCollectibleNameLength);

			// �� ������Ʈ�� Ʈ������
			shared_ptr<CSphereComponent> spSphereComponent = wpCollectible.lock()->FindActorComponent<CSphereComponent>(L"SphereComponent");
			Vector3 vWorldPosition = spSphereComponent->GetComponentWorldPosition();
			_outFile.write(reinterpret_cast<char*>(&vWorldPosition), sizeof(Vector3));

			// ���� ������
			float fRadius = spSphereComponent->GetRadius();
			_outFile.write(reinterpret_cast<char*>(&fRadius), sizeof(float));
		}
	}*/
}

void Editor::CTabWindow::SaveConsoleGroups(std::ofstream& _outFile)
{
	/*
	* ���� Ÿ��: �ܼ� �׷�		uint32
	* �ܼ� �׷��� ����			uint32
	* {
	*	�ܼ� �׷��� �̸�		wstring
	*	�ܼ� Ÿ��				uint32
	*	����ƽ ������Ʈ �̸�	wstring
	*	���ؽ� ���̴� �̸�		wstring
	*	�ȼ� ���̴� �̸�		wstring
	* }
	*/

	/*
	const std::unordered_map<std::wstring, std::weak_ptr<CConsoleGroup>>& umapConsoleGroups = m_wpEditorLevel.lock()->GetConsoleGroups();

	// ���� Ÿ��
	uint32 iInstancableActorType = static_cast<uint32>(EInstancableActorType::CONSOLE_GROUP);
	_outFile.write(reinterpret_cast<char*>(&iInstancableActorType), sizeof(uint32));

	// �ܼ� �׷� ����
	uint32 iNumConsoleGroups = static_cast<uint32>(umapConsoleGroups.size());
	_outFile.write(reinterpret_cast<char*>(&iNumConsoleGroups), sizeof(uint32));

	for (const auto& pair : umapConsoleGroups)
	{
		// �ܼ� �׷� �̸�
		wstring wstrConsoleGroupName = pair.second.lock()->GetActorName();
		uint32 iConsoleGroupNameLength = static_cast<uint32>(wstrConsoleGroupName.length());

		string strConsoleGroupName = "";
		strConsoleGroupName.assign(wstrConsoleGroupName.begin(), wstrConsoleGroupName.end());

		_outFile.write(reinterpret_cast<char*>(&iConsoleGroupNameLength), sizeof(uint32));
		_outFile.write(strConsoleGroupName.c_str(), iConsoleGroupNameLength);

		// �ܼ� Ÿ��(�����۷���, ���� �ܼ�, ���� ī�޶�)
		uint32 iConsoleType = static_cast<uint32>(pair.second.lock()->GetConsoleType());
		_outFile.write(reinterpret_cast<char*>(&iConsoleType), sizeof(uint32));

		// ����ƽ ������Ʈ �̸�
		const vector<shared_ptr<CStaticMeshComponent>>& vecStaticMeshComponents = pair.second.lock()->FindActorComponent<CStaticMeshComponent>(EComponentType::STATIC_MESH);
		wstring wstrComponentName = vecStaticMeshComponents.front()->GetComponentName();
		uint32 iComponentNameLength = static_cast<uint32>(wstrComponentName.length());

		string strComponentName = "";
		strComponentName.assign(wstrComponentName.begin(), wstrComponentName.end());

		_outFile.write(reinterpret_cast<char*>(&iComponentNameLength), sizeof(uint32));
		_outFile.write(strComponentName.c_str(), iComponentNameLength);

		// �� �̸�
		wstring wstrModelDescName = vecStaticMeshComponents.front()->GetModelDesc();
		uint32 iModelDescLength = static_cast<uint32>(wstrModelDescName.length());

		string strModelDescName = "";
		strModelDescName.assign(wstrModelDescName.begin(), wstrModelDescName.end());

		_outFile.write(reinterpret_cast<char*>(&iModelDescLength), sizeof(uint32));
		_outFile.write(strModelDescName.c_str(), iModelDescLength);

		// ���ؽ� ���̴� �̸�
		wstring wstrVertexShaderDescName = vecStaticMeshComponents.front()->GetVertexShaderDesc();
		uint32 iVertexShaderDescLength = static_cast<uint32>(wstrVertexShaderDescName.length());

		string strVertexShaderDescName = "";
		strVertexShaderDescName.assign(wstrVertexShaderDescName.begin(), wstrVertexShaderDescName.end());

		_outFile.write(reinterpret_cast<char*>(&iVertexShaderDescLength), sizeof(uint32));
		_outFile.write(strVertexShaderDescName.c_str(), iVertexShaderDescLength);

		// �ȼ� ���̴� �̸�
		wstring wstrPixelShaderDescName = vecStaticMeshComponents.front()->GetPixelShaderDesc();
		uint32 iPixelShaderDescNameLength = static_cast<uint32>(wstrPixelShaderDescName.length());

		string strPixelShaderDescName = "";
		strPixelShaderDescName.assign(wstrPixelShaderDescName.begin(), wstrPixelShaderDescName.end());

		_outFile.write(reinterpret_cast<char*>(&iPixelShaderDescNameLength), sizeof(uint32));
		_outFile.write(strPixelShaderDescName.c_str(), iPixelShaderDescNameLength);

		std::vector<std::weak_ptr<CConsole>>& vecConsoles = pair.second.lock()->GetConsoles();

		// �ܼ��� ����
		uint32 iNumConsoles = static_cast<uint32>(vecConsoles.size());
		_outFile.write(reinterpret_cast<char*>(&iNumConsoles), sizeof(uint32));

		for (const auto& wpConsole : vecConsoles)
		{
			// �ܼ� �̸�
			wstring wstrConsoleName = wpConsole.lock()->GetActorName();
			uint32 iConsoleNameLength = static_cast<uint32>(wstrConsoleName.length());

			string strConsoleName = "";
			strConsoleName.assign(wstrConsoleName.begin(), wstrConsoleName.end());

			_outFile.write(reinterpret_cast<char*>(&iConsoleNameLength), sizeof(uint32));
			_outFile.write(strConsoleName.c_str(), iConsoleNameLength);

			// �� ������Ʈ�� Ʈ������
			shared_ptr<CSphereComponent> spSphereComponent = wpConsole.lock()->FindActorComponent<CSphereComponent>(L"SphereComponent");
			Vector3 vWorldPosition = spSphereComponent->GetComponentWorldPosition();
			_outFile.write(reinterpret_cast<char*>(&vWorldPosition), sizeof(Vector3));

			// ���� ������
			float fRadius = spSphereComponent->GetRadius();
			_outFile.write(reinterpret_cast<char*>(&fRadius), sizeof(float));
		}
	}*/
}

void Editor::CTabWindow::SaveWildAnimal(std::ofstream& _outFile)
{
	/*
	* �߻� ���� Ÿ��			uint32
	* �߻� ������ ���� ��		uint32
	* {
	*		�� ��ġ				int32
	*		���� ��ġ			Vector3
	* }
	*/

	{
		const std::unordered_map<std::wstring, std::weak_ptr<CBear>>& umapBears = m_wpEditorLevel.lock()->GetBears();

		uint32 iBearType = static_cast<uint32>(EWildAnimalType::BEAR);
		_outFile.write(reinterpret_cast<char*>(&iBearType), sizeof(uint32));

		uint32 iNumBears = static_cast<uint32>(umapBears.size());
		_outFile.write(reinterpret_cast<char*>(&iNumBears), sizeof(uint32));

		for (const auto& pair : umapBears)
		{
			// �� ��ġ
			int32 iCellIndex = pair.second.lock()->GetSpawnCellIndex();
			_outFile.write(reinterpret_cast<char*>(&iCellIndex), sizeof(int32));

			// ���� ��ġ
			Vector3 vSpawnPosition = pair.second.lock()->GetSpawnPosition();
			_outFile.write(reinterpret_cast<char*>(&vSpawnPosition), sizeof(Vector3));
		}
	}
	
	{
		const std::unordered_map<std::wstring, std::weak_ptr<CBoar>>& umapBoars = m_wpEditorLevel.lock()->GetBoars();

		uint32 iBoarType = static_cast<uint32>(EWildAnimalType::BOAR);
		_outFile.write(reinterpret_cast<char*>(&iBoarType), sizeof(uint32));

		uint32 iNumBoars = static_cast<uint32>(umapBoars.size());
		_outFile.write(reinterpret_cast<char*>(&iNumBoars), sizeof(uint32));

		for (const auto& pair : umapBoars)
		{
			// �� ��ġ
			int32 iCellIndex = pair.second.lock()->GetSpawnCellIndex();
			_outFile.write(reinterpret_cast<char*>(&iCellIndex), sizeof(int32));

			// ���� ��ġ
			Vector3 vSpawnPosition = pair.second.lock()->GetSpawnPosition();
			_outFile.write(reinterpret_cast<char*>(&vSpawnPosition), sizeof(Vector3));
		}
	}

	{
		const std::unordered_map<std::wstring, std::weak_ptr<CChicken>>& umapChickens = m_wpEditorLevel.lock()->GetChickens();

		uint32 iChickenType = static_cast<uint32>(EWildAnimalType::CHICKEN);
		_outFile.write(reinterpret_cast<char*>(&iChickenType), sizeof(uint32));

		uint32 iNumChickens = static_cast<uint32>(umapChickens.size());
		_outFile.write(reinterpret_cast<char*>(&iNumChickens), sizeof(uint32));

		for (const auto& pair : umapChickens)
		{
			// �� ��ġ
			int32 iCellIndex = pair.second.lock()->GetSpawnCellIndex();
			_outFile.write(reinterpret_cast<char*>(&iCellIndex), sizeof(int32));

			// ���� ��ġ
			Vector3 vSpawnPosition = pair.second.lock()->GetSpawnPosition();
			_outFile.write(reinterpret_cast<char*>(&vSpawnPosition), sizeof(Vector3));
		}
	}

	{
		const std::unordered_map<std::wstring, std::weak_ptr<CDog>>& umapDogs = m_wpEditorLevel.lock()->GetDogs();

		uint32 iDogType = static_cast<uint32>(EWildAnimalType::DOG);
		_outFile.write(reinterpret_cast<char*>(&iDogType), sizeof(uint32));

		uint32 iNumDogs = static_cast<uint32>(umapDogs.size());
		_outFile.write(reinterpret_cast<char*>(&iNumDogs), sizeof(uint32));

		for (const auto& pair : umapDogs)
		{
			// �� ��ġ
			int32 iCellIndex = pair.second.lock()->GetSpawnCellIndex();
			_outFile.write(reinterpret_cast<char*>(&iCellIndex), sizeof(int32));

			// ���� ��ġ
			Vector3 vSpawnPosition = pair.second.lock()->GetSpawnPosition();
			_outFile.write(reinterpret_cast<char*>(&vSpawnPosition), sizeof(Vector3));
		}
	}

	{
		const std::unordered_map<std::wstring, std::weak_ptr<CWolf>>& umapWolfs = m_wpEditorLevel.lock()->GetWolfs();

		uint32 iWolfType = static_cast<uint32>(EWildAnimalType::WOLF);
		_outFile.write(reinterpret_cast<char*>(&iWolfType), sizeof(uint32));

		uint32 iNumWolfs = static_cast<uint32>(umapWolfs.size());
		_outFile.write(reinterpret_cast<char*>(&iNumWolfs), sizeof(uint32));

		for (const auto& pair : umapWolfs)
		{
			// �� ��ġ
			int32 iCellIndex = pair.second.lock()->GetSpawnCellIndex();
			_outFile.write(reinterpret_cast<char*>(&iCellIndex), sizeof(int32));

			// ���� ��ġ
			Vector3 vSpawnPosition = pair.second.lock()->GetSpawnPosition();
			_outFile.write(reinterpret_cast<char*>(&vSpawnPosition), sizeof(Vector3));
		}
	}
}



void Editor::CTabWindow::TickLoadButton()
{
	ImGui::SeparatorText("Load");

	ImGui::InputTextWithHint("Load File", "Lumia", m_chLoadFileName, IM_ARRAYSIZE(m_chLoadFileName));

	if (ImGui::Button("Load", ImVec2(-FLT_MIN, 0.0f)))
	{
		string strFileName(m_chLoadFileName);
		string strPath = m_strFilePath + "/" + strFileName + ".dat";

		std::ifstream inFile;
		inFile.open(strPath.c_str(), ios_base::in | ios_base::binary);

		ZeroMemory(m_chLoadFileName, MAX_PATH);

		// ������ ������ ���� ���
		if (!inFile.is_open()) { return; }

		// LoadLocations(inFile);
		// LoadNavigations(inFile);
		// LoadCollectibleGroups(inFile);
		// LoadConsoleGroups(inFile);
		LoadWildAnimal(inFile);
	}
}

void Editor::CTabWindow::LoadLocations(std::ifstream& _inFile)
{
	/*
	* ���� Ÿ��: ����			uint32
	* ���� ����					uint32
	* {
	*	���� �̸�				wstring
	*	���� Ÿ��				uint32
	*	����ƽ ������Ʈ �̸�	wstring
	*	���ؽ� ���̴� �̸�		wstring
	*	�ȼ� ���̴� �̸�		wstring
	* }
	*/

	/*
	// ���� Ÿ��
	uint32 iInstancableActorType = 0;
	_inFile.read(reinterpret_cast<char*>(&iInstancableActorType), sizeof(uint32));

	// ���� ����
	uint32 iNumLocations = 0;
	_inFile.read(reinterpret_cast<char*>(&iNumLocations), sizeof(uint32));

	for (uint32 iIndex = 0; iIndex < iNumLocations; ++iIndex)
	{
		// ���� �̸�
		uint32 iLocationNameLength = 0;
		_inFile.read(reinterpret_cast<char*>(&iLocationNameLength), sizeof(uint32));

		string strLocationName = "";
		strLocationName.reserve(iLocationNameLength);
		strLocationName.resize(iLocationNameLength);
		_inFile.read(strLocationName.data(), iLocationNameLength);

		wstring wstrLocationName = L"";
		wstrLocationName.assign(strLocationName.begin(), strLocationName.end());

		// ���� Ÿ��
		uint32 iLocationType = 0;
		_inFile.read(reinterpret_cast<char*>(&iLocationType), sizeof(uint32));

		// ����ƽ ������Ʈ �̸�
		uint32 iComponentNameLength = 0;
		_inFile.read(reinterpret_cast<char*>(&iComponentNameLength), sizeof(uint32));

		string strComponentName = "";
		strComponentName.reserve(iComponentNameLength);
		strComponentName.resize(iComponentNameLength);
		_inFile.read(strComponentName.data(), iComponentNameLength);

		wstring wstrComponentName = L"";
		wstrComponentName.assign(strComponentName.begin(), strComponentName.end());

		// ���ؽ� ���̴� �̸�
		uint32 iVertexShaderDescLength = 0;
		_inFile.read(reinterpret_cast<char*>(&iVertexShaderDescLength), sizeof(uint32));

		string strVertexShaderDescName = "";
		strVertexShaderDescName.reserve(iVertexShaderDescLength);
		strVertexShaderDescName.resize(iVertexShaderDescLength);
		_inFile.read(strVertexShaderDescName.data(), iVertexShaderDescLength);

		wstring wstrVertexShaderDescName = L"";
		wstrVertexShaderDescName.assign(strVertexShaderDescName.begin(), strVertexShaderDescName.end());

		// �ȼ� ���̴� �̸�
		uint32 iPixelShaderDescNameLength = 0;
		_inFile.read(reinterpret_cast<char*>(&iPixelShaderDescNameLength), sizeof(uint32));

		string strPixelShaderDescName = "";
		strPixelShaderDescName.reserve(iPixelShaderDescNameLength);
		strPixelShaderDescName.resize(iPixelShaderDescNameLength);
		_inFile.read(strPixelShaderDescName.data(), iPixelShaderDescNameLength);

		wstring wstrPixelShaderDescName = L"";
		wstrPixelShaderDescName.assign(strPixelShaderDescName.begin(), strPixelShaderDescName.end());



		// ������ �����մϴ�.
		shared_ptr<CLocation> spLocation = m_wpEditorLevel.lock()->CreateActor<CLocation>(wstrLocationName);
		spLocation->SetLocationType(static_cast<ELocationType>(iLocationType));

		m_wpEditorLevel.lock()->AddToLocations(wstrLocationName, spLocation);

		// ������ �ʱ�ȭ�մϴ�.
		spLocation->PreInitialize();
		spLocation->Initialize();
		spLocation->PostInitialize();
		spLocation->BeginPlay();
	}*/
}

void Editor::CTabWindow::LoadNavigations(std::ifstream& _inFile)
{
}

void Editor::CTabWindow::LoadCollectibleGroups(std::ifstream& _inFile)
{
	/*
	* ���� Ÿ��: ä�� �׷�		uint32
	* ä�� �׷��� ����			uint32
	* {
	*	ä�� �׷��� �̸�		wstring
	*	���� Ÿ��				uint32
	*	ä�� Ÿ��				uint32
	*	����ƽ ������Ʈ �̸�	wstring
	*	�� �̸�				wstring
	*	���ؽ� ���̴� �̸�		wstring
	*	�ȼ� ���̴� �̸�		wstring
	* }
	*/

	/*
	// ���� Ÿ��
	uint32 iInstancableActorType = 0;
	_inFile.read(reinterpret_cast<char*>(&iInstancableActorType), sizeof(uint32));
	
	// ä�� �׷� ����
	uint32 iNumCollectibleGroups = 0;
	_inFile.read(reinterpret_cast<char*>(&iNumCollectibleGroups), sizeof(uint32));

	for (uint32 iIndex = 0; iIndex < iNumCollectibleGroups; ++iIndex)
	{
		// ä�� �׷� �̸�
		uint32 iCollectibleGroupNameLength = 0;
		_inFile.read(reinterpret_cast<char*>(&iCollectibleGroupNameLength), sizeof(uint32));

		string strCollectibleGroupName = "";
		strCollectibleGroupName.reserve(iCollectibleGroupNameLength);
		strCollectibleGroupName.resize(iCollectibleGroupNameLength);
		_inFile.read(strCollectibleGroupName.data(), iCollectibleGroupNameLength);

		wstring wstrCollectibleGroupName = L"";
		wstrCollectibleGroupName.assign(strCollectibleGroupName.begin(), strCollectibleGroupName.end());

		// ���� Ÿ��(�б�, ȣ�� ��)
		uint32 iLocationType = 0;
		_inFile.read(reinterpret_cast<char*>(&iLocationType), sizeof(uint32));

		// ä�� Ÿ��(��������, ��, ����, ��)
		uint32 iCollectibleType = 0;
		_inFile.read(reinterpret_cast<char*>(&iCollectibleType), sizeof(uint32));

		// ����ƽ ������Ʈ �̸�
		uint32 iComponentNameLength = 0;
		_inFile.read(reinterpret_cast<char*>(&iComponentNameLength), sizeof(uint32));

		string strComponentName = "";
		strComponentName.reserve(iComponentNameLength);
		strComponentName.resize(iComponentNameLength);
		_inFile.read(strComponentName.data(), iComponentNameLength);

		wstring wstrComponentName = L"";
		wstrComponentName.assign(strComponentName.begin(), strComponentName.end());

		// �� �̸�
		uint32 iModelDescLength = 0;
		_inFile.read(reinterpret_cast<char*>(&iModelDescLength), sizeof(uint32));

		string strModelDescName = "";
		strModelDescName.reserve(iModelDescLength);
		strModelDescName.resize(iModelDescLength);
		_inFile.read(strModelDescName.data(), iModelDescLength);

		wstring wstrModelDescName = L"";
		wstrModelDescName.assign(strModelDescName.begin(), strModelDescName.end());

		// ���ؽ� ���̴� �̸�
		uint32 iVertexShaderDescLength = 0;
		_inFile.read(reinterpret_cast<char*>(&iVertexShaderDescLength), sizeof(uint32));

		string strVertexShaderDescName = "";
		strVertexShaderDescName.reserve(iVertexShaderDescLength);
		strVertexShaderDescName.resize(iVertexShaderDescLength);
		_inFile.read(strVertexShaderDescName.data(), iVertexShaderDescLength);

		wstring wstrVertexShaderDescName = L"";
		wstrVertexShaderDescName.assign(strVertexShaderDescName.begin(), strVertexShaderDescName.end());

		// �ȼ� ���̴� �̸�
		uint32 iPixelShaderDescNameLength = 0;
		_inFile.read(reinterpret_cast<char*>(&iPixelShaderDescNameLength), sizeof(uint32));

		string strPixelShaderDescName = "";
		strPixelShaderDescName.reserve(iPixelShaderDescNameLength);
		strPixelShaderDescName.resize(iPixelShaderDescNameLength);
		_inFile.read(strPixelShaderDescName.data(), iPixelShaderDescNameLength);

		wstring wstrPixelShaderDescName = L"";
		wstrPixelShaderDescName.assign(strPixelShaderDescName.begin(), strPixelShaderDescName.end());

		// ä���� ����
		uint32 iNumCollectibles = 0;
		_inFile.read(reinterpret_cast<char*>(&iNumCollectibles), sizeof(uint32));


		// ä�� �׷��� �����մϴ�.
		shared_ptr<CCollectibleGroup> spCollectibleGroup = m_wpEditorLevel.lock()->CreateActor<CCollectibleGroup>(wstrCollectibleGroupName);
		spCollectibleGroup->SetLocationType(static_cast<ELocationType>(iLocationType));
		spCollectibleGroup->SetCollectibleType(static_cast<ECollectibleType>(iCollectibleType));

		m_wpEditorLevel.lock()->AddToCollectibleGroups(wstrCollectibleGroupName, spCollectibleGroup);

		// ä�� �׷��� �ʱ�ȭ�մϴ�.
		spCollectibleGroup->PreInitialize();
		spCollectibleGroup->Initialize();
		spCollectibleGroup->PostInitialize();
		spCollectibleGroup->BeginPlay();

		for (uint32 jIndex = 0; jIndex < iNumCollectibles; ++jIndex)
		{
			// ä�� �̸�
			uint32 iCollectibleNameLength = 0;
			_inFile.read(reinterpret_cast<char*>(&iCollectibleNameLength), sizeof(uint32));

			string strCollectibleName = "";
			strCollectibleName.reserve(iCollectibleNameLength);
			strCollectibleName.resize(iCollectibleNameLength);
			_inFile.read(strCollectibleName.data(), iCollectibleNameLength);

			wstring wstrCollectibleName = L"";
			wstrCollectibleName.assign(strCollectibleName.begin(), strCollectibleName.end());

			// �� ������Ʈ�� Ʈ������
			Vector3 vLocalPosition = Vector3::Zero;
			_inFile.read(reinterpret_cast<char*>(&vLocalPosition), sizeof(Vector3));

			// ���� ������
			float fRadius = 0.0f;
			_inFile.read(reinterpret_cast<char*>(&fRadius), sizeof(float));

			// ä���� �����մϴ�.
			shared_ptr<CCollectible> spCollectible = m_wpEditorLevel.lock()->CreateActor<CCollectible>(wstrCollectibleName);
			spCollectible->SetLocationType(static_cast<ELocationType>(iLocationType));
			spCollectible->SetCollectibleType(static_cast<ECollectibleType>(iCollectibleType));

			spCollectibleGroup->AddCollectible(spCollectible);
			spCollectible->SetOwnerActor(spCollectibleGroup);

			// ä���� �ʱ�ȭ�մϴ�.
			spCollectible->PreInitialize();
			spCollectible->Initialize();

			shared_ptr<CSphereComponent> spSphereComponent = spCollectible->FindActorComponent<CSphereComponent>(L"SphereComponent");
			spSphereComponent->SetComponentLocalPosition(vLocalPosition);
			spSphereComponent->SetRadius(fRadius);

			spCollectible->PostInitialize();
			spCollectible->BeginPlay();
		}
	}*/
}

void Editor::CTabWindow::LoadConsoleGroups(std::ifstream& _inFile)
{
	/*
	* ���� Ÿ��: �ܼ� �׷�		uint32
	* �ܼ� �׷��� ����			uint32
	* {
	*	�ܼ� �׷��� �̸�		wstring
	*	�ܼ� Ÿ��				uint32
	*	����ƽ ������Ʈ �̸�	wstring
	*	���ؽ� ���̴� �̸�		wstring
	*	�ȼ� ���̴� �̸�		wstring
	* }
	*/

	/*
	// ���� Ÿ��
	uint32 iInstancableActorType = 0;
	_inFile.read(reinterpret_cast<char*>(&iInstancableActorType), sizeof(uint32));

	// �ܼ� �׷� ����
	uint32 iNumConsoleGroups = 0;
	_inFile.read(reinterpret_cast<char*>(&iNumConsoleGroups), sizeof(uint32));

	for (uint32 iIndex = 0; iIndex < iNumConsoleGroups; ++iIndex)
	{
		// �ܼ� �׷� �̸�
		uint32 iConsoleGroupNameLength = 0;
		_inFile.read(reinterpret_cast<char*>(&iConsoleGroupNameLength), sizeof(uint32));

		string strConsoleGroupName = "";
		strConsoleGroupName.reserve(iConsoleGroupNameLength);
		strConsoleGroupName.resize(iConsoleGroupNameLength);
		_inFile.read(strConsoleGroupName.data(), iConsoleGroupNameLength);

		wstring wstrConsoleGroupName = L"";
		wstrConsoleGroupName.assign(strConsoleGroupName.begin(), strConsoleGroupName.end());

		// �ܼ� Ÿ��(�����۷���, ���� �ܼ�, ���� ī�޶�)
		uint32 iConsoleType = 0;
		_inFile.read(reinterpret_cast<char*>(&iConsoleType), sizeof(uint32));

		// ����ƽ ������Ʈ �̸�
		uint32 iComponentNameLength = 0;
		_inFile.read(reinterpret_cast<char*>(&iComponentNameLength), sizeof(uint32));

		string strComponentName = "";
		strComponentName.reserve(iComponentNameLength);
		strComponentName.resize(iComponentNameLength);
		_inFile.read(strComponentName.data(), iComponentNameLength);

		wstring wstrComponentName = L"";
		wstrComponentName.assign(strComponentName.begin(), strComponentName.end());

		// �� �̸�
		uint32 iModelDescLength = 0;
		_inFile.read(reinterpret_cast<char*>(&iModelDescLength), sizeof(uint32));

		string strModelDescName = "";
		strModelDescName.reserve(iModelDescLength);
		strModelDescName.resize(iModelDescLength);
		_inFile.read(strModelDescName.data(), iModelDescLength);

		wstring wstrModelDescName = L"";
		wstrModelDescName.assign(strModelDescName.begin(), strModelDescName.end());

		// ���ؽ� ���̴� �̸�
		uint32 iVertexShaderDescLength = 0;
		_inFile.read(reinterpret_cast<char*>(&iVertexShaderDescLength), sizeof(uint32));

		string strVertexShaderDescName = "";
		strVertexShaderDescName.reserve(iVertexShaderDescLength);
		strVertexShaderDescName.resize(iVertexShaderDescLength);
		_inFile.read(strVertexShaderDescName.data(), iVertexShaderDescLength);

		wstring wstrVertexShaderDescName = L"";
		wstrVertexShaderDescName.assign(strVertexShaderDescName.begin(), strVertexShaderDescName.end());

		// �ȼ� ���̴� �̸�
		uint32 iPixelShaderDescNameLength = 0;
		_inFile.read(reinterpret_cast<char*>(&iPixelShaderDescNameLength), sizeof(uint32));

		string strPixelShaderDescName = "";
		strPixelShaderDescName.reserve(iPixelShaderDescNameLength);
		strPixelShaderDescName.resize(iPixelShaderDescNameLength);
		_inFile.read(strPixelShaderDescName.data(), iPixelShaderDescNameLength);

		wstring wstrPixelShaderDescName = L"";
		wstrPixelShaderDescName.assign(strPixelShaderDescName.begin(), strPixelShaderDescName.end());

		// �ܼ��� ����
		uint32 iNumConsoles = 0;
		_inFile.read(reinterpret_cast<char*>(&iNumConsoles), sizeof(uint32));

		// �ܼ� �׷��� �����մϴ�.
		shared_ptr<CConsoleGroup> spConsoleGroup = m_wpEditorLevel.lock()->CreateActor<CConsoleGroup>(wstrConsoleGroupName);
		spConsoleGroup->SetConsoleType(static_cast<EConsoleType>(iConsoleType));

		m_wpEditorLevel.lock()->AddToConsoleGroups(wstrConsoleGroupName, spConsoleGroup);

		// �ܼ� �׷��� �ʱ�ȭ�մϴ�.
		spConsoleGroup->PreInitialize();
		spConsoleGroup->Initialize();
		spConsoleGroup->PostInitialize();
		spConsoleGroup->BeginPlay();

		for (uint32 jIndex = 0; jIndex < iNumConsoles; ++jIndex)
		{
			// �ܼ� �̸�
			uint32 iConsoleNameLength = 0;
			_inFile.read(reinterpret_cast<char*>(&iConsoleNameLength), sizeof(uint32));

			string strConsoleName = "";
			strConsoleName.reserve(iConsoleNameLength);
			strConsoleName.resize(iConsoleNameLength);
			_inFile.read(strConsoleName.data(), iConsoleNameLength);

			wstring wstrConsoleName = L"";
			wstrConsoleName.assign(strConsoleName.begin(), strConsoleName.end());

			// �� ������Ʈ�� Ʈ������
			Vector3 vLocalPosition = Vector3::Zero;
			_inFile.read(reinterpret_cast<char*>(&vLocalPosition), sizeof(Vector3));

			// ���� ������
			float fRadius = 0.0f;
			_inFile.read(reinterpret_cast<char*>(&fRadius), sizeof(float));

			// �ܼ��� �����մϴ�.
			shared_ptr<CConsole> spConsole = m_wpEditorLevel.lock()->CreateActor<CConsole>(wstrConsoleName);
			spConsole->SetConsoleType(static_cast<EConsoleType>(iConsoleType));

			spConsoleGroup->AddConsole(spConsole);
			spConsole->SetOwnerActor(spConsoleGroup);

			// �ܼ��� �ʱ�ȭ�մϴ�.
			spConsole->PreInitialize();
			spConsole->Initialize();

			shared_ptr<CSphereComponent> spSphereComponent = spConsole->FindActorComponent<CSphereComponent>(L"SphereComponent");
			spSphereComponent->SetComponentLocalPosition(vLocalPosition);
			spSphereComponent->SetRadius(fRadius);

			spConsole->PostInitialize();
			spConsole->BeginPlay();
		}
	}*/
}

void Editor::CTabWindow::LoadWildAnimal(std::ifstream& _inFile)
{
	/*
	* �߻� ���� Ÿ��			uint32
	* �߻� ������ ���� ��		uint32
	* {
	*		�� ��ġ				int32
	*		���� ��ġ			Vector3
	* }
	*/

	{
		uint32 iBearType = 0;
		_inFile.read(reinterpret_cast<char*>(&iBearType), sizeof(uint32));

		uint32 iNumBears = 0;
		_inFile.read(reinterpret_cast<char*>(&iNumBears), sizeof(uint32));

		for (uint32 iIndex = 0; iIndex < iNumBears; ++iIndex)
		{
			// �� ��ġ
			int32 iCellIndex = 0;
			_inFile.read(reinterpret_cast<char*>(&iCellIndex), sizeof(int32));

			// ���� ��ġ
			Vector3 vSpawnPosition = Vector3::Zero;
			_inFile.read(reinterpret_cast<char*>(&vSpawnPosition), sizeof(Vector3));

			wstring wstrName = L"Bear" + to_wstring(iIndex);
			shared_ptr<CBear> spBear = m_wpEditorLevel.lock()->CreateActor<CBear>(wstrName);

			m_wpEditorLevel.lock()->AddWildAnimal(EWildAnimalType::BEAR, wstrName, spBear);

			spBear->SetSpawnCellIndex(iCellIndex);
			spBear->SetSpawnPosition(vSpawnPosition);

			spBear->PreInitialize();
			spBear->Initialize();
			spBear->PostInitialize();
			spBear->BeginPlay();
		}
	}

	{
		uint32 iBoarType = 0;
		_inFile.read(reinterpret_cast<char*>(&iBoarType), sizeof(uint32));

		uint32 iNumBoars = 0;
		_inFile.read(reinterpret_cast<char*>(&iNumBoars), sizeof(uint32));

		for (uint32 iIndex = 0; iIndex < iNumBoars; ++iIndex)
		{
			// �� ��ġ
			int32 iCellIndex = 0;
			_inFile.read(reinterpret_cast<char*>(&iCellIndex), sizeof(int32));

			// ���� ��ġ
			Vector3 vSpawnPosition = Vector3::Zero;
			_inFile.read(reinterpret_cast<char*>(&vSpawnPosition), sizeof(Vector3));

			wstring wstrName = L"Boar" + to_wstring(iIndex);
			shared_ptr<CBoar> spBoar = m_wpEditorLevel.lock()->CreateActor<CBoar>(wstrName);

			m_wpEditorLevel.lock()->AddWildAnimal(EWildAnimalType::BOAR, wstrName, spBoar);

			spBoar->SetSpawnCellIndex(iCellIndex);
			spBoar->SetSpawnPosition(vSpawnPosition);

			spBoar->PreInitialize();
			spBoar->Initialize();
			spBoar->PostInitialize();
			spBoar->BeginPlay();
		}
	}

	{
		uint32 iChickenType = 0;
		_inFile.read(reinterpret_cast<char*>(&iChickenType), sizeof(uint32));

		uint32 iNumChickens = 0;
		_inFile.read(reinterpret_cast<char*>(&iNumChickens), sizeof(uint32));

		for (uint32 iIndex = 0; iIndex < iNumChickens; ++iIndex)
		{
			// �� ��ġ
			int32 iCellIndex = 0;
			_inFile.read(reinterpret_cast<char*>(&iCellIndex), sizeof(int32));

			// ���� ��ġ
			Vector3 vSpawnPosition = Vector3::Zero;
			_inFile.read(reinterpret_cast<char*>(&vSpawnPosition), sizeof(Vector3));

			wstring wstrName = L"Chicken" + to_wstring(iIndex);
			shared_ptr<CChicken> spChicken = m_wpEditorLevel.lock()->CreateActor<CChicken>(wstrName);

			m_wpEditorLevel.lock()->AddWildAnimal(EWildAnimalType::CHICKEN, wstrName, spChicken);

			spChicken->SetSpawnCellIndex(iCellIndex);
			spChicken->SetSpawnPosition(vSpawnPosition);

			spChicken->PreInitialize();
			spChicken->Initialize();
			spChicken->PostInitialize();
			spChicken->BeginPlay();
		}
	}

	{
		uint32 iDogType = 0;
		_inFile.read(reinterpret_cast<char*>(&iDogType), sizeof(uint32));

		uint32 iNumDogs = 0;
		_inFile.read(reinterpret_cast<char*>(&iNumDogs), sizeof(uint32));

		for (uint32 iIndex = 0; iIndex < iNumDogs; ++iIndex)
		{
			// �� ��ġ
			int32 iCellIndex = 0;
			_inFile.read(reinterpret_cast<char*>(&iCellIndex), sizeof(int32));

			// ���� ��ġ
			Vector3 vSpawnPosition = Vector3::Zero;
			_inFile.read(reinterpret_cast<char*>(&vSpawnPosition), sizeof(Vector3));

			wstring wstrName = L"Dog" + to_wstring(iIndex);
			shared_ptr<CDog> spDog = m_wpEditorLevel.lock()->CreateActor<CDog>(wstrName);

			m_wpEditorLevel.lock()->AddWildAnimal(EWildAnimalType::DOG, wstrName, spDog);

			spDog->SetSpawnCellIndex(iCellIndex);
			spDog->SetSpawnPosition(vSpawnPosition);

			spDog->PreInitialize();
			spDog->Initialize();
			spDog->PostInitialize();
			spDog->BeginPlay();
		}
	}

	{
		uint32 iWolfType = 0;
		_inFile.read(reinterpret_cast<char*>(&iWolfType), sizeof(uint32));

		uint32 iNumWolfs = 0;
		_inFile.read(reinterpret_cast<char*>(&iNumWolfs), sizeof(uint32));

		for (uint32 iIndex = 0; iIndex < iNumWolfs; ++iIndex)
		{
			// �� ��ġ
			int32 iCellIndex = 0;
			_inFile.read(reinterpret_cast<char*>(&iCellIndex), sizeof(int32));

			// ���� ��ġ
			Vector3 vSpawnPosition = Vector3::Zero;
			_inFile.read(reinterpret_cast<char*>(&vSpawnPosition), sizeof(Vector3));

			wstring wstrName = L"Wolf" + to_wstring(iIndex);
			shared_ptr<CWolf> spWolf = m_wpEditorLevel.lock()->CreateActor<CWolf>(wstrName);

			m_wpEditorLevel.lock()->AddWildAnimal(EWildAnimalType::WOLF, wstrName, spWolf);

			spWolf->SetSpawnCellIndex(iCellIndex);
			spWolf->SetSpawnPosition(vSpawnPosition);

			spWolf->PreInitialize();
			spWolf->Initialize();
			spWolf->PostInitialize();
			spWolf->BeginPlay();
		}
	}
}
