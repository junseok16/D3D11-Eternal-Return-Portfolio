#pragma once
#include "Image.h"

namespace Client
{
    class CStatusCharLevelCircleImage : public CImage
    {
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CStatusCharLevelCircleImage() = default;

		virtual ~CStatusCharLevelCircleImage() = default;

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

		virtual void Release();
    };
}
