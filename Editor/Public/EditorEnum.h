#pragma once

namespace Editor
{
	/********************
		������ ����
	********************/
	enum class EEditorState
	{
		PLAY,
		EDIT,
		ENUM_END
	};

	enum class EEditorCreateMode
	{
		WILD_ANIMAL,
		BOUNDARY,
		NONE,
	};

	/********************
		������Ʈ Ÿ��
	********************/
	enum class EInstancableComponentType
	{
		CAMERA_COMPONENT,
		STATIC_MESH_COMPONENT,
		SKELETAL_MESH_COMPONENT,
		SPHERE_COMPONENT,
		AABB_COMPONENT,
		OBB_COMPONENT,
		ENUM_END
	};

	/********************
		���� Ÿ��
	********************/
	enum class EInstancableActorType
	{
		LOCATION,
		COLLECTIBLE_GROUP,
		CONSOLE_GROUP,
		WILD_ANIMAL_GROUP,
		COLLECTIBLE,
		CONSOLE,

		ENUM_END,
	};

	/********************
		�߻����� ����
	********************/
	enum class EWildAnimalState
	{
		// �߻��� ���� �� �⺻ ����
		SLEEP_BEGIN,
		SLEEP,
		WAKE,

		// �߻���, ���༺ ���� �� �⺻ ����
		WAIT,

		// ��� �ȿ� ���� ��
		BEWARE_BEGIN,

		// ��� �ȿ� ���� ��
		BEWARE,

		// ��� ������ ���� ��
		BEWARE_END,

		ATTACK_01,
		ATTACK_02,

		CHASE,
		END_BATTLE,
		RETREAT,

		SKILL_BEGIN,
		SKILL,

		DANCE,
		DEATH,
		ENUM_END
	};

	enum class EWildAnimalAnimState
	{
		// APPEAR,
		SLEEP_BEGIN,
		SLEEP,
		WAKE,
		WAIT,

		// ��� �ȿ� ���� ��
		BEWARE_BEGIN,

		// ��� �ȿ� ���� ��
		BEWARE,

		// ��� ������ ���� ��
		BEWARE_END,

		RUN,
		ATTACK_01,
		ATTACK_02,

		SKILL_BEGIN,
		SKILL,

		END_BATTLE,
		DANCE,
		DEATH,
	};

	enum class EBossState
	{
		WANDER,
		WAIT,
		CHASE,

		ATTACK_01,
		ATTACK_02,

		SKILL_01_BEGIN,
		SKILL_01,
		SKILL_01_END,

		SKILL_02_BEGIN,
		SKILL_02,
		SKILL_02_END,

		SKILL_03_BEGIN,
		SKILL_03,
		SKILL_03_END,
		/*
		SKILL_04_BEGIN,
		SKILL_04,
		SKILL_04_END,
		*/

		END_BATTLE,

		DEATH,
		ENUM_END
	};

	enum class EBossAnimState
	{
		WAIT,
		RUN,

		ATTACK_01,
		ATTACK_02,

		SKILL_01_BEGIN,
		SKILL_01,
		SKILL_01_END,

		SKILL_02_BEGIN,
		SKILL_02,
		SKILL_02_END,

		SKILL_03_BEGIN,
		SKILL_03,
		SKILL_03_END,

		END_BATTLE,

		DEATH,
		ENUM_END
	};

	/********************
		������ ����
	********************/
	enum class ESurvivorState
	{
		WAIT,
		RUN,

		ATTACK_01,
		ATTACK_02,

		SKILL_01,

		SKILL_02_BEGIN,
		SKILL_02,
		SKILL_02_END,

		SKILL_03_BEGIN,
		SKILL_03,
		SKILL_03_END,

		SKILL_04_BEGIN,
		SKILL_04,
		SKILL_04_END,

		COLLECT_STONE,
		COLLECT_WATER,
		COLLECT_WOOD,
		CRAFT_FOOD,
		CRAFT_METAL,

		OPERATE,

		REST_BEGIN,
		REST,
		REST_END,

		ARRIVE,
		DEATH,
		ENUM_END
	};

	enum class ESurvivorAnimState
	{
		WAIT,
		RUN,

		ATTACK_01,
		ATTACK_02,

