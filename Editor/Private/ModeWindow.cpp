// default
#include "pch.h"
#include "ModeWindow.h"

// manager
#include "IMGUIManager.h"
#include "InputManager.h"

// handler
#include "ShaderHandler.h"
#include "ModelHandler.h"
#include "NavHandler.h"

// engine
#include "World.h"
#include "Cell.h"

// editor
#include "EditorLevel.h"
#include "EditorCamera.h"

// wild animal
#include "Bear.h"
#include "Boar.h"
#include "Chicken.h"
#include "Dog.h"
#include "Wolf.h"

// boundary
#include "Boundary.h"

std::shared_ptr<CModeWindow> Editor::CModeWindow::Create(const std::shared_ptr<CIMGUIManager>& _spIMGUIManager)
{
	const shared_ptr<CModeWindow> spWindow = make_shared<CModeWindow>();
	ENSURE(spWindow->Initialize(_spIMGUIManager));
	return spWindow;
}

HRESULT Editor::CModeWindow::Initialize(const std::shared_ptr<CIMGUIManager>& _spIMGUIManager)
{
	m_wpEditorLevel = dynamic_pointer_cast<CEditorLevel>(CWorld::GetInstance()->GetCurLevel());

	m_wpIMGUIManager = _spIMGUIManager;
	m_wpInputManager = _spIMGUIManager->GetInputManager();
	m_wpEditorCamera = _spIMGUIManager->GetEditorCamera();

	m_wpShaderHandler = CShaderHandler::GetInstance();
	m_wpModelHandler = CModelHandler::GetInstance();
	m_wpNavHandler = CNavHandler::GetInstance();
	return S_OK;
}

int32 Editor::CModeWindow::Tick()
{
	ImGui::Begin("ModeWindow");
	if (ImGui::CollapsingHeader("Mode"))
	{
		TickSeparaterMode();
	}
	ImGui::End();
	return 0;
}

void Editor::CModeWindow::Release()
{
}

void Editor::CModeWindow::TickSeparaterMode()
{
	TickWildAnimalTab();
	CreateWildAnimal();
}

void Editor::CModeWindow::TickWildAnimalTab()
{
	// 야생 동물
	if (ImGui::TreeNode("Wild Animal"))
	{
		// 야생 동물 타입
		const char* szPreviewWildAnimalName = m_arrWildAnimalNames[m_iChangableWildAnimalType];
		if (ImGui::BeginCombo("Wild Animal Type", szPreviewWildAnimalName))
		{
			for (uint32 iIndex = 0; iIndex < m_arrWildAnimalNames.size(); ++iIndex)
			{
				const bool bSelected = (m_iChangableWildAnimalType == iIndex);
				if (ImGui::Selectable(m_arrWildAnimalNames[iIndex], bSelected))
				{
					m_iChangableWildAnimalType = iIndex;
				}
				if (bSelected) { ImGui::SetItemDefaultFocus(); }
			}
			ImGui::EndCombo();
		}

		if (ImGui::Button("Wild Animal On", ImVec2(-FLT_MIN, 0.0f)))
		{
			if (m_iChangableWildAnimalType == m_arrWildAnimalNames.size() - 1) { ImGui::TreePop(); ImGui::Spacing(); return; }

			m_eEditorCreateMode = EEditorCreateMode::WILD_ANIMAL;
		}

		if (ImGui::Button("Wild Animal Off", ImVec2(-FLT_MIN, 0.0f)))
		{
			m_eEditorCreateMode = EEditorCreateMode::NONE;
		}
		ImGui::TreePop();

		string strCellIndex = to_string(m_iCellIndex);
		ImGui::Text(strCellIndex.c_str());
	}

	ImGui::SeparatorText("Save/Load Chicken");
	if (ImGui::Button("Save Chicken")) { SaveChicken(); }
	if (ImGui::Button("Load Chicken")) { LoadChicken(); }

	ImGui::SeparatorText("Save/Load Bear");
	if (ImGui::Button("Save Bear")) { SaveBear(); }
	if (ImGui::Button("Load Bear")) { LoadBear(); }

	ImGui::SeparatorText("Save/Load Boar");
	if (ImGui::Button("Save Boar")) { SaveBoar(); }
	if (ImGui::Button("Load Boar")) { LoadBoar(); }

	ImGui::SeparatorText("Save/Load Dog");
	if (ImGui::Button("Save Dog")) { SaveDog(); }
	if (ImGui::Button("Load Dog")) { LoadDog(); }

	ImGui::SeparatorText("Save/Load Wolf");
	if (ImGui::Button("Save Wolf")) { SaveWolf(); }
	if (ImGui::Button("Load Wolf")) { LoadWolf(); }
}

