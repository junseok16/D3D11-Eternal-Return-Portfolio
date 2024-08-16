#pragma once
#include "Image.h"

namespace Client
{
	class CItemBox;

	class CInItemBoxBackground final : public CImage
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CInItemBoxBackground() = default;

		virtual ~CInItemBoxBackground() = default;
		
	/********************
		Events
	********************/
	public:
		virtual HRESULT PreInitialize() override;

		virtual HRESULT Initialize() override;

		virtual HRESULT PostInitialize() override;

		virtual HRESULT BeginPlay() override;

		virtual int32 PreTick(float _fDeltaSeconds) override;

		virtual int32 Tick(float _fDeltaSeconds) override;
		
		virtual int32 PostTick(float _fDeltaSeconds) override;

		virtual HRESULT EndPlay() override;

		virtual void Render() override;

		virtual void Release() override;

	public:
		void SetItemBox(const std::shared_ptr<CItemBox>& _spItemBox) { m_wpItemBox = _spItemBox; }

	private:
		std::weak_ptr<CItemBox> m_wpItemBox;
	};
}
