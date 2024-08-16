#pragma once
#include "ConstantBuffer.h"

namespace Engine
{
	class CCameraManager;
	class CEffectMeshData;

	class CMeshEffectTransformConstantBuffer : public CConstantBuffer
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CMeshEffectTransformConstantBuffer() = default;

		virtual ~CMeshEffectTransformConstantBuffer() = default;
		
	/********************
		Events
	********************/
	public:
		virtual HRESULT Initialize(const std::shared_ptr<CActor>& _spOwnerActor, const std::wstring& _wstrConstantBufferName, uint8 _iBindPoint) override;

		virtual void Release() override;

	/********************
		Getter/Setter
	********************/
	public:
		void SetEffectMeshData(const std::shared_ptr<CEffectMeshData>& _spEffectMeshData) { m_wpEffectMeshData = _spEffectMeshData; }

	/********************
		Methods
	********************/
	public:
		virtual void TickConstantBuffer(uint32 _iIndex) override;

		virtual void CopyConstantBuffer(uint32 _iIndex) override;
		
	/********************
		Data Members
	********************/
	private:
		std::weak_ptr<CCameraManager> m_wpCameraManager;

	private:
		std::weak_ptr<CEffectMeshData> m_wpEffectMeshData;

	private:
		FMeshEffectTransformConstantBuffer m_tMeshEffectTransformConstantBuffer;
    };
}