void Editor::CModeWindow::CreateWildAnimal()
{
	if (m_eEditorCreateMode != EEditorCreateMode::WILD_ANIMAL)
	{
		//return;
	}

	if (m_wpInputManager.lock()->IsMouseDown(EMouseActionType::RIGHT_BUTTON))
	{
		Matrix matView = m_wpEditorCamera.lock()->GetViewMatrix();
		Matrix matPerspectiveProjection = m_wpEditorCamera.lock()->GetPerspectiveProjectionMatrix();
		Matrix matInvPV = (matView * matPerspectiveProjection).Invert();

		pair<float, float> prCursorNDCPos = m_wpInputManager.lock()->GetCursorNDCPos();
		Vector3 vCursorNDCNear = Vector3(prCursorNDCPos.first, prCursorNDCPos.second, 0.0f);
		Vector3 vCursorNDCFar = Vector3(prCursorNDCPos.first, prCursorNDCPos.second, 1.0f);

		Vector3 vCursorWorldNear = Vector3::Transform(vCursorNDCNear, matInvPV);
		Vector3 vCursorWorldFar = Vector3::Transform(vCursorNDCFar, matInvPV);

		Vector3 vRayDirection = vCursorWorldFar - vCursorWorldNear;
		vRayDirection.Normalize();

		Ray tRay = Ray(vCursorWorldNear, vRayDirection);
		const std::vector<std::shared_ptr<CCell>>& vecCells = m_wpNavHandler.lock()->FindNavigation(L"LumiaNavigation");

		float fDistance = 0.0f;

		Vector3 vCameraToWorldNear = m_wpEditorCamera.lock()->GetLocalPosition() - vCursorWorldNear;
		float fCameraToWorldNear = vCameraToWorldNear.Length();

		for (const auto& spCell : vecCells)
		{
			const std::array<Vector3, (int8)ECellPoint::ENUM_END>& arrPoints = spCell->GetThreePoints();
			if (tRay.Intersects(arrPoints[0], arrPoints[1], arrPoints[2], fDistance))
			{
				Vector3 vSpawnPosition = m_wpEditorCamera.lock()->GetLocalPosition() + vRayDirection * (fDistance + fCameraToWorldNear);
				int32 iCellIndex = spCell->GetCellIndex();

				m_iCellIndex = iCellIndex;

				/*
				shared_ptr<CWildAnimal> spWildAnimal = nullptr;
				wstring wstrName = L"";

				switch (static_cast<EWildAnimalType>(m_iChangableWildAnimalType))
				{
				case EWildAnimalType::BEAR:
				{
					wstrName = L"Bear" + to_wstring(m_wpEditorLevel.lock()->GetWildAnimalSize(EWildAnimalType::BEAR));
					spWildAnimal = m_wpEditorLevel.lock()->CreateActor<CBear>(wstrName);
				}
				break;

				case EWildAnimalType::BOAR:
				{
					wstrName = L"Boar" + to_wstring(m_wpEditorLevel.lock()->GetWildAnimalSize(EWildAnimalType::BOAR));
					spWildAnimal = m_wpEditorLevel.lock()->CreateActor<CBoar>(wstrName);
				}
				break;
				
				case EWildAnimalType::CHICKEN:
				{
					wstrName = L"Chicken" + to_wstring(m_wpEditorLevel.lock()->GetWildAnimalSize(EWildAnimalType::CHICKEN));
					spWildAnimal = m_wpEditorLevel.lock()->CreateActor<CChicken>(wstrName);
				}
				break;

				case EWildAnimalType::DOG:
				{
					wstrName = L"Dog" + to_wstring(m_wpEditorLevel.lock()->GetWildAnimalSize(EWildAnimalType::DOG));
					spWildAnimal = m_wpEditorLevel.lock()->CreateActor<CDog>(wstrName);
				}
				break;

				case EWildAnimalType::WOLF:
				{
					wstrName = L"Wolf" + to_wstring(m_wpEditorLevel.lock()->GetWildAnimalSize(EWildAnimalType::WOLF));
					spWildAnimal = m_wpEditorLevel.lock()->CreateActor<CWolf>(wstrName);
				}
				break;

				default:
					CHECKF(false, L"Wild animal type is not designated.");
					break;
				}

				m_wpEditorLevel.lock()->AddWildAnimal(static_cast<EWildAnimalType>(m_iChangableWildAnimalType), wstrName, spWildAnimal);

				spWildAnimal->SetSpawnCellIndex(iCellIndex);
				spWildAnimal->SetSpawnPosition(vSpawnPosition);

				spWildAnimal->PreInitialize();
				spWildAnimal->Initialize();
				spWildAnimal->PostInitialize();
				spWildAnimal->BeginPlay();
				*/
				break;
			}
		}
	}
}

