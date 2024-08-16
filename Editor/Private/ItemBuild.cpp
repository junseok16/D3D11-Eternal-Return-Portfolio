#include "pch.h"
#include "ItemBuild.h"

#include "Inventory.h"

std::shared_ptr<CItemBuild> Editor::CItemBuild::Create(const shared_ptr<CInventory>& _spInventory)
{
	const std::shared_ptr<CItemBuild> spItemBuild = make_shared<CItemBuild>();
	spItemBuild->Initialize(_spInventory);
	return spItemBuild;
}

HRESULT Editor::CItemBuild::Initialize(const shared_ptr<CInventory>& _spInventory)
{
	m_wpInventory = _spInventory;

	// ÀÏ¹Ý Àç·á > °í±Þ Àç·á
	CreateItemBuildOrder({ EItemType::FLOWER, EItemType::PLAYING_CARDS }, EItemType::FLOWER_OF_FATE, EItemCategoryType::MATERIAL, EItemLevel::UNCOMMON);
	CreateItemBuildOrder({ EItemType::GLASS_BOTTLE, EItemType::STONE }, EItemType::GLASS_PIECES, EItemCategoryType::MATERIAL, EItemLevel::UNCOMMON);
	CreateItemBuildOrder({ EItemType::LASER_POINTER, EItemType::BINOCULARS }, EItemType::SNIPER_SCOPE, EItemCategoryType::MATERIAL, EItemLevel::UNCOMMON);
	CreateItemBuildOrder({ EItemType::BUDDHIST_SCRIPTURE, EItemType::MONKS_ROBE }, EItemType::BUDDHA_SARIRA, EItemCategoryType::MATERIAL, EItemLevel::UNCOMMON);
	// CreateItemBuildOrder({ EItemType::FEATHER, EItemType::BAMBOO }, EItemType::QUIVER, EItemCategoryType::MATERIAL, EItemLevel::UNCOMMON);
	// CreateItemBuildOrder({ EItemType::SHORT_ROD, EItemType::FEATHER }, EItemType::FEATHER_DUSTER, EItemCategoryType::MATERIAL, EItemLevel::UNCOMMON);
	CreateItemBuildOrder({ EItemType::RUSTY_SWORD, EItemType::STALLION_MEDAL },EItemType::SHAMANS_BRONZE, EItemCategoryType::MATERIAL, EItemLevel::UNCOMMON);
	// CreateItemBuildOrder({ EItemType::SHORT_CROSSBOW, EItemType::FEDOROVA }, EItemType::MARKSMAN_HANDBOOK, EItemCategoryType::MATERIAL, EItemLevel::UNCOMMON);
	CreateItemBuildOrder({ EItemType::OIL, EItemType::BANDAGE }, EItemType::OIL_CLOTH, EItemCategoryType::MATERIAL, EItemLevel::UNCOMMON);
	CreateItemBuildOrder({ EItemType::CHALK, EItemType::STONE }, EItemType::CHALK_POWDER, EItemCategoryType::MATERIAL, EItemLevel::UNCOMMON);
	CreateItemBuildOrder({ EItemType::PAPER, EItemType::LIGHTER }, EItemType::ASH, EItemCategoryType::MATERIAL, EItemLevel::UNCOMMON);
	CreateItemBuildOrder({ EItemType::BATTERY, EItemType::PIANO_WIRE }, EItemType::ELECTRONIC_PARTS, EItemCategoryType::MATERIAL, EItemLevel::UNCOMMON);
	CreateItemBuildOrder({ EItemType::FOUNTAIN_PEN, EItemType::PAPER }, EItemType::BLUEPRINT, EItemCategoryType::MATERIAL, EItemLevel::UNCOMMON);
	// CreateItemBuildOrder({ EItemType::SCRAP_METAL, EItemType::HAMMER }, EItemType::IRON_SHEET, EItemCategoryType::MATERIAL, EItemLevel::UNCOMMON);
	CreateItemBuildOrder({ EItemType::PICKAXE, EItemType::GEMSTONE }, EItemType::GOLD, EItemCategoryType::MATERIAL, EItemLevel::UNCOMMON);
	CreateItemBuildOrder({ EItemType::STONE, EItemType::LIGHTER }, EItemType::HEATED_STONE, EItemCategoryType::MATERIAL, EItemLevel::UNCOMMON);
	// CreateItemBuildOrder({ EItemType::PIANO_WIRE, EItemType::HAMMER }, EItemType::BARBED_WIRE, EItemCategoryType::MATERIAL, EItemLevel::UNCOMMON);
	// CreateItemBuildOrder({ EItemType::HAMMER, EItemType::GEMSTONE }, EItemType::RUBY, EItemCategoryType::MATERIAL, EItemLevel::UNCOMMON);
	CreateItemBuildOrder({ EItemType::PAPER, EItemType::LEATHER }, EItemType::HARDCOVER, EItemCategoryType::MATERIAL, EItemLevel::UNCOMMON);
	// CreateItemBuildOrder({ EItemType::BATTERY, EItemType::CARBONATED_WATER }, EItemType::ION_BATTERY, EItemCategoryType::MATERIAL, EItemLevel::UNCOMMON);

	// °í±Þ Àç·á > Èñ±Í Àç·á
	CreateItemBuildOrder({ EItemType::FEATHER, EItemType::FLOWER_OF_FATE }, EItemType::AETHER_FRINGE, EItemCategoryType::MATERIAL, EItemLevel::RARE);
	CreateItemBuildOrder({ EItemType::ELECTRONIC_PARTS, EItemType::SCRAP_METAL }, EItemType::MOTOR, EItemCategoryType::MATERIAL, EItemLevel::RARE);
	CreateItemBuildOrder({ EItemType::GLASS_PIECES, EItemType::GLUE }, EItemType::GLASS_PANEL, EItemCategoryType::MATERIAL, EItemLevel::RARE);

	// Èñ±Í Àç·á > ¿µ¿õ Àç·á
	CreateItemBuildOrder({ EItemType::LIGHTER, EItemType::TREE_OF_LIFE }, EItemType::TRUE_SAMADHI_FIRE, EItemCategoryType::MATERIAL, EItemLevel::EPIC);
	CreateItemBuildOrder({ EItemType::STONE, EItemType::METEORITE }, EItemType::MOONSTONE, EItemCategoryType::MATERIAL, EItemLevel::EPIC);
	CreateItemBuildOrder({ EItemType::METEORITE, EItemType::TREE_OF_LIFE }, EItemType::FORCE_CORE, EItemCategoryType::MATERIAL, EItemLevel::EPIC);




	// ÀÏ¹Ý ±Û·¯ºê > °í±Þ ±Û·¯ºê
	CreateItemBuildOrder({ EItemType::COTTON_GLOVE, EItemType::LEATHER }, EItemType::LEATHER_GLOVES, EItemCategoryType::WEAPON, EItemLevel::UNCOMMON);
	CreateItemBuildOrder({ EItemType::COTTON_GLOVE, EItemType::SCRAP_METAL }, EItemType::IRON_KNUCKLES, EItemCategoryType::WEAPON, EItemLevel::UNCOMMON);

	// °í±Þ ±Û·¯ºê > Èñ±Í ±Û·¯ºê
	CreateItemBuildOrder({ EItemType::LEATHER_GLOVES, EItemType::TURTLE_SHELL }, EItemType::BONE_GAUNTLET, EItemCategoryType::WEAPON, EItemLevel::RARE);
	CreateItemBuildOrder({ EItemType::LEATHER_GLOVES, EItemType::ASH }, EItemType::PHOENIX_GLOVES, EItemCategoryType::WEAPON, EItemLevel::RARE);
	CreateItemBuildOrder({ EItemType::IRON_KNUCKLES, EItemType::CLOTH }, EItemType::GAUNTLET, EItemCategoryType::WEAPON, EItemLevel::RARE);
	CreateItemBuildOrder({ EItemType::IRON_KNUCKLES, EItemType::FEATHER }, EItemType::WING_KNUCKLES, EItemCategoryType::WEAPON, EItemLevel::RARE);
	CreateItemBuildOrder({ EItemType::GAUNTLET, EItemType::GUNPOWDER }, EItemType::SHATTER_SHELL_GAUNTLET, EItemCategoryType::WEAPON, EItemLevel::RARE);

	// Èñ±Í ±Û·¯ºê > ¿µ¿õ ±Û·¯ºê
	CreateItemBuildOrder({ EItemType::BONE_GAUNTLET, EItemType::FEATHER_DUSTER }, EItemType::ONE_INCH_PUNCH, EItemCategoryType::WEAPON, EItemLevel::EPIC);
	CreateItemBuildOrder({ EItemType::SHATTER_SHELL_GAUNTLET, EItemType::CROSS }, EItemType::DIVINE_FIST, EItemCategoryType::WEAPON, EItemLevel::EPIC);
	CreateItemBuildOrder({ EItemType::WING_KNUCKLES, EItemType::RUBY }, EItemType::BLOODWING_KNUCKLES, EItemCategoryType::WEAPON, EItemLevel::EPIC);
	// CreateItemBuildOrder({ EItemType::PHOENIX_GLOVES, EItemType::ICE }, EItemType::FROST_PETAL_HAND);
	CreateItemBuildOrder({ EItemType::PHOENIX_GLOVES, EItemType::BUDDHIST_SCRIPTURE }, EItemType::BUDDHAS_PALM, EItemCategoryType::WEAPON, EItemLevel::EPIC);
	CreateItemBuildOrder({ EItemType::GAUNTLET, EItemType::OIL_CLOTH }, EItemType::BRASIL_GAUNTLET, EItemCategoryType::WEAPON, EItemLevel::EPIC);
	CreateItemBuildOrder({ EItemType::PHOENIX_GLOVES, EItemType::CHALK_POWDER }, EItemType::WHITE_CLAW_PUNCH, EItemCategoryType::WEAPON, EItemLevel::EPIC);
	


	// ÀÏ¹Ý ¾ç¼Õ°Ë > °í±Þ ¾ç¼Õ°Ë

	// °í±Þ ¾ç¼Õ°Ë > Èñ±Í ¾ç¼Õ°Ë

	// Èñ±Í ¾ç¼Õ°Ë > ¿µ¿õ ¾ç¼Õ°Ë


	// ÀÏ¹Ý ÇÇ½ºÅç > °í±Þ ÇÇ½ºÅç
	CreateItemBuildOrder({ EItemType::WALTHER_PPK, EItemType::OIL }, EItemType::MAGNUM_PYTHON, EItemCategoryType::WEAPON, EItemLevel::UNCOMMON);
	CreateItemBuildOrder({ EItemType::WALTHER_PPK, EItemType::LEATHER }, EItemType::BERETTA_M92F, EItemCategoryType::WEAPON, EItemLevel::UNCOMMON);

	// °í±Þ ÇÇ½ºÅç > Èñ±Í ÇÇ½ºÅç
	CreateItemBuildOrder({ EItemType::BERETTA_M92F, EItemType::LASER_POINTER }, EItemType::FN57, EItemCategoryType::WEAPON, EItemLevel::RARE);
	CreateItemBuildOrder({ EItemType::MAGNUM_PYTHON, EItemType::BLUEPRINT }, EItemType::MAGNUM_ANACONDA, EItemCategoryType::WEAPON, EItemLevel::RARE);
	CreateItemBuildOrder({ EItemType::WALTHER_PPK, EItemType::BARBED_WIRE }, EItemType::DERRINGER, EItemCategoryType::WEAPON, EItemLevel::RARE);

	// Èñ±Í ÇÇ½ºÅç > ¿µ¿õ ÇÇ½ºÅç
	CreateItemBuildOrder({ EItemType::FN57, EItemType::ASH }, EItemType::ELEGANCE, EItemCategoryType::WEAPON, EItemLevel::EPIC);
	CreateItemBuildOrder({ EItemType::MAGNUM_ANACONDA, EItemType::BATTERY }, EItemType::ELECTRON_BLASTER, EItemCategoryType::WEAPON, EItemLevel::EPIC);
	CreateItemBuildOrder({ EItemType::MAGNUM_ANACONDA, EItemType::GOLD }, EItemType::MAGNUM_BOA, EItemCategoryType::WEAPON, EItemLevel::EPIC);
	CreateItemBuildOrder({ EItemType::FN57, EItemType::FEATHER_DUSTER }, EItemType::GLOCK48, EItemCategoryType::WEAPON, EItemLevel::EPIC);
	CreateItemBuildOrder({ EItemType::DERRINGER, EItemType::GOLD }, EItemType::STAMPEDE, EItemCategoryType::WEAPON, EItemLevel::EPIC);




	// ÀÏ¹Ý ¿Ê > °í±Þ ¿Ê
	CreateItemBuildOrder({ EItemType::FABRIC_ARMOR, EItemType::LEATHER }, EItemType::LEATHER_ARMOR, EItemCategoryType::ARMOR, EItemLevel::UNCOMMON);
	CreateItemBuildOrder({ EItemType::WINDBREAKER, EItemType::LEATHER }, EItemType::LEATHER_JACKET, EItemCategoryType::ARMOR, EItemLevel::UNCOMMON);
	CreateItemBuildOrder({ EItemType::WINDBREAKER, EItemType::BRANCH }, EItemType::MILITARY_SUIT, EItemCategoryType::ARMOR, EItemLevel::UNCOMMON);
	CreateItemBuildOrder({ EItemType::MONKS_ROBE, EItemType::BANDAGE }, EItemType::PATCHED_ROBE, EItemCategoryType::ARMOR, EItemLevel::UNCOMMON);
	CreateItemBuildOrder({ EItemType::CLOTH, EItemType::SCISSORS }, EItemType::DRESS, EItemCategoryType::ARMOR, EItemLevel::UNCOMMON);
	CreateItemBuildOrder({ EItemType::WETSUIT, EItemType::SCISSORS }, EItemType::BIKINI, EItemCategoryType::ARMOR, EItemLevel::UNCOMMON);
	CreateItemBuildOrder({ EItemType::WETSUIT, EItemType::RUBBER }, EItemType::DIVING_SUIT, EItemCategoryType::ARMOR, EItemLevel::UNCOMMON);
	CreateItemBuildOrder({ EItemType::CROSS, EItemType::CLOTH }, EItemType::DEACON_ROBES, EItemCategoryType::ARMOR, EItemLevel::UNCOMMON);
	
	// °í±Þ ¿Ê > Èñ±Í ¿Ê
	// CreateItemBuildOrder({ EItemType::LEATHER_JACKET, EItemType::STEEl_CHAIN }, EItemType::RIDER_JACKET, EItemCategoryType::ARMOR, EItemLevel::RARE);
	// CreateItemBuildOrder({ EItemType::LEATHER_ARMOR, EItemType::STEEl_CHAIN }, EItemType::CHAIN_ARMOR, EItemCategoryType::ARMOR, EItemLevel::RARE);
	CreateItemBuildOrder({ EItemType::LEATHER_JACKET, EItemType::RIBBON }, EItemType::SUIT, EItemCategoryType::ARMOR, EItemLevel::RARE);
	// CreateItemBuildOrder({ EItemType::DRESS, EItemType::RAZOR }, EItemType::QIPAO, EItemCategoryType::ARMOR, EItemLevel::RARE);
	CreateItemBuildOrder({ EItemType::FABRIC_ARMOR, EItemType::IRON_SHEET }, EItemType::SHEET_METAL_ARMOR, EItemCategoryType::ARMOR, EItemLevel::RARE);
	CreateItemBuildOrder({ EItemType::PATCHED_ROBE, EItemType::FLOWER }, EItemType::HANBOK, EItemCategoryType::ARMOR, EItemLevel::RARE);
	CreateItemBuildOrder({ EItemType::MILITARY_SUIT, EItemType::SCRAP_METAL }, EItemType::BULLETPROOF_VEST, EItemCategoryType::ARMOR, EItemLevel::RARE);
	
	// Èñ±Í ¿Ê > ¿µ¿õ ¿Ê
	CreateItemBuildOrder({ EItemType::DEACON_ROBES, EItemType::OIL_CLOTH }, EItemType::CARDINAL_ROBES, EItemCategoryType::ARMOR, EItemLevel::EPIC);
	CreateItemBuildOrder({ EItemType::CHAIN_ARMOR, EItemType::RUBY }, EItemType::SUNSET_ARMOR, EItemCategoryType::ARMOR, EItemLevel::EPIC);
	CreateItemBuildOrder({ EItemType::HANBOK, EItemType::STALLION_MEDAL }, EItemType::COVERT_AGENT_UNIFORM, EItemCategoryType::ARMOR, EItemLevel::EPIC);
	CreateItemBuildOrder({ EItemType::DIVING_SUIT, EItemType::GLASS_PANEL }, EItemType::OPTICAL_CAMOUFLAGE_SUIT, EItemCategoryType::ARMOR, EItemLevel::EPIC);
	CreateItemBuildOrder({ EItemType::RIDER_JACKET, EItemType::IRON_BALL }, EItemType::ROCKERS_JACKET, EItemCategoryType::ARMOR, EItemLevel::EPIC);
	// CreateItemBuildOrder({ EItemType::SHEET_METAL_ARMOR, EItemType::SAINTS_RELIC }, EItemType::CRUSADER_ARMOR, EItemCategoryType::ARMOR, EItemLevel::EPIC);
	CreateItemBuildOrder({ EItemType::SHEET_METAL_ARMOR, EItemType::BIKINI }, EItemType::AMAZONESS_ARMOR, EItemCategoryType::ARMOR, EItemLevel::EPIC);
	CreateItemBuildOrder({ EItemType::QIPAO, EItemType::MONKS_ROBE }, EItemType::DRAGON_DOBOK, EItemCategoryType::ARMOR, EItemLevel::EPIC);
	CreateItemBuildOrder({ EItemType::CHAIN_ARMOR, EItemType::GOLD }, EItemType::COMMANDERS_ARMOR, EItemCategoryType::ARMOR, EItemLevel::EPIC);
	CreateItemBuildOrder({ EItemType::SUIT, EItemType::FEATHER_DUSTER }, EItemType::BUTLERS_SUIT, EItemCategoryType::ARMOR, EItemLevel::EPIC);
	CreateItemBuildOrder({ EItemType::BULLETPROOF_VEST, EItemType::DIVING_SUIT }, EItemType::BATTLE_SUIT, EItemCategoryType::ARMOR, EItemLevel::EPIC);
	CreateItemBuildOrder({ EItemType::BULLETPROOF_VEST, EItemType::PATCHED_ROBE }, EItemType::EOD_SUIT, EItemCategoryType::ARMOR, EItemLevel::EPIC);
	CreateItemBuildOrder({ EItemType::SUIT, EItemType::CLOTH }, EItemType::TUXEDO, EItemCategoryType::ARMOR, EItemLevel::EPIC);
	CreateItemBuildOrder({ EItemType::DEACON_ROBES, EItemType::SHAMANS_BRONZE }, EItemType::HIGH_PRIEST_ROBES, EItemCategoryType::ARMOR, EItemLevel::EPIC);
	CreateItemBuildOrder({ EItemType::QIPAO, EItemType::QUIVER }, EItemType::CHANGPAO, EItemCategoryType::ARMOR, EItemLevel::EPIC);



	// ÀÏ¹Ý ¸Ó¸® > °í±Þ ¸Ó¸®
	CreateItemBuildOrder({ EItemType::HAIR_BAND, EItemType::FEATHER }, EItemType::MASK, EItemCategoryType::HEAD, EItemLevel::UNCOMMON);
	CreateItemBuildOrder({ EItemType::HAIR_BAND, EItemType::BRANCH }, EItemType::CIRCLET, EItemCategoryType::HEAD, EItemLevel::UNCOMMON);
	CreateItemBuildOrder({ EItemType::HAT, EItemType::SCISSORS }, EItemType::BERET, EItemCategoryType::HEAD, EItemLevel::UNCOMMON);
	// CreateItemBuildOrder({ EItemType::HAT, EItemType::STEEL_CHAIN }, EItemType::CHAIN_COIF, EItemCategoryType::HEAD, EItemLevel::UNCOMMON);
	CreateItemBuildOrder({ EItemType::BIKE_HELMET, EItemType::STONE }, EItemType::SAFETY_HELMET, EItemCategoryType::HEAD, EItemLevel::UNCOMMON);

	// °í±Þ ¸Ó¸® > Èñ±Í ¸Ó¸®
	CreateItemBuildOrder({ EItemType::BERET, EItemType::BIKE_HELMET }, EItemType::BALLISTIC_HELMET, EItemCategoryType::HEAD, EItemLevel::RARE);
	CreateItemBuildOrder({ EItemType::SAFETY_HELMET, EItemType::LIGHTER }, EItemType::FIRE_HELMET, EItemCategoryType::HEAD, EItemLevel::RARE);
	CreateItemBuildOrder({ EItemType::CIRCLET, EItemType::STALLION_MEDAL }, EItemType::TIARA, EItemCategoryType::HEAD, EItemLevel::RARE);
	CreateItemBuildOrder({ EItemType::BERET, EItemType::GOLD }, EItemType::CROWN, EItemCategoryType::HEAD, EItemLevel::RARE);
	// CreateItemBuildOrder({ EItemType::STEEL_CHAIN, EItemType::MASK }, EItemType::CLOSE_HELM, EItemCategoryType::HEAD, EItemLevel::RARE);

	// Èñ±Í ¸Ó¸® > ¿µ¿õ ¸Ó¸®
	CreateItemBuildOrder({ EItemType::CLOTH, EItemType::AETHER_FRINGE }, EItemType::VIRTUOUS_OUTLAW, EItemCategoryType::HEAD, EItemLevel::EPIC);
	CreateItemBuildOrder({ EItemType::TIARA, EItemType::GLASS_PIECES }, EItemType::CRYSTAL_TIARA, EItemCategoryType::HEAD, EItemLevel::EPIC);
	CreateItemBuildOrder({ EItemType::SAFETY_HELMET, EItemType::MOTOR }, EItemType::MOTORCYCLE_HELMET, EItemCategoryType::HEAD, EItemLevel::EPIC);
	CreateItemBuildOrder({ EItemType::BALLISTIC_HELMET, EItemType::ELECTRONIC_PARTS }, EItemType::TACTICAL_OPS_HELMET, EItemCategoryType::HEAD, EItemLevel::EPIC);
	CreateItemBuildOrder({ EItemType::CLOSE_HELM, EItemType::RUBBER }, EItemType::HELM_OF_BANNERET, EItemCategoryType::HEAD, EItemLevel::EPIC);
	CreateItemBuildOrder({ EItemType::CROWN, EItemType::RIBBON }, EItemType::IMPERIAL_CROWN, EItemCategoryType::HEAD, EItemLevel::EPIC);
	CreateItemBuildOrder({ EItemType::CLOSE_HELM, EItemType::SCRAP_METAL }, EItemType::IMPERIAL_BURGONET, EItemCategoryType::HEAD, EItemLevel::EPIC);
	CreateItemBuildOrder({ EItemType::FIRE_HELMET, EItemType::NAIL }, EItemType::MOHAWK_HEADGEAR, EItemCategoryType::HEAD, EItemLevel::EPIC);
	CreateItemBuildOrder({ EItemType::FIRE_HELMET, EItemType::SCRAP_METAL }, EItemType::VIGILANTE, EItemCategoryType::HEAD, EItemLevel::EPIC);
	CreateItemBuildOrder({ EItemType::BARBED_BLOSSOM, EItemType::CIRCLET }, EItemType::DIADEM, EItemCategoryType::HEAD, EItemLevel::EPIC);
	CreateItemBuildOrder({ EItemType::CROWN, EItemType::CROSS }, EItemType::CRUSADER_HELMET, EItemCategoryType::HEAD, EItemLevel::EPIC);


	// ÀÏ¹Ý ÆÈ > °í±Þ ÆÈ
	CreateItemBuildOrder({ EItemType::TURTLE_SHELL, EItemType::LEATHER }, EItemType::LEATHER_SHIELD, EItemCategoryType::ARM, EItemLevel::UNCOMMON);
	// CreateItemBuildOrder({ EItemType::BANDAGE, EItemType::NEEDLE }, EItemType::SQUARD_LEADER_ARMBAND, EItemCategoryType::ARM, EItemLevel::UNCOMMON);
	CreateItemBuildOrder({ EItemType::BANDAGE, EItemType::LEATHER }, EItemType::BRACER, EItemCategoryType::ARM, EItemLevel::UNCOMMON);
	CreateItemBuildOrder({ EItemType::WATCH, EItemType::GLUE }, EItemType::BROKEN_WATCH, EItemCategoryType::ARM, EItemLevel::UNCOMMON);

	// °í±Þ ÆÈ > Èñ±Í ÆÈ
	// CreateItemBuildOrder({ EItemType::IRON_SHEET, EItemType::PATCHED_LEATHER }, EItemType::SHEATH, EItemCategoryType::ARM, EItemLevel::RARE);
	CreateItemBuildOrder({ EItemType::BRACELET, EItemType::GOLD }, EItemType::GOLDEN_BRACELET, EItemCategoryType::ARM, EItemLevel::RARE);
	CreateItemBuildOrder({ EItemType::BRACER, EItemType::IRON_SHEET }, EItemType::BAZUBAND, EItemCategoryType::ARM, EItemLevel::RARE);
	CreateItemBuildOrder({ EItemType::BRACELET, EItemType::RUBY }, EItemType::CRIMSON_BRACELET, EItemCategoryType::ARM, EItemLevel::RARE);
	CreateItemBuildOrder({ EItemType::FLOWER, EItemType::BARBED_WIRE }, EItemType::BARBED_BLOSSOM, EItemCategoryType::ARM, EItemLevel::RARE);
	CreateItemBuildOrder({ EItemType::LEATHER_SHIELD, EItemType::SCRAP_METAL }, EItemType::STEEL_SHIELD, EItemCategoryType::ARM, EItemLevel::RARE);

	// Èñ±Í ÆÈ > ¿µ¿õ ÆÈ
	CreateItemBuildOrder({ EItemType::OIL_CLOTH, EItemType::ASH }, EItemType::CORRUPTING_TOUCH, EItemCategoryType::ARM, EItemLevel::EPIC);
	CreateItemBuildOrder({ EItemType::BAZUBAND, EItemType::NAIL }, EItemType::SWORD_STOPPER, EItemCategoryType::ARM, EItemLevel::EPIC);
	CreateItemBuildOrder({ EItemType::GOLDEN_BRACELET, EItemType::BRACER }, EItemType::DRAUPNIR, EItemCategoryType::ARM, EItemLevel::EPIC);
	CreateItemBuildOrder({ EItemType::BROKEN_WATCH, EItemType::ELECTRONIC_PARTS }, EItemType::VITAL_SIGH_SENSOR, EItemCategoryType::ARM, EItemLevel::EPIC);
	CreateItemBuildOrder({ EItemType::STEEL_SHIELD, EItemType::SQUARD_LEADER_ARMBAND }, EItemType::CREED_OF_THE_KNIGHT, EItemCategoryType::ARM, EItemLevel::EPIC);
	CreateItemBuildOrder({ EItemType::SHEATH, EItemType::GEMSTONE }, EItemType::SHEATH_OF_SHAH_JUHAN, EItemCategoryType::ARM, EItemLevel::EPIC);
	CreateItemBuildOrder({ EItemType::CRIMSON_BRACELET, EItemType::LEATHER_SHIELD }, EItemType::BURNISHED_AEGIS, EItemCategoryType::ARM, EItemLevel::EPIC);
	CreateItemBuildOrder({ EItemType::GOLDEN_BRACELET, EItemType::BROKEN_WATCH }, EItemType::TINDALOS_BAND, EItemCategoryType::ARM, EItemLevel::EPIC);
	// CreateItemBuildOrder({ EItemType::BANDAGE, EItemType::HEALING_POTION }, EItemType::NIGHTINGALE, EItemCategoryType::ARM, EItemLevel::EPIC);
	CreateItemBuildOrder({ EItemType::STEEL_SHIELD, EItemType::ELECTRONIC_PARTS }, EItemType::PLASMA_ARC, EItemCategoryType::ARM, EItemLevel::EPIC);
	CreateItemBuildOrder({ EItemType::BARBED_BLOSSOM, EItemType::BLUEPRINT }, EItemType::SMART_BAND, EItemCategoryType::ARM, EItemLevel::EPIC);
	CreateItemBuildOrder({ EItemType::BARBED_WIRE, EItemType::BROKEN_WATCH }, EItemType::SPORTS_WATCH, EItemCategoryType::ARM, EItemLevel::EPIC);


	// ÀÏ¹Ý ´Ù¸® > °í±Þ ´Ù¸®
	CreateItemBuildOrder({ EItemType::TIGHTS, EItemType::LEATHER }, EItemType::KNEE_PADS, EItemCategoryType::LEG, EItemLevel::UNCOMMON);
	// CreateItemBuildOrder({ EItemType::TIGHTS, EItemType::STEEL_CHAIN }, EItemType::CHAIN_LEGGINGS, EItemCategoryType::LEG, EItemLevel::UNCOMMON);
	CreateItemBuildOrder({ EItemType::SLIPPER, EItemType::SCRAP_METAL }, EItemType::HIGH_HEELS, EItemCategoryType::LEG, EItemLevel::UNCOMMON);
	CreateItemBuildOrder({ EItemType::RUNNING_SHOES, EItemType::IRON_BALL }, EItemType::HEELYS, EItemCategoryType::LEG, EItemLevel::UNCOMMON);
	CreateItemBuildOrder({ EItemType::BRANCH, EItemType::PICKAXE }, EItemType::CLOGS, EItemCategoryType::LEG, EItemLevel::UNCOMMON);
	CreateItemBuildOrder({ EItemType::SLIPPER, EItemType::CLOTH }, EItemType::REPAIRED_SLIPPERS, EItemCategoryType::LEG, EItemLevel::UNCOMMON);
	CreateItemBuildOrder({ EItemType::RUNNING_SHOES, EItemType::LEATHER }, EItemType::BOOTS, EItemCategoryType::LEG, EItemLevel::UNCOMMON);

	// °í±Þ ´Ù¸® > Èñ±Í ´Ù¸®
	CreateItemBuildOrder({ EItemType::KNEE_PADS, EItemType::SCRAP_METAL }, EItemType::STEEL_KNEE_PADS, EItemCategoryType::LEG, EItemLevel::RARE);
	CreateItemBuildOrder({ EItemType::BOOTS, EItemType::OIL_CLOTH }, EItemType::COMBAT_BOOTS, EItemCategoryType::LEG, EItemLevel::RARE);

	// Èñ±Í ´Ù¸® > ¿µ¿õ ´Ù¸®
	// CreateItemBuildOrder({ EItemType::CLOGS, EItemType::PATCHED_LEATHER }, EItemType::HIKING_BOOTS, EItemCategoryType::LEG, EItemLevel::EPIC);
	CreateItemBuildOrder({ EItemType::HIGH_HEELS, EItemType::SHAMANS_BRONZE }, EItemType::GLACIER_CRAMPONS, EItemCategoryType::LEG, EItemLevel::EPIC);
	CreateItemBuildOrder({ EItemType::COMBAT_BOOTS, EItemType::FEATHER }, EItemType::FEATHER_BOOTS, EItemCategoryType::LEG, EItemLevel::EPIC);
	CreateItemBuildOrder({ EItemType::HEELYS, EItemType::BLUEPRINT }, EItemType::MAVERICK_RUNNER, EItemCategoryType::LEG, EItemLevel::EPIC);
	CreateItemBuildOrder({ EItemType::REPAIRED_SLIPPERS, EItemType::ASH }, EItemType::STRAITJACKET_SNEAKERS, EItemCategoryType::LEG, EItemLevel::EPIC);
	CreateItemBuildOrder({ EItemType::HIGH_HEELS, EItemType::CHAIN_LEGGINGS }, EItemType::BUCEPHALUS, EItemCategoryType::LEG, EItemLevel::EPIC);
	CreateItemBuildOrder({ EItemType::BOOTS, EItemType::STEEL_KNEE_PADS }, EItemType::EOD_BOOTS, EItemCategoryType::LEG, EItemLevel::EPIC);
	CreateItemBuildOrder({ EItemType::COMBAT_BOOTS, EItemType::NAIL }, EItemType::WHITE_RHINOS, EItemCategoryType::LEG, EItemLevel::EPIC);
	CreateItemBuildOrder({ EItemType::KNEE_PADS, EItemType::MOTOR }, EItemType::TACHYON_BRACE, EItemCategoryType::LEG, EItemLevel::EPIC);
	CreateItemBuildOrder({ EItemType::HEELYS, EItemType::ELECTRONIC_PARTS }, EItemType::SCV, EItemCategoryType::LEG, EItemLevel::EPIC);

	// ÀÏ¹Ý À½½Ä > °í±Þ À½½Ä

	// ÀÏ¹Ý À½·á > °í±Þ À½·á
	CreateItemBuildOrder({ EItemType::WATER, EItemType::LIGHTER }, EItemType::BOILING_WATER, EItemCategoryType::DRINK, EItemLevel::UNCOMMON);
	CreateItemBuildOrder({ EItemType::HONEY, EItemType::CARBONATED_WATER }, EItemType::COLA, EItemCategoryType::DRINK, EItemLevel::UNCOMMON);
	CreateItemBuildOrder({ EItemType::WHISKEY, EItemType::CARBONATED_WATER }, EItemType::HIGHBALL, EItemCategoryType::DRINK, EItemLevel::UNCOMMON);
	CreateItemBuildOrder({ EItemType::WATER, EItemType::HONEY }, EItemType::HONEY_WATER, EItemCategoryType::DRINK, EItemLevel::UNCOMMON);

	return S_OK;
}