		SKILL_01,

		SKILL_02_BEGIN,
		SKILL_02,
		SKILL_02_END,

		SKILL_03_BEGIN,
		SKILL_03,
		SKILL_03_END,

		SKILL_04_BEGIN,
		SKILL_04,
		SKILL_04_END,

		COLLECT_STONE,
		COLLECT_WATER,
		COLLECT_WOOD,
		CRAFT_FOOD,
		CRAFT_METAL,

		OPERATE,

		REST_BEGIN,
		REST,
		REST_END,

		ARRIVE,
		DEATH,
	};

	/********************
		���� Ÿ��
	********************/
	enum class EWeaponType
	{
		GLOVE,
		TONFA,
		PISTOL,
		ASSAULT_RIFLE,
		SNIPER_RIFLE,
		ENUM_END
	};

	/********************
		�߻� ���� ����
	********************/
	enum class EWildAnimalHabitType
	{
		DIURNAL,	// ���༺
		NOCTURNAL,	// ���༺
		ENUM_END
	};

	enum class EWildAnimalType
	{
		BEAR,
		BOAR,
		CHICKEN,
		DOG,
		WOLF,
		ENUM_END
	};

	/********************
		���� Ÿ��
	********************/
	enum class ELocationType
	{
		ALLEY1x1,
		ALLEY10x10,

		ARCHERY1x1,
		ARCHERY10x10,

		CEMETERY,
		CHURCH,
		DOWNTOWN,
		FACTORY,

		FOREST1x1,
		FOREST10x10,

		HARBOR,
		HOSPITAL,
		HOTEL,
		LABORATORY,
		POND,
		SANDY_BEACH,

		SCHOOL1x1,
		SCHOOL10x10,

		TEMPLE,
		UPTOWN,

		ALLEY_GREEN,
		SCHOOL_GREEN,
		HOTEL_GREEN,
		FOREST_GREEN,
		DOWNTOWN_GREEN,
		ARCHERY_GREEN,
		ENUM_END,
	};

	/********************
		ä�� Ÿ��
	********************/
	enum class ECollectibleType
	{
		ITEM_SPOT,
		BRANCH,
		STONE,
		POTATO,
		WATER,
		ENUM_END
	};

	/********************
		�ܼ� Ÿ��
	********************/
	enum class EConsoleType
	{
		HYPERLOOP,
		SECURITY_CONSOLE,
		SECURITY_CAMERA,
		ENUM_END
	};

	enum class ECharacterStatusType
	{
		// ù ��° ��
		TENACITY,
		ATTACK_RANGE,
		MAGNETISE_DIFFERENCE_SPEED,
		SIGHT_RANGE,

		// �� ��° ��
		CRITICAL_STRIKE_CHANCE,
		LIFE_STEAL,
		STAMINA_DIFFERENCE_SPEED,
		COOL_DOWN_REDUCTION,

		// �� ��° ��
		ATTACK_POWER,
		DEFENSE,
		INCREASE_BASIC_ATTACK_DAMAGE_RATIO,
		NORMAL_ATTACK_DAMAGE_REDUCTION,

		// �� ��° ��
		SKILL_AMP_RATIO,
		SKILL_DAMAGE_REDUCTION,
		ATTACK_SPEED_RATIO,
		MOVE_SPEED_RATIO,

		/*
		CRITICAL_STRIKE_DAMAGE,
		DEFENSIVE_PENETRATION,
		MAX_HEALTH_POINT,
		MAX_STAMINA,
		MOVE_SPEED_NON_COMBAY,
		PENETRATION_DEFENSE_RATIO,
		RESISTANCE,
		*/
		ENUM_END
	};

	enum class EItemBelongType
	{
		EQUIPMENT,
		CRAFT,
		INVENTORY,
		ITEM_BOX,
		DEAD_BODY,
		WILD_ANIMAL,
		ENUM_END
	};

	enum class EItemSlotType
	{
		FIRST,
		SECOND,
		THIRD,
		FOURTH,
		FIFTH,
		SIXTH,
		SEVENTH,
		EIGHTH,
		NINETH,
		TENTH,
		ENUM_END
	};