void Editor::CModeWindow::SaveChicken()
{
	string strPath = m_strWildAnimalFilePath + "Chicken.dat";

	std::ofstream outFile;
	outFile.open(strPath.c_str(), ios_base::out | ios_base::binary | ios_base::trunc);

	ZeroMemory(m_chSaveWildAnimalFileName, MAX_PATH);

	// 파일이 열리지 않은 경우
	if (!outFile.is_open()) { return; }

	const std::unordered_map<std::wstring, std::weak_ptr<CChicken>>& umapChickens = m_wpEditorLevel.lock()->GetChickens();

	// 닭의 마릿수를 씁니다.
	uint32 iNumChickens = static_cast<uint32>(umapChickens.size());
	outFile.write(reinterpret_cast<char*>(&iNumChickens), sizeof(uint32));

	for (const auto& pair : umapChickens)
	{
		// 스폰 위치
		Vector3 vSpawnPosition = pair.second.lock()->GetSpawnPosition();
		outFile.write(reinterpret_cast<char*>(&vSpawnPosition), sizeof(Vector3));

		// 스폰 인덱스
		int32 iSpawnCellIndex = pair.second.lock()->GetSpawnCellIndex();
		outFile.write(reinterpret_cast<char*>(&iSpawnCellIndex), sizeof(int32));

		// Y축 회전 각도
		float fYDegree = pair.second.lock()->GetSpawnYDegree();
		outFile.write(reinterpret_cast<char*>(&fYDegree), sizeof(float));
	}
}

void Editor::CModeWindow::SaveBear()
{
	string strPath = m_strWildAnimalFilePath + "Bear.dat";

	std::ofstream outFile;
	outFile.open(strPath.c_str(), ios_base::out | ios_base::binary | ios_base::trunc);

	ZeroMemory(m_chSaveWildAnimalFileName, MAX_PATH);

	// 파일이 열리지 않은 경우
	if (!outFile.is_open()) { return; }

	const std::unordered_map<std::wstring, std::weak_ptr<CBear>>& umapBears = m_wpEditorLevel.lock()->GetBears();

	// 곰의 마릿수를 씁니다.
	uint32 iNumBears = static_cast<uint32>(umapBears.size());
	outFile.write(reinterpret_cast<char*>(&iNumBears), sizeof(uint32));

	for (const auto& pair : umapBears)
	{
		// 스폰 위치
		Vector3 vSpawnPosition = pair.second.lock()->GetSpawnPosition();
		outFile.write(reinterpret_cast<char*>(&vSpawnPosition), sizeof(Vector3));

		// 스폰 인덱스
		int32 iSpawnCellIndex = pair.second.lock()->GetSpawnCellIndex();
		outFile.write(reinterpret_cast<char*>(&iSpawnCellIndex), sizeof(int32));

		// Y축 회전 각도
		float fYDegree = pair.second.lock()->GetSpawnYDegree();
		outFile.write(reinterpret_cast<char*>(&fYDegree), sizeof(float));
	}
}

void Editor::CModeWindow::SaveBoar()
{
	string strPath = m_strWildAnimalFilePath + "Boar.dat";

	std::ofstream outFile;
	outFile.open(strPath.c_str(), ios_base::out | ios_base::binary | ios_base::trunc);

	ZeroMemory(m_chSaveWildAnimalFileName, MAX_PATH);

	// 파일이 열리지 않은 경우
	if (!outFile.is_open()) { return; }

	const std::unordered_map<std::wstring, std::weak_ptr<CBoar>>& umapBoars = m_wpEditorLevel.lock()->GetBoars();

	// 멧돼지의 마릿수를 씁니다.
	uint32 iNumBoars = static_cast<uint32>(umapBoars.size());
	outFile.write(reinterpret_cast<char*>(&iNumBoars), sizeof(uint32));

	for (const auto& pair : umapBoars)
	{
		// 스폰 위치
		Vector3 vSpawnPosition = pair.second.lock()->GetSpawnPosition();
		outFile.write(reinterpret_cast<char*>(&vSpawnPosition), sizeof(Vector3));

		// 스폰 인덱스
		int32 iSpawnCellIndex = pair.second.lock()->GetSpawnCellIndex();
		outFile.write(reinterpret_cast<char*>(&iSpawnCellIndex), sizeof(int32));

		// Y축 회전 각도
		float fYDegree = pair.second.lock()->GetSpawnYDegree();
		outFile.write(reinterpret_cast<char*>(&fYDegree), sizeof(float));
	}
}

