![header](https://capsule-render.vercel.app/api?type=waving&color=gradient&height=280&section=header&text=D3D11%20Eternal%20Return&fontSize=70&fontColor=ffffff&fontAlign=50&fontAlignY=45)

# 🎮 D3D11를 활용한 이터널 리턴 모작 포트폴리오

## ⭐ 하이라이트
|▼ 아이템 조합 시스템, 사용자 인터페이스|▼ 상태 컴포넌트로 구현한 보스 패턴|
|:---|:---|
|<img src="https://github.com/user-attachments/assets/002e6741-f9a2-442a-8e3f-ad78007a34db" width="368" height="207">|<img src="https://github.com/user-attachments/assets/01f5f820-8959-4250-a297-2fd10db6fa1f" width="368" height="207">|
|**▼ 3인칭 사이드 뷰와 몬스터**|**▼ 이펙트 툴로 제작한 스킬**|
|<img src="https://github.com/user-attachments/assets/41135717-4f02-4d4d-8419-b35b9ebb7c6e" width="368" height="207">|<img src="https://github.com/user-attachments/assets/694e3635-bac9-4ded-9fad-83908ab8d323" width="368" height="207">|
<br>

## 🔗 링크
- [이터널 리턴 포트폴리오 동영상](https://youtu.be/cZCmvKb5MZE)
- 이터널 리턴 기술 소개서는 첨부 파일에 있습니다.
<br>

## 🔎 프로필
- 이름 `D3D11를 활용한 이터널 리턴 모작`
- 기간 `2024-01 ~ 2024-03`
- 인원 `1명`
- 역할 `엔진, 클라이언트`
- 장르 `3D`, `배틀로얄`, `TPS`
- 플랫폼 `PC`
<br>

## ⚙️ 개발 환경
- 언어 `C++`, `D3D11`
- 통합개발환경 `Visual Studio 2022`, `Blender`
- 형상관리 `Git`
- 운영체제 `Windows 11`
<br>

## 💻 목적
- 렌더링 파이프라인을 학습하고 DX11 라이브러리로 프레임워크를 제작합니다.
- 버텍스, 인덱스 `버퍼`와 버텍스, 픽셀, 그리고 기하 `셰이더`의 역할을 이해합니다.
- 모델을 구성하는 `애니메이션`, `본`, `채널`의 구조를 파악하고 캐릭터의 상태를 제어합니다.
- `포워드 렌더링`과 `디퍼드 렌더링`의 차이점을 이해하고 여러 렌더 타겟들을 활용할 수 있습니다.
<br>

## 📜 ️구현 사항
- `상태 패턴`으로 행동에 우선순위를 결정하고 캐릭터 상태를 제어하는 `상태 컴포넌트`를 제작합니다.
- `구 좌표계`를 도입해 3인칭 카메라를 제어합니다.
- 삼각형으로 구성된 셀 집합 위에 캐릭터가 이동할 수 있도록 `내비메시 컴포넌트`를 구현합니다.
- `기하 셰이더`에서 점을 렉트(rect)로 확장해 `사용자 인터페이스`를 렌더합니다.
- `디퍼드 렌더링`으로 디퓨즈, 셰이드, 셰도우 렌더 타겟을 혼합합니다.
- 메시 피킹을 활용해 필드에 야생 동물을 배치하고 클라이언트로 파싱하는 `맵 툴`을 제작합니다.
- 이펙트에 노이즈 텍스처를 적용하고 트랜스폼, uv 좌표를 변경할 수 있는 `이펙트 툴`을 제작합니다.
<br>

## ⓒ 2024 Tak Junseok all rights reserved.
이 리포지토리에 기재된 코드와 리포트에 대한 저작권은 탁준석에게 있습니다. 사전에 합의되지 않은 내용을 무단으로 도용(URL 연결 등), 불법으로 복사(캡처)하여 사용할 경우 사전 경고 없이 저작권법에 의한 처벌을 받을 수 있습니다.

The copyright for the codes and reports listed in this repository belongs to Tak Junseok. If you steal(such as URL connection) or illegally copy(capture) anything that is not agreed in advance, you may be punished by copyright law without prior warning.
