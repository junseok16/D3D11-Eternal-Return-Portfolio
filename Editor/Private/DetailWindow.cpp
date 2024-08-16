// default
#include "pch.h"
#include "DetailWindow.h"

// handler
#include "ShaderHandler.h"
#include "ModelHandler.h"

// engine
#include "World.h"
#include "Level.h"
#include "Actor.h"

// editor
#include "EditorLevel.h"

// wild animal
#include "Bear.h"
#include "Boar.h"
#include "Chicken.h"
#include "Dog.h"
#include "Wolf.h"

// component
#include "CameraComponent.h"
#include "NavigationComponent.h"

std::shared_ptr<CDetailWindow> Editor::CDetailWindow::Create(const std::shared_ptr<CIMGUIManager>& _spIMGUIManager)
{
	const shared_ptr<CDetailWindow> spWindow = make_shared<CDetailWindow>();
	ENSURE(spWindow->Initialize(_spIMGUIManager));
	return spWindow;
}

HRESULT Editor::CDetailWindow::Initialize(const std::shared_ptr<CIMGUIManager>& _spIMGUIManager)
{
	m_wpIMGUIManager = _spIMGUIManager;
	m_wpEditorLevel = dynamic_pointer_cast<CEditorLevel>(CWorld::GetInstance()->GetCurLevel());
	m_wpShaderHandler = CShaderHandler::GetInstance();
	m_wpModelHandler = CModelHandler::GetInstance();
	return S_OK;
}

int32 Editor::CDetailWindow::Tick()
{
	ImGui::Begin("OutlinerWindow");
	if (ImGui::CollapsingHeader("Outliner"))
	{
		TickSeparaterLevel();
		TickSeparaterDetail();
	}
	ImGui::End();
	return 0;
}

void Editor::CDetailWindow::Release()
{
}

void Editor::CDetailWindow::TickSeparaterLevel()
{
	ImGui::SeparatorText("Level");

	TickWildAnimalTabBar();
}

void Editor::CDetailWindow::TickWildAnimalTabBar()
{
	if (!ImGui::BeginTabBar("WildAnimal", ImGuiTabBarFlags_None)) { return; }

	// °õ
	if (ImGui::BeginTabItem("Bear"))
	{
		if (ImGui::BeginListBox("Bear", ImVec2(-FLT_MIN, 10 * ImGui::GetTextLineHeightWithSpacing())))
		{
			const std::unordered_map<std::wstring, std::weak_ptr<CBear>>& umapBears = m_wpEditorLevel.lock()->GetBears();
			for (const auto& pair : umapBears)
			{
				string strLabel = "";
				strLabel.assign(pair.first.begin(), pair.first.end());

				bool bSelected = (m_wstrActorName == pair.first);
				if (ImGui::Selectable(strLabel.c_str(), bSelected))
				{
					m_wstrActorName = pair.first;
					m_wpActor = pair.second.lock();
				}
			}
			ImGui::EndListBox();
		}
		ImGui::EndTabItem();
	}

	// ¸äµÅÁö
	if (ImGui::BeginTabItem("Boar"))
	{
		if (ImGui::BeginListBox("Boar", ImVec2(-FLT_MIN, 10 * ImGui::GetTextLineHeightWithSpacing())))
		{
			const std::unordered_map<std::wstring, std::weak_ptr<CBoar>>& umapBoars = m_wpEditorLevel.lock()->GetBoars();
			for (const auto& pair : umapBoars)
			{
				string strLabel = "";
				strLabel.assign(pair.first.begin(), pair.first.end());

				bool bSelected = (m_wstrActorName == pair.first);
				if (ImGui::Selectable(strLabel.c_str(), bSelected))
				{
					m_wstrActorName = pair.first;
					m_wpActor = pair.second.lock();
				}
			}
			ImGui::EndListBox();
		}
		ImGui::EndTabItem();
	}

	// ´ß
	if (ImGui::BeginTabItem("Chicken"))
	{
		if (ImGui::BeginListBox("Chicken", ImVec2(-FLT_MIN, 10 * ImGui::GetTextLineHeightWithSpacing())))
		{
			const std::unordered_map<std::wstring, std::weak_ptr<CChicken>>& umapChickens = m_wpEditorLevel.lock()->GetChickens();
			for (const auto& pair : umapChickens)
			{
				string strLabel = "";
				strLabel.assign(pair.first.begin(), pair.first.end());

				bool bSelected = (m_wstrActorName == pair.first);
				if (ImGui::Selectable(strLabel.c_str(), bSelected))
				{
					m_wstrActorName = pair.first;
					m_wpActor = pair.second.lock();
				}
			}
			ImGui::EndListBox();
		}
		ImGui::EndTabItem();
	}

	// °³
	if (ImGui::BeginTabItem("Dog"))
	{
		if (ImGui::BeginListBox("Dog", ImVec2(-FLT_MIN, 10 * ImGui::GetTextLineHeightWithSpacing())))
		{
			const std::unordered_map<std::wstring, std::weak_ptr<CDog>>& umapDogs = m_wpEditorLevel.lock()->GetDogs();
			for (const auto& pair : umapDogs)
			{
				string strLabel = "";
				strLabel.assign(pair.first.begin(), pair.first.end());

				bool bSelected = (m_wstrActorName == pair.first);
				if (ImGui::Selectable(strLabel.c_str(), bSelected))
				{
					m_wstrActorName = pair.first;
					m_wpActor = pair.second.lock();
				}
			}
			ImGui::EndListBox();
		}
		ImGui::EndTabItem();
	}

	// ´Á´ë
	if (ImGui::BeginTabItem("Wolf"))
	{
		if (ImGui::BeginListBox("Wolf", ImVec2(-FLT_MIN, 10 * ImGui::GetTextLineHeightWithSpacing())))
		{
			const std::unordered_map<std::wstring, std::weak_ptr<CWolf>>& umapWolfs = m_wpEditorLevel.lock()->GetWolfs();
			for (const auto& pair : umapWolfs)
			{
				string strLabel = "";
				strLabel.assign(pair.first.begin(), pair.first.end());

				bool bSelected = (m_wstrActorName == pair.first);
				if (ImGui::Selectable(strLabel.c_str(), bSelected))
				{
					m_wstrActorName = pair.first;
					m_wpActor = pair.second.lock();
				}
			}
			ImGui::EndListBox();
		}
		ImGui::EndTabItem();
	}

	ImGui::EndTabBar();
}

