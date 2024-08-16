#pragma once
#include "Buffer.h"

namespace Engine
{
	class CActor;

	class CSkeletalMeshData;

	class CSceneComponent;
	class CShaderHandler;

	class ENGINE_DLL CConstantBuffer
	{
	/******************
		Ctor/Dtor
	******************/
	public:
		explicit CConstantBuffer() = default;

		virtual ~CConstantBuffer() = default;

	/******************
		Events
	******************/
	public:
		template<typename T>
		static std::shared_ptr<T> Create(const std::shared_ptr<CActor>& _spOwnerActor, const std::wstring& _wstrConstantBufferName, uint8 _iBindPoint)
		{
			const shared_ptr<T> spBuffer = make_shared<T>();
			ENSUREF(spBuffer->Initialize(_spOwnerActor, _wstrConstantBufferName, _iBindPoint), L"Failed to initialize Constant Buffer.");
			return spBuffer;
		}

		virtual HRESULT Initialize(const std::shared_ptr<CActor>& _spOwnerActor, const std::wstring& _wstrConstantBufferName, uint8 _iBindPoint);

		virtual void Release();

	/******************
		Methods
	******************/
	public:
		void VSSetConstantBuffers();

		void PSSetConstantBuffers();

		void GSSetConstantBuffers();

		virtual void TickConstantBuffer(uint32 _iIndex);

		virtual void CopyConstantBuffer(uint32 _iIndex);
		
	/******************
		Getter/Setter
	******************/
	public:
		void SetSkeletalMeshData(const std::shared_ptr<CSkeletalMeshData>& _spSkeletalMeshData) { m_wpSkeletalMeshData = _spSkeletalMeshData; }

		const std::wstring& GetConstantBufferName() const { return m_wstrConstantBufferName; }

	/******************
		Data Members
	******************/
	protected:
		std::weak_ptr<CSkeletalMeshData> m_wpSkeletalMeshData;

		std::weak_ptr<CShaderHandler> m_wpShaderHandler;

		std::weak_ptr<CActor> m_wpOwnerActor;

	protected:
		uint8 m_iBindPoint = -1;

		ComPtr<ID3D11Buffer> m_cpBuffer = nullptr;

		bool m_bDirty = false;

	protected:
		EBufferType m_eBufferType = EBufferType::CONSTANT;

		std::wstring m_wstrConstantBufferName = L"";
	};
}
