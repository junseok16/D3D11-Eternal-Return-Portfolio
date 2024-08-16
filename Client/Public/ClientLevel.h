#pragma once
#include "Level.h"

namespace Client
{
	// survivors
	class CHyunwoo;
	class CAya;

	class CClientLevel : public CLevel
	{
	/******************
		Ctor/Dtor
	******************/
	public:
		explicit CClientLevel() = default;

		virtual ~CClientLevel() = default;
		
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
		HRESULT LoadLevelFromFile();

		HRESULT LoadWildAnimalFromFile(EWildAnimalType _eWildAnimalType);
		
	/******************
		Data Members
	******************/
	private:
		std::weak_ptr<CHyunwoo> m_wpHyunwoo;

		std::weak_ptr<CAya> m_wpAya;
	};
}
