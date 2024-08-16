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
		// 점 버텍스 데이터들
		std::unordered_map<std::wstring, TPosition> m_umapPointVertices;

		// 렉트 버텍스 데이터들
		std::unordered_map<std::wstring, std::vector<TPositionTexCoord2>> m_umapRectVertices;

		// 렉트 인덱스 데이터들
		std::unordered_map<std::wstring, std::vector<uint32>> m_umapRectIndices;

		// 큐브 버텍스 데이터들
		std::unordered_map<std::wstring, std::vector<TPositionTexCoord3>> m_umapCubeVertices;

		// 큐브 인덱스 데이터들
		std::unordered_map<std::wstring, std::vector<uint32>> m_umapCubeIndices;

	private:
		// 인스턴스 렉트 버텍스 데이터들
		std::unordered_map<std::wstring, std::vector<TPositionSize>> m_umapInstancePointVertices;

		// 인스턴스 렉트 인덱스 데이터들
		std::unordered_map<std::wstring, std::vector<uint32>> m_umapInstancePointIndices;

		// 인스턴스 렉트 트랜스폼 데이터들
		std::unordered_map<std::wstring, std::vector<TInstanceTransform>> m_umapInstanceTransforms;

	private:
		std::weak_ptr<CDeviceManager> m_wpDeviceManager;

		std::weak_ptr<CBufferHandler> m_wpBufferHandler;
	};
}

