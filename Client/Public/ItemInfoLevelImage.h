#pragma once
#include "Image.h"

namespace Client
{
	enum class EItemInfoLevelImageType
	{
		BACKGROUND,
		LINE,
		ENUM_END
	};

	class CItemInfoLevelImage : public CImage
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CItemInfoLevelImage() = default;

		virtual ~CItemInfoLevelImage() = default;
		
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
		
	/********************
		Getter/Setter
	********************/
	public:
		void SetItemInfoLevelImageType(EItemInfoLevelImageType _eItemInfoLevelImageType) { m_eItemInfoLevelImageType = _eItemInfoLevelImageType; }

		void SetUIColor(const Vector4& _vUIColor) { m_vActorColor = _vUIColor; }

	/********************
		Data Members
	********************/
	private:
		EItemInfoLevelImageType m_eItemInfoLevelImageType = EItemInfoLevelImageType::ENUM_END;
	};
}
