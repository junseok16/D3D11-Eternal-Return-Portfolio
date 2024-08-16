#pragma once
#include "ConstantBuffer.h"

namespace Engine
{
	class CEffectMeshData;

	class CMeshEffectConstantBuffer final : public CConstantBuffer
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CMeshEffectConstantBuffer() = default;

		virtual ~CMeshEffectConstantBuffer() = default;
		
	/********************
		Events
	********************/
	public:
		virtual HRESULT Initialize(const std::shared_ptr<CActor>& _spOwnerActor, const std::wstring& _wstrConstantBufferName, uint8 _iBindPoint) override;

		virtual void Release() override;
		
	/********************
		Methods
	********************/
	public:
		virtual void TickConstantBuffer(uint32 _iIndex) override;

		virtual void CopyConstantBuffer(uint32 _iIndex) override;
		
	/******************
		Getter/Setter
	******************/
	public:
		void SetEffectMeshData(const std::shared_ptr<CEffectMeshData>& _spEffectMeshData) { m_wpEffectMeshData = _spEffectMeshData; }

	/********************
		Data Members
	********************/
	private:
		std::weak_ptr<CEffectMeshData> m_wpEffectMeshData;

	private:
		FMeshEffectConstantBuffer m_tMeshEffectConstantBuffer;
	};
}
