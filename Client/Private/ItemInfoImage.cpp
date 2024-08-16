#include "pch.h"
#include "ItemInfoImage.h"

HRESULT Client::CItemInfoImage::PreInitialize()
{
	SetActorRenderType(ERenderType::TRANSLUCENT_USER_INTERFACE);
	SetPrimitiveType(EPrimitiveType::POINT);

	SetImageNames
	(
		{
			// µ¹, ³ª¹µ°¡Áö, °¡Á×
			L"ItemIcon_108101",
			L"ItemIcon_112101",
			L"ItemIcon_401103",

			// ÀÏ¹Ý Àç·á
			L"ItemIcon_101101",
			L"ItemIcon_101102",
			L"ItemIcon_105102",

			L"ItemIcon_112103",
			L"ItemIcon_112104",
			L"ItemIcon_113102",
			L"ItemIcon_113104",
			L"ItemIcon_205101",
			L"ItemIcon_205102",
			L"ItemIcon_205103",
			L"ItemIcon_205106",
			L"ItemIcon_205108",
			L"ItemIcon_205109",
			L"ItemIcon_205110",
			L"ItemIcon_401101",
			L"ItemIcon_401104",
			L"ItemIcon_401105",
			L"ItemIcon_401106",
			L"ItemIcon_401107",
			L"ItemIcon_401108",
			L"ItemIcon_401109",
			L"ItemIcon_401110",
			L"ItemIcon_401112",
			L"ItemIcon_401113",
			L"ItemIcon_401114",
			L"ItemIcon_401116",
			L"ItemIcon_401117",
			L"ItemIcon_401121",
			L"ItemIcon_502104",

			// ÀÏ¹Ý ¹«±â
			L"ItemIcon_110102",
			L"ItemIcon_111101",
			L"ItemIcon_102101",
			L"ItemIcon_116101",
			L"ItemIcon_104101",

			// ÀÏ¹Ý ¿Ê
			L"ItemIcon_202101",
			L"ItemIcon_202103",
			L"ItemIcon_202105",
			L"ItemIcon_202106",

			// ÀÏ¹Ý ¸Ó¸®
			L"ItemIcon_201101",
			L"ItemIcon_201102",
			L"ItemIcon_201104",

			// ÀÏ¹Ý ÆÈ
			L"ItemIcon_203101",
			L"ItemIcon_203102",
			L"ItemIcon_203104",

			// ÀÏ¹Ý ´Ù¸®
			L"ItemIcon_204101",
			L"ItemIcon_204102",
			L"ItemIcon_204103",

			// °í±Þ Àç·á
			L"ItemIcon_205203",
			L"ItemIcon_205204",
			L"ItemIcon_205206",
			L"ItemIcon_205207",
			L"ItemIcon_205208",
			L"ItemIcon_205209",
			L"ItemIcon_205211",
			L"ItemIcon_205213",
			L"ItemIcon_401202",
			L"ItemIcon_401206",
			L"ItemIcon_401210",
			L"ItemIcon_401211",
			L"ItemIcon_401212",
			L"ItemIcon_401213",
			L"ItemIcon_401214",
			L"ItemIcon_401215",
			L"ItemIcon_401216",
			L"ItemIcon_401217",
			L"ItemIcon_401218",
			L"ItemIcon_401306",

			// Èñ±Í Àç·á
			L"ItemIcon_205312",
			L"ItemIcon_401303",
			L"ItemIcon_401305",

			// ¿µ¿õ Àç·á
			L"ItemIcon_205402",
			L"ItemIcon_205403",
			L"ItemIcon_401208",
			L"ItemIcon_401209",
			L"ItemIcon_401301",
			L"ItemIcon_401304",
			L"ItemIcon_401401",
			L"ItemIcon_401402",
			L"ItemIcon_401403",

			// ÀÏ¹Ý À½½Ä
			L"ItemIcon_301111",
			L"ItemIcon_301110",
			L"ItemIcon_301113",
			L"ItemIcon_301119",

			// ÀÏ¹Ý À½·á
			L"ItemIcon_302101",
			L"ItemIcon_302102",
			L"ItemIcon_302104",
			L"ItemIcon_302107",

			// °í±Þ ±Û·¯ºê
			L"ItemIcon_110201",
			L"ItemIcon_110202",

			// Èñ±Í ±Û·¯ºê
			L"ItemIcon_110301",
			L"ItemIcon_110302",
			L"ItemIcon_110401",
			L"ItemIcon_110402",
			L"ItemIcon_110404",

			// ¿µ¿õ ±Û·¯ºê
			L"ItemIcon_110405",
			L"ItemIcon_110406",
			L"ItemIcon_110407",
			L"ItemIcon_110408",
			L"ItemIcon_110409",
			L"ItemIcon_110410",
			L"ItemIcon_110411",

			// °í±Þ ¾ç¼Õ°Ë
			L"ItemIcon_102401",

			// Èñ±Í ¾ç¼Õ°Ë
			L"ItemIcon_102301",
			L"ItemIcon_102402",
			L"ItemIcon_102403",
			L"ItemIcon_102404",

			// ¿µ¿õ ¾ç¼Õ°Ë
			L"ItemIcon_102405",
			L"ItemIcon_102406",
			L"ItemIcon_102407",
			L"ItemIcon_102410",
			L"ItemIcon_102411",
			L"ItemIcon_102413",

			// °í±Þ ÇÇ½ºÅç
			L"ItemIcon_116201",
			L"ItemIcon_116202",

			// Èñ±Í ÇÇ½ºÅç
			L"ItemIcon_116301",
			L"ItemIcon_116402",
			L"ItemIcon_116408",

			// ¿µ¿õ ÇÇ½ºÅç
			L"ItemIcon_116404",
			L"ItemIcon_116405",
			L"ItemIcon_116406",
			L"ItemIcon_116407",
			L"ItemIcon_116409",

			// °í±Þ ¿Ê
			L"ItemIcon_202201",
			L"ItemIcon_202202",
			L"ItemIcon_202205",
			L"ItemIcon_202206",
			L"ItemIcon_202207",
			L"ItemIcon_202209",
			L"ItemIcon_202210",
			L"ItemIcon_202211",


			// Èñ±Í ¿Ê
			L"ItemIcon_202301",
			L"ItemIcon_202302",
			L"ItemIcon_202303",
			L"ItemIcon_202304",
			L"ItemIcon_202305",
			L"ItemIcon_202306",
			L"ItemIcon_202401",


			// ¿µ¿õ ¿Ê
			L"ItemIcon_202307",
			L"ItemIcon_202402",
			L"ItemIcon_202404",
			L"ItemIcon_202405",
			L"ItemIcon_202406",
			L"ItemIcon_202408",
			L"ItemIcon_202410",
			L"ItemIcon_202411",
			L"ItemIcon_202412",
			L"ItemIcon_202413",
			L"ItemIcon_202415",
			L"ItemIcon_202417",
			L"ItemIcon_202418",
			L"ItemIcon_202419",
			L"ItemIcon_202414",

			// °í±Þ ¸Ó¸®
			L"ItemIcon_201201",
			L"ItemIcon_201202",
			L"ItemIcon_201203",
			L"ItemIcon_201204",
			L"ItemIcon_201205",

			// Èñ±Í ¸Ó¸®
			L"ItemIcon_201301",
			L"ItemIcon_201302",
			L"ItemIcon_201303",
			L"ItemIcon_201401",
			L"ItemIcon_201402",

			// ¿µ¿õ ¸Ó¸®
			L"ItemIcon_201304",
			L"ItemIcon_201404",
			L"ItemIcon_201405",
			L"ItemIcon_201406",
			L"ItemIcon_201407",
			L"ItemIcon_201409",
			L"ItemIcon_201410",
			L"ItemIcon_201412",
			L"ItemIcon_201413",
			L"ItemIcon_201414",
			L"ItemIcon_201415",

			// °í±Þ ÆÈ
			L"ItemIcon_203201",
			L"ItemIcon_203202",
			L"ItemIcon_203203",
			L"ItemIcon_203204",

			// Èñ±Í ÆÈ
			L"ItemIcon_203301",
			L"ItemIcon_203302",
			L"ItemIcon_203303",
			L"ItemIcon_203304",
			L"ItemIcon_203305",
			L"ItemIcon_203401",

			// ¿µ¿õ ÆÈ
			L"ItemIcon_203306",
			L"ItemIcon_203402",
			L"ItemIcon_203403",
			L"ItemIcon_203405",
			L"ItemIcon_203406",
			L"ItemIcon_203407",
			L"ItemIcon_203409",
			L"ItemIcon_203410",
			L"ItemIcon_203411",
			L"ItemIcon_203412",
			L"ItemIcon_203414",
			L"ItemIcon_203506",

			// °í±Þ ´Ù¸®
			L"ItemIcon_204201",
			L"ItemIcon_204202",
			L"ItemIcon_204203",
			L"ItemIcon_204204",
			L"ItemIcon_204205",
			L"ItemIcon_204301",
			L"ItemIcon_204302",

			// Èñ±Í ´Ù¸®
			L"ItemIcon_204401",
			L"ItemIcon_204404",

			// ¿µ¿õ ´Ù¸®
			L"ItemIcon_204303",
			L"ItemIcon_204304",
			L"ItemIcon_204402",
			L"ItemIcon_204403",
			L"ItemIcon_204406",
			L"ItemIcon_204408",
			L"ItemIcon_204409",
			L"ItemIcon_204411",
			L"ItemIcon_204412",
			L"ItemIcon_204415",

			// °í±Þ À½·á
			L"ItemIcon_302201",
			L"ItemIcon_302209",
			L"ItemIcon_302213",
			L"ItemIcon_302215",
		}
	);

	return CImage::PreInitialize();
}

HRESULT Client::CItemInfoImage::Initialize()
{
	SetWidth(55.0f);
	SetHeight(50.0f);
	SetPivot({ 944.0f, 438.0f });
	return CImage::Initialize();
}

HRESULT Client::CItemInfoImage::PostInitialize()
{
	if (FAILED(CImage::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CItemInfoImage::BeginPlay()
{
	if (FAILED(CImage::BeginPlay())) { return E_FAIL; }

	SetTextureIndex(0);
	return S_OK;
}

int32 Client::CItemInfoImage::PreTick(float _fDeltaSeconds)
{
	if (!m_bActive) { return 0; }

	switch (CImage::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CItemInfoImage::Tick(float _fDeltaSeconds)
{
	if (!m_bActive) { return 0; }

	switch (CImage::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CItemInfoImage::PostTick(float _fDeltaSeconds)
{
	if (!m_bActive) { return 0; }

	switch (CImage::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Client::CItemInfoImage::EndPlay()
{
	if (FAILED(CImage::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Client::CItemInfoImage::Render()
{
	if (!m_bActive) { return; }

	CImage::Render();
}

void Client::CItemInfoImage::Release()
{
	CImage::Release();
}
