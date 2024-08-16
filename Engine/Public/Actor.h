#pragma once
#include "Object.h"

namespace Engine
{
	class CActorComponent;
	class CSceneComponent;
	class CShapeComponent;
	class CController;
	class CWorld;
	class CLevel;
	class CLayer;
	class CPawn;

	/**
	* @brief	
	* @details	
	* @author	Ź�ؼ�
	* @date		2023-12-13
	*/
	class ENGINE_DLL CActor : public CObject
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CActor() = default;

		virtual ~CActor() = default;
		
	/********************
		Events
	********************/
	public:
		virtual HRESULT PreInitialize();

		virtual HRESULT Initialize();

		virtual HRESULT PostInitialize();

		virtual HRESULT BeginPlay();

		virtual int32 PreTick(float _fDeltaSeconds);

		virtual int32 Tick(float _fDeltaSeconds);
		
		virtual int32 PostTick(float _fDeltaSeconds);

		virtual HRESULT EndPlay();

		virtual void Render();

		virtual void RenderShadow();

		virtual void Release();
		
	/********************
		Getter/Setter
	********************/
	public:
		// Ʈ������
		const std::shared_ptr<CSceneComponent> GetRootComponent() const;

		const std::unordered_map<std::wstring, std::shared_ptr<CActorComponent>>& GetActorComponents() const { return m_umapActorComponents; }

		const std::optional<Vector3> GetActorWorldForwardVector() const;

		const std::optional<Vector3> GetActorWorldUpVector() const;

		const std::optional<Vector3> GetActorWorldRightVector() const;

		const std::optional<Matrix> GetActorWorldMatrix() const;

		const std::optional<Vector3> GetActorWorldPosition() const;
		
		const std::optional<Vector3> GetActorWorldScale() const;

		// �����
		std::shared_ptr<CPawn> GetInstigatorPawn() const;

		// ����
		const ERenderType GetActorRenderType() const { return m_eActorRenderType; }

		// �Ӽ�
		const std::wstring& GetActorName() const { return m_wstrActorName; }

		// �Ҽ�
		const std::shared_ptr<CWorld> GetOwnerWorld() const;

		const std::shared_ptr<CLevel> GetOwnerLevel() const;

		const std::shared_ptr<CActor> GetOwnerActor() const;

		const Vector4 GetActorColor() const { return m_vActorColor; }

	public:
		// Ʈ������
		void SetRootComponent(const std::shared_ptr<CSceneComponent> _spSceneComponent);

		void SetActorLocalPosition(const Vector3& _vLocalPosition);
		 
		void SetActorLocalScale(const Vector3& _vLocalScale);

		void SetActorLocalRotate(const Vector3& _vAxis, float _fDegree);

		void SetActorLocalMatrix(const Matrix& _matMatrix);

		const std::optional<Vector3> GetActorLocalPosition() const;

		const std::optional<Vector3> GetActorLocalScale() const;

		void SetActorTransform(ETransformType _eTransformType, Vector4 _vTransform);

		// �Ӽ�
		void SetActorName(const std::wstring& _wstrActorName) { m_wstrActorName = _wstrActorName; }

		void SetActorRenderType(ERenderType _eRenderType) { m_eActorRenderType = _eRenderType; }

		// �Ҽ�
		void SetOwnerWorld(const std::shared_ptr<CWorld> _spWorld) { m_wpOwnerWorld = _spWorld; }

		void SetOwnerLevel(const std::shared_ptr<CLevel> _spLevel) { m_wpOwnerLevel = _spLevel; }

		void SetOwnerActor(const std::shared_ptr<CActor> _spOwnerActor) { m_wpOwnerActor = _spOwnerActor; }

		// �����
		void SetSocketMatrix(const Matrix& _matSocket);

	public:
		bool HasComponent(EComponentType _eComponentType) const;

		void SetOnAir(bool _bOnAir) { m_bOnAir = _bOnAir; }

		bool IsOnAir() { return m_bOnAir; }

		uint32 GetComponentCounts(EComponentType _eComponentType) const { return m_umapComponentCounts.at(_eComponentType); }

	/******************
		Methods
	******************/
	public:
		bool IsInFrustum(float _fRadius);

		bool IsInFrustum(const Vector4& _vWorldPosition, float _fRadius);

		void LookAt(const Vector3& _vPoint);

	public:
		virtual float TakeDamage(float _fDamageAmount, std::shared_ptr<CController> _spInstigatorController, std::shared_ptr<CPawn> _spInstigatorPawn);

		virtual void OnCollisionEnter(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst);

		virtual void OnCollisionStay(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst);

		virtual void OnCollisionExit(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst);

		virtual void OnAnimEnter(uint32 _iAnimState, uint32 _iAnimIndex, float _fRatio);

		virtual void OnAnimStay(uint32 _iAnimState, uint32 _iAnimIndex, float _fRatio);

