#pragma once
#include "Level.h"

namespace Editor
{
	// location
	class CLocation;

	// survivors
	class CHyunwoo;
	class CYuki;
	class CAya;
	class CRozzi;

	// wild animals
	class CWildAnimal;
	class CChicken;
	class CBear;
	class CBoar;
	class CDog;
	class CWolf;

	// boss
	class CWickline;
	class CAlpha;
	class COmega;

	// tester
	class CEffectTester;

	class CEditorLevel final : public CLevel
	{
	/******************
		Ctor/Dtor
	******************/
	public:
		explicit CEditorLevel() = default;

		virtual ~CEditorLevel() = default;
		
	/******************
		Events
	******************/
	public:
		virtual HRESULT PreInitialize();

		virtual HRESULT Initialize();

		virtual HRESULT PostInitialize();
		
	/******************
		Methods
	******************/
	public:
		HRESULT AddLocations(const std::wstring& _wstrLocationName, const std::shared_ptr<CLocation>& _spLocation);

		HRESULT AddWildAnimal(EWildAnimalType _eWildAnimalType, const std::wstring& _wstrWildAnimalName, const std::shared_ptr<CWildAnimal>& _spWildAnimal);

		int32 GetWildAnimalSize(EWildAnimalType _eWildAnimalType);

	public:
		HRESULT RemoveLocations(const std::wstring& _wstrLocationName);

		HRESULT RemoveWildAnimal(EWildAnimalType _eWildAnimalType, const std::wstring& _wstrWildAnimalName);

	/******************
		Getter/Setter
	******************/
	public:
		const std::unordered_map<std::wstring, std::weak_ptr<CLocation>>& GetLocations() { return m_umapLocations; }

		const std::unordered_map<std::wstring, std::weak_ptr<CBear>>& GetBears() { return m_umapBears; }

		const std::unordered_map<std::wstring, std::weak_ptr<CBoar>>& GetBoars() { return m_umapBoars; };

		const std::unordered_map<std::wstring, std::weak_ptr<CChicken>>& GetChickens() { return m_umapChickens; };

		const std::unordered_map<std::wstring, std::weak_ptr<CDog>>& GetDogs() { return m_umapDogs; } ;

		const std::unordered_map<std::wstring, std::weak_ptr<CWolf>>& GetWolfs() { return m_umapWolfs; };

	/******************
		Data Members
	******************/
	private:
		// effect
		std::weak_ptr<CEffectTester> m_wpEffectTester;

		// survivor
		std::weak_ptr<CHyunwoo> m_wpHyunwoo;

		std::weak_ptr<CYuki> m_wpYuki;

		std::weak_ptr<CAya> m_wpAya;

		std::weak_ptr<CRozzi> m_wpRozzi;

		// Location
		std::unordered_map<std::wstring, std::weak_ptr<CLocation>> m_umapLocations;

		// Wild animal
		std::unordered_map<std::wstring, std::weak_ptr<CBear>> m_umapBears;

		std::unordered_map<std::wstring, std::weak_ptr<CBoar>> m_umapBoars;

		std::unordered_map<std::wstring, std::weak_ptr<CChicken>> m_umapChickens;

		std::unordered_map<std::wstring, std::weak_ptr<CDog>> m_umapDogs;

		std::unordered_map<std::wstring, std::weak_ptr<CWolf>> m_umapWolfs;

		// Boss
		std::weak_ptr<CWickline> m_wpWickline;

		std::weak_ptr<CAlpha> m_wpAlpha;

		std::weak_ptr<COmega> m_wpOmega;
	};
}
