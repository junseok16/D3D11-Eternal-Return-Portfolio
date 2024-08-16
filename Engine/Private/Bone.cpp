#include "pch.h"
#include "Bone.h"

Engine::CBone::CBone(const CBone& _rhs)
	: m_strBoneName(_rhs.m_strBoneName)
	, m_matLocal(_rhs.m_matLocal)
	, m_matWorld(_rhs.m_matWorld)
	, m_iParentBone(_rhs.m_iParentBone)
{
}

shared_ptr<CBone> Engine::CBone::Create(const std::string& _strBoneName, const Matrix& _matLocal, int32 _iParentBone)
{
	const shared_ptr<CBone> spBone = make_shared<CBone>();
	ENSUREF(spBone->Initialize(_strBoneName, _matLocal, _iParentBone), L"Failed to initialize bone.");
	return spBone;
}

HRESULT Engine::CBone::Initialize(const std::string& _strBoneName, const Matrix& _matLocal, int32 _iParentBone)
{
	m_strBoneName = _strBoneName;
	m_matLocal = _matLocal;
	m_iParentBone = _iParentBone;
	return S_OK;
}

void Engine::CBone::Release()
{
}

void Engine::CBone::RecalcBone(const std::vector<std::shared_ptr<CBone>>& _vecBones)
{
	if (m_iParentBone == -1)
	{
		m_matWorld = m_matLocal;
	}
	else
	{
		m_matWorld = m_matLocal * _vecBones[m_iParentBone]->m_matWorld;
	}
}
