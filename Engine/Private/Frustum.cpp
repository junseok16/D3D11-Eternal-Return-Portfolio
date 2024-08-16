#include "pch.h"
#include "Frustum.h"

#include "CameraManager.h"

std::shared_ptr<CFrustum> Engine::CFrustum::Create()
{
	const std::shared_ptr<CFrustum> spFrustum = make_shared<CFrustum>();
	spFrustum->Initialize();
	return spFrustum;
}

HRESULT Engine::CFrustum::Initialize()
{
	m_arrLocalPoints[0] = { -1.0f,  1.0f, 0.0f };
	m_arrLocalPoints[1] = {  1.0f,  1.0f, 0.0f };
	m_arrLocalPoints[2] = {  1.0f, -1.0f, 0.0f };
	m_arrLocalPoints[3] = { -1.0f, -1.0f, 0.0f };
	m_arrLocalPoints[4] = { -1.0f,  1.0f, 1.0f };
	m_arrLocalPoints[5] = {  1.0f,  1.0f, 1.0f };
	m_arrLocalPoints[6] = {  1.0f, -1.0f, 1.0f };
	m_arrLocalPoints[7] = { -1.0f, -1.0f, 1.0f };
	return S_OK;
}

int32 Engine::CFrustum::Tick()
{
	Matrix matInvView = m_wpCameraManager.lock()->GetCurViewMatrix();
	matInvView.Invert(matInvView);

	Matrix matInvPerspectiveProjection = m_wpCameraManager.lock()->GetCurPerspectiveProjectionMatrix();
	matInvPerspectiveProjection.Invert(matInvPerspectiveProjection);

	for (size_t iIndex = 0; iIndex < m_arrLocalPoints.size(); ++iIndex)
	{
		m_arrWorldPoints[iIndex] = Vector3::Transform(m_arrLocalPoints[iIndex], matInvPerspectiveProjection);
		m_arrWorldPoints[iIndex] = Vector3::Transform(m_arrWorldPoints[iIndex], matInvView);
	}


	/*		4		5
	*	0		1
	*		7		6
	*	3		2
	*
	*/

	XMStoreFloat4(&m_arrWorldPlanes[0], XMPlaneFromPoints(XMLoadFloat3(&m_arrWorldPoints[1]), XMLoadFloat3(&m_arrWorldPoints[5]), XMLoadFloat3(&m_arrWorldPoints[6])));
	XMStoreFloat4(&m_arrWorldPlanes[1], XMPlaneFromPoints(XMLoadFloat3(&m_arrWorldPoints[4]), XMLoadFloat3(&m_arrWorldPoints[0]), XMLoadFloat3(&m_arrWorldPoints[3])));
	XMStoreFloat4(&m_arrWorldPlanes[2], XMPlaneFromPoints(XMLoadFloat3(&m_arrWorldPoints[4]), XMLoadFloat3(&m_arrWorldPoints[5]), XMLoadFloat3(&m_arrWorldPoints[1])));
	XMStoreFloat4(&m_arrWorldPlanes[3], XMPlaneFromPoints(XMLoadFloat3(&m_arrWorldPoints[3]), XMLoadFloat3(&m_arrWorldPoints[2]), XMLoadFloat3(&m_arrWorldPoints[6])));
	XMStoreFloat4(&m_arrWorldPlanes[4], XMPlaneFromPoints(XMLoadFloat3(&m_arrWorldPoints[5]), XMLoadFloat3(&m_arrWorldPoints[4]), XMLoadFloat3(&m_arrWorldPoints[7])));
	XMStoreFloat4(&m_arrWorldPlanes[5], XMPlaneFromPoints(XMLoadFloat3(&m_arrWorldPoints[0]), XMLoadFloat3(&m_arrWorldPoints[1]), XMLoadFloat3(&m_arrWorldPoints[2])));

	return 0;
}

bool Engine::CFrustum::IsInFrustum(const Vector4& _vWorldPosition, float _fRadius)
{
	for (size_t iIndex = 0; iIndex < m_arrWorldPlanes.size(); ++iIndex)
	{
		if (_fRadius < XMVectorGetX(XMPlaneDotCoord(m_arrWorldPlanes[iIndex], _vWorldPosition)))
		{
			return false;
		}
	}

	return true;
}