	enum class EEquipSlotType
	{
		WEAPON,
		ARMOR,
		HEAD,
		ARM,
		LEG,
		DECO,
		ENUM_END
	};

	enum class EItemLevel
	{
		NORMAL = 1,
		UNCOMMON,
		RARE,
		EPIC,
		LEGENGARY,
		MYTHIC,
		ENUM_END
	};

	/*
	enum class EItemBuildType
	{
		WEAPON,
		ARMOR,
		HEAD,
		ARM,
		LEG,
		ENUM_END
	};
	*/
	enum class EItemCategoryType
	{
		WEAPON,
		ARMOR,
		HEAD,
		ARM,
		LEG,
		DECO,
		FOOD,
		DRINK,
		MATERIAL,
		ENUM_END
	};

	enum class EItemType
	{
		BRANCH,					//ItemIcon_108101
		STONE,					//ItemIcon_112101
		LEATHER,				//ItemIcon_401103


		// �Ϲ� ���
		SCISSORS,				//ItemIcon_101101
		FOUNTAIN_PEN,			//ItemIcon_101102
		PICKAXE,				//ItemIcon_105102

		IRON_BALL,				//ItemIcon_112103
		GLASS_BOTTLE,			//ItemIcon_112104
		PLAYING_CARDS,			//ItemIcon_113102
		CHALK,					//ItemIcon_113104
		FEATHER,				//ItemIcon_205101
		FLOWER,					//ItemIcon_205102
		RIBBON,					//ItemIcon_205103
		BUDDHIST_SCRIPTURE,		//ItemIcon_205106
		HOLY_GRAIL,				//ItemIcon_205108
		CROSS,					//ItemIcon_205109
		BINOCULARS,				//ItemIcon_205110
		NAIL,					//ItemIcon_401101

		TURTLE_SHELL,			//ItemIcon_401104
		RUBBER,					//ItemIcon_401105
		SCRAP_METAL,			//ItemIcon_401106
		LIGHTER,				//ItemIcon_401107
		LASER_POINTER,			//ItemIcon_401108
		STALLION_MEDAL,			//ItemIcon_401109
		BATTERY,				//ItemIcon_401110
		OIL,					//ItemIcon_401112
		CLOTH,					//ItemIcon_401113
		GEMSTONE,				//ItemIcon_401114
		GLUE,					//ItemIcon_401116
		PAPER,					//ItemIcon_401117
		GUNPOWDER,				//ItemIcon_401121
		PIANO_WIRE,				//ItemIcon_502104

		// �Ϲ� �۷���
		COTTON_GLOVE,			//ItemIcon_110102

		// �Ϲ� ��հ�
		RUSTY_SWORD,			//ItemIcon_102101

		// �Ϲ� �ǽ���
		WALTHER_PPK,			//ItemIcon_116101

		// �Ϲ� ��ġ
		HAMMER,					//ItemIcon_104101

		// �Ϲ� ��
		WINDBREAKER,			//ItemIcon_202101
		MONKS_ROBE,				//ItemIcon_202103
		WETSUIT,				//ItemIcon_202105
		FABRIC_ARMOR,			//ItemIcon_202106

		// �Ϲ� �Ӹ�
		HAIR_BAND,				//ItemIcon_201101
		HAT,					//ItemIcon_201102
		BIKE_HELMET,			//ItemIcon_201104

		// �Ϲ� ��
		WATCH,					//ItemIcon_203101
		BANDAGE,				//ItemIcon_203102
		BRACELET,				//ItemIcon_203104

		// �Ϲ� �ٸ�
		SLIPPER,				//ItemIcon_204101
		RUNNING_SHOES,			//ItemIcon_204102
		TIGHTS,					//ItemIcon_204103