void Editor::CModeWindow::SaveDog()
{
	string strPath = m_strWildAnimalFilePath + "Dog.dat";

	std::ofstream outFile;
	outFile.open(strPath.c_str(), ios_base::out | ios_base::binary | ios_base::trunc);

	ZeroMemory(m_chSaveWildAnimalFileName, MAX_PATH);

	// 파일이 열리지 않은 경우
	if (!outFile.is_open()) { return; }

	const std::unordered_map<std::wstring, std::weak_ptr<CDog>>& umapDogs = m_wpEditorLevel.lock()->GetDogs();

	// 멧돼지의 마릿수를 씁니다.
	uint32 iNumDogs = static_cast<uint32>(umapDogs.size());
	outFile.write(reinterpret_cast<char*>(&iNumDogs), sizeof(uint32));

	for (const auto& pair : umapDogs)
	{
		// 스폰 위치
		Vector3 vSpawnPosition = pair.second.lock()->GetSpawnPosition();
		outFile.write(reinterpret_cast<char*>(&vSpawnPosition), sizeof(Vector3));

		// 스폰 인덱스
		int32 iSpawnCellIndex = pair.second.lock()->GetSpawnCellIndex();
		outFile.write(reinterpret_cast<char*>(&iSpawnCellIndex), sizeof(int32));

		// Y축 회전 각도
		float fYDegree = pair.second.lock()->GetSpawnYDegree();
		outFile.write(reinterpret_cast<char*>(&fYDegree), sizeof(float));
	}
}

void Editor::CModeWindow::SaveWolf()
{
	string strPath = m_strWildAnimalFilePath + "Wolf.dat";

	std::ofstream outFile;
	outFile.open(strPath.c_str(), ios_base::out | ios_base::binary | ios_base::trunc);

	ZeroMemory(m_chSaveWildAnimalFileName, MAX_PATH);

	// 파일이 열리지 않은 경우
	if (!outFile.is_open()) { return; }

	const std::unordered_map<std::wstring, std::weak_ptr<CWolf>>& umapWolfs = m_wpEditorLevel.lock()->GetWolfs();

	// 멧돼지의 마릿수를 씁니다.
	uint32 iNumWolfs = static_cast<uint32>(umapWolfs.size());
	outFile.write(reinterpret_cast<char*>(&iNumWolfs), sizeof(uint32));

	for (const auto& pair : umapWolfs)
	{
		// 스폰 위치
		Vector3 vSpawnPosition = pair.second.lock()->GetSpawnPosition();
		outFile.write(reinterpret_cast<char*>(&vSpawnPosition), sizeof(Vector3));

		// 스폰 인덱스
		int32 iSpawnCellIndex = pair.second.lock()->GetSpawnCellIndex();
		outFile.write(reinterpret_cast<char*>(&iSpawnCellIndex), sizeof(int32));

		// Y축 회전 각도
		float fYDegree = pair.second.lock()->GetSpawnYDegree();
		outFile.write(reinterpret_cast<char*>(&fYDegree), sizeof(float));
	}
}

