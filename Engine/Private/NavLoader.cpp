#include "pch.h"
#include "NavLoader.h"

#include "Cell.h"
#include "NavHandler.h"

std::shared_ptr<CNavLoader> Engine::CNavLoader::Create()
{
	const std::shared_ptr<CNavLoader> spLoader = make_shared<CNavLoader>();
	ENSUREF(spLoader->Initialize(), L"Failed to create nav loader.");
	return spLoader;
}

HRESULT Engine::CNavLoader::Initialize()
{
	m_wpNavHandler = CNavHandler::GetInstance();
	m_wpDeviceManager = CNavHandler::GetInstance()->GetDeviceManager();

	// �ܺο��� ������ �ҷ��ɴϴ�.
	LoadNavigationFromFile();
	return S_OK;
}

void Engine::CNavLoader::Release()
{
}

HRESULT Engine::CNavLoader::LoadNavigationFromFile()
{
	for (const std::filesystem::directory_entry& fsEntry : filesystem::recursive_directory_iterator(m_wstrNavigationFilePath))
	{
		// ������ �ƴ� ���
		if (!filesystem::is_regular_file(fsEntry)) { continue; }

		// dat ������ �ƴ� ���
		if (fsEntry.path().extension().generic_string() != ".dat" && fsEntry.path().extension().generic_string() != ".DAT") { continue; }

		std::ifstream inFile;
		inFile.open(fsEntry.path().c_str(), ios_base::in | ios_base::binary);

		// ������ ������ ���� ���
		if (!inFile.is_open()) { return E_FAIL; }

		// �� Ÿ���� �н��ϴ�.
		int8 iModelType = (int8)EModelType::NAVIGATION;
		inFile.read((char*)&iModelType, sizeof(int8));

		LoadCell(inFile, fsEntry);

		inFile.close();
	}
	return S_OK;
}

void Engine::CNavLoader::LoadCell(std::ifstream& _inFile, const std::filesystem::directory_entry& _fsEntry)
{
	// �޽��� ������ �н��ϴ�.
	uint32 iNumMeshes = 0;
	_inFile.read(reinterpret_cast<char*>(&iNumMeshes), sizeof(uint32));

	CHECK(iNumMeshes == 1);

	// �޽��� �̸��� �н��ϴ�.
	uint32 iMeshNameLength = 0;
	_inFile.read(reinterpret_cast<char*>(&iMeshNameLength), sizeof(uint32));

	string strMeshName;
	strMeshName.reserve(iMeshNameLength);
	_inFile.read(strMeshName.data(), iMeshNameLength);

	// ���ؽ� �����͸� �н��ϴ�.
	uint64 iVertexSize = 0;
	_inFile.read(reinterpret_cast<char*>(&iVertexSize), sizeof(uint64));

	vector<TPosition> vecVertices;
	vecVertices.reserve(iVertexSize);
	vecVertices.resize(iVertexSize);
	_inFile.read(reinterpret_cast<char*>(vecVertices.data()), sizeof(TPosition) * iVertexSize);

	// �ε��� �����͸� �н��ϴ�.
	uint64 iIndexSize = 0;
	_inFile.read(reinterpret_cast<char*>(&iIndexSize), sizeof(uint64));

	vector<uint32> vecIndices;
	vecIndices.reserve(iIndexSize);
	vecIndices.resize(iIndexSize);
	_inFile.read(reinterpret_cast<char*>(vecIndices.data()), sizeof(uint32) * iIndexSize);

	// ���� ������ ���մϴ�.
	uint32 iNumCells = static_cast<uint32>(vecIndices.size() / 3);

	vector<std::shared_ptr<CCell>> vecCells;
	vecCells.reserve(iNumCells);

	for (uint32 iIndex = 0; iIndex < iNumCells; ++iIndex)
	{
		array<Vector3, (int8)ECellPoint::ENUM_END> arrPoints;
	
		// TODO; �ݽð� �����̹Ƿ� �� B�� �� C�� �ٲߴϴ�.(�̰� ���ұ�?) ���ϸ� ������ ������ �ٲ㼭 �δ����� �д� �� �� ����.
		arrPoints[(int8)ECellPoint::A] = vecVertices[vecIndices[3 * iIndex + 0]].m_vPosition;
		arrPoints[(int8)ECellPoint::C] = vecVertices[vecIndices[3 * iIndex + 1]].m_vPosition;
		arrPoints[(int8)ECellPoint::B] = vecVertices[vecIndices[3 * iIndex + 2]].m_vPosition;
		
		// �� ������ ���� �����մϴ�.
		shared_ptr<CCell> spCell = CCell::Create(arrPoints, static_cast<int32>(vecCells.size()));
		CHECK(spCell != nullptr);

		vecCells.push_back(spCell);
	}

	// �̿��� ���� �����մϴ�.
	for (auto& spSrcCell : vecCells)
	{
		for (auto& spDstCell : vecCells)
		{
			if (spSrcCell == spDstCell) { continue; }

			// ���� ���� ���翵�� �� ���� �̿��� ���� ���翵�� �� ���� ���մϴ�.
			if (true == spDstCell->IsNeighborLine(spSrcCell->GetOrthogonalPoint(ECellPoint::A), spSrcCell->GetOrthogonalPoint(ECellPoint::B)))
			{
				spSrcCell->SetNeighborCell(ECellLine::AB, spDstCell);
			}

			if (true == spDstCell->IsNeighborLine(spSrcCell->GetOrthogonalPoint(ECellPoint::B), spSrcCell->GetOrthogonalPoint(ECellPoint::C)))
			{
				spSrcCell->SetNeighborCell(ECellLine::BC, spDstCell);
			}

			if (true == spDstCell->IsNeighborLine(spSrcCell->GetOrthogonalPoint(ECellPoint::C), spSrcCell->GetOrthogonalPoint(ECellPoint::A)))
			{
				spSrcCell->SetNeighborCell(ECellLine::CA, spDstCell);
			}
		}
	}

	// ������ �̸��� ���մϴ�.
	wstring wstrFileName = _fsEntry.path().stem().generic_wstring();
	m_wpNavHandler.lock()->AddNavigation(wstrFileName, vecCells);
}