		/********************
			��� Ÿ��
		********************/
		// ��� ���
		// SAINTS_RELIC,
		FLOWER_OF_FATE,			//ItemIcon_205203
		GLASS_PIECES,			//ItemIcon_205204
		SNIPER_SCOPE,			//ItemIcon_205206
		BUDDHA_SARIRA,			//ItemIcon_205207
		QUIVER,					//ItemIcon_205208
		FEATHER_DUSTER,			//ItemIcon_205209
		SHAMANS_BRONZE,			//ItemIcon_205211
		MARKSMAN_HANDBOOK,		//ItemIcon_205213
		OIL_CLOTH,				//ItemIcon_401202
		CHALK_POWDER,			//ItemIcon_401206
		ASH,					//ItemIcon_401210
		ELECTRONIC_PARTS,		//ItemIcon_401211
		BLUEPRINT,				//ItemIcon_401211
		IRON_SHEET,				//ItemIcon_401213
		GOLD,					//ItemIcon_401214
		HEATED_STONE,			//ItemIcon_401215
		BARBED_WIRE,			//ItemIcon_401216
		RUBY,					//ItemIcon_401217
		HARDCOVER,				//ItemIcon_401218
		ION_BATTERY,			//ItemIcon_401306
		// PATCHED_LEATHER,

		// ��� ���
		AETHER_FRINGE,			//ItemIcon_205312
		MOTOR,					//ItemIcon_401303
		GLASS_PANEL,			//ItemIcon_401305

		// ���� ���
		GLACIAL_ICE,			//ItemIcon_205402
		TRUE_SAMADHI_FIRE,		//ItemIcon_205403
		TREE_OF_LIFE,			//ItemIcon_401208
		METEORITE,				//ItemIcon_401209
		MOONSTONE,				//ItemIcon_401301
		MYTHRIL,				//ItemIcon_401304
		VF_BLOOD_SAMPLE,		//ItemIcon_401401
		GEM_OF_EVOLUTION,		//ItemIcon_401402
		FORCE_CORE,				//ItemIcon_401403
		// TAC_SKILL_MODULE,

		/********************
			���� Ÿ��
		********************/
		// �Ϲ� ����
		MEAT,					//ItemIcon_301111
		BREAD,					//ItemIcon_301110
		RAMEN,					//ItemIcon_301113
		CHOCOLATE,				//ItemIcon_301119

		/********************
			���� Ÿ��
		********************/
		// �Ϲ� ����
		HONEY,					//ItemIcon_302101
		WATER,					//ItemIcon_302102
		WHISKEY,				//ItemIcon_302104
		CARBONATED_WATER,		//ItemIcon_302107

		/********************
			�۷��� Ÿ��
		********************/
		// ��� �۷���
		LEATHER_GLOVES,			//ItemIcon_110201
		IRON_KNUCKLES,			//ItemIcon_110202
		
		// ��� �۷���
		GAUNTLET,				//ItemIcon_110301
		WING_KNUCKLES,			//ItemIcon_110302
		BONE_GAUNTLET,			//ItemIcon_110401
		SHATTER_SHELL_GAUNTLET,	//ItemIcon_110402
		PHOENIX_GLOVES,			//ItemIcon_110404
		
		// ���� �۷���
		ONE_INCH_PUNCH,			//ItemIcon_110405
		DIVINE_FIST,			//ItemIcon_110406
		BLOODWING_KNUCKLES,		//ItemIcon_110407
		FROST_PETAL_HAND,		//ItemIcon_110408
		BUDDHAS_PALM,			//ItemIcon_110409
		BRASIL_GAUNTLET,		//ItemIcon_110410
		WHITE_CLAW_PUNCH,		//ItemIcon_110411
		
		/********************
			��հ� Ÿ��
		********************/
		// ��� ��հ�
		LONG_SWORD,				//ItemIcon_102401
		
		// ��� ��հ�
		KATANA,					//ItemIcon_102301
		MURAMASA,				//ItemIcon_102402
		BASTARD_SWORD,			//ItemIcon_102403
		JEWEL_SWORD,			//ItemIcon_102404
		
		// ���� ��հ�
		THUAN_THIEN,			//ItemIcon_102405
		ARONDIGHT,				//ItemIcon_102406
		EXCALIBUR,				//ItemIcon_102407
		MONOHOSHIZAO,			//ItemIcon_102410
		HOVUD,					//ItemIcon_102411
		ARCANE_EDGE,			//ItemIcon_102413
		
		/********************
			�ǽ��� Ÿ��
		********************/
		// ��� �ǽ���
		MAGNUM_PYTHON,			//ItemIcon_116201
		BERETTA_M92F,			//ItemIcon_116202
		
