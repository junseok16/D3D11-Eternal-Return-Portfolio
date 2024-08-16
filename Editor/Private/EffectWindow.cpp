// default
#include "pch.h"
#include "EffectWindow.h"

// engine
#include "World.h"

// manager
#include "IMGUIManager.h"

// level
#include "EditorLevel.h"

// handler
#include "EffectHandler.h"
#include "ShaderHandler.h"

// data
#include "EffectMeshData.h"
#include "EffectParticleData.h"

// component
#include "EffectComponent.h"

// actor
#include "EffectTester.h"

std::shared_ptr<CEffectWindow> Editor::CEffectWindow::Create(const std::shared_ptr<CIMGUIManager>& _spIMGUIManager)
{
	const shared_ptr<CEffectWindow> spWindow = make_shared<CEffectWindow>();
	ENSURE(spWindow->Initialize(_spIMGUIManager));
	return spWindow;
}

HRESULT Editor::CEffectWindow::Initialize(const std::shared_ptr<CIMGUIManager>& _spIMGUIManager)
{
	m_wpEditorLevel = dynamic_pointer_cast<CEditorLevel>(CWorld::GetInstance()->GetCurLevel());
	m_wpEffectHandler = CEffectHandler::GetInstance();
	m_wpShaderHandler = CShaderHandler::GetInstance();
	m_wpEffectTester = m_wpEditorLevel.lock()->FindActor<CEffectTester>(L"EffectTester");
	m_wpEffectComponent = m_wpEffectTester.lock()->FindActorComponent<CEffectComponent>(L"EffectComponent");

	// 메시 이펙트
	{
		const std::unordered_map<std::wstring, std::shared_ptr<FModelDesc>>& umapEffectModelDescs = m_wpEffectHandler.lock()->GetEffectModelDescs();
		for (auto& pair : umapEffectModelDescs)
		{
			string strEffectMeshDesc(pair.first.begin(), pair.first.end());
			m_vecEffectMeshDescs.push_back({ strEffectMeshDesc, pair.second });
		}

		const std::unordered_map<std::wstring, ComPtr<ID3D11ShaderResourceView>>& umapMaskSRVs = m_wpEffectHandler.lock()->GetMaskShaderResourceViews();
		for (auto& pair : umapMaskSRVs)
		{
			string strMaskSRVName(pair.first.begin(), pair.first.end());
			m_vecMeshMasks.push_back({ strMaskSRVName, pair.second });
		}

		const std::unordered_map<std::wstring, ComPtr<ID3D11ShaderResourceView>>& umapNoiseSRVs = m_wpEffectHandler.lock()->GetNoiseShaderResourceViews();
		for (auto& pair : umapNoiseSRVs)
		{
			string strNoiseSRVName(pair.first.begin(), pair.first.end());
			m_vecMeshNoises.push_back({ strNoiseSRVName, pair.second });
		}

		const std::unordered_map<std::wstring, std::shared_ptr<FVertexShaderDesc>>& umapVSDescs = m_wpShaderHandler.lock()->GetVertexShaderDescs();
		for (auto& pair : umapVSDescs)
		{
			string strVSName(pair.first.begin(), pair.first.end());
			m_vecMeshVSDescs.push_back({ strVSName, pair.second });
		}

		const std::unordered_map<std::wstring, std::shared_ptr<FPixelShaderDesc>>& umapPSDescs = m_wpShaderHandler.lock()->GetPixelShaderDescs();
		for (auto& pair : umapPSDescs)
		{
			string strPSName(pair.first.begin(), pair.first.end());
			m_vecMeshPSDescs.push_back({ strPSName, pair.second });
		}
	}
	
	return S_OK;
}

int32 Editor::CEffectWindow::Tick()
{
	ImGui::Begin("MeshEffectWindow");
	if (ImGui::CollapsingHeader("MeshEffect"))
	{
		TickSeparaterMeshEffect();
	}
	ImGui::End();

	/*
	ImGui::Begin("ParticleEffectWindow");
	if (ImGui::CollapsingHeader("ParticleEffect"))
	{
		TickSeparaterParticleEffect();
	}
	ImGui::End();
	*/
	return 0;
}

void Editor::CEffectWindow::Release()
{
	for (auto& pair : m_vecEffectMeshData)
	{
		pair.second->Release();
		pair.second = nullptr;
	}
	m_vecEffectMeshData.clear();

	m_spCurEffectMeshData = nullptr;

	for (auto& pair : m_vecMeshMasks) { pair.second = nullptr; }

	for (auto& pair : m_vecMeshNoises) { pair.second = nullptr; }
}