		virtual void OnAnimExit(uint32 _iAnimState, uint32 _iAnimIndex, float _fRatio);

	/******************
		Create
	******************/
	public:
		template<typename T, typename = std::enable_if_t<std::is_base_of_v<CActorComponent, T>>>
		std::shared_ptr<T> CreateActorComponent(const std::wstring& _wstrActorComponentName, EComponentType _eComponentType)
		{
			if (m_umapActorComponents.find(_wstrActorComponentName) != m_umapActorComponents.end()) { return nullptr; }
			
			std::shared_ptr<T> spActorComponent = std::make_shared<T>();
			spActorComponent->SetOwnerActor(std::dynamic_pointer_cast<CActor>(shared_from_this()));
			spActorComponent->SetComponentType(_eComponentType);
			spActorComponent->SetComponentName(_wstrActorComponentName);
			AddActorComponent(_wstrActorComponentName, _eComponentType, spActorComponent);
			AddToManager(_wstrActorComponentName, _eComponentType, spActorComponent);
			
			// ������Ʈ ī���͸� ������ŵ�ϴ�.
			m_umapComponentCounts[_eComponentType]++;
			return spActorComponent;
		}

		void AddActorComponent(const std::wstring& _wstrActorComponentName, EComponentType _eComponentType, std::shared_ptr<CActorComponent> _spActorComponent);

		template<typename T>
		std::shared_ptr<T> FindActorComponent(const std::wstring& _wstrActorComponentName)
		{
			if (m_umapActorComponents.find(_wstrActorComponentName) == m_umapActorComponents.end()) { return nullptr; }
			return std::dynamic_pointer_cast<T>(m_umapActorComponents[_wstrActorComponentName]);
		}

		template<typename T>
		std::vector<std::shared_ptr<T>> FindActorComponent(EComponentType _eComponentType)
		{
			std::vector<std::shared_ptr<T>> vecActorcomponents;
			auto pair = m_ummapComponentTypes.equal_range(_eComponentType);
			for (auto iter = pair.first; iter != pair.second; ++iter)
			{
				vecActorcomponents.emplace_back(std::dynamic_pointer_cast<T>(m_umapActorComponents[iter->second]));
			}

			return vecActorcomponents;
		}

		bool RemoveActorComponent(const std::wstring& _wstrActorComponentName, EComponentType _eComponentType);

		void AddToManager(const std::wstring& _wstrActorComponentName, EComponentType _eComponentType, std::shared_ptr<CActorComponent> _spActorComponent);

		void RemoveFromManager(const std::wstring& _wstrActorComponentName, EComponentType _eComponentType);

	/******************
		Data Members
	******************/
	protected:
		// �� ���Ͱ� ���� ����
		std::weak_ptr<CWorld> m_wpOwnerWorld;

		// �� ���Ͱ� ���� ����
		std::weak_ptr<CLevel> m_wpOwnerLevel;

		// �� ���Ͱ� ���� ���̾��
		std::weak_ptr<CLayer> m_wpLayers;

		// �� ���Ͱ� ���� �±׵�
		std::unordered_set<std::wstring> m_setTags;

		// �� ���Ͱ� ���� ����
		std::weak_ptr<CActor> m_wpOwnerActor;

	protected:
		// �� ���Ͱ� ���� �ִ� �ڽ� ���͵�
		std::vector<std::weak_ptr<CActor>> m_wpChildrenActors;

		// �� ���Ͱ� ���� �ִ� ������Ʈ��
		std::unordered_map<std::wstring, std::shared_ptr<CActorComponent>> m_umapActorComponents;

		std::unordered_multimap<EComponentType, std::wstring> m_ummapComponentTypes;

		std::unordered_map<EComponentType, uint32> m_umapComponentCounts;

		// �� ������ ��Ʈ ������Ʈ
		std::weak_ptr<CSceneComponent> m_wpRootComponent;

	protected:
		// �� ������ �̸�
		std::wstring m_wstrActorName = L"";

		ERenderType m_eActorRenderType = ERenderType::OPAQUE_OBJECT;

		// �� ���Ͱ� �浹�� Ȱ��ȭ�Ǿ����� ����
		bool m_bEnableCollision = true;

		// ������ ����
		Vector4 m_vActorColor = Vector4::One;

	protected:
		// �� ���͸� ������ ��
		std::weak_ptr<CPawn> m_wpInstigatorPawn;

		// �� ���͸� ������ ���� ��Ʈ�ѷ�
		std::weak_ptr<CController> m_wpInstigatorController;

		bool m_bIsInFrustum = false;

	protected:
		// ������
		bool m_bOnAir = false;

	public:
		int32 GetDayNightType() const { return m_iDayNightType; }

		float GetDayTime() const { return m_fDayTime; }

		float GetNightTime() const { return m_fNightTime; }

	protected:
		int32 m_iDayNightType = 1;

		float m_fDayTime = 0.0f;

		float m_fNightTime = 0.0f;
	};
}
