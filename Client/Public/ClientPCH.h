#pragma once

// Windows 라이브러리
#define NOMINMAX
#include <Windows.h>
#include <wrl.h>
using namespace Microsoft::WRL;

// 사용자 정의 라이브러리
#include "ClientDefine.h"
#include "ClientEnum.h"
#include "ClientStruct.h"
using namespace Client;