void Editor::CEffectWindow::TickSeparaterMeshEffect()
{
	/************************
		이펙트 메시 데이터
	************************/
	// 이펙트 메시 데이터 목록들
	ImGui::SeparatorText("Mesh Effect Data");
	if (ImGui::BeginListBox("##MeshEffectData", ImVec2(-FLT_MIN, 5 * ImGui::GetTextLineHeightWithSpacing())))
	{
		for (size_t iIndex = 0; iIndex < m_vecEffectMeshData.size(); ++iIndex)
		{
			wstring wstrEffectMeshDescName = m_vecEffectMeshData[iIndex].first;
			string strEffectMeshDescName(wstrEffectMeshDescName.begin(), wstrEffectMeshDescName.end());

			if (ImGui::Selectable(strEffectMeshDescName.c_str(), true))
			{
				// 이전 이펙트를 끕니다.
				if (m_spCurEffectMeshData)
				{
					m_spCurEffectMeshData->SetEffectMeshDataState(EEffectMeshDataState::OFF);
				}

				m_iCurEffectMeshDataIndex = static_cast<int32>(iIndex);
				m_spCurEffectMeshData = m_vecEffectMeshData[iIndex].second;

				// 현재 이펙트를 켭니다.
				m_spCurEffectMeshData->SetEffectMeshDataState(EEffectMeshDataState::ON);

				FPlayEffectProperty tPlayProperty = m_spCurEffectMeshData->GetPlayProperty();
				m_fMeshStartTime = tPlayProperty.m_fStartPlaySeconds;
				m_fMeshFinishTime = tPlayProperty.m_fFinishPlaySeconds;
				m_bMeshLoop = tPlayProperty.m_bLoop;

				FUVEffectProperty tUVEffectProperty = m_spCurEffectMeshData->GetUVProperty();
				m_bUseMeshEffectUV = tUVEffectProperty.m_bUseEffectUV;
				m_fMeshStartEffectUV[0] = tUVEffectProperty.m_vEffectStartUV.x;
				m_fMeshStartEffectUV[1] = tUVEffectProperty.m_vEffectStartUV.y;
				m_fMeshFinishEffectUV[0] = tUVEffectProperty.m_vEffectFinishUV.x;
				m_fMeshFinishEffectUV[1] = tUVEffectProperty.m_vEffectFinishUV.y;

				FMaskEffectProperty tMaskProperty = m_spCurEffectMeshData->GetMaskProperty();
				m_bUseMeshMask = tMaskProperty.m_bUseMask;
				m_bUseColorMeshMask = tMaskProperty.m_bUseColorMask;
				m_iMeshMaskRowColumn[0] = tMaskProperty.m_iMaskRowColume[0];
				m_iMeshMaskRowColumn[1] = tMaskProperty.m_iMaskRowColume[1];
				m_fMeshMaskUVSpeed[0] = tMaskProperty.m_vMaskUVSpeed.x;
				m_fMeshMaskUVSpeed[1] = tMaskProperty.m_vMaskUVSpeed.y;
				m_fMeshMaskMaxUV[0] = tMaskProperty.m_vMaskMaxUV.x;
				m_fMeshMaskMaxUV[1] = tMaskProperty.m_vMaskMaxUV.y;

				FNoiseEffectProperty tNoiseProperty = m_spCurEffectMeshData->GetNoiseProperty();
				m_bUseMeshNoise = tNoiseProperty.m_bUseNoise;
				m_iMeshNoiseRowColumn[0] = tNoiseProperty.m_iNoiseRowColume[0];
				m_iMeshNoiseRowColumn[1] = tNoiseProperty.m_iNoiseRowColume[1];
				m_fMeshNoiseUVSpeed[0] = tNoiseProperty.m_vNoiseUVSpeed.x;
				m_fMeshNoiseUVSpeed[1] = tNoiseProperty.m_vNoiseUVSpeed.y;
				m_fMeshNoiseMaxUV[0] = tNoiseProperty.m_vNoiseMaxUV.x;
				m_fMeshNoiseMaxUV[1] = tNoiseProperty.m_vNoiseMaxUV.y;

				FColorEffectProperty tColorProperty = m_spCurEffectMeshData->GetColorProperty();
				m_vMeshStartColor = tColorProperty.m_vStartColor;
				m_vMeshFinishColor = tColorProperty.m_vFinishColor;

				FTransformEffectProperty tTransformEffectProperty = m_spCurEffectMeshData->GetTransformProperty();
				m_vMeshStartScale = tTransformEffectProperty.m_vStartScale;
				m_vMeshStartRotate = tTransformEffectProperty.m_vStartRotate;
				m_vMeshStartTranslate = tTransformEffectProperty.m_vStartTranslate;

				m_vMeshFinishScale = tTransformEffectProperty.m_vFinishScale;
				m_vMeshFinishRotate = tTransformEffectProperty.m_vFinishRotate;
				m_vMeshFinishTranslate = tTransformEffectProperty.m_vFinishTranslate;
			}
		}
		ImGui::EndListBox();
	}

	// 이펙트 메시 데이터를 생성합니다.
	ImGui::InputTextWithHint("##EffectMeshDataName", "EffectMeshDataName", m_chEffectMeshDataName, IM_ARRAYSIZE(m_chEffectMeshDataName));

	if (ImGui::Button("Create EMD"))
	{
		wstring wstrEMDName(m_chEffectMeshDataName, m_chEffectMeshDataName + strlen(m_chEffectMeshDataName));
		if (!wstrEMDName.empty())
		{
			bool bFound = false;
			for (const auto& pair : m_vecEffectMeshData)
			{
				if (pair.first == wstrEMDName)
				{
					bFound = true;
					break;
				}
			}

			if (!bFound)
			{
				shared_ptr<CEffectMeshData> spEffectMeshData = CEffectMeshData::Create(m_wpEffectComponent.lock(), L"", L"", L"");
				m_vecEffectMeshData.push_back({ wstrEMDName, spEffectMeshData });
				m_wpEffectComponent.lock()->AddMeshEffect(wstrEMDName, spEffectMeshData);
				ZeroMemory(m_chEffectMeshDataName, MAX_PATH);
			}
		}
	}
	ImGui::SameLine();

	// 이펙트 메시 데이터를 없앱니다.
	if (ImGui::Button("Remove EMD"))
	{
		if (m_iCurEffectMeshDataIndex < m_vecEffectMeshData.size())
		{
			m_wpEffectComponent.lock()->RemoveMeshEffect(m_vecEffectMeshData[m_iCurEffectMeshDataIndex].first);

			m_vecEffectMeshData[m_iCurEffectMeshDataIndex].second->Release();
			m_vecEffectMeshData[m_iCurEffectMeshDataIndex].second = nullptr;
			m_spCurEffectMeshData = nullptr;

			auto iter = m_vecEffectMeshData.begin() + m_iCurEffectMeshDataIndex;
			m_vecEffectMeshData.erase(iter);
		}
	}

	/********************
		이펙트 메시
	********************/
	ImGui::SeparatorText("Effect Mesh FBX");
	if (ImGui::BeginListBox("##EffectMeshFBX", ImVec2(-FLT_MIN, 10 * ImGui::GetTextLineHeightWithSpacing())))
	{
		for (size_t iIndex = 0; iIndex < m_vecEffectMeshDescs.size(); ++iIndex)
		{
			if (ImGui::Selectable(m_vecEffectMeshDescs[iIndex].first.c_str(), true))
			{
				m_iCurEffectMeshDataIndex = static_cast<int32>(iIndex);

				// 이펙트 메시 데이터가 선택된 경우, 이 메시를 적용합니다.
				if (m_spCurEffectMeshData)
				{
					m_spCurEffectMeshData->ChangeEffectModelDesc(m_vecEffectMeshDescs[m_iCurEffectMeshDataIndex].second->m_wstrModelName);
				}
			}
		}
		ImGui::EndListBox();
	}

	/********************
		버텍스 셰이더
	********************/
	// 이펙트 버텍스 셰이더
	ImGui::SeparatorText("Mesh Vertex Shader");
	if (ImGui::BeginListBox("##MeshVertexShader", ImVec2(-FLT_MIN, 5 * ImGui::GetTextLineHeightWithSpacing())))
	{
		for (size_t iIndex = 0; iIndex < m_vecMeshVSDescs.size(); ++iIndex)
		{
			if (ImGui::Selectable(m_vecMeshVSDescs[iIndex].first.c_str(), true))
			{
				m_iCurMeshVSIndex = static_cast<int32>(iIndex);
			}
		}
		ImGui::EndListBox();
	}

	/********************
		픽셀 셰이더
	********************/
	// 이펙트 픽셀 셰이더
	ImGui::SeparatorText("Mesh Pixel Shader");
	if (ImGui::BeginListBox("##MeshPixelShader", ImVec2(-FLT_MIN, 5 * ImGui::GetTextLineHeightWithSpacing())))
	{
		for (size_t iIndex = 0; iIndex < m_vecMeshPSDescs.size(); ++iIndex)
		{
			if (ImGui::Selectable(m_vecMeshPSDescs[iIndex].first.c_str(), true))
			{
				m_iCurMeshPSIndex = static_cast<int32>(iIndex);
			}
		}
		ImGui::EndListBox();
	}

	/********************
		셰이더 적용
	********************/
	ImGui::SeparatorText("Apply Mesh Shader");
	if (ImGui::Button("Apply Mesh Shaders"))
	{
		if (m_spCurEffectMeshData && m_iCurMeshPSIndex != -1 && m_iCurMeshVSIndex != -1)
		{
			m_spCurEffectMeshData->ChangeShaders(m_wpEffectComponent.lock(), m_vecMeshVSDescs[m_iCurMeshVSIndex].second->m_wstrVertexShaderName, m_vecMeshPSDescs[m_iCurMeshPSIndex].second->m_wstrPixelShaderName);
		}
	}

	/********************
		이펙트 시간
	********************/
	// 이펙트 시간
	ImGui::SeparatorText("Mesh Effect Time");
	ImGui::InputFloat("Mesh Start Time", &m_fMeshStartTime);
	ImGui::InputFloat("Mesh Finish Time", &m_fMeshFinishTime);
	ImGui::Checkbox("Mesh Loop", &m_bMeshLoop);
	ImGui::Spacing();

	// 이펙트 시간을 업데이트합니다.
	if (m_spCurEffectMeshData)
	{
		m_spCurEffectMeshData->SetPlayProperty
		(
			m_fMeshStartTime,
			m_fMeshFinishTime,
			m_bMeshLoop
		);
	}

	/********************
		이펙트 마스크
	********************/
	// 마스크 이미지들
	ImGui::SeparatorText("Mesh Mask Textures");
	ImGui::Checkbox("Use Mesh Mask", &m_bUseMeshMask);
	if (m_bUseMeshMask)
	{
		if (ImGui::BeginListBox("##MeshMask", ImVec2(-FLT_MIN, 10 * ImGui::GetTextLineHeightWithSpacing())))
		{
			ImGui::Checkbox("Use Color Mesh Mask", &m_bUseColorMeshMask);

			for (size_t iIndex = 0; iIndex < m_vecMeshMasks.size(); ++iIndex)
			{
				// 이미지 크기
				ImVec2 vSize = ImVec2(32.0f, 32.0f);
				ImVec2 vUV0 = ImVec2(0.0f, 0.0f);
				ImVec2 vUV1 = ImVec2(1.0f, 1.0f);
				ImVec4 vBGCol = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
				ImVec4 vTintCol = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

				string strMaskID = "##MeshMask" + to_string(iIndex);
				if (ImGui::ImageButton(strMaskID.c_str(), m_vecMeshMasks[iIndex].second.Get(), vSize, vUV0, vUV1, vBGCol, vTintCol))
				{
					m_iCurMeshMaskTextureIndex = static_cast<int32>(iIndex);

					// 이펙트 메시 데이터가 선택된 경우, 이 마스크 이미지를 적용합니다.
					if (m_spCurEffectMeshData && m_iCurMeshMaskTextureIndex != -1)
					{
						wstring wstrTextureName(m_vecMeshMasks[iIndex].first.begin(), m_vecMeshMasks[iIndex].first.end());
						m_spCurEffectMeshData->ModifyPixelShaderTexture(0, 0, wstrTextureName);
					}
				}

				if ((iIndex + 1) % 5) { ImGui::SameLine(); }
			}
			ImGui::EndListBox();
		}

		// 마스크 이미지 종횡수
		ImGui::SeparatorText("Mesh Mask Row Column");
		ImGui::DragInt2("Mesh Mask Row Colume", m_iMeshMaskRowColumn, 1, 1, 32);

		// 마스크 uv 재생 속도
		ImGui::SeparatorText("Mesh Mask UV Speed");
		ImGui::DragFloat2("Mesh Mask UV Speed", m_fMeshMaskUVSpeed, 0.001f, 0.0f, 15.0f);

		// 마스크 uv 최댓값
		ImGui::SeparatorText("Mesh Mask Max UV");
		ImGui::DragFloat2("Mesh Mask Max UV", m_fMeshMaskMaxUV, 0.1f, 1.0f, 155.0f);
		ImGui::Spacing();

		// 이펙트 마스크를 업데이트합니다.
		if (m_spCurEffectMeshData)
		{
			m_spCurEffectMeshData->SetMaskProperty
			(
				m_bUseMeshMask,
				m_bUseColorMeshMask,
				m_iMeshMaskRowColumn[0],
				m_iMeshMaskRowColumn[1],
				{ m_fMeshMaskUVSpeed[0], m_fMeshMaskUVSpeed[1] },
				{ m_fMeshMaskMaxUV[0], m_fMeshMaskMaxUV[1] }
			);
		}
	}
	else
	{
		// 이펙트 마스크를 업데이트합니다.
		if (m_spCurEffectMeshData)
		{
			m_spCurEffectMeshData->SetMaskProperty
			(
				false,
				false,
				1,
				1,
				{ 0.0f, 0.0f },
				{ 1.0f, 1.0f }
			);
		}
	}
	
	/********************
		이펙트 노이즈
	********************/
	// 이펙트 노이즈 이미지들
	ImGui::SeparatorText("Mesh Noise Textures");
	ImGui::Checkbox("Use Mesh Noise", &m_bUseMeshNoise);
	if (m_bUseMeshNoise)
	{
		if (ImGui::BeginListBox("##MeshNoise", ImVec2(-FLT_MIN, 10 * ImGui::GetTextLineHeightWithSpacing())))
		{
			for (size_t iIndex = 0; iIndex < m_vecMeshNoises.size(); ++iIndex)
			{
				// 이미지 크기
				ImVec2 vSize = ImVec2(32.0f, 32.0f);
				ImVec2 vUV0 = ImVec2(0.0f, 0.0f);
				ImVec2 vUV1 = ImVec2(1.0f, 1.0f);
				ImVec4 vBGCol = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
				ImVec4 vTintCol = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

				string strNoiseID = "##MeshNoise" + to_string(iIndex);
				if (ImGui::ImageButton(strNoiseID.c_str(), m_vecMeshNoises[iIndex].second.Get(), vSize, vUV0, vUV1, vBGCol, vTintCol))
				{
					m_iCurMeshNoiseTextureIndex = static_cast<int32>(iIndex);

					// 이펙트 메시 데이터가 선택된 경우, 이 노이즈 이미지를 적용합니다.
					if (m_spCurEffectMeshData && m_iCurMeshNoiseTextureIndex != -1)
					{
						wstring wstrTextureName(m_vecMeshNoises[iIndex].first.begin(), m_vecMeshNoises[iIndex].first.end());

						// 0번 메시의 1번 텍스처(첫 번째 메시에 노이즈 텍스처를 설정합니다.)
						m_spCurEffectMeshData->ModifyPixelShaderTexture(0, 1, wstrTextureName);
					}
				}

				if ((iIndex + 1) % 5) { ImGui::SameLine(); }
			}
			ImGui::EndListBox();
		}

		// 노이즈 이미지 종횡수
		ImGui::SeparatorText("Mesh Noise Row Column");
		ImGui::DragInt2("Mesh Noise Row Colume", m_iMeshNoiseRowColumn, 1, 1, 8);

		// 노이즈 uv 재생 속도
		ImGui::SeparatorText("Mesh Noise UV Speed");
		ImGui::DragFloat2("Mesh Noise UV Speed", m_fMeshNoiseUVSpeed, 0.001f, 0.0f, 15.0f);

		// 노이즈 uv 최댓값
		ImGui::SeparatorText("Mesh Noise Max UV");
		ImGui::DragFloat2("Mesh Noise Max UV", m_fMeshNoiseMaxUV, 0.1f, 1.0f, 255.0f);
		ImGui::Spacing();

		// 이펙트 노이즈를 업데이트합니다.
		if (m_spCurEffectMeshData)
		{
			m_spCurEffectMeshData->SetNoiseProperty
			(
				m_bUseMeshNoise,
				m_iMeshNoiseRowColumn[0],
				m_iMeshNoiseRowColumn[1],
				{ m_fMeshNoiseUVSpeed[0], m_fMeshNoiseUVSpeed[1] },
				{ m_fMeshNoiseMaxUV[0], m_fMeshNoiseMaxUV[1] }
			);
		}

	}
	else
	{
		// 이펙트 노이즈를 업데이트합니다.
		if (m_spCurEffectMeshData)
		{
			m_spCurEffectMeshData->SetNoiseProperty
			(
				false,
				1,
				1,
				{ 0.0f, 0.0f },
				{ 1.0f, 1.0f }
			);
		}
	}

	/********************
		이펙트 uv
	********************/
	// 이펙트 시작 uv
	ImGui::SeparatorText("Mesh Effect UV");
	ImGui::Checkbox("Use Mesh Effect UV", &m_bUseMeshEffectUV);
	if (m_bUseMeshEffectUV)
	{
		// 이펙트 시작 uv
		ImGui::DragFloat2("Mesh Start Effect UV", m_fMeshStartEffectUV, 0.1f, 0.0f, 1.0f);
		ImGui::Spacing();

		// 이펙트 종료 uv
		ImGui::DragFloat2("Mesh Finish Effect UV", m_fMeshFinishEffectUV, 1.0f, 0.0f, 1.0f);
		ImGui::Spacing();
	}
	else
	{
		m_fMeshStartEffectUV[0] = 0.0f;
		m_fMeshStartEffectUV[1] = 0.0f;
		m_fMeshFinishEffectUV[0] = 1.0f;
		m_fMeshFinishEffectUV[1] = 1.0f;
	}

	// 이펙트 uv를 업데이트합니다.
	if (m_spCurEffectMeshData)
	{
		m_spCurEffectMeshData->SetUVProperty
		(
			m_bUseMeshEffectUV,
			{ m_fMeshStartEffectUV[0], m_fMeshStartEffectUV[1] },
			{ m_fMeshFinishEffectUV[0], m_fMeshFinishEffectUV[1] }
		);
	}

	/********************
		이펙트 색상
	********************/
	// 이펙트 색상
	ImGui::SeparatorText("Mesh Effect Color");
	ImGui::TextWrapped("Mesh Start Color"); ImGui::SameLine();
	ImGui::ColorEdit4("##MeshStartColor", &m_vMeshStartColor.x, ImGuiColorEditFlags_NoInputs);
	ImGui::Spacing();

	ImGui::TextWrapped("Mesh Finish Color"); ImGui::SameLine();
	ImGui::ColorEdit4("##MeshFinishColor", &m_vMeshFinishColor.x, ImGuiColorEditFlags_NoInputs);
	ImGui::Spacing();

	// 이펙트 색상을 업데이트합니다.
	if (m_spCurEffectMeshData)
	{
		m_spCurEffectMeshData->SetColorProperty
		(
			m_vMeshStartColor,
			m_vMeshFinishColor
		);
	}

	/********************
		이펙트 트랜스폼
	********************/
	// 이펙트 트랜스폼
	ImGui::SeparatorText("Mesh Transform");
	ImGui::InputFloat3("Mesh Start Scale", reinterpret_cast<float*>(&m_vMeshStartScale));
	ImGui::InputFloat3("Mesh Start Rotate", reinterpret_cast<float*>(&m_vMeshStartRotate));
	ImGui::InputFloat3("Mesh Start Translate", reinterpret_cast<float*>(&m_vMeshStartTranslate));
	ImGui::Spacing();

	ImGui::InputFloat3("Mesh Finish Scale", reinterpret_cast<float*>(&m_vMeshFinishScale));
	ImGui::InputFloat3("Mesh Finish Rotate", reinterpret_cast<float*>(&m_vMeshFinishRotate));
	ImGui::InputFloat3("Mesh Finish Translate", reinterpret_cast<float*>(&m_vMeshFinishTranslate));
	ImGui::Spacing();

	// 이펙트 트랜스폼을 업데이트합니다.
	if (m_spCurEffectMeshData)
	{
		m_spCurEffectMeshData->SetTransformProperty
		(
			m_vMeshStartScale, m_vMeshStartRotate, m_vMeshStartTranslate,
			m_vMeshFinishScale, m_vMeshFinishRotate, m_vMeshFinishTranslate
		);
	}

	/********************
		이펙트 재생
	********************/
	// 싱글 이펙트 프로토타입
	ImGui::SeparatorText("Mesh Effect Prototype");
	if (ImGui::Button("Play Mesh Effect"))
	{
		if (m_spCurEffectMeshData)
		{
			m_spCurEffectMeshData->SetEffectMeshDataState(EEffectMeshDataState::PLAY);
		}
	}
	ImGui::SameLine();

	if (ImGui::Button("Stop Mesh Effect"))
	{
		if (m_spCurEffectMeshData)
		{
			m_spCurEffectMeshData->SetEffectMeshDataState(EEffectMeshDataState::STOP);
		}
	}
	ImGui::SameLine();

	if (ImGui::Button("Reset Mesh Effect"))
	{
		if (m_spCurEffectMeshData)
		{
			m_spCurEffectMeshData->SetEffectMeshDataState(EEffectMeshDataState::RESET);
		}
	}

	ImGui::SeparatorText("Mesh Effect Prototypes");
	if (ImGui::Button("Play Mesh Effects"))
	{
		for (const auto& pair : m_vecEffectMeshData)
		{
			pair.second->SetEffectMeshDataState(EEffectMeshDataState::PLAY);
		}
	}
	ImGui::SameLine();

	if (ImGui::Button("Stop Mesh Effects"))
	{
		for (const auto& pair : m_vecEffectMeshData)
		{
			pair.second->SetEffectMeshDataState(EEffectMeshDataState::STOP);
		}
	}
	ImGui::SameLine();

	if (ImGui::Button("Reset Mesh Effects"))
	{
		for (const auto& pair : m_vecEffectMeshData)
		{
			pair.second->SetEffectMeshDataState(EEffectMeshDataState::RESET);
		}
	}

	/**************************
		메시 이펙트 저장하기
	**************************/
	ImGui::SeparatorText("Save Mesh");
	ImGui::InputTextWithHint("##SaveMeshFile", "FX...", m_chSaveMeshEffectFileName, IM_ARRAYSIZE(m_chSaveMeshEffectFileName));

	if (ImGui::Button("Save Mesh Effects"))
	{
		string strFileName(m_chSaveMeshEffectFileName);
		string strPath = m_strMeshEffectFilePath + strFileName + ".dat";

		std::ofstream outFile;
		outFile.open(strPath.c_str(), ios_base::out | ios_base::binary | ios_base::trunc);

		ZeroMemory(m_chSaveMeshEffectFileName, MAX_PATH);

		// 파일이 열리지 않은 경우
		if (!outFile.is_open()) { return; }

		// 이펙트 메시들을 저장합니다.

		// 이펙트 개수를 씁니다.
		uint32 iNumEffectMeshData = static_cast<uint32>(m_vecEffectMeshData.size());
		outFile.write(reinterpret_cast<char*>(&iNumEffectMeshData), sizeof(uint32));

		for (const auto& pair : m_vecEffectMeshData)
		{
			// 이펙트 메시 데이터 이름
			{
				wstring wstrEffectMeshDataName = pair.first;
				uint32 iEffectMeshDataNameLength = static_cast<uint32>(wstrEffectMeshDataName.length());

				string strEffectMeshDataName = "";
				strEffectMeshDataName.assign(wstrEffectMeshDataName.begin(), wstrEffectMeshDataName.end());

				outFile.write(reinterpret_cast<char*>(&iEffectMeshDataNameLength), sizeof(uint32));
				outFile.write(strEffectMeshDataName.c_str(), iEffectMeshDataNameLength);
			}

			// 메시 이름
			{
				wstring wstrEffectModelDescName = pair.second->GetEffectModelDesc();
				uint32 iEffectModelDescNameLength = static_cast<uint32>(wstrEffectModelDescName.length());

				string strEffectModelDescName = "";
				strEffectModelDescName.assign(wstrEffectModelDescName.begin(), wstrEffectModelDescName.end());

				outFile.write(reinterpret_cast<char*>(&iEffectModelDescNameLength), sizeof(uint32));
				outFile.write(strEffectModelDescName.c_str(), iEffectModelDescNameLength);
			}

			// 버텍스 셰이더 이름
			{
				wstring wstrVSDescName = pair.second->GetVertexShaderDescName();
				uint32 iVSDescNameLength = static_cast<uint32>(wstrVSDescName.length());

				string strVSDescName = "";
				strVSDescName.assign(wstrVSDescName.begin(), wstrVSDescName.end());

				outFile.write(reinterpret_cast<char*>(&iVSDescNameLength), sizeof(uint32));
				outFile.write(strVSDescName.c_str(), iVSDescNameLength);
			}

			// 픽셀 셰이더 이름
			{
				wstring wstrPSDescName = pair.second->GetPixelShaderDescName();
				uint32 iPSDescNameLength = static_cast<uint32>(wstrPSDescName.length());

				string strPSDescName = "";
				strPSDescName.assign(wstrPSDescName.begin(), wstrPSDescName.end());

				outFile.write(reinterpret_cast<char*>(&iPSDescNameLength), sizeof(uint32));
				outFile.write(strPSDescName.c_str(), iPSDescNameLength);
			}

			// 플레이 프로퍼티
			{
				FPlayEffectProperty tPlayProperty = pair.second->GetPlayProperty();
				outFile.write(reinterpret_cast<char*>(&tPlayProperty.m_fStartPlaySeconds), sizeof(float));
				outFile.write(reinterpret_cast<char*>(&tPlayProperty.m_fFinishPlaySeconds), sizeof(float));
				outFile.write(reinterpret_cast<char*>(&tPlayProperty.m_bLoop), sizeof(bool));
			}

			// 마스크 프로퍼티
			{
				FMaskEffectProperty tMaskProperty = pair.second->GetMaskProperty();
				outFile.write(reinterpret_cast<char*>(&tMaskProperty.m_bUseMask), sizeof(bool));
				outFile.write(reinterpret_cast<char*>(&tMaskProperty.m_bUseColorMask), sizeof(bool));

				wstring wstrMaskTextureName = tMaskProperty.m_wstrMaskTextureName;
				uint32 iMaskTextureNameLength = static_cast<uint32>(wstrMaskTextureName.length());

				string strMaskTextureName = "";
				strMaskTextureName.assign(wstrMaskTextureName.begin(), wstrMaskTextureName.end());

				outFile.write(reinterpret_cast<char*>(&iMaskTextureNameLength), sizeof(uint32));
				outFile.write(strMaskTextureName.c_str(), iMaskTextureNameLength);


				outFile.write(reinterpret_cast<char*>(&tMaskProperty.m_iMaskRowColume[0]), sizeof(int32));
				outFile.write(reinterpret_cast<char*>(&tMaskProperty.m_iMaskRowColume[1]), sizeof(int32));
				outFile.write(reinterpret_cast<char*>(&tMaskProperty.m_vMaskUVSpeed), sizeof(Vector2));
				outFile.write(reinterpret_cast<char*>(&tMaskProperty.m_vMaskMaxUV), sizeof(Vector2));
			}

			// 노이즈 프로퍼티
			{
				FNoiseEffectProperty tNoiseProperty = pair.second->GetNoiseProperty();
				outFile.write(reinterpret_cast<char*>(&tNoiseProperty.m_bUseNoise), sizeof(bool));


				wstring wstrNoiseTextureName = tNoiseProperty.m_wstrNoiseTextureName;
				uint32 iNoiseTextureNameLength = static_cast<uint32>(wstrNoiseTextureName.length());

				string strNoiseTextureName = "";
				strNoiseTextureName.assign(wstrNoiseTextureName.begin(), wstrNoiseTextureName.end());

				outFile.write(reinterpret_cast<char*>(&iNoiseTextureNameLength), sizeof(uint32));
				outFile.write(strNoiseTextureName.c_str(), iNoiseTextureNameLength);


				outFile.write(reinterpret_cast<char*>(&tNoiseProperty.m_iNoiseRowColume[0]), sizeof(int32));
				outFile.write(reinterpret_cast<char*>(&tNoiseProperty.m_iNoiseRowColume[1]), sizeof(int32));
				outFile.write(reinterpret_cast<char*>(&tNoiseProperty.m_vNoiseUVSpeed), sizeof(Vector2));
				outFile.write(reinterpret_cast<char*>(&tNoiseProperty.m_vNoiseMaxUV), sizeof(Vector2));
			}

			// 색상 프로퍼티
			{
				FColorEffectProperty tColorProperty = pair.second->GetColorProperty();
				outFile.write(reinterpret_cast<char*>(&tColorProperty.m_vStartColor), sizeof(Vector4));
				outFile.write(reinterpret_cast<char*>(&tColorProperty.m_vFinishColor), sizeof(Vector4));
			}

			// 트랜스폼 프로퍼티
			{
				FTransformEffectProperty tTransformProperty = pair.second->GetTransformProperty();
				outFile.write(reinterpret_cast<char*>(&tTransformProperty.m_vStartScale), sizeof(Vector3));
				outFile.write(reinterpret_cast<char*>(&tTransformProperty.m_vStartRotate), sizeof(Vector3));
				outFile.write(reinterpret_cast<char*>(&tTransformProperty.m_vStartTranslate), sizeof(Vector3));
				outFile.write(reinterpret_cast<char*>(&tTransformProperty.m_vFinishScale), sizeof(Vector3));
				outFile.write(reinterpret_cast<char*>(&tTransformProperty.m_vFinishRotate), sizeof(Vector3));
				outFile.write(reinterpret_cast<char*>(&tTransformProperty.m_vFinishTranslate), sizeof(Vector3));
			}

			// UV 프로퍼티
			{
				FUVEffectProperty tUVProperty = pair.second->GetUVProperty();
				outFile.write(reinterpret_cast<char*>(&tUVProperty.m_bUseEffectUV), sizeof(bool));
				outFile.write(reinterpret_cast<char*>(&tUVProperty.m_vEffectStartUV), sizeof(Vector2));
				outFile.write(reinterpret_cast<char*>(&tUVProperty.m_vEffectFinishUV), sizeof(Vector2));
			}
		}

	}

	/**************************
		메시 이펙트 불러오기
	**************************/
	ImGui::SeparatorText("Load Mesh");
	ImGui::InputTextWithHint("##LoadMeshFile", "FX...", m_chLoadMeshEffectFileName, IM_ARRAYSIZE(m_chLoadMeshEffectFileName));

	if (ImGui::Button("Load Mesh Effects"))
	{
		string strFileName(m_chLoadMeshEffectFileName);
		string strPath = m_strMeshEffectFilePath + strFileName + ".dat";

		std::ifstream inFile;
		inFile.open(strPath.c_str(), ios_base::in | ios_base::binary);

		ZeroMemory(m_chLoadMeshEffectFileName, MAX_PATH);

		// 파일이 열리지 않은 경우
		if (!inFile.is_open()) { return; }

		// 이펙트 메시들을 불러옵니다.

		// 이펙트 개수를 읽습니다.
		uint32 iNumEffectMeshData = 0;
		inFile.read(reinterpret_cast<char*>(&iNumEffectMeshData), sizeof(uint32));

		for (uint32 iIndex = 0; iIndex < iNumEffectMeshData; ++iIndex)
		{
			// 이펙트 메시 데이터 이름
			uint32 iEffectMeshDataNameLength = 0;
			inFile.read(reinterpret_cast<char*>(&iEffectMeshDataNameLength), sizeof(uint32));

			string strEffectMeshDataName = "";
			strEffectMeshDataName.resize(iEffectMeshDataNameLength);
			inFile.read(strEffectMeshDataName.data(), iEffectMeshDataNameLength);

			wstring wstrEffectMeshDataName = L"";
			wstrEffectMeshDataName.assign(strEffectMeshDataName.begin(), strEffectMeshDataName.end());


			// 메시 이름
			uint32 iEffectModelDescNameLength = 0;
			inFile.read(reinterpret_cast<char*>(&iEffectModelDescNameLength), sizeof(uint32));

			string strEffectModelDescName = "";
			strEffectModelDescName.resize(iEffectModelDescNameLength);
			inFile.read(strEffectModelDescName.data(), iEffectModelDescNameLength);

			wstring wstrEffectModelDescName = L"";
			wstrEffectModelDescName.assign(strEffectModelDescName.begin(), strEffectModelDescName.end());


			// 버텍스 셰이더 이름
			uint32 iVSDescNameLength = 0;
			inFile.read(reinterpret_cast<char*>(&iVSDescNameLength), sizeof(uint32));

			string strVSDescName = "";
			strVSDescName.resize(iVSDescNameLength);
			inFile.read(strVSDescName.data(), iVSDescNameLength);

			wstring wstrVSDescName = L"";
			wstrVSDescName.assign(strVSDescName.begin(), strVSDescName.end());


			// 픽셀 셰이더 이름
			uint32 iPSDescNameLength = 0;
			inFile.read(reinterpret_cast<char*>(&iPSDescNameLength), sizeof(uint32));

			string strPSDescName = "";
			strPSDescName.resize(iPSDescNameLength);
			inFile.read(strPSDescName.data(), iPSDescNameLength);

			wstring wstrPSDescName = L"";
			wstrPSDescName.assign(strPSDescName.begin(), strPSDescName.end());


			// 플레이 프로퍼티
			FPlayEffectProperty tPlayProperty;
			inFile.read(reinterpret_cast<char*>(&tPlayProperty.m_fStartPlaySeconds), sizeof(float));
			inFile.read(reinterpret_cast<char*>(&tPlayProperty.m_fFinishPlaySeconds), sizeof(float));
			inFile.read(reinterpret_cast<char*>(&tPlayProperty.m_bLoop), sizeof(bool));


			// 마스크 프로퍼티
			FMaskEffectProperty tMaskProperty;
			inFile.read(reinterpret_cast<char*>(&tMaskProperty.m_bUseMask), sizeof(bool));
			inFile.read(reinterpret_cast<char*>(&tMaskProperty.m_bUseColorMask), sizeof(bool));

			uint32 iMaskTextureNameLength = 0;
			inFile.read(reinterpret_cast<char*>(&iMaskTextureNameLength), sizeof(uint32));

			string strMaskTextureName = "";
			strMaskTextureName.resize(iMaskTextureNameLength);
			inFile.read(strMaskTextureName.data(), iMaskTextureNameLength);

			wstring wstrMaskTextureName = L"";
			wstrMaskTextureName.assign(strMaskTextureName.begin(), strMaskTextureName.end());

			inFile.read(reinterpret_cast<char*>(&tMaskProperty.m_iMaskRowColume[0]), sizeof(int32));
			inFile.read(reinterpret_cast<char*>(&tMaskProperty.m_iMaskRowColume[1]), sizeof(int32));
			inFile.read(reinterpret_cast<char*>(&tMaskProperty.m_vMaskUVSpeed), sizeof(Vector2));
			inFile.read(reinterpret_cast<char*>(&tMaskProperty.m_vMaskMaxUV), sizeof(Vector2));


			// 노이즈 프로퍼티
			FNoiseEffectProperty tNoiseProperty;
			inFile.read(reinterpret_cast<char*>(&tNoiseProperty.m_bUseNoise), sizeof(bool));

			uint32 iNoiseTextureNameLength = 0;
			inFile.read(reinterpret_cast<char*>(&iNoiseTextureNameLength), sizeof(uint32));

			string strNoiseTextureName = "";
			strNoiseTextureName.resize(iNoiseTextureNameLength);
			inFile.read(strNoiseTextureName.data(), iNoiseTextureNameLength);

			wstring wstrNoiseTextureName = L"";
			wstrNoiseTextureName.assign(strNoiseTextureName.begin(), strNoiseTextureName.end());


			inFile.read(reinterpret_cast<char*>(&tNoiseProperty.m_iNoiseRowColume[0]), sizeof(int32));
			inFile.read(reinterpret_cast<char*>(&tNoiseProperty.m_iNoiseRowColume[1]), sizeof(int32));
			inFile.read(reinterpret_cast<char*>(&tNoiseProperty.m_vNoiseUVSpeed), sizeof(Vector2));
			inFile.read(reinterpret_cast<char*>(&tNoiseProperty.m_vNoiseMaxUV), sizeof(Vector2));


			// 색상 프로퍼티
			FColorEffectProperty tColorProperty;
			inFile.read(reinterpret_cast<char*>(&tColorProperty.m_vStartColor), sizeof(Vector4));
			inFile.read(reinterpret_cast<char*>(&tColorProperty.m_vFinishColor), sizeof(Vector4));


			// 트랜스폼 프로퍼티
			FTransformEffectProperty tTransformProperty;
			inFile.read(reinterpret_cast<char*>(&tTransformProperty.m_vStartScale), sizeof(Vector3));
			inFile.read(reinterpret_cast<char*>(&tTransformProperty.m_vStartRotate), sizeof(Vector3));
			inFile.read(reinterpret_cast<char*>(&tTransformProperty.m_vStartTranslate), sizeof(Vector3));
			inFile.read(reinterpret_cast<char*>(&tTransformProperty.m_vFinishScale), sizeof(Vector3));
			inFile.read(reinterpret_cast<char*>(&tTransformProperty.m_vFinishRotate), sizeof(Vector3));
			inFile.read(reinterpret_cast<char*>(&tTransformProperty.m_vFinishTranslate), sizeof(Vector3));


			// UV 프로퍼티
			FUVEffectProperty tUVProperty;
			inFile.read(reinterpret_cast<char*>(&tUVProperty.m_bUseEffectUV), sizeof(bool));
			inFile.read(reinterpret_cast<char*>(&tUVProperty.m_vEffectStartUV), sizeof(Vector2));
			inFile.read(reinterpret_cast<char*>(&tUVProperty.m_vEffectFinishUV), sizeof(Vector2));


			shared_ptr<CEffectMeshData> spEffectMeshData = CEffectMeshData::Create(m_wpEffectComponent.lock());
			m_vecEffectMeshData.push_back({ wstrEffectMeshDataName, spEffectMeshData });
			
			spEffectMeshData->SetPlayProperty
			(
				tPlayProperty.m_fStartPlaySeconds,
				tPlayProperty.m_fFinishPlaySeconds,
				tPlayProperty.m_bLoop
			);
			
			spEffectMeshData->SetMaskProperty
			(
				tMaskProperty.m_bUseMask,
				tMaskProperty.m_bUseColorMask,
				tMaskProperty.m_iMaskRowColume[0],
				tMaskProperty.m_iMaskRowColume[1],
				tMaskProperty.m_vMaskUVSpeed,
				tMaskProperty.m_vMaskMaxUV
			);

			spEffectMeshData->SetNoiseProperty
			(
				tNoiseProperty.m_bUseNoise,
				tNoiseProperty.m_iNoiseRowColume[0],
				tNoiseProperty.m_iNoiseRowColume[1],
				tNoiseProperty.m_vNoiseUVSpeed,
				tNoiseProperty.m_vNoiseMaxUV
			);
			
			spEffectMeshData->SetColorProperty
			(
				tColorProperty.m_vStartColor,
				tColorProperty.m_vFinishColor
			);
			
			spEffectMeshData->SetTransformProperty
			(
				tTransformProperty.m_vStartScale,
				tTransformProperty.m_vStartRotate,
				tTransformProperty.m_vStartTranslate,
				tTransformProperty.m_vFinishScale,
				tTransformProperty.m_vFinishRotate,
				tTransformProperty.m_vFinishTranslate
			);
			
			spEffectMeshData->SetUVProperty
			(
				tUVProperty.m_bUseEffectUV,
				tUVProperty.m_vEffectStartUV,
				tUVProperty.m_vEffectFinishUV
			);

			spEffectMeshData->ChangeEffectModelDesc(wstrEffectModelDescName);
			spEffectMeshData->ChangeShaders(m_wpEffectComponent.lock(), wstrVSDescName, wstrPSDescName);
			spEffectMeshData->ModifyPixelShaderTexture(0, 0, wstrMaskTextureName);

			m_wpEffectComponent.lock()->AddMeshEffect(wstrEffectMeshDataName, spEffectMeshData);
		}
	}
	ImGui::SameLine();
}

