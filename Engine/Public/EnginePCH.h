#pragma once
#pragma warning(disable:4251)

// Windows ���̺귯��
#include <Windows.h>
#include <wrl.h>
using namespace Microsoft::WRL;

// Direct3D ���̺귯��
#include <d3d11.h>
#include <DirectXMath.h>
#include <DirectXColors.h>
#include <DirectXCollision.h>
#include <d3dcompiler.h>

#define INITGUID
#include <d3d11shader.h>

#define DIRECTINPUT_VERSION	0x0800
#include <dinput.h>
#include <SimpleMath.h>
using namespace DirectX::SimpleMath;

#include <DDSTextureLoader.h>
#include <WICTextureLoader.h>
#include <ScreenGrab.h>

#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <Effects.h>
#include <SpriteBatch.h>
#include <SpriteFont.h>
#include "DebugDraw.h"
using namespace DirectX;

// C++ ǥ�� ���̺귯��
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <numeric>
#include <utility>
#include <functional>
#include <memory>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <random>
using namespace std;

// C ���̺귯��
#include <cassert>
#include <cmath>
#include <ctime>

// FMOD ���̺귯��
#include "fmod.hpp"

// ����� ���� ��� ����
#include "EngineType.h"
#include "EngineDefine.h"
#include "EngineEnum.h"
#include "EngineDesc.h"
#include "EngineStruct.h"
using namespace Engine;
