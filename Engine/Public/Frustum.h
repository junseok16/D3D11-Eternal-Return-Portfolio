#pragma once

namespace Engine
{
	class CCameraManager;

	class CFrustum final
	{
	public:
		explicit CFrustum() = default;

		virtual ~CFrustum() = default;

	public:
		static std::shared_ptr<CFrustum> Create();

	public:
		HRESULT Initialize();

		int32 Tick();

	public:
		bool IsInFrustum(const Vector4& _vWorldPosition, float _fRadius);

	public:
		void SetCameraManager(const shared_ptr<CCameraManager>& _spCameraManager) { m_wpCameraManager = _spCameraManager; }

	private:
		std::array<Vector3, 8> m_arrLocalPoints{ Vector3::Zero };

		std::array<Vector3, 8> m_arrWorldPoints{ Vector3::Zero };

		std::array<Vector4, 6> m_arrWorldPlanes{ Vector4::Zero };

		std::weak_ptr<CCameraManager> m_wpCameraManager;
	};
}