void Editor::CEffectWindow::TickSeparaterParticleEffect()
{
	/**************************
		이펙트 파티클 데이터
	**************************/
	// 이펙트 파티클 데이터 목록들
	/*
	ImGui::SeparatorText("Particle Effect Data");
	if (ImGui::BeginListBox("##ParticleEffectData", ImVec2(-FLT_MIN, 5 * ImGui::GetTextLineHeightWithSpacing())))
	{
		for (size_t iIndex = 0; iIndex < m_vecEffectParticleData.size(); ++iIndex)
		{
			wstring wstrEffectParticleDataName = m_vecEffectParticleData[iIndex].first;
			string strEffectParticleDataName(wstrEffectParticleDataName.begin(), wstrEffectParticleDataName.end());

			if (ImGui::Selectable(strEffectParticleDataName.c_str(), true))
			{
				// 이전 이펙트를 끕니다.
				if (m_spCurEffectParticleData)
				{
					m_spCurEffectParticleData->SetEffectParticleDataState(EEffectParticleDataState::OFF);
				}

				m_iCurEffectParticleDataIndex = static_cast<int32>(iIndex);
				m_spCurEffectParticleData = m_vecEffectParticleData[iIndex].second;

				// 현재 이펙트를 켭니다.
				m_spCurEffectParticleData->SetEffectParticleDataState(EEffectParticleDataState::ON);

			}
		}
		ImGui::EndListBox();
	}
	*/

	// 이펙트 파티클 데이터를 생성합니다.
	/*
	ImGui::InputTextWithHint("##EffectParticleDataName", "EffectParticleDataName", m_chEffectParticleDataName, IM_ARRAYSIZE(m_chEffectParticleDataName));

	if (ImGui::Button("Create EPD"))
	{
		wstring wstrEPDName(m_chEffectParticleDataName, m_chEffectParticleDataName + strlen(m_chEffectParticleDataName));
		if (!wstrEPDName.empty())
		{
			bool bFound = false;
			for (const auto& pair : m_vecEffectParticleData)
			{
				if (pair.first == wstrEPDName)
				{
					bFound = true;
					break;
				}
			}

			if (!bFound)
			{
				shared_ptr<CEffectParticleData> spEffectParticleData = CEffectParticleData::Create(m_wpEffectComponent.lock(), L"", L"", L"");
				m_vecEffectParticleData.push_back({ wstrEPDName, spEffectParticleData });
				m_wpEffectComponent.lock()->AddParticleEffect(wstrEPDName, spEffectParticleData);
				ZeroMemory(m_chEffectParticleDataName, MAX_PATH);
			}
		}
	}
	ImGui::SameLine();
	*/

	// 이펙트 메시 데이터를 없앱니다.
	/*
	if (ImGui::Button("Remove EMD"))
	{
		if (m_iCurEffectMeshDataIndex < m_vecEffectMeshData.size())
		{
			m_wpEffectComponent.lock()->RemoveMeshEffect(m_vecEffectMeshData[m_iCurEffectMeshDataIndex].first);

			m_vecEffectMeshData[m_iCurEffectMeshDataIndex].second->Release();
			m_vecEffectMeshData[m_iCurEffectMeshDataIndex].second = nullptr;
			m_spCurEffectMeshData = nullptr;

			auto iter = m_vecEffectMeshData.begin() + m_iCurEffectMeshDataIndex;
			m_vecEffectMeshData.erase(iter);
		}
	}
	*/
}
