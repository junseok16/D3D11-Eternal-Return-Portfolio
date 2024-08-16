#pragma once

/********************
	Win32 ��ũ��
********************/
#define WIN32_LEAN_AND_MEAN 


/********************
	DirectX ��ũ��
********************/


/********************
	dll ��ũ��
********************/
#define AI_TEXTURE_TYPE_MAX 21

#ifdef ENGINE_EXPORTS
#define ENGINE_DLL _declspec(dllexport)
#else
#define ENGINE_DLL _declspec(dllimport)
#endif


/********************
	����� ��ũ��
********************/
#define MESSAGE_BOX(_message)							\
		MessageBox(NULL, _message, L"Error", MB_OK)		\

// ǥ������ ������ Ȯ���մϴ�.
#define CHECK(_expression)								\
		assert(_expression);							\

#define CHECKF(_expression, _message)					\
		if (!(_expression))								\
		{												\
			MESSAGE_BOX(_message);						\
			CHECK(_expression);							\
		}												\

// HRESULT ��ȯ ���� ������ Ȯ���մϴ�.
#define ENSURE(_hr)										\
		assert(SUCCEEDED(_hr));							\

#define ENSUREF(_hr, _message)							\
		if (!SUCCEEDED(_hr))							\
		{												\
			MESSAGE_BOX(_message);						\
			ENSURE(_hr);								\
		}												\


/********************
	�̱��� ��ũ��
********************/
#define DELETE_COPY(_classType)								\
		public:												\
		_classType() = default;								\
		virtual ~_classType() = default;					\
															\
		_classType(const _classType&) = delete;				\
		_classType(_classType&&) = delete;					\
															\
		_classType& operator=(const _classType&) = delete;	\
		_classType& operator=(_classType&&) = delete;		\


#define DECLARE_SINGLETON(_classType)						\
		DELETE_COPY(_classType)								\
		private:											\
		static std::shared_ptr<_classType> m_spInstance;	\
															\
		public:												\
		static std::shared_ptr<_classType>& GetInstance();	\


#define IMPLEMENT_SINGLETON(_classType)									\
		std::shared_ptr<_classType> _classType::m_spInstance = nullptr;	\
																		\
		std::shared_ptr<_classType>& _classType::GetInstance()			\
		{																\
			if (!m_spInstance)											\
			{															\
				m_spInstance = std::make_shared<_classType>();			\
			}															\
			return m_spInstance;										\
		}
