#pragma once

namespace Engine
{
	class CShaderHandler;

	class IShader
	{
	/********************
		Events
	********************/
	public:
		template<typename T>
		static std::shared_ptr<T> Create(std::shared_ptr<FShaderDesc> _spShaderDesc = nullptr)
		{
			const std::shared_ptr<T> spShader = make_shared<T>();
			ENSUREF(spShader->Initialize(_spShaderDesc), L"Failed to initialize shader.");
			return spShader;
		}

		virtual HRESULT Initialize(std::shared_ptr<FShaderDesc> _spShaderDesc = nullptr);

		virtual void Release();
		
	/********************
		Data Members
	********************/
	protected:
		std::weak_ptr<CShaderHandler> m_wpShaderHandler;
	};
}
