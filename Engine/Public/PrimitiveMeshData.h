#pragma once

namespace Engine
{
	class CConstantBuffer;
	class CSceneComponent;
	class CPrimitiveBuffer;
	class CPrimitiveShader;

	class CPrimitiveMeshData final
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CPrimitiveMeshData() = default;

		virtual ~CPrimitiveMeshData() = default;

	/********************
		Events
	********************/
	public:
		static std::shared_ptr<CPrimitiveMeshData> Create
		(
			const std::shared_ptr<CSceneComponent>& _spOwnerComponent,
			EPrimitiveType _ePrimitiveType,
			const std::vector<std::wstring>& _vecTextureNames,
			const std::wstring& _wstrVertexShaderDesc = L"",
			const std::wstring& _wstrPixelShaderDesc = L"",
			const std::wstring & _wstrGeometryShaderDesc = L""
		);

		HRESULT Initialize
		(
			const std::shared_ptr<CSceneComponent>& _spOwnerComponent,
			EPrimitiveType _ePrimitiveType,
			const std::vector<std::wstring>& _vecTextureNames,
			const std::wstring& _wstrVertexShaderDesc = L"",
			const std::wstring& _wstrPixelShaderDesc = L"",
			const std::wstring & _wstrGeometryShaderDesc = L""
		);

		int32 Tick();

		void Render(uint32 _iTextureIndex);

		void Release();
		
	/********************
		Getter/Setter
	********************/
	public:
		void SetPrimitiveBuffer(std::shared_ptr<CPrimitiveBuffer> _spPrimitiveBuffer) { m_spPrimitiveBuffer = _spPrimitiveBuffer; }

		std::shared_ptr<CPrimitiveBuffer> GetPrimitiveBuffer() const { return m_spPrimitiveBuffer; }
		
		void SetPrimitiveShader(std::shared_ptr<CPrimitiveShader> _spPrimitiveShader) { m_spPrimitiveShader = _spPrimitiveShader; }

		void SetConstantBuffer(const shared_ptr<CConstantBuffer>& _spConstantBuffer);

	/********************
		Data Members
	********************/
	private:
		// 이 데이터를 소유한 컴포넌트
		std::weak_ptr<CSceneComponent> m_wpOwnerComponent;

	private:
		// 도형 타입
		EPrimitiveType m_ePrimitiveType = EPrimitiveType::ENUM_END;

		std::wstring m_wstrTextureName = L"";

		// 이 도형을 표현하는 메시들
		std::shared_ptr<CPrimitiveBuffer> m_spPrimitiveBuffer = nullptr;

		// 이 도형을 표현하는 셰이더들
		std::shared_ptr<CPrimitiveShader> m_spPrimitiveShader = nullptr;
	};
}