		// ��� �ǽ���
		FN57,					//ItemIcon_116301
		MAGNUM_ANACONDA,		//ItemIcon_116402
		DERRINGER,				//ItemIcon_116408
		
		// ���� �ǽ���
		ELEGANCE,				//ItemIcon_116404
		ELECTRON_BLASTER,		//ItemIcon_116405
		MAGNUM_BOA,				//ItemIcon_116406
		GLOCK48,				//ItemIcon_116407
		STAMPEDE,				//ItemIcon_116409
		
		/********************
			�� Ÿ��
		********************/
		// ��� ��
		LEATHER_ARMOR,			//ItemIcon_202201
		LEATHER_JACKET,			//ItemIcon_202202
		MILITARY_SUIT,			//ItemIcon_202205
		PATCHED_ROBE,			//ItemIcon_202206
		DRESS,					//ItemIcon_202207
		BIKINI,					//ItemIcon_202209
		DIVING_SUIT,			//ItemIcon_202210
		DEACON_ROBES,			//ItemIcon_202211
		
		// ��� ��
		RIDER_JACKET,			//ItemIcon_202301
		CHAIN_ARMOR,			//ItemIcon_202302
		SUIT,					//ItemIcon_202303
		QIPAO,					//ItemIcon_202304
		SHEET_METAL_ARMOR,		//ItemIcon_202305
		HANBOK,					//ItemIcon_202306
		BULLETPROOF_VEST,		//ItemIcon_202401
		
		// ���� ��
		CARDINAL_ROBES,			//ItemIcon_202307
		SUNSET_ARMOR,			//ItemIcon_202402
		COVERT_AGENT_UNIFORM,	//ItemIcon_202404
		OPTICAL_CAMOUFLAGE_SUIT,//ItemIcon_202405
		ROCKERS_JACKET,			//ItemIcon_202406
		CRUSADER_ARMOR,			//ItemIcon_202408
		AMAZONESS_ARMOR,		//ItemIcon_202410
		DRAGON_DOBOK,			//ItemIcon_202411
		COMMANDERS_ARMOR,		//ItemIcon_202412
		BUTLERS_SUIT,			//ItemIcon_202413
		BATTLE_SUIT,			//ItemIcon_202415
		EOD_SUIT,				//ItemIcon_202417
		TUXEDO,					//ItemIcon_202418
		HIGH_PRIEST_ROBES,		//ItemIcon_202419
		CHANGPAO,				//ItemIcon_202414
		// TURNOUT_COAT,
		

		// ��� �Ӹ�
		MASK,					//ItemIcon_201201
		CIRCLET,				//ItemIcon_201202
		BERET,					//ItemIcon_201203
		CHAIN_COIF,				//ItemIcon_201204
		SAFETY_HELMET,			//ItemIcon_201205

		// ��� �Ӹ�
		BALLISTIC_HELMET,		//ItemIcon_201301
		FIRE_HELMET,			//ItemIcon_201302
		TIARA,					//ItemIcon_201303
		CROWN,					//ItemIcon_201401
		CLOSE_HELM,				//ItemIcon_201402

		// ���� �Ӹ�
		VIRTUOUS_OUTLAW,		//ItemIcon_201304
		CRYSTAL_TIARA,			//ItemIcon_201404
		MOTORCYCLE_HELMET,		//ItemIcon_201405
		TACTICAL_OPS_HELMET,	//ItemIcon_201406
		HELM_OF_BANNERET,		//ItemIcon_201407
		IMPERIAL_CROWN,			//ItemIcon_201409
		IMPERIAL_BURGONET,		//ItemIcon_201410
		MOHAWK_HEADGEAR,		//ItemIcon_201412
		VIGILANTE,				//ItemIcon_201413
		DIADEM,					//ItemIcon_201414
		CRUSADER_HELMET,		//ItemIcon_201415
		// COWBOY_HAT,
		// PLASMA_HELMET,


		// ��� ��
		LEATHER_SHIELD,			//ItemIcon_203201
		SQUARD_LEADER_ARMBAND,	//ItemIcon_203202
		BRACER,					//ItemIcon_203203
		BROKEN_WATCH,			//ItemIcon_203204

