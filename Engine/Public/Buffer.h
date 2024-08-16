#pragma once

namespace Engine
{
	class CEffectHandler;
	class CModelHandler;
	class CBufferHandler;

	class IBuffer
	{
	/********************
		Events
	********************/
	public:
		template<typename T>
		static std::shared_ptr<T> Create(std::shared_ptr<FModelDesc> _spModelDesc = nullptr, int32 _iMeshIndex = -1, EPrimitiveType _ePrimitiveType = EPrimitiveType::ENUM_END)
		{
			const shared_ptr<T> spBuffer = make_shared<T>();
			ENSUREF(spBuffer->Initialize(_spModelDesc, _iMeshIndex, _ePrimitiveType), L"Failed to initialize buffer.");
			return spBuffer;
		}

		virtual HRESULT Initialize(std::shared_ptr<FModelDesc> _spModelDesc = nullptr, int32 _iMeshIndex = -1, EPrimitiveType _ePrimitiveType = EPrimitiveType::ENUM_END);

		virtual void Release();

	/********************
		Data Members
	********************/
	protected:
		ComPtr<ID3D11Buffer> m_cpBuffer = nullptr;

		std::wstring m_wstrBufferName = L"";

		EBufferType m_eBufferType = EBufferType::ENUM_END;

	protected:
		std::weak_ptr<CModelHandler> m_wpModelHandler;

		std::weak_ptr<CBufferHandler> m_wpBufferHandler;

		std::weak_ptr<CEffectHandler> m_wpEffectHandler;
	};
}