void Editor::CDetailWindow::TickSeparaterDetail()
{
	if (m_wpActor.expired()) { return; }

	ImGui::SeparatorText("Detail");

	// ·çÆ® ÄÄÆ÷³ÍÆ®
	TickSceneComponentDetail();
	ImGui::Spacing();
}

void Editor::CDetailWindow::TickSceneComponentDetail()
{
	if (!m_wpActor.lock()->GetRootComponent()) { return; }
	
	if (!ImGui::BeginTabBar("Scene Component Detail", ImGuiTabBarFlags_None)) { return; }
	
	if (!ImGui::BeginTabItem("Scene Component(Root)")) { ImGui::EndTabBar(); return; }
	
	Vector3 vOutTranslate = m_wpActor.lock()->GetActorLocalPosition().value();

	Vector3 vOutScale = m_wpActor.lock()->GetActorLocalScale().value();

	float fOutTranslate[3]	= { vOutTranslate.x, vOutTranslate.y, vOutTranslate.z };
	
	float fYDegree = 0.0f;
	std::shared_ptr<CWildAnimal> spWildAnimal = dynamic_pointer_cast<CWildAnimal>(m_wpActor.lock());
	if (spWildAnimal)
	{
		fYDegree = spWildAnimal->GetSpawnYDegree();
	}

	float fOutScale[3]		= { vOutScale.x, vOutScale.y, vOutScale.z };

	ImGui::InputFloat3("Translate", fOutTranslate);
	ImGui::InputFloat("Y Rotate", &fYDegree);
	ImGui::InputFloat3("Scale", fOutScale);
	m_wpActor.lock()->SetActorLocalPosition({ fOutTranslate[0], fOutTranslate[1], fOutTranslate[2] });
	
	if (spWildAnimal)
	{
		m_wpActor.lock()->SetActorLocalRotate(Vector3::Up, fYDegree);
		spWildAnimal->SetSpawnYDegree(fYDegree);
	}

	m_wpActor.lock()->SetActorLocalScale({ fOutScale[0], fOutScale[1], fOutScale[2] });

	ImGui::EndTabItem();
	ImGui::EndTabBar();
}
