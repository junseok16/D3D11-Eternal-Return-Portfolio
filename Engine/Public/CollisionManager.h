#pragma once
#include "Manager.h"

namespace Engine
{
	class CShapeComponent;
	class CSphereComponent;
	class CAABBComponent;
	class COBBComponent;

    class ENGINE_DLL CCollisionManager : public CManager
    {
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CCollisionManager() = default;

		virtual ~CCollisionManager() = default;

	/********************
		Events
	********************/
	public:
		HRESULT PreInitialize();

		HRESULT Initialize();

		int32 Tick();

		virtual void Release() override;
		
	/********************
		Getter/Setter
	********************/
	public:
		HRESULT AddShapeComponent(const std::shared_ptr<CShapeComponent>& _spShapeComponent);

		HRESULT RemoveShapeComponent(const std::shared_ptr<CShapeComponent>& _spShapeComponent);

	/********************
		Data Members
	********************/
	private:
		std::vector<std::shared_ptr<CShapeComponent>> m_vecShapeComponents;
    };
}
