#pragma once

// Windows ���̺귯��
#define NOMINMAX
#include <Windows.h>
#include <wrl.h>
using namespace Microsoft::WRL;

// IMGUI ���̺귯��
#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>

// ����� ���� ���̺귯��
#include "EditorDefine.h"
#include "EditorEnum.h"
#include "EditorStruct.h"
using namespace Editor;