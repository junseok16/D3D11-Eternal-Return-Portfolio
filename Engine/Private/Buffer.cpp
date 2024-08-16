#include "pch.h"
#include "Buffer.h"

#include "ModelHandler.h"
#include "BufferHandler.h"
#include "EffectHandler.h"

HRESULT Engine::IBuffer::Initialize(std::shared_ptr<FModelDesc> _spModelDesc, int32 _iMeshIndex, EPrimitiveType _ePrimitiveType)
{
	m_wpModelHandler = CModelHandler::GetInstance();
	CHECK(!m_wpModelHandler.expired());

	m_wpBufferHandler = CBufferHandler::GetInstance();
	CHECK(!m_wpBufferHandler.expired());

	m_wpEffectHandler = CEffectHandler::GetInstance();
	CHECK(!m_wpEffectHandler.expired());

	return S_OK;
}

void Engine::IBuffer::Release()
{
	m_cpBuffer = nullptr;
}
