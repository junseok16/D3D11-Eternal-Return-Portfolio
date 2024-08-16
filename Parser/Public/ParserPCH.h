#pragma once

// ASSIMP ���̺귯��
#include "assimp/scene.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"

// Windows ���̺귯��
#define NOMINMAX
#include <Windows.h>
#include <wrl.h>
using namespace Microsoft::WRL;

// Direct3D ���̺귯��
#include <d3d11.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>
using namespace DirectX;

#include <SimpleMath.h>
using namespace DirectX::SimpleMath;

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
using namespace std;

// C ���̺귯��
#include <cassert>
#include <cmath>

// ����� ���� ���̺귯��
#include "ParserType.h"
#include "ParserDefine.h"
#include "ParserEnum.h"
#include "ParserStruct.h"
using namespace Parser;