void Editor::CModeWindow::LoadChicken()
{
	string strPath = m_strWildAnimalFilePath + "Chicken.dat";

	std::ifstream inFile;
	inFile.open(strPath.c_str(), ios_base::in | ios_base::binary);

	// 파일이 열리지 않은 경우
	if (!inFile.is_open()) { return; }

	uint32 iNumChickens = 0;
	inFile.read(reinterpret_cast<char*>(&iNumChickens), sizeof(uint32));

	for (uint32 iIndex = 0; iIndex < iNumChickens; ++iIndex)
	{
		// 스폰 위치
		Vector3 vSpawnPosition = Vector3::Zero;
		inFile.read(reinterpret_cast<char*>(&vSpawnPosition), sizeof(Vector3));

		// 스폰 인덱스
		int32 iSpawnCellIndex = 0;
		inFile.read(reinterpret_cast<char*>(&iSpawnCellIndex), sizeof(int32));

		// Y축 회전 각도
		float fYDegree = 0.0f;
		inFile.read(reinterpret_cast<char*>(&fYDegree), sizeof(float));


		wstring wstrWildAnimalName = L"Chicken" + to_wstring(iIndex);
		shared_ptr<CWildAnimal> spWildAnimal = m_wpEditorLevel.lock()->CreateActor<CChicken>(wstrWildAnimalName);
		m_wpEditorLevel.lock()->AddWildAnimal(EWildAnimalType::CHICKEN, wstrWildAnimalName, spWildAnimal);

		spWildAnimal->SetSpawnCellIndex(iSpawnCellIndex);
		spWildAnimal->SetSpawnPosition(vSpawnPosition);

		spWildAnimal->PreInitialize();
		spWildAnimal->Initialize();
		spWildAnimal->PostInitialize();
		spWildAnimal->BeginPlay();
		spWildAnimal->SetActorLocalRotate(Vector3::Up, fYDegree);
	}
}

void Editor::CModeWindow::LoadBear()
{
	string strPath = m_strWildAnimalFilePath + "Bear.dat";

	std::ifstream inFile;
	inFile.open(strPath.c_str(), ios_base::in | ios_base::binary);

	// 파일이 열리지 않은 경우
	if (!inFile.is_open()) { return; }

	uint32 iNumBears = 0;
	inFile.read(reinterpret_cast<char*>(&iNumBears), sizeof(uint32));

	for (uint32 iIndex = 0; iIndex < iNumBears; ++iIndex)
	{
		// 스폰 위치
		Vector3 vSpawnPosition = Vector3::Zero;
		inFile.read(reinterpret_cast<char*>(&vSpawnPosition), sizeof(Vector3));

		// 스폰 인덱스
		int32 iSpawnCellIndex = 0;
		inFile.read(reinterpret_cast<char*>(&iSpawnCellIndex), sizeof(int32));

		// Y축 회전 각도
		float fYDegree = 0.0f;
		inFile.read(reinterpret_cast<char*>(&fYDegree), sizeof(float));


		wstring wstrWildAnimalName = L"Bear" + to_wstring(iIndex);
		shared_ptr<CWildAnimal> spWildAnimal = m_wpEditorLevel.lock()->CreateActor<CBear>(wstrWildAnimalName);
		m_wpEditorLevel.lock()->AddWildAnimal(EWildAnimalType::BEAR, wstrWildAnimalName, spWildAnimal);

		spWildAnimal->SetSpawnCellIndex(iSpawnCellIndex);
		spWildAnimal->SetSpawnPosition(vSpawnPosition);

		spWildAnimal->PreInitialize();
		spWildAnimal->Initialize();
		spWildAnimal->PostInitialize();
		spWildAnimal->BeginPlay();
		spWildAnimal->SetActorLocalRotate(Vector3::Up, fYDegree);
	}
}

void Editor::CModeWindow::LoadBoar()
{
	string strPath = m_strWildAnimalFilePath + "Boar.dat";

	std::ifstream inFile;
	inFile.open(strPath.c_str(), ios_base::in | ios_base::binary);

	// 파일이 열리지 않은 경우
	if (!inFile.is_open()) { return; }

	uint32 iNumBoars = 0;
	inFile.read(reinterpret_cast<char*>(&iNumBoars), sizeof(uint32));

	for (uint32 iIndex = 0; iIndex < iNumBoars; ++iIndex)
	{
		// 스폰 위치
		Vector3 vSpawnPosition = Vector3::Zero;
		inFile.read(reinterpret_cast<char*>(&vSpawnPosition), sizeof(Vector3));

		// 스폰 인덱스
		int32 iSpawnCellIndex = 0;
		inFile.read(reinterpret_cast<char*>(&iSpawnCellIndex), sizeof(int32));

		// Y축 회전 각도
		float fYDegree = 0.0f;
		inFile.read(reinterpret_cast<char*>(&fYDegree), sizeof(float));


		wstring wstrWildAnimalName = L"Boar" + to_wstring(iIndex);
		shared_ptr<CWildAnimal> spWildAnimal = m_wpEditorLevel.lock()->CreateActor<CBoar>(wstrWildAnimalName);
		m_wpEditorLevel.lock()->AddWildAnimal(EWildAnimalType::BOAR, wstrWildAnimalName, spWildAnimal);

		spWildAnimal->SetSpawnCellIndex(iSpawnCellIndex);
		spWildAnimal->SetSpawnPosition(vSpawnPosition);

		spWildAnimal->PreInitialize();
		spWildAnimal->Initialize();
		spWildAnimal->PostInitialize();
		spWildAnimal->BeginPlay();
		spWildAnimal->SetActorLocalRotate(Vector3::Up, fYDegree);
	}
}

