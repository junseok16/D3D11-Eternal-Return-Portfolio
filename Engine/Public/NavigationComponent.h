#pragma once
#include "SceneComponent.h"

namespace Engine
{
	class CNavHandler;
	class CCell;

	class ENGINE_DLL CNavigationComponent final : public CSceneComponent
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CNavigationComponent() = default;

		virtual ~CNavigationComponent() = default;

	/********************
		Framework
	********************/
	public:
		virtual HRESULT PreInitializeComponent();

		virtual HRESULT InitializeComponent();

		virtual HRESULT PostInitializeComponent();

		virtual HRESULT BeginPlay();

		virtual int32 PreTickComponent(float _fDeltaSeconds);

		virtual int32 TickComponent(float _fDeltaSeconds);

		virtual int32 PostTickComponent(float _fDeltaSeconds);

		virtual HRESULT EndPlay();

		virtual void Render();

		virtual void Release();
		
	/********************
		Methods
	********************/
	public:
		bool IsValidCell(Vector3& _vInWorldPosition, Vector3& _vOutWorldPosition);
		
		bool FindValidCell(Vector3& _vInWorldPosition, Vector3& _vOutWorldPosition);

	/********************
		Gettser/Setter
	********************/
	public:
		void SetNavigation(const std::wstring& _wstrNavigationName) { m_wstrNavigationName = _wstrNavigationName; }

		void SetCurCellIndex(int32 _iCurCellIndex) { m_iCurCellIndex = _iCurCellIndex; }

		int32 GetCurCellIndex() const { return m_iCurCellIndex; }

		Vector3 GetCentroidPosition(uint32 _iCellIndex);

	/********************
		Data Members
	********************/
	private:
		std::weak_ptr<CNavHandler> m_wpNavHandler;

	private:
		std::wstring m_wstrNavigationName = L"";

		std::vector<std::shared_ptr<CCell>> m_vecCells;

		int32 m_iCurCellIndex = -1;

		Matrix m_matWorld = Matrix::Identity;
	};
}
