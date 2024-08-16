#pragma once

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
