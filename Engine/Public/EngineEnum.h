#pragma once

namespace Engine
{
	/************************
		Engine Enumeration
	************************/
	enum class ETransformType
	{
		RIGHT,
		UP,
		FORWARD,
		POSITION,
		ENUM_END,
	};

	enum class EDirectionType
	{
		FORWARD,
		FORWARD_RIGHT,
		RIGHT,
		BACKWARD_RIGHT,
		BACKWARD,
		BACKWARD_LEFT,
		LEFT,
		FORWARD_LEFT,
		ENUM_END,
	};

	enum class EModelType
	{
		STATIC,
		SKELETAL,
		NAVIGATION,
		EFFECT,
	};

	enum class ERenderType
	{
		NOT_RENDER,
		PRE_RENDER,
		SHADOW,
		OPAQUE_OBJECT,
		LIGHT,
		POST_PROCESS,
		EFFECT,
		PARTICLE_OBJECT,
		TRANSLUCENT_OBJECT,
		OPAQUE_USER_INTERFACE,
		TRANSLUCENT_USER_INTERFACE,
		POST_RENDER,
		ENUM_END
	};

	enum class EPrimitiveType
	{
		POINT,
		RECT,
		CUBE,
		INSTANCE_POINT,
		ENUM_END
	};

	enum class EShaderType
	{
		VERTEX,
		PIXEL,
		GEOMETRY,
		COMPUTE,
		ENUM_END
	};

	enum class ETextureType
	{
		VERTEX,
		PIXEL,
		ENUM_END
	};

	enum class EBufferType
	{
		VERTEX,
		INDEX,
		CONSTANT,
		INSTANCE,
		ENUM_END
	};

	enum class EProjectionType
	{
		ORTHOGONAL,
		PERSPECTIVE,
		ENUM_END
	};

	enum class ELightType
	{
		DIRECTIONAL,
		POINT,
		SPOT,
		ENUM_END
	};

	enum class EComponentType
	{
		ACTOR,
		SCENE,
		CAMERA,
		PRIMITIVE,
		MESH,
		STATIC_MESH,
		SKELETAL_MESH,
		SHAPE,
		SPHERE,
		AABB,
		OBB,
		LANDSCAPE,
		BRAIN,
		BLACKBOARD,
		INPUT,
		PAWN_MOVEMENT,
		CHARACTER_MOVEMENT,
		LIGHT,
		DIRECTIONAL_LIGHT,
		POINT_LIGHT,
		SPOT_LIGHT,
		NAVIGATION,
		STATE,
		GEOMETRY,

		RECT,
		CUBE,
		EFFECT,
		SOUND,
	};

	enum class EVariableType
	{
		BOOL,
		INT32,
		FLOAT,
		WSTRING,
	};

	enum class ECellPoint
	{
		A,
		B,
		C,
		ENUM_END
	};

	enum class ECellLine
	{
		AB,
		BC,
		CA,
		ENUM_END
	};

	enum class EShapeType
	{
		SPHERE,
		AABB,
		OBB,
		ENUM_END
	};

	enum class ECollisionLayer
	{
		PLAYER,		// Survivor
		MONSTER,	// Wild Animal
		ITEM,		// Item
		ENVIRONMENT,// Collectible
		WALL,		
		STRUCTURE,	// Console
		PLAYER_PROJECTILE,
		MONSTER_PROJECTILE,
		PLAYER_SKILL,
		MONSTER_SKILL,
		BOUNDARY,
		ENUM_END
	};

	enum class EButtonState
	{
		INACTIVE,	// ������ �� �Ǵ� ����
		ENABLE,		// ��ư�� Ȱ��ȭ�� ����
		DISABLE,	// ��ư�� ��Ȱ��ȭ�� ����
		ENUM_END
	};

	enum class EButtonMouseState
	{
		RELEASE,	// ��ư�� ���콺�� ���� ����
		HOVER,		// ��ư�� ���콺�� �ø� ����
		PRESS_IN,	// ��ư�� ������ �ִ� ����
		PRESS_OUT,	// ��ư�� ������ ��ư ������ ��� ����
		DOWN,		// ��ư�� ���� ����
		UP_IN,		// ��ư�� �� ����
		UP_OUT,		// ��ư �ۿ��� �� ����
		ENUM_END
	};

	enum class ESoundType
	{
		BGM_01,
		BGM_02,
		TALK_01,
		TALK_02,
		CREATURE_01,
		CREATURE_02,
		EFFECT_01,
		EFFECT_02,
		EFFECT_03,
		EFFECT_04,
		HIT_01,
		HIT_02,
		RULE_01,
		RULE_02,
		UI_01,
		UI_02,
		WALK_01,
		ENUM_END
	};

	enum class EEffectShapeType
	{
		SPREAD,
		SPOT,
		FALL_DOWN,
		ENUM_END
	};

	/************************
		Input Enumeration
	************************/
	enum class EMouseState
	{
		DOWN,
		PRESSED,
		UP,
		RELEASED,
		ENUM_END
	};

	enum class EKeyState
	{
		DOWN,
		PRESSED,
		UP,
		RELEASED,
		ENUM_END
	};

	enum class EMouseActionType
	{
		LEFT_BUTTON,
		RIGHT_BUTTON,
		SCROLL_WHEEL_BUTTON,
		ENUM_END
	};

	enum class EMouseAxisType
	{
		X_AXIS,
		Y_AXIS,
		Z_AXIS,
		ENUM_END
	};

	enum class ECameraType
	{
		FIRST_PERSON,
		THIRD_PERSON,
		ENUM_END
	};

	enum class ESoundAttenuationType
	{
		LINEAR,
		ENUM_END
	};
}