void Editor::CItemBuild::Release()
{
	for (auto& pair : m_mapItemBuildOrders)
	{
		pair.second = nullptr;
	}
	m_mapItemBuildOrders.clear();
}

void Editor::CItemBuild::CreateItemBuildOrder
(
	const std::vector<EItemType>& _vecInputItems,
	EItemType _eOutputItemType,
	EItemCategoryType _eOuputItemTCategoryType,
	EItemLevel _eOutputItemLevel
)
{
	std::shared_ptr<TItemBuildOrder> spItemBuildOrder = make_shared<TItemBuildOrder>();
	spItemBuildOrder->m_vecInputItems = _vecInputItems;
	spItemBuildOrder->m_eOutputItemType = _eOutputItemType;
	spItemBuildOrder->m_eOuputItemCategoryType = _eOuputItemTCategoryType;
	spItemBuildOrder->m_eOutputItemLevel = _eOutputItemLevel;
	m_mapItemBuildOrders.insert({ (int32)_eOutputItemType, spItemBuildOrder });
}

const std::vector<std::weak_ptr<TItemBuildOrder>>& Editor::CItemBuild::CheckItemBuildOrder()
{
	const std::unordered_set<EItemType>& usetItemTypes = m_wpInventory.lock()->GetItemTypes();

	m_vecItemBuildOrders.clear();

	for (const auto& pair : m_mapItemBuildOrders)
	{
		bool bSatisfied = true;

		for (const auto& eItemType : pair.second->m_vecInputItems)
		{
			if (!usetItemTypes.contains(eItemType))
			{
				bSatisfied = false;
				break;
			}
		}

		if (bSatisfied)
		{
			m_vecItemBuildOrders.push_back(pair.second);
		}
	}

	return m_vecItemBuildOrders;
}

std::pair<EItemType, EItemType> Editor::CItemBuild::FindInputItems(EItemType _eParentItemType)
{
	if (m_mapItemBuildOrders.find((int32)_eParentItemType) == m_mapItemBuildOrders.end())
	{
		return { EItemType::ENUM_END, EItemType::ENUM_END };
	}

	std::vector<EItemType> vecInputItems =m_mapItemBuildOrders[(int32)_eParentItemType]->m_vecInputItems;
	return { vecInputItems[0], vecInputItems[1] };
}
