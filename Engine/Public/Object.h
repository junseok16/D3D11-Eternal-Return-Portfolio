#pragma once

namespace Engine
{
	class ENGINE_DLL CObject : public enable_shared_from_this<CObject>
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CObject() = default;

		virtual ~CObject() = default;
	};
}