void Editor::CModeWindow::LoadDog()
{
	string strPath = m_strWildAnimalFilePath + "Dog.dat";

	std::ifstream inFile;
	inFile.open(strPath.c_str(), ios_base::in | ios_base::binary);

	// 파일이 열리지 않은 경우
	if (!inFile.is_open()) { return; }

	uint32 iNumDogs = 0;
	inFile.read(reinterpret_cast<char*>(&iNumDogs), sizeof(uint32));

	for (uint32 iIndex = 0; iIndex < iNumDogs; ++iIndex)
	{
		// 스폰 위치
		Vector3 vSpawnPosition = Vector3::Zero;
		inFile.read(reinterpret_cast<char*>(&vSpawnPosition), sizeof(Vector3));

		// 스폰 인덱스
		int32 iSpawnCellIndex = 0;
		inFile.read(reinterpret_cast<char*>(&iSpawnCellIndex), sizeof(int32));

		// Y축 회전 각도
		float fYDegree = 0.0f;
		inFile.read(reinterpret_cast<char*>(&fYDegree), sizeof(float));


		wstring wstrWildAnimalName = L"Dog" + to_wstring(iIndex);
		shared_ptr<CWildAnimal> spWildAnimal = m_wpEditorLevel.lock()->CreateActor<CDog>(wstrWildAnimalName);
		m_wpEditorLevel.lock()->AddWildAnimal(EWildAnimalType::DOG, wstrWildAnimalName, spWildAnimal);

		spWildAnimal->SetSpawnCellIndex(iSpawnCellIndex);
		spWildAnimal->SetSpawnPosition(vSpawnPosition);

		spWildAnimal->PreInitialize();
		spWildAnimal->Initialize();
		spWildAnimal->PostInitialize();
		spWildAnimal->BeginPlay();
		spWildAnimal->SetActorLocalRotate(Vector3::Up, fYDegree);
	}
}

void Editor::CModeWindow::LoadWolf()
{
	string strPath = m_strWildAnimalFilePath + "Wolf.dat";

	std::ifstream inFile;
	inFile.open(strPath.c_str(), ios_base::in | ios_base::binary);

	// 파일이 열리지 않은 경우
	if (!inFile.is_open()) { return; }

	uint32 iNumWolfs = 0;
	inFile.read(reinterpret_cast<char*>(&iNumWolfs), sizeof(uint32));

	for (uint32 iIndex = 0; iIndex < iNumWolfs; ++iIndex)
	{
		// 스폰 위치
		Vector3 vSpawnPosition = Vector3::Zero;
		inFile.read(reinterpret_cast<char*>(&vSpawnPosition), sizeof(Vector3));

		// 스폰 인덱스
		int32 iSpawnCellIndex = 0;
		inFile.read(reinterpret_cast<char*>(&iSpawnCellIndex), sizeof(int32));

		// Y축 회전 각도
		float fYDegree = 0.0f;
		inFile.read(reinterpret_cast<char*>(&fYDegree), sizeof(float));


		wstring wstrWildAnimalName = L"Wolf" + to_wstring(iIndex);
		shared_ptr<CWildAnimal> spWildAnimal = m_wpEditorLevel.lock()->CreateActor<CWolf>(wstrWildAnimalName);
		m_wpEditorLevel.lock()->AddWildAnimal(EWildAnimalType::WOLF, wstrWildAnimalName, spWildAnimal);

		spWildAnimal->SetSpawnCellIndex(iSpawnCellIndex);
		spWildAnimal->SetSpawnPosition(vSpawnPosition);

		spWildAnimal->PreInitialize();
		spWildAnimal->Initialize();
		spWildAnimal->PostInitialize();
		spWildAnimal->BeginPlay();
		spWildAnimal->SetActorLocalRotate(Vector3::Up, fYDegree);
	}
}
