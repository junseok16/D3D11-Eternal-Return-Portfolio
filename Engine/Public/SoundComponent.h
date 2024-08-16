#pragma once
#include "SceneComponent.h"

namespace Engine
{
    class CSoundHandler;

    class ENGINE_DLL CSoundComponent final : public CSceneComponent
    {
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CSoundComponent() = default;

		virtual ~CSoundComponent() = default;

	/********************
		Events
	********************/
	public:
		virtual HRESULT PreInitializeComponent() override;

		virtual HRESULT InitializeComponent() override;

		virtual HRESULT PostInitializeComponent() override;

		virtual HRESULT BeginPlay() override;

		virtual int32 PreTickComponent(float _fDeltaSeconds) override;

		virtual int32 TickComponent(float _fDeltaSeconds) override;

		virtual int32 PostTickComponent(float _fDeltaSeconds) override;

		virtual HRESULT EndPlay() override;

		virtual void Render() override;

		virtual void Release() override;

	/********************
		Methods
	********************/
	public:
		void PlaySoundEx(const std::string& _strSoundFileName, ESoundType _eSoundType, float _fVolume = 1.0f, bool _bLoop = false);

		void StopSoundEx(ESoundType _eSoundType);

		void StopAllSoundEx();

		void ModifyVolume(ESoundType _eSoundType, float _fVolume);

	private:
		void RecalcAttenuation();
		
	/********************
		Getter/Setter
	********************/
	public:
		void SetListener(const std::shared_ptr<CActor>& _spListener) { m_wpListener = _spListener; }

	/********************
		Data Members
	********************/
	private:
		float m_fCurRadius = 0.0f;
		
		float m_fNearRadius = 0.0f;

		float m_fFarRadius = 10.0f;

		float m_fCurVolume = 1.0f;

		float m_fMinVolume = 0.0f;

		float m_fMaxVolume = 1.0f;

		ESoundAttenuationType m_eSoundAttenuationType = ESoundAttenuationType::LINEAR;

		std::weak_ptr<CActor> m_wpListener;

	private:
		std::weak_ptr<CSoundHandler> m_wpSoundHandler;
    };
}
