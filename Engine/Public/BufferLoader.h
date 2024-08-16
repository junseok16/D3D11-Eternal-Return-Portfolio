#pragma once

namespace Engine
{
	class CDeviceManager;
	class CBufferHandler;

	class CBufferLoader final
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CBufferLoader() = default;

		virtual ~CBufferLoader() = default;
		
	/********************
		Events
	********************/
	public:
		static std::shared_ptr<CBufferLoader> Create();

		HRESULT Initialize();

		void Release();
		
	/********************
		Methods
	********************/
	public:
		HRESULT LoadBufferFromFile();
		
		HRESULT LoadPoint();

		HRESULT LoadRect();

		HRESULT LoadCube();

		HRESULT CreateVertexBuffer();

		HRESULT CreateIndexBuffer();

	public:
		HRESULT LoadInstanceVertex();

		HRESULT CreateInstanceVertexBuffer();

	public:
		HRESULT LoadInstanceIndex(const std::wstring& _wstrInstanceIndexDataName, int32 _iNumInstances);

		HRESULT CreateInstanceIndexBuffer(const std::wstring& _wstrInstanceIndexDataName);

	public:
		HRESULT LoadInstanceTransform(const std::wstring& _wstrInstanceTransformDataName, int32 _iNumInstances);

		HRESULT CreateInstanceTransformBuffer(const std::wstring& _wstrInstanceTransformDataName);

	/********************
		Data Members
	********************/
	private:
		// �� ���ؽ� �����͵�
		std::unordered_map<std::wstring, TPosition> m_umapPointVertices;

		// ��Ʈ ���ؽ� �����͵�
		std::unordered_map<std::wstring, std::vector<TPositionTexCoord2>> m_umapRectVertices;

		// ��Ʈ �ε��� �����͵�
		std::unordered_map<std::wstring, std::vector<uint32>> m_umapRectIndices;

		// ť�� ���ؽ� �����͵�
		std::unordered_map<std::wstring, std::vector<TPositionTexCoord3>> m_umapCubeVertices;

		// ť�� �ε��� �����͵�
		std::unordered_map<std::wstring, std::vector<uint32>> m_umapCubeIndices;

	private:
		// �ν��Ͻ� ��Ʈ ���ؽ� �����͵�
		std::unordered_map<std::wstring, std::vector<TPositionSize>> m_umapInstancePointVertices;

		// �ν��Ͻ� ��Ʈ �ε��� �����͵�
		std::unordered_map<std::wstring, std::vector<uint32>> m_umapInstancePointIndices;

		// �ν��Ͻ� ��Ʈ Ʈ������ �����͵�
		std::unordered_map<std::wstring, std::vector<TInstanceTransform>> m_umapInstanceTransforms;

	private:
		std::weak_ptr<CDeviceManager> m_wpDeviceManager;

		std::weak_ptr<CBufferHandler> m_wpBufferHandler;
	};
}