		// ��� ��
		SHEATH,					//ItemIcon_203301
		GOLDEN_BRACELET,		//ItemIcon_203302
		BAZUBAND,				//ItemIcon_203303
		CRIMSON_BRACELET,		//ItemIcon_203304
		BARBED_BLOSSOM,			//ItemIcon_203305
		STEEL_SHIELD,			//ItemIcon_203401

		// ���� ��
		CORRUPTING_TOUCH,		//ItemIcon_203306
		SWORD_STOPPER,			//ItemIcon_203402
		DRAUPNIR,				//ItemIcon_203403
		VITAL_SIGH_SENSOR,		//ItemIcon_203405
		CREED_OF_THE_KNIGHT,	//ItemIcon_203406
		SHEATH_OF_SHAH_JUHAN,	//ItemIcon_203407
		BURNISHED_AEGIS,		//ItemIcon_203409
		TINDALOS_BAND,			//ItemIcon_203410
		NIGHTINGALE,			//ItemIcon_203411
		PLASMA_ARC,				//ItemIcon_203412
		SMART_BAND,				//ItemIcon_203414
		// MINUTEMAN_ARMBAND,
		SPORTS_WATCH,			//ItemIcon_203506


		// ��� �ٸ�
		KNEE_PADS,				//ItemIcon_204201
		CHAIN_LEGGINGS,			//ItemIcon_204202
		HIGH_HEELS,				//ItemIcon_204203
		HEELYS,					//ItemIcon_204204
		CLOGS,					//ItemIcon_204205
		REPAIRED_SLIPPERS,		//ItemIcon_204301
		BOOTS,					//ItemIcon_204302

		// ��� �ٸ�
		STEEL_KNEE_PADS,		//ItemIcon_204401
		COMBAT_BOOTS,			//ItemIcon_204404

		// ���� �ٸ�
		HIKING_BOOTS,			//ItemIcon_204303
		GLACIER_CRAMPONS,		//ItemIcon_204304
		FEATHER_BOOTS,			//ItemIcon_204402
		MAVERICK_RUNNER,		//ItemIcon_204403
		STRAITJACKET_SNEAKERS,	//ItemIcon_204406
		BUCEPHALUS,				//ItemIcon_204408
		EOD_BOOTS,				//ItemIcon_204409
		WHITE_RHINOS,			//ItemIcon_204411
		TACHYON_BRACE,			//ItemIcon_204412
		SCV,					//ItemIcon_204415

		// ��� ����

		// ��� ����
		BOILING_WATER,			//ItemIcon_302201
		COLA,					//ItemIcon_302209
		HIGHBALL,				//ItemIcon_302213
		HONEY_WATER,			//ItemIcon_302215

		ENUM_END
	};

	enum class ESkillType
	{
		FIRST,
		SECOND,
		THIRD,
		FOURTH,
		PASSIVE,
		ENUM_END
	};

	enum class EBossType
	{
		WICKLINE,
		ALPHA,
		OMEGA,
		ENUM_END
	};

	enum class ESurvivorType
	{
		HYUNWOO,
		AYA,
		ROZZI,
		YUKI,
		ENUM_END
	};

	enum class EDayType
	{
		DAY,
		NIGHT
	};

	enum class ECraftType
	{
		METAL,
		FOOD,
		ENUM_END
	};

	enum class ECraftState
	{
		CRAFT_NONE,
		CRAFT_METAL_BEGIN,
		CRAFT_METAL,
		CRAFT_FOOD_BEGIN,
		CRAFT_FOOD,
		ENUM_END
	};

	enum class ECraftAnimState
	{
		CRAFT_NONE,
		CRAFT_METAL_BEGIN,
		CRAFT_METAL,
		CRAFT_FOOD_BEGIN,
		CRAFT_FOOD,
		ENUM_END
	};

	enum class ECraftToolType
	{
		HAMMER,
		DRIVER,
		FRYING_PAN,
		ENUM_END
	};

	enum class EProjectileType
	{
		AYA,
		ROZZI,

		WICKLINE_SKILL_01,
		WICKLINE_SKILL_02,
		ALPHA_SKILL_02,
		OMEGA_SKILL_02,
		ENUM_END
	};

	enum class EEnemyType
	{
		WILD_ANIMAL,
		SURVIVOR,
		BOSS,
		ENUM_END
	};
}
