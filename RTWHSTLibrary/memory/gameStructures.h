#pragma once
template<unsigned int IIdx, typename TRet, typename ... TArgs>
TRet CallVFunc(void* thisptr, TArgs ... argList)
{
	using Fn = TRet(__thiscall*)(void*, decltype(argList)...);
	return (*static_cast<Fn**>(thisptr))[IIdx](thisptr, argList...);
}

#include <cstdint>
#include <windows.h>
#include <basetsd.h>
#include "offsets.h"

typedef unsigned char   undefined;
typedef unsigned int    uint;
typedef unsigned char    uchar;
typedef unsigned short    ushort;
#pragma pack(push,1)
typedef struct stackStruct stackStruct, * PstackStruct;
typedef struct settlementStruct settlementStruct, * PsettlementStruct;
typedef signed int int_32;
typedef unsigned short int_16;
typedef int undefined4;

#define GAME_FUNC(funcType, funcAddr) reinterpret_cast<funcType>(funcAddr)

struct vector_2
{
	float sx, sy;
};

struct vector_3
{
	float sx, sy, sz;
};

enum unitCategory
{
	INFANTRY,
	CAVALRY,
	SIEGE_ENGINE,
	NON_COMBATANT,
	SHIP,
	ANIMAL_HANDLER,
};

enum unitClass
{
	HEAVY,
	LIGHT,
	SKIRMISH,
	SPEARMEN,
	MISSILE
};

enum unitCategoryClass
{
	MASS,
	INFANTRY_LIGHT,
	INFANTRY_HEAVY,
	INFANTRY_SPEARMEN,
	INFANTRY_MISSILE,
	CAVALRY_LIGHT,
	CAVALRY_HEAVY,
	CAVALRY_MISSILE,
	SIEGE_ARTILLERY,
	SPECIAL,
	SHIP_
};

enum deathTypes
{
	ALIVE,
	NATURAL,
	DISASTER,
	BATTLE,
	ASSASSINATED,
	EXECUTED,
	EXECUTED_POISONED,
	PLAGUE,
	STARVATION,
	CAPTAIN_REMOVAL,
	REMOVED_FOR_RETRAINING,
	INCOMPATIBLE_FACTION,
	BRIBED,
	DISBANDED,
	SUNK
};

enum characterType
{
	SPY,
	ASSASSIN,
	DIPLOMAT,
	ADMIRAL,
	GENERAL,
	NAMED_CHARACTER,
};

//enum siegeEngineEnum
//{
//	ONAGER,
//	HEAVY_ONAGER,
//	BALLISTA,
//	RAPIDFIRE_BALLISTA,
//	SCORPION,
//	SOMETHING,
//	TOWER,
//	RAM,
//	LADDER,
//	SAP_POINT,
//};

enum siegeEngineType
{
	RAM,
	LADDERS,
	SIEGE_TOWER,
	SAP_POINT,
};

struct enumDescriptions
{
	std::string settlementLevel[6] = { "village","town","large_town","city","large_city","huge_city" };

	std::string season[4] = { "winter","spring","summer","autumn" };

	std::string battleTypeStr[7]
	{
		"AMBUSH_SUCCESSFUL",	// УСПЕШНАЯ ЗАСАДКА
		"AMBUSH_FAILED",		// НЕУДАЧНАЯ ЗАСАДКА
		"NORMAL",				// поле
		"SIEGE",				// осада
		"SALLY",				// вылазка
		"NAVAL",				// море
		"WITHDRAW",				// отступление
	};

	std::string battleStateStr[10]
	{
		"NOTHING",
		"PRE_BATTLE",
		"DELAY",
		"DEPLOYMENT_0",
		"DEPLOYMENT_1",
		"CONFLICT",
		"END_1",
		"END_2",
		"FINISHED_1",
		"FINISHED_2"
	};

	std::string characterTypeStr[6]
	{
		"SPY",
		"ASSASSIN",
		"DIPLOMAT",
		"ADMIRAL",
		"CAPTAIN",
		"NAMED_CHARACTER",
	};
};
extern enumDescriptions ds;

struct battleStatus
{
	bool walk;
	bool run;
	bool under_missile_fire;
	bool attackMissile;
	bool attackMelee;
	bool routing;
	bool fighting_to_the_death;
	bool amok;
	bool wavering;
	bool hide;
	bool hasLadders;
	bool hasRam;
	bool hasSiegeTower;
	bool hasSapPoint;
	bool aiControl;
	bool withdraw;
	bool berserk;
	bool swim;
};

enum battleType
{
	AMBUSH_SUCCESSFUL,	// УСПЕШНАЯ ЗАСАДКА
	AMBUSH_FAILED,		// НЕУДАЧНАЯ ЗАСАДКА
	NORMAL,				// поле
	SIEGE,				// осада
	SALLY,				// вылазка
	NAVAL,				// море
	WITHDRAW,			// отступление
};

enum battleState
{
	NOTHING,
	PRE_BATTLE,
	DELAY,
	DEPLOYMENT_0,
	DEPLOYMENT_1,
	CONFLICT,
	END_1,
	END_2,
	FINISHED_1,
	FINISHED_2
};

struct UNICODE_STRING {
	USHORT something;//idk
	USHORT Length;//idk
	USHORT something2;//idk
	PWSTR Buffer;//y
};

struct rcString
{
public:
	char pad_0000[12]; //0x0000
	wchar_t* string; //0x000C
	char pad_0010[104]; //0x0010
}; //Size: 0x0078

struct generalStats
{
public:
	struct soldierInBattle* generalBgSoldier; //0x0000
	struct soldierInBattle* generalBgMount; //0x0004
}; //Size: 0x0008

struct legioString
{
public:
	char* name; //0x0000
	int32_t nameHash; //0x0004
	struct UNICODE_STRING** localizedLegoName; //0x0008
	int32_t recruitCount; //0x000C
	char pad_0010[4]; //0x0010
}; //Size: 0x0014

struct cultureModels
{
public:
	char pad_0000[5584]; //0x0000
}; //Size: 0x15D0

struct cultureAgent
{
public:
	char* cardName; //0x0000
	int32_t cardNameHash; //0x0004
	char* infoCardName; //0x0008
	int32_t infoCardNameHash; //0x000C
	char* cardName2; //0x0010
	int32_t cardName2Hash; //0x0014
	int16_t index1; //0x0018
	char pad_001A[2]; //0x001A
	int16_t index2; //0x001C
	char pad_001E[2]; //0x001E
	int16_t cost; //0x0020
	int16_t time; //0x0022
	int16_t popCost; //0x0024
	int16_t someOtherRomeShit; //0x0026
	char pad_0028[4]; //0x0028
}; //Size: 0x002C



struct culture
{
public:
	int32_t cultureID; //0x0000
	char* cultureName; //0x0004
	int32_t cultureNameHash; //0x0008
	char pad_000C[1072]; //0x000C
	int32_t fortCost; //0x043C
	int32_t watchTowerCost; //0x0440
	char pad_0444[24]; //0x0444
	struct cultureModels cultureModelCrap; //0x045C
	struct cultureAgent cultureAgents[6]; //0x1A2C
	char pad_1B34[4]; //0x1B34
}; //Size: 0x1B38

struct coordPair
{
public:
	int32_t xCoord; //0x0000
	int32_t yCoord; //0x0004
}; //Size: 0x0008

struct movePath
{
public:
	struct coordPair* tileCoords; //0x0000
	int32_t tileCoordsSize; //0x0004
	int32_t tileCoordsCount; //0x0008
}; //Size: 0x000C


struct eventTrigger
{
	void* eventTrigger_vtbl; //0x0000
	char pad_0004[28]; //0x0004
};

struct buildingBattle
{
public:
	char pad_0000[24]; //0x0000
	int32_t type; //0x0018
	char pad_001C[8]; //0x001C
	float posX; //0x0024
	float posZ; //0x0028
	float posY; //0x002C
	char pad_0030[4]; //0x0030
	int32_t endHealth; //0x0034
	int32_t currentHealth; //0x0038
	int32_t startHealth; //0x003C
	char pad_0040[4]; //0x0040
	int32_t isDefenderControlled; //0x0044
	char pad_0048[8]; //0x0048
}; //Size: 0x0050



struct religionDatabase
{
public:
	void* religionDatabase_vtbl;//0x0000
	struct rcString** religionNames; //0x0004
	int32_t religionNamesSize; //0x0008
	int32_t religionCount; //0x000C
	struct rcString** religionPips; //0x0010
	int32_t religionPipsSize; //0x0014
	int32_t religionPipsCount; //0x0018
	void* hashedStringTable; //0x001C

}; //Size: 0x0020

struct capturedCharacter
{
	struct namedCharacter* namedChar;
	int32_t capturedValue;
};

struct capturedUnit
{
	struct unit* unit;
	int32_t capturedSoldiers;
	int32_t capturedValue;
};

struct capturedFactionInfo
{
	int32_t targetFactionID;
	int32_t factionID;
	struct namedCharacter* character;
	struct namedCharacter* targetCharacter;
	int32_t bitMap;
	struct capturedCharacter* capturedCharacters;
	uint32_t capturedCharactersEnd;
	uint32_t capturedCharactersEnd2;
	char* logString;
	struct capturedUnit* capturedUnits;
	uint32_t capturedUnitsEnd;
	int32_t capturedUnitsEnd2;
	int32_t ransomValue;
};

struct floatsSeaConnect
{
public:
	uint32_t tileId; //0x0000
	float someFloat; //0x0004
}; //Size: 0x0008

struct seaConnectedRegion
{
public:
	int32_t regionID; //0x0000
	char pad_0004[4]; //0x0004
	float angle; //0x0008
	float distance; //0x000C
	int32_t seaExportValue; //0x0010
	int32_t seaImportValue; //0x0014
	struct floatsSeaConnect* tilesReachable; //0x0018
	int32_t tilesReachableSize; //0x001C
	int32_t tilesReachableCount; //0x0020
	struct coordPair* seaTradeLanePath; //0x0024
	int32_t seaTradeLanePathSize; //0x0028
	int32_t seaTradeLanePathCount; //0x002C
	char pad_0030[4]; //0x0030
}; //Size: 0x0034

struct resourceStruct {
	DWORD* vtbl;
	void* nextObject;
	void* prevObject;
	int xCoord;
	int yCoord;
	int fade;
	bool render;
	char pad0[3];
	float opacity;
	bool highlighted;
	char pad1[3];
	struct stratResMod* stratMod;
	struct settlementStruct* settlement;
	int regionID;
	int resourceID;
	int duration;
};

struct regionStruct { // 0x0166C558 
	char* regionName;
	int regionNameHash;
	char* settlementName; /* null for sea */
	int settlementNameHash;
	char* legioName; /* null for sea */
	int legioNameHash;
	struct legioString* legioPointer;
	int regionID;
	int32_t roadLevel;
	int32_t farmingLevel;
	int32_t famineThreat;
	struct stackStruct** armies;
	int32_t armyCountArraySize;
	int32_t stacksNum;
	struct fortStruct** forts;
	int32_t fortCountArraySize;
	int32_t fortsNum;
	struct watchTowerStruct** watchtowers;
	int32_t watchtowerCountArraySize;
	int32_t watchtowersNum;
	int8_t isSea;
	bool peninsular;
	char pad_2[2];
	struct landMass* landMass;
	struct roadStruct* roadToPort;
	struct seaConnectedRegion* seaConnectedRegions;
	int32_t seaConnectedRegionsCountArraySize;
	int32_t seaConnectedRegionsCount;
	int32_t loyaltyFactionID;
	struct seaConnectedRegion* seaExportRegions[3];
	struct seaConnectedRegion** seaImportRegions;
	int32_t seaImportRegionsSize;
	int32_t seaImportRegionsCount;
	int32_t tradeFleetCount;
	struct mercPool* mercPool;
	int32_t* patrolPoints;
	int32_t patrolPointsSize;
	int32_t patrolPointsCount;
	int landingPoints;
	int32_t landingPointsSize;
	int32_t landingPointsCount;
	int32_t* devastatedTiles;
	int32_t devastatedTilesSize;
	int32_t devastatedTilesCount;
	char* r_38[38];
	struct settlementStruct* settlement;
	int* tiles;
	int32_t tilesSize;
	int32_t tileCount;
	int* fertileTiles;
	int32_t fertileTilesSize;
	int32_t fertileTilesCount;
	struct neighbourRegion* neighbourRegions;
	int32_t neighbourRegionsCountArraySize;
	int32_t neighbourRegionsNum;
	struct resourceStruct** resources;
	int32_t resourcesSize;
	int32_t resourcesNum;
	int32_t field_1c4;
	uint32_t resourceTypesBitMap;
	int32_t field_1cC;
	int32_t hiddenResources;
	int32_t hiddenResources2;
	int32_t field_1d8;
	int32_t settlementXCoord;
	int32_t settlementYCoord;
	int32_t portEntranceXCoord;
	int32_t portEntranceYCoord;
	uint8_t colorBlue;
	uint8_t colorGreen;
	uint8_t colorRed;
	char pad_1[1];
	struct factionStruct* factionOwner;
	int landmark; // ???   
	bool hasTradeRoute;
	char pad_3[3];
	UNICODE_STRING** localizedRegionName;
	UNICODE_STRING** localizedSettlementName;
	UNICODE_STRING** localizedRebelsName;
	char* rebelType;
	int32_t rebelTypeHash;
	int32_t harvestSuccess;
	int32_t triumphValue;
	int32_t totalLandValue;
	int32_t totalTradeValue;
public:
	std::string getLocalizedName();
	std::string getLocalizedRebelsName();

	stackStruct* getArmy(const int index)
	{
		if (index < 0 || index >= stacksNum)
			return nullptr;
		return armies[index];
	}
	fortStruct* getFort(const int index)
	{
		if (index < 0 || index >= fortsNum)
			return nullptr;
		return forts[index];
	}
	watchTowerStruct* getWatchTower(const int index)
	{
		if (index < 0 || index >= watchtowersNum)
			return nullptr;
		return watchtowers[index];
	}
	resourceStruct* getResource(const int index)
	{
		if (index < 0 || index >= resourcesNum)
			return nullptr;
		return resources[index];
	}
	void changeRegionSettlementName(const char* newName);
};// size 0xA8 

struct allRegions
{
	struct regionStruct regions[200];
};

struct neighbourRegion
{
public:
	struct regionStruct* region; //0x0000
	int32_t regionID; //0x0004
	float value; //0x0008
	int8_t alliedRegion; //0x000C
	char pad_000D[3]; //0x000D
	struct roadStruct* connectingRoad; //0x0010
	int32_t tradeValue; //0x0014
	int32_t* bordertiles; //0x0018
	int32_t borderTilessize; //0x001C
	int32_t borderTilesCount; //0x0020
	char pad_0024[52]; //0x0024
}; //Size: 0x0058

struct landMass
{
public:
	int32_t index; //0x0000
	int32_t* regions; //0x0004
	int32_t regionsSize; //0x0008
	int32_t regionsNum; //0x000C
}; //Size: 0x0010

struct climate
{
public:
	struct rcString* rcString; //0x0000
	struct UNICODE_STRING*** localizedName; //0x0004
	uint8_t colorBlue; //0x0008
	uint8_t colorGreen; //0x0009
	uint8_t colorRed; //0x000A
	char pad_000B[1]; //0x000B
	int32_t heatValue; //0x000C
	uint8_t hasWinter; //0x0010
	char pad_0011[3]; //0x0011
	void* treeModelsSummerSparse; //0x0014
	int32_t treeModelsSummerSparseSize; //0x0018
	int32_t treeModelsSummerSparseNum; //0x001C
	void* treeModelsSummerDense; //0x0020
	int32_t treeModelsSummerDenseSize; //0x0024
	int32_t treeModelsSummerDenseNum; //0x0028
	void* treeModelsSummerCanopy; //0x002C
	int32_t treeModelsSummerCanopysize; //0x0030
	int32_t treeModelsSummerCanopyNum; //0x0034
	void* treeModelsWinterSparse; //0x0038
	int32_t treeModelsWinterSparsesize; //0x003C
	int32_t treeModelsWinterSparseNum; //0x0040
	void* treeModelsWinterDense; //0x0044
	int32_t treeModelsWinterDensesize; //0x0048
	int32_t treeModelsWinterDenseNum; //0x004C
	void* treeModelsWinterCanopy; //0x0050
	int32_t treeModelsWinterCanopySize; //0x0054
	int32_t treeModelsWinterCanopyNum; //0x0058
}; //Size: 0x005C

struct climates
{
public:
	char pad_0000[4]; //0x0000
	struct climate* climateArray; //0x0004
	int32_t climatesSize; //0x0008
	int32_t climatesNum; //0x000C
}; //Size: 0x0010

struct oneTileDouble
{
public:
	float height; //0x0000
	int8_t climate; //0x0004
	int8_t groundType; //0x0005
	int8_t Nx0006; //0x0006
	int8_t Nx0007; //0x0007
}; //Size: 0x0008

/*
struct oneTile {
	DWORD* object; //can be character, resource, fort, 
	struct roadStruct* road; //0x0004
	uint16_t tileIncome;
	int8_t isLand;
	int8_t field_0xB;
	uint16_t modelIndex;
	int8_t modelSeed;
	int8_t pad;
	int groundType;
	int regionId;
	int32_t choke; //choke value like in toggle_terrain
	uint32_t factionId : 5;
	uint32_t riverSource : 1;
	uint32_t river : 1;
	uint32_t crossing : 1;
	uint32_t cliff : 3;
	uint32_t volcano : 1;
//	uint32_t seaCrossing : 3;
	uint32_t roadLevel : 3;
	uint32_t wallLevel : 2;
	uint32_t landmark : 1;
	uint32_t earthQuake : 3;
	uint32_t flood : 3;
	uint32_t storm : 3;
	uint32_t volcanoStrength : 3;
	uint32_t scorched : 1;
	uint32_t tradeRoute : 1;
	uint32_t devastationLevel : 3;
	uint32_t deforested : 1;
	uint32_t highlightExtents : 4;
	uint32_t border : 1;
	uint32_t landCoast : 1;
	uint32_t seaCost : 1;
	bool settlement : 1;
	bool fort : 1;
	bool dock : 1;
	bool port : 1;
	bool watchtower : 1;
	bool navy : 1;
	bool army : 1;
	int8_t nonPassable;
	uint32_t armiesNearTile; //0x0028
	uint32_t charactersOnTile; //0x002C
	float mpModifier; //0x0030
};
*/

struct oneTile {
	DWORD* object; //can be character, resource, fort, 
	struct roadStruct* road; //0x0004
	uint16_t tileIncome;
	int8_t isLand;
	int8_t field_0xB;
	uint16_t modelIndex;
	int8_t modelSeed;
	int8_t pad;
	int groundType;
	int regionId;
	int32_t choke; //choke value like in toggle_terrain
	uint32_t factionId;

	int r_5[5];
};

struct stratMap {
	bool isOpen;
	char pad[3];
	struct UNICODE_STRING** campaignName; //0x0004
	struct UNICODE_STRING*** campaignPath; //0x0008
	float minRoughness; //0x000C
	float maxRoughness; //0x0010
	float maxLandHeight; //0x0014
	float minSeaHeight; //0x0018
	float fractalMultiplier; //0x001C
	float minLatitude; //0x0020
	float maxLatitude; //0x0024
	climates* climates; //0x0028
	int mapWidth;
	int mapHeight;
	float tileSize; //0x0034
	float maxHeight;
	float minHeight; //0x003C
	void* storesMapRoughness; //0x0040
	struct oneTileDouble* climateTileArray; //0x0044
	struct oneTile* tilesArr;
	coordPair* riverSources;
	int32_t riverSourcesSize;
	int32_t riverSourcesNum;
	coordPair* crossings;
	int32_t crossingsSize;
	int32_t crossingsNum;
	struct coordPair* volcanoes; //0x0064
	int32_t volcanoesSize; //0x0068
	int32_t volcanoesNum; //0x006C
//	struct coordPair* landMassConnections; //0x0070
//	int32_t landMassConnectionsSize; //0x0074
//	int32_t landMassConnectionsNum; //0x0078
	struct regionStruct regions[200];
	int regionsNum;
	struct landMass landMass[20]; //0x1A660
	int32_t landMassNum; //0x1A7A0
public:
	regionStruct* getRegion(const int index)
	{
		if (!isOpen)
			return nullptr;
		if (index < 0 || index >= regionsNum)
			return nullptr;
		return &regions[index];
	}
	oneTile* getTile(const int x, const int y)
	{
		if (!isOpen)
			return nullptr;
		if (x < 0 || x >= mapWidth || y < 0 || y >= mapHeight)
			return nullptr;
		return &tilesArr[y * mapWidth + x];
	}
};
struct 	mercPoolUnit
{
public:
	struct eduEntry* eduEntry; //0x0000
	int32_t experience; //0x0004
	int32_t cost; //0x0008
	float replenishMin; //0x000C
	float replenishMax; //0x0010
	int32_t maxUnits; //0x0014
	float currentPool; //0x0018
	float startYear; //0x001C
	float endYear; //0x0020
	char pad_0024[4]; //0x0024
	int* religionsList; //0x0028
	int* religionsListEnd; //0x002C
	int* religionsListEnd2; //0x0030
	int32_t crusading; //0x0034
	char pad_0038[4]; //0x0038
	int* eventsList; //0x003C
	int* eventsListEnd; //0x0040
	int* eventsListEnd2; //0x0044
	int16_t poolIndex; //0x0048
	int16_t mercPoolUnitIndex; //0x004A
	struct mercPool* mercPool; //0x004C
}; //Size: 0x0050

struct mercPoolUnits
{
public:
	struct mercPoolUnit mercPoolUnit[64]; //0x0000
};

struct mercPoolUnitsPtr
{
public:
	struct mercPoolUnit* mercPoolUnits;
	struct mercPoolUnitsPtr* nextUnitsPtr;
	struct mercPoolUnit* prevPoolUnits;
	int Maxpool;
	int currentPool;
};

struct mercPool
{
public:
	char* name; //0x0000
	char pad_0004[4]; //0x0004
	struct regionStruct* regions; //0x008
	char pad_000C[16]; //0x000C
	struct mercPoolUnitsPtr firstUnits; //0x001C
}; //Size: 0x0180

struct mercPoolList
{
public:
	struct mercPool* mercPools; //0x0000
	struct mercPoolList* nextMercPools; //0x0004
	struct mercPoolList* previousMercPools; //0x0008
	int32_t currentSize; //0x000C
	int32_t currentCount; //0x0010
}; //Size: 0x0014

struct uiElement {
	undefined field_0x0[16];
	int xSize;
	int ySize;
	undefined field_0x18[4];
	char* elementName; /* can be nullptr */
	undefined field_0x20[32];
	int xPos;
	int yPos;
	undefined field_0x48[4];
	struct uiElement** subElements;
	undefined field_0x50[4];
	int subElementsNum;
	undefined field_0x58[112];
};

struct roadStruct
{
public:
	struct coordPair* coords; //0x0000
	int32_t coordsSize; //0x0004
	int32_t coordsNum; //0x0008
	void* someOtherArray; //0x000C
	int32_t someOtherArraySize; //0x0010
	int32_t someOtherArrayCount; //0x0014
	int32_t regionIdStart; //0x0018
	int32_t regionIdEnd; //0x001C
	int32_t tradeValue; //0x0020
	char pad_0020[20]; //0x0020
}; //Size: 0x0038

struct aiSiegeEquipStruct
{
	int type;
	int8_t byte4;
	int8_t byte5_init1;
	int8_t byte6;
	int8_t byte7;
	int normalCost;
	int cost;
	int int10;
};

struct siegeS {
	void* vTable;
	struct oneSiege* sieges; //0x0004
	int8_t field_8;
	char pad_0009[3]; //0x0009
	struct settlementStruct* goal; /* settlement or fort */
	struct stackStruct* army;
	struct aiSiegeEquipStruct aiEquipmentQueue[25];
	int someCount;
	int field_20C;
	int field_210;
	int field_214;
	int field_218;
	int field_21C;
	int field_220;
	int field_224;
	int field_228;
	int siegeTurns;
	int field_230;
	int field_234;
	int soldierCount;
	int8_t gotCaptured;
	char pad_x[3];
};

struct stringWithHash
{
public:
	char* name; //0x0000
	int32_t hash; //0x0004
}; //Size: 0x0008

struct holdRegionsWinCondition
{
public:
	char pad_0000[4]; //0x0000
	uint32_t stratTableStringIndex; //0x0004
	struct stringWithHash* regionsToHold; //0x0008
	int32_t regionsToHoldSize; //0x000C
	int32_t regionsToHoldCount; //0x0010
	uint32_t factionsToOutliveBitfield; //0x0014
	int32_t numberOfRegions; //0x0018
	char pad_001C[4]; //0x001C
	int32_t* holdRegionLengths; //0x0020
	int32_t holdRegionLengthsSize; //0x0024
	int32_t holdRegionLengthsCount; //0x0028
	char pad_002C[12]; //0x002C
}; //Size: 0x0080

struct battleSettlement
{
public:
	char pad_0000[4]; //0x0000
	struct settlementStruct* settlement; //0x0004
	char pad_0008[4]; //0x0008
	struct battleResidence* battleResidence; //0x000C
	char pad_0010[304]; //0x0010
}; //Size: 0x0140

struct settlementBuildings
{
public:
	struct buildingBattle** buildingList; //0x0000
	int32_t buildingListSize; //0x0004
	int32_t buildingNum; //0x0008
}; //Size: 0x000C

struct battleBuildings
{
public:
	char pad_0000[20]; //0x0000
	struct buildingBattle** allBuildings; //0x0014
	int32_t allBuildingsSize; //0x0020
	int32_t allBuildingsNum; //0x0020
	int32_t* allBuildingsInt; //0x0020
	char pad_0024[8]; //0x0024
	struct settlementBuildings* settlementBuildings; //0x002C
}; //Size: 0x0444

struct battleResidence
{
public:
	char pad_0000[28]; //0x0000
	struct settlementStruct* settlement; //0x001C
	char pad_0020[8]; //0x0020
	struct factionStruct** faction; //0x0028
	char pad_002C[4]; //0x002C
	int32_t isFortBattle; //0x0030
	struct battleBuildings* battleBuildings; //0x0034
	char pad_0038[4]; //0x0038
	float N000203C6; //0x003C
	float N000203C7; //0x0040
	char pad_0044[40]; //0x0044
	int8_t settlementWallsBreached; //0x006C
	int8_t settlementGateDestroyed; //0x006D
	char pad_006E[2]; //0x006E
	int8_t N0003A33C; //0x0070
	char pad_0071[7]; //0x0071
	float N0003A33E; //0x0078
	char pad_007C[200]; //0x007C
}; //Size: 0x0144

struct factionRanking
{
public:
	float totalRanking; //0x0000
	float militaryRanking; //0x0004
	float productionRanking; //0x0008
	float territoryRanking; //0x000C
	float financialRanking; //0x0010
	float populationRanking; //0x0014
}; //Size: 0x0018

struct projectile
{
	char pad_0000[4];
	char *name;
	int32_t nameHash;
	int32_t specialType;
	struct projectile *flamingProjectile;
	int8_t shatterDust;
	int8_t shatterDebris;
	int8_t vanishDust;
	int8_t vanishDebris;
	int8_t fiery;
	int8_t particleTrail;
	int8_t aimed;
	int8_t invertModelZ;
	int8_t spin;
	int8_t rocket;
	int8_t explosive;
	int8_t bool1f;
	float spinAmount;
	void *ptr24;
	float minAngle;
	float maxAngle;
	int8_t preferHigh;
	int8_t byte31;
	int8_t byte32;
	int8_t byte33;
	char pad_0034[4];
	float maxVelocity;
	char pad_003C[12];
	float minVelocity;
	float float4c;
	float float50;
	char pad_0054[20];
	float radius;
	float mass;
	float area;
	float accuracyVsUnits;
	float accuracyVsBuildings;
	float accuracyVsTowers;
	int8_t affectedByRain;
	int8_t damageToTroops;
	int8_t groundShatter;
	int8_t bounce;
	float bounceFloat1;
	float bounceFloat2;
	float bounceFloat3;
	float bounceFloat4;
	int8_t erratic;
	int8_t isBodyPiercing;
	int16_t short96;
	int8_t destroyMaxRange;
	int destroyMaxRangeVariation;
	char pad_0098[20];
	int32_t damage;
	char end_effect1[32];
	char *endEffect;
	char pad_00DC[24];
	char *endManEffect;
	char pad_00F8[24];
	char *endPackageEffect;
	char pad_0114[24];
	char *endShatterPackageEffect;
	char pad_0130[24];
	char *endShatterManEffect;
	char pad_014C[24];
	char *endShatterEffect;
	char pad_0168[48];
	char areaEffect[24];
	char pad_01B0[48];
	float EffectOffset;
	char pad_01E4[588];
};

struct factionStratMapDescrS { /* see descr_sm_factions.txt */
	int id;
	char* facName;
	DWORD facNameHash;
	int shadowedByID;
	char* shadowedBy;
	char pad_4[4];
	int32_t shadowingID;
	wchar_t* shadowing;
	char pad_4_2[4];
	int32_t spawnsOnRevoltID;
	char* spawnsOnRevolt;
	char pad_4_3[4];
	int32_t otherId;
	char pad_12[12];
	struct culture* culture;
	struct model_Rigid* symbol;
	char* symbolPath;
	DWORD symbolPathHash;
	struct model_Rigid* rebel_symbol;
	char* rebel_symbolPath;
	DWORD rebel_symbolPathHash;
	undefined u_8[8];
	char* loading_logo;
	DWORD loading_logoHash;
	uchar primary_colour_blue;
	uchar primary_colour_green;
	uchar primary_colour_red;
	uchar secondary_colour_blue;
	uchar secondary_colour_green;
	uchar secondary_colour_red;
	undefined field_0x76[2];
	int triumph_value;
	int standard_index;
	int logo_index;
	int small_logo_index;
	stringWithHash movieIntro;
	stringWithHash movieVictory;
	stringWithHash movieDefeat;
	stringWithHash movieDeath;
	bool roman;
	bool barbarian;
	bool eastern;
	bool slave;
	struct stringWithHash* hordeUnitNames;
	int32_t hordeUnitNamesSize;
	int32_t hordeUnitNamesCount;
	int32_t hordeMinUnits;
	int32_t hordeMaxUnits;
	int32_t reductionPerHorde;
	int32_t hordeUnitPerSettlementPop;
	int32_t hordeMinNamedCharacters;
	int32_t hordeMaxPercentArmyStack;
	void* N00008DBD;
	int32_t N00008DBE;
	int32_t N00008DBF;
	bool customBattleAvailability;
	char pad_3[3];
	bool canHorde;
	bool canSap;
	char pad_2[2];
	int32_t prefersNavalInvasions;
};

struct watchTowerModel {
	struct model_Rigid* modelP;
	undefined field_0x4[26];
};

//watchtower
struct watchTowerStruct {
	void* watchTowerVtable; //0x0000
	DWORD* object; //0x0004
	struct character* character; //0x0008
	int xCoord;
	int yCoord;
	char pad_0014[4]; //0x0014
	int8_t N000021C7; //0x0018
	char pad_0019[3]; //0x0019
	float N000021C8; //0x001C
	int8_t N000021C9; //0x0020
	char pad_0021[3]; //0x0021
	struct watchTowerModel* model;
	int32_t regionID; //0x0028
	struct factionStruct* faction; //0x002C
	struct settlementStruct* settlement; //0x0030
	void* trackedPointerArmyVtable; //0x0034
	struct stackStruct* blockingArmy; //0x0038
	int32_t factionID; //0x003C
	char pad_0040[8]; //0x0040
};

struct worldRecord {
	undefined field_0x0[4];
	char recordName[16]; /* pointer if allocatedNameLen>15 */
	int nameLen;
	int allocatedNameLen;
	undefined field_0x1c[4];
	char recordGroup[16]; /* pointer if allocatedGroupLen>15 */
	int groupLen;
	int allocatedGroupLen;
	undefined field_0x38[40];
};

struct crusade
{
public:
	char pad_0000[20]; //0x0000
	void* N0000121D; //0x0014
	char pad_0018[28]; //0x0018
	int32_t startTurn; //0x0034
	int32_t endTurn; //0x0038
	struct settlementStruct* targetSettlement; //0x003C
	int32_t length; //0x0040
	int32_t outcome; //0x0044
	char pad_0048[252]; //0x0048
	void* N00001269; //0x0144
	char pad_0148[44]; //0x0148
}; //Size: 0x0174



struct jihad
{
public:
	char pad_0000[52]; //0x0000
	int32_t startTurn; //0x0034
	int32_t endTurn; //0x0038
	struct settlementStruct* targetSettlement; //0x003C
	int32_t length; //0x0040
	int32_t outcome; //0x0044
	char pad_0048[292]; //0x0048
}; //Size: 0x016C

struct settlementList
{
	struct settlementStruct** settlements; //0x0000
	struct settlementList* nextSettlements; //0x0004
	struct settlementList* previousSettlements; //0x0008
	int32_t settlementsSize; //0x000C
	int32_t settlementsNum; //0x0010
};

struct trackedCharacter
{
public:
	struct N0001F08D* N0001F061; //0x0000
	struct character* character; //0x0004
}; //Size: 0x0008

enum DipRelEnum : uint8_t
{
	War = 1,
	Peace = 2,
	Alliance = 3,
	Suzerain = 4,
	MilitaryAccess = 5,
	Trade = 6
};
enum DipStateInternalEnum : uint16_t
{
	AllianceState = 0,
	PeaceState = 200,
	WarState = 600
};

struct factionDiplomacy
{
public:
	int prevState;
	int state;  /* diplomatic state(war, alliance, peace)(600/0/200) */
	int trade; /* trade rights(0 or 1) */
	int protectorate; /* protectorate or not(15 or 6) */

	int32_t aggressionLevel;
	int32_t protectoratePayment;
	int32_t numTurnsAllied;
	int32_t numTurnsWar;
	int numTreaties;
	int numAssists;
	int numAssistFailures;
	int numEmptyThreats;
	int numValidThreats;
	int32_t leaveTerritoryTimer;
	int winsInBattle;
	int tributeAmount;
	int tributeDuration;
	int preWarRegions[8];
	int turnsSinceLastMeeting;
	int32_t diplomaticSuccess;
	int diplomaticBalance;
	int32_t lastMapInfoTrade;

}; //Size: 0x0074

struct factionDiplomacy_2
{
public:
	int prevState;
	int state;  /* diplomatic state(war, alliance, peace)(600/0/200) */
	int trade; /* trade rights(0 or 1) */
	int protectorate; /* protectorate or not(15 or 6) */
	int f_25[25];
}; //Size: 0x0074

struct factionLocName
{
	std::string name[21];
	std::string nameAnsi[21];
public:
	std::string getName(int facID) const 
	{ 
		return name[facID]; 
	}
	std::string getNameAnsi(int facID) const
	{ 
		return nameAnsi[facID];
	}
};
extern factionLocName factionLocalizedName;

struct campaign {
	int c_90[90];
	struct factionStruct* factionsSortedByDescrStrat[21];	// descr_strat.txt   
	struct factionStruct* factionsSortedByID[21];			// descr_sm_factions.txt   
	int factionCount;
	int c_6[6];
	struct factionStruct* currentFactionTurn;
	int factionTurnID; /* FactionTurn? */
	UNICODE_STRING** currentDescrFile; /* path to descr_battle.txt or to descr_strat.txt */
	int c_5[5];
	int turnNumber;
	int c_42[42];
	int currentDate;
	int season; /* season(0-winter,1-spring,2-summer,3-autumn) */
	int startDate;
	int startSeason;
	int endDate;
	int endSeason; // 0x30C 
	int _g_140[140];
	struct factionDiplomacy diplomaticStandings[21][21];
	struct settlementList settlementList;
	char* introVid;
	char pad_215FC[16];
	struct fortStruct** fortsArray;
	int32_t fortsSize;
	int32_t fortsNum; // 0xCD44 
	struct portBuildingStruct** portsBuildings;
	int32_t portsBuildingsSize;
	int32_t portsBuildingsNum;
	struct watchTowerStruct** watchtowers;
	int32_t watchtowersSize;
	int32_t watchtowersNum;
	char pad[16];
	struct mercPoolList allMercPools;
	void* unk3;
	void* unk4;
public:
	factionStruct* getFactionById(int index)
	{
		if (index < 0 || index >= 21)
			return nullptr;
		return factionsSortedByID[index];
	}
	void setDipStance(const DipRelEnum dipType, const factionStruct* fac1, const factionStruct* fac2);
	bool checkDipStance(const DipRelEnum dipType, const factionStruct* fac1, const factionStruct* fac2);
	factionLocName getLocalizedNames();
	factionStruct* getLocalFaction();
};

struct uiUnitCard
{
public:
	char pad_0000[900];
	unit* unit;
};

struct uiCardManager
{
public:
	char pad_0000[16]; //0x0000
	struct uiUnitCard** selectedUnitCards; //0x0010
	int32_t selectedUnitCardsSize; //0x0014
	int32_t selectedUnitCardsCount; //0x0018
	char pad_001C[24]; //0x001C
	struct uiUnitCard** unitCards; //0x0034
	int32_t unitCardsSize; //0x0038
	int32_t unitCardsCount; //0x003C
	char pad_0060[328]; //0x0060
	struct settlementStruct* selectedSettlement; //0x0188
	char pad_018C[12]; //0x018C
	struct character* selectedCharacter; //0x0198
	char pad_019C[12]; //0x019C
	struct fortStruct* selectedFort; //0x01A8
};

struct stratPathFinding
{
	float minMpCost;
	struct trackedCharacter trackedPointerCharacter;
	int characterType;
	struct factionStruct* faction;
	int invalidOrReached;
	bool followCharacters;
	bool displayStandards;
	int8_t bytex1A[2];
	int cameraMode;
	bool exchangeScroll;
	bool waitingForScroll;
	bool waitingForScrollInTurnEnd;
	int8_t bytex23;
	void* floatingGeneral1;
	struct character* someCharacter;
	void* charVerification;
	void* charVerificationPos;
	int charVerThing;
	int battleResolution;
	int endTurnX;
	int endTurnY;
	int stratToBattleX;
	int stratToBattleY;
	struct character* lastSelectedCharacter;
	struct settlementStruct* lastSelectedSettlement;
	struct fortStruct* lastSelectedFort;
	int conflictType;
	int8_t isNightBattle;
	int8_t fieldx5D[3];
	stackStruct* attackingArmy;
	stackStruct* defendingArmy;
	int campaignBattlePhase;
	bool hideDisplay;
	char padHide[3];
	struct character** displacedCharacters;
	int displacedCharactersSize;
	int displacedCharactersNum;
	struct character** nextTurnCharacters;
	int nextTurnCharactersSize;
	int nextTurnCharactersNum;
	int extentsManager;
	struct coordPair* coords;
	int coordsSize;
	int coordsNum;
};

struct gameDataAllStruct {
	struct campaign* campaignData;
	int g_64019[64019];
//	struct stratMap* stratMap;
//	struct campaign* field_0x38;
//	undefined field_0x3c[28];
	struct battleDataS* battleHandler;
	int* localFactionID2;
	int* localFactionID;
	undefined field_0x64[28];
	struct battleSettlement* battleSettlement;
	char pad[112];
	struct uiCardManager* uiCardManager;
	char pad2[4];
	struct uiManager* uiManager;








//	struct stratMap* stratMap;
};

struct battleUnit
{
public:
	struct unit* unit; //0x0000
	struct UNICODE_STRING** localizedName; //0x0004
	float valuePerSoldier; //0x0008
	int32_t soldiersLost; //0x000C
	int32_t soldiersKilled; //0x0010
	int32_t takenPrisoner; //0x0014
	int32_t prisonersCaught; //0x0018
	int32_t soldiersStart; //0x001C
	uint32_t unitsRouted; //0x0020
	int32_t soldiersHealed; //0x0024
	int32_t unitsRoutedEnd; //0x0028
	int32_t soldiersEnd; //0x002C
//	int32_t friendlyFireCasualties; //0x0030
	int32_t expStart; //0x0034
	int32_t expGained; //0x0038
	int8_t isGeneral; //0x003C
	int8_t hasWithdrawn; //0x003D
	uint16_t N000400D6; //0x003E
	int32_t N0001FD2C; //0x0040
	int32_t N0001FDB3; //0x0044
}; //Size: 0x0048

struct options1
{
	void* cursor; //0x0000
	int8_t N0003DD45; //0x0004
	int8_t widescreen; //0x0005
	char pad_0006[2]; //0x0006
	int64_t antiAliasMode; //0x0008
	int16_t subtitles; //0x0010
	int8_t english; //0x0012
	int8_t noBattleTimeLimit; //0x0013
	char pad_0014[4]; //0x0014
	int32_t useNewCursorActions; //0x0018
	int32_t campaignNumTimesPlay; //0x001C
	int8_t uiWinConditions; //0x0020
	int8_t isScenario; //0x0021
	char pad_0022[2]; //0x0022
	int32_t isHotseatEnabled; //0x0024
	int8_t hotseatAutosave; //0x0028
	int8_t email; //0x0029
	int8_t saveConfig; //0x002A
	int8_t closeAfterSave; //0x002B
	int8_t validateData; //0x002C
	int8_t campaignMapSpeedUp; //0x002D
	char pad_002E[2]; //0x002E
	int32_t skipAiFactions; //0x0030
	int8_t labelCharacters; //0x0034
	int8_t noBackGroundFmv; //0x0035
	int8_t disableArrowMarkers; //0x0036
	int8_t arcadeBattles; //0x0037
	int8_t disableEvents; //0x0038
	int8_t isPrologue; //0x0039
	int8_t updateAiCamera; //0x003A
	int8_t hideCampaign; //0x003B
	int32_t unlimitedMenOnBattlefield; //0x003C
	char pad_0040[4]; //0x0040
	void* prefFactionsPlayed; //0x0044
	int32_t tgaReserveSpace; //0x0048
	int32_t keysetUsed; //0x004C
	class N0003DD67* descrShortcuts; //0x0050
	int8_t muteAdvisor; //0x0054
	int8_t advancedStatsAlways; //0x0055
	int8_t microManageAllSettlements; //0x0056
	int8_t blindAdvisor; //0x0057
	int32_t terrainQuality; //0x0058
	int32_t vegetationQuality; //0x005C
	int8_t useQuickChat; //0x0060
	int8_t someBoolNetworkManager; //0x0061
	char pad_0062[1]; //0x0062
	int8_t someBoolOnlinePlay; //0x0063
	int32_t graphicsAdaptor; //0x0064
	int8_t byte_2C6D86C; //0x0068
	int8_t showDemeanour; //0x0069
	char pad_006A[2]; //0x006A
	int32_t radar; //0x006C
	int32_t unitCards; //0x0070
	int32_t sa_cards; //0x0074
	int32_t buttons; //0x0078
	int8_t tutorialBattlePlayed; //0x007C
	int8_t disableVnVs; //0x007D
	int8_t allUsers; //0x007E
	char pad_007F[29]; //0x007F
	int32_t unk_2C6D8A0; //0x009C
	char pad_00A0[28]; //0x00A0
	char* audioProvider; //0x00BC
	char pad_00C0[20]; //0x00C0
	struct UNICODE_STRING** campaignName; //0x00D4
	char pad_00D8[4]; //0x00D8
	struct UNICODE_STRING*** N0003DA7C; //0x00DC
	struct UNICODE_STRING*** maybeGameSpyUsername; //0x00E0
	struct UNICODE_STRING*** gameSpyPassword; //0x00E4
	char pad_00E8[4]; //0x00E8
	char* gameName; //0x00EC
	char pad_00F0[24]; //0x00F0
	char adminPassword[28]; //0x0108
	char* tutorialPath; //0x0124
}; //Size: 0x0128


struct options2
{
	uint16_t defaultCampaignResolutionX; //0x0000
	uint16_t defaultCampaignResolutionY; //0x0002
	uint16_t campaignResolutionX; //0x0004
	uint16_t campaignResolutionY; //0x0006
	uint16_t defaultBattleResolutionX; //0x0008
	uint16_t defaultBattleResolutionY; //0x000A
	uint16_t battleResolutionX; //0x000C
	uint16_t battleResolutionY; //0x000E
	int8_t idk; //0x0010
	int8_t vSync; //0x0011
	char pad_0012[6]; //0x0012
	int8_t uiIconBarCheck; //0x0018
	int8_t uiRadarCheck; //0x0019
	int8_t useMorale; //0x001A
	int8_t uiAmmoCheck; //0x001B
	int8_t useFatigue; //0x001C
	int8_t uiSupplyCheck; //0x001D
	int8_t toggleFowState; //0x001E
	int8_t cameraRestrict; //0x001F
	int8_t eventCutscenes; //0x0020
	char pad_0021[3]; //0x0021
	int32_t defaultCameraInBattle; //0x0024
	int8_t splashes; //0x0028
	int8_t vegetationVideo; //0x0029
	int8_t byte_1639F1A; //0x002A
	int8_t stencilShadows; //0x002B
	int8_t byte_1639F1C; //0x002C
	int8_t audioEnable; //0x002D
	int8_t speechEnable; //0x002E
	int8_t firstTimePlay; //0x002F
	char* audioProviderName; //0x0030
	char pad_0034[1]; //0x0034
	int8_t byte_1639F25; //0x0035
	char pad_0036[1]; //0x0036
	int8_t toggleAutoSave; //0x0037
	int8_t showBanners; //0x0038
	int8_t passwords; //0x0039
	int8_t hotseatTurns; //0x003A
	int8_t hotseatScroll; //0x003B
	int32_t allowValidationFeatures; //0x003C
	int32_t campaignSpeed; //0x0040
	int8_t labelSettlements; //0x0044
	int8_t disablePapalElections; //0x0045
	int8_t autoresolveAllBattles; //0x0046
	int8_t savePrefs; //0x0047
	int8_t disableConsole; //0x0048
	int8_t validateDiplomacy; //0x0049
	char pad_004A[2]; //0x004A
	float someFloat; //0x004C
	int32_t unitDetail; //0x0050
	int32_t buildingDetail; //0x0054
	int32_t maxSoldiersOnBattlefield; //0x0058
	int32_t unitSize; //0x005C
	int32_t cameraRotateSpeed; //0x0060
	int32_t cameraMoveSpeed; //0x0064
	float cameraSmoothing; //0x0068
	int32_t somethingBasedOnBuildingDetail; //0x006C
	int32_t masterVolume; //0x0070
	int32_t musicVolume; //0x0074
	int32_t speechVolume; //0x0078
	int32_t sfxVolume; //0x007C
	int32_t subFactionAccents; //0x0080
	int32_t playerFactionId; //0x0084
	int32_t campaignDifficulty; //0x0088
	int32_t battleDifficulty; //0x008C
	int32_t tgaWidth; //0x0090
	float tgaAspect; //0x0094
	int32_t tgaInputScale; //0x0098
	int32_t scrollMinZoom; //0x009C
	int32_t scrollMaxZoom; //0x00A0
	int32_t advisorVerbosity; //0x00A4
	int8_t useSomethingTgaTextures; //0x00A8
	int8_t byte_1639F99; //0x00A9
	char pad_00AA[2]; //0x00AA
	int32_t effectQuality; //0x00AC
	int32_t EnableCameraCampaignSmoothing; //0x00B0
	int32_t chatMsgDuration; //0x00B4
	int8_t N0003DDF9; //0x00B8
	int8_t saveGameSpyPassword; //0x00B9
	int8_t addDateToLogs; //0x00BA
	int8_t showToolTips; //0x00BB
	int8_t isNormalHud; //0x00BC
	int8_t showPackageLitter; //0x00BD
	char pad_00BE[2]; //0x00BE
	char* normal; //0x00C0
	char pad_00C4[8]; //0x00C4
	int32_t effectNormal; //0x00CC
	char pad_00D0[8]; //0x00D0
	char* low; //0x00D8
	char pad_00DC[8]; //0x00DC
	int32_t effectLow; //0x00E4
	char pad_00E8[8]; //0x00E8
	char* high; //0x00F0
	char pad_00F4[8]; //0x00F4
	int32_t effectHigh; //0x00FC
	char pad_0100[8]; //0x0100
	char* lowest; //0x0108
	char pad_010C[8]; //0x010C
	int32_t effectLowest; //0x0114
	char pad_0118[8]; //0x0118
	char* highest; //0x0120
	char pad_0124[8]; //0x0124
	int32_t effectHighest; //0x012C
	char pad_0130[8]; //0x0130
	char* custom; //0x0138
	char pad_013C[8]; //0x013C
	int32_t effectCustom; //0x0144
	char pad_0148[8]; //0x0148
	char* lower; //0x0150
	char pad_0154[8]; //0x0154
	int32_t effectLower; //0x015C
	char pad_0160[8]; //0x0160
	char* higher; //0x0168
	char pad_016C[8]; //0x016C
	int32_t effectHigher; //0x0174
	char pad_0178[8]; //0x0178
	char* off; //0x0180
	char pad_0184[8]; //0x0184
	int32_t effectOff; //0x018C
	char pad_0190[32]; //0x0190
	int32_t maxSizeEduMaybe1; //0x01B0
	float unitMultDefault; //0x01B4
	int32_t unitMultDefaultId; //0x01B8
	int32_t maxSizeEduMaybe2; //0x01BC
	float unitSizeMultiplierLow; //0x01C0
	int32_t unitMult1ID; //0x01C4
	int32_t maxSizeEduMaybe3; //0x01C8
	float unitSizeMultiplierMedium; //0x01CC
	int32_t unitMult2ID; //0x01D0
	int32_t maxSizeEduMaybe4; //0x01D4
	float unitSizeMultiplierLarge; //0x01D8
	int32_t unitMult3ID; //0x01DC
	char pad_01E0[12]; //0x01E0
	uint16_t word_163A0DC; //0x01EC
	char pad_01EE[10]; //0x01EE
	uint16_t word_163A0E8; //0x01F8
	char pad_01FA[2]; //0x01FA
	uint16_t word_163A0EC; //0x01FC
	char pad_01FE[54]; //0x01FE
	int16_t currentHotseatPlayerOrSomething; //0x0234
	char pad_0236[2]; //0x0236
	class N0003DF44* keysetPointer; //0x0238
	char pad_023C[4]; //0x023C
	int32_t keySetUsed; //0x0240
	int32_t preferencesWereLoaded; //0x0244
};

struct battleArmy { /* in battle leader and leader army */


//	struct stackStruct* army_900[900];

	//46


	struct stackStruct* army;
	struct character* character;
	int32_t generalNumKillsBattle;
	float generalHPRatioLost;
	float totalValue;
	float battleOdds;
	char pad_12[12];
	struct character* killedGenerals;
	int32_t killedGeneralsSize;
	int32_t numKilledGenerals; // 12   
	char pad_24[24]; // 18   
	struct character* generalsDied;
	int32_t generalsDiedSize;
	int32_t generalsDiedCount;
	struct character* killedCaptains;
	int32_t killedCaptainsSize;
	int32_t killedCaptainsCount; // 24   
	char pad_60[60]; // 39   
	struct battleUnit* units;
	int32_t unitArraySize;
	int32_t unitCount; // 42 

	int b_4[4];

//	char pad_20[20];

//	char pad_84[84];





public:
	battleUnit* getBattleUnit(const int index)
	{
		return &units[index];
	}
};

struct deploymentAreaS {
	undefined field_0x0[4];
	float* coordsPairs;
	undefined field_0x8[4];
	int coordsNum;
};

struct trackedPointerArmy {
	undefined field_0x0[4];//0x0000
	struct stackStruct* stack;//0x0004
	struct deploymentAreaS* area_14[14];
	struct deploymentAreaS* deploymentArea;//0x0048
	undefined field_0x38[40];
};

struct trackedPointerArmyORIG {
	undefined field_0x0[4];//0x0000
	struct stackStruct* stack;//0x0004
	undefined field_0x8[44];//0x0008
	struct deploymentAreaS* deploymentArea;//0x0048
	undefined field_0x38[40];
};

struct aiDetachmentUnit
{
public:
	struct unit* unit; //0x0000
	DWORD objective; //0x0004
	char pad_0008[4]; //0x0008
}; //Size: 0x000C


struct aiDetachment
{
public:
	char pad_0000[4]; //0x0000
	struct AIBattleObjectiveBase* aiObjective; //0x0004
	struct aiDetachmentUnit** aiDetachUnits; //0x0008
	int32_t aiDetachUnitsSize; //0x000C
	int32_t aiDetachUnitsCount; //0x0010
	char pad_0014[8]; //0x0014
	DWORD objPhases; //0x001C
	int32_t objPhasesSize; //0x0020
	int32_t objPhasesCount; //0x0024
}; //Size: 0x0028


struct AIBattleObjectiveBase
{
public:
	char pad_0000[8]; //0x0000
	struct aiDetachment** aiDetachments; //0x0008
	int32_t aiDetachmentsSize; //0x000C
	int32_t aiDetachmentsCount; //0x0010
	struct unit** aiUnits; //0x0014
	int32_t aiUnitsSize; //0x0018
	int32_t aiUnitsCount; //0x001C
	char pad_0020[12]; //0x0020
	int32_t priority; //0x002C
	char pad_0030[24]; //0x0030
	DWORD battleFieldNode; //0x0048
	char pad_004C[20]; //0x004C
	struct aiDetachment** activeDetachments; //0x0060
	uint32_t activeDetachmentsEnd; //0x0064
	uint32_t activeDetachmentsEnd2; //0x0068
	char pad_006C[12]; //0x006C
}; //Size: 0x0078

struct aiObjectiveArrayBattle
{
public:
	struct AIBattleObjectiveBase* aIBattleObjective[50]; //0x0000
	char pad_00C8[16]; //0x00C8
}; //Size: 0x00D8

struct battleAI
{
public:
	char pad_0000[4]; //0x0000
	uint8_t newPlan; //0x0004
	char pad_0005[3]; //0x0005
	uint32_t currentAIPlan; //0x0008
	char pad_000C[8]; //0x000C
	char pad_0014[8]; //0x0014
	int32_t somethingHasUnitsagain; //0x001C
	char pad_0020[8]; //0x0020
	struct unit** aiUnitArray; //0x0028
	int32_t aiUnitMax; //0x002C
	int32_t aiUnitCount; //0x0030
	char pad_0034[4]; //0x0034
	struct unit** aiUnitArrayReversed; //0x0038
	int32_t aiUnitMaxReversed; //0x003C
	int32_t aiUnitCountReversed; //0x0040
	char pad_0044[340]; //0x0044
	struct unit** enemyUnitArray; //0x0198
	int32_t enemyUnitArraySize; //0x019C
	int32_t enemyUnitCount; //0x01A0
	char pad_01A4[4]; //0x01A4
	struct unit** enemyUnitArrayReversed; //0x01A8
	int32_t enemyUnitArraySizeReversed; //0x01AC
	int32_t enemyUnitCountReversed; //0x01B0
	char pad_01B4[1420]; //0x01B4
	struct unit** units; //0x0740
	int32_t unitArraySize; //0x0744
	int32_t unitCount; //0x0748
	char pad_074C[12]; //0x074C
	struct AIBattleObjectiveBase** currentObjectives; //0x0758
	int32_t currentObjectivesSize; //0x075C
	int32_t currentObjectivesCount; //0x0760
	char pad_0764[4]; //0x0764
	struct AIBattleObjectiveBase** addedObjectives; //0x0768
	int32_t addedObjectivesSize; //0x076C
	int32_t addedObjectivesCount; //0x0770
	char pad_0774[44]; //0x0774
	DWORD aiAnalysers; //0x07A0
	char pad_07A4[96]; //0x07A4
}; //Size: 0x0804

struct battleSide {
	bool isDefender;//0x0000
	uchar field_0x1;//0x0001
	bool isCanDeploy;//0x0002
	char pad_0003[1]; //0x0003
	uint32_t factionBitMap; //0x0004
	char pad_0008[4]; //0x0008
	DWORD winConditions[4];//0x000C
	int32_t winConditionCount; //0x001C
	char pad_0020[4]; //0x0020
	int32_t wonBattle; //0x0024 2 means won, 0 means lost, 1 is draw maybe
	int32_t battleSuccess; //0x0028 0 = close, 1 = average, 2 = clear, 3 = crushing
	char pad_002C[4]; //0x002C
	struct battleArmy* forces;//0x0030
	int32_t armyArraySize; //0x0034
	int armiesNum;//0x0038
	char pad_003C[12]; //0x003C
	int32_t alliance; //0x0048
	struct battleAI* battleAIPlan; //0x004C
	char pad_0050[8]; //0x0050
	struct trackedPointerArmy armies[64];//0x0058
	int32_t armyAICount; //0x1858
	struct factionStruct* factions[8]; //0x185C
	int32_t factionCount; //0x187C
	char pad_1880[4]; //0x1880
	struct unit** units; //0x1884
	int32_t unitSize; //0x1888
	int32_t unitNum; //0x188C
	struct stackStruct** armies2; //0x1890
	int32_t armies2Size; //0x1894
	int32_t armies2Num; //0x1898 --often broken dont bind to lua
	char pad_189C[104]; //0x189C
	int32_t totalStrength; //0x1904
	int32_t totalValue; //0x1908
	char pad_190C[4]; //0x190C
	int32_t totalStrength2; //0x1910
	int32_t totalStrength3; //0x1914
	int32_t soldierCount; //0x1918
	float battleOdds; //0x191C
	float battleOdds2; //0x1920
	float someFloat; //0x1924
	char pad_1928[4]; //0x1928
};
struct playerArmy
{
public:
	struct stackStruct* army;
	char pad_0004[20];
};

struct battleDataS {
	int b1;
	battleState battleState;
	battleType battleType;
	int isNightBattle;
	int battleWinType;
	int battleResult;
	int xCoord;
	int yCoord;
	int b9;
	int b10;
	int b11;
	int b12;
	int attackerXCoord;
	int attackerYCoord;
	int b15;
	int b16;
	int b17;
	int b18;
	int b19;
	int setPause;
	float speed;
	int b22;
	int b23;
	int b24;
	int b25;
	float secondsPassed;
	int secondsSinceBattleLoaded;
	float centerX;
	float centerY;
	float mapWidth;
	float mapHeight;
	int hidingEnabledSet;
	int b33;
	int b34;
	int b35;
	int b36;
	int deadSoldiers;
	struct UNICODE_STRING** someUniString;
	struct battleSide sides[8];
	int32_t factionSide[21];
	int sidesNum;
	int timeWinningAlliance;
	int numOfMenOnBattlefield;
	char pad_36[36];
	struct playerArmy playerArmies[21];
	int b_33[33];
	struct battleDataS* thisStruct;
};

struct stratPortModel {
	struct model_Rigid* model_rigid;
	undefined field_0x4[4];
	char* modelPath;
	int modelPathCrypt;
};

//dock (water tile)
struct portDockStrat {
	undefined field_0x0[8];
	struct character* character; /* character on port (enemy or not, army or not) */
	int xCoord;
	int yCoord;
	undefined field_0x14[28];
	struct settlementStruct* settlement;
	undefined field_0x34[4];
	int tradeFleets;
	char pad_0040[8]; //0x0040
	struct stackStruct* occupantsArmy; /* if port block by army then it here */
	int32_t numTurnsBlocked; //0x004C
	int32_t N00008216; //0x0050
	int32_t N00008217; //0x0054
	int32_t rallyCoordX; //0x0058
	int32_t rallyCoordY; //0x005C
	void* rallyPoint; //0x0060
	struct factionStruct* fac; /* blockading faction becomes owner */
	undefined field_0x68[4];
	struct stackStruct* occupantsArmy2; /* if port block by army then it here */
	int fieldx70;
	struct stratPortModel* dockStratModel;
	struct portBuildingStruct* port;
	void* trackedPointerArmyVtbl3;
	struct stackStruct* someArmy3;
};

struct custom_tile {
	char* name;
	int nameCrypt;
	int x;
	int y;
	char** pathToModel_UNICODE;
	char* weather;
	int weatherCrypt;
	int timeCode;
};

struct modelFlexiMixed
{
	char structsize[0x12c];
};

struct modelFlexi
{
	char structsize[0x11c];
};

struct casTextures
{
	int textureIndex;
	int glossTextureIndex;
};

struct stratModelArrayEntry
{
public:
	DWORD model_flexi_m; //0x0000
	int32_t zeropoint; //0x0004
	int32_t zeroarray[6]; //0x0008
	float lodRange; //0x0020
	int32_t zeroarray2[9]; //0x0024
	struct casTextures modelTexturesFactionArray[31]; //0x0048
	int32_t somearray[33]; //0x0140
	int32_t somearray2[3]; //0x01C4
	float lod2; //0x01D0
	DWORD skeleton; //0x01D4
	float scale; //0x01D8
	int32_t modelCountNotShadow; //0x01DC
	float indevRangeSquared; //0x01E0
	DWORD shadow_model_flexi; //0x01E4
	int32_t zeroarray3[7]; //0x01E8
	float lod3; //0x0204
	int32_t zeroarray4[7]; //0x0208
	int32_t modelCountShadow; //0x0224
	int32_t zeroint; //0x0228
	char* typeName; //0x022C
	int32_t N54788969; //0x0230

}; //Size: 0x0234

struct stratModelListEntry
{
public:
	char* modelName; //0x0000
	int32_t crypt; //0x0004
	struct stratModelArrayEntry* stratModelEntry; //0x0008
}; //Size: 0x000C

struct descrCharacterStratModelArray
{
public:
	struct stratModelListEntry stratModelsArray[16]; //0x0000
}; //Size: 0x00C0


struct genMod {
	int type; /* 0-spy, 2 - diplomat, etc */
	struct descrCharacterStratModelArray* stratInfo;
	int modelCountArrayMax;
	int modelCount;
	char* card;
	undefined field_0x14[5];
	char* portrait;
	undefined field_0x1d[3];
	char* card_rebel;
	undefined field_0x24[4];
	char* portrait_rebel;
	undefined field_0x2c[4];
	struct genBattleMod* battleMod;
	undefined field_0x34[4];
};

//fort model struct on stratmap
struct stratFortMod {
	struct model_Rigid* centerModel;
	struct model_Rigid* wallsModel;
	char* centerModelPath;
	int centerModelPathCrypt;
	char* wallsModelPath;
	int wallsModelPathCrypt;
};

//resource model struct on stratmap
struct stratResMod {
	struct model_Rigid* model;
	char* patchToModel;
	undefined field_0x8[4];
	int resource_num;
	int resource_cost;
	char* tga;
	undefined field_0x18[4];
	int hasMine;
};

/* rigid model(cas model for "static" objects - settlements, resources, etc) on stratmap! */
struct model_Rigid { /* rigid model(cas model for "static" objects - settlements, resources, etc) on stratmap! */
	undefined field_0x0[4];
};

struct descrCharacterEntry
{
public:
	char* type; //0x0000
	char pad_0004[4]; //0x0004
	int32_t dictionary; //0x0008
	struct genMod* ptrsToDescrCharacterFactionEntries[31]; //0x000C
	struct genMod factionEntries[31]; //0x0088
	int32_t factionCount; //0x0750
	int8_t hasAction[40]; //0x0754
	int32_t wageBase; //0x077C
	float startingActionPoints; //0x0780
}; //Size: 0x0784

struct descrCharacterArray
{
public:
	int32_t entryCount; //0x0000
	char pad_0004[4]; //0x0004
	int32_t defaultStartingActionPoints; //0x0008
	char pad_000C[8]; //0x000C
	int16_t N0000416D; //0x0014
	char pad_0016[2]; //0x0016
	struct descrCharacterEntry entries[12]; //0x0018
}; //Size: 0x5A48


//trading resource on stratmap
struct resStrat {
	undefined field_0x0[12];
	int xCoord;
	int yCoord;
	undefined field_0x14[16];
	struct stratResMod* stratMod;
	struct settlementStruct* settlement;
	int regionID;
	int resourceID;
	undefined field_0x2c[12];
};

//settlement model struct
struct settMod {
	struct model_Rigid* town;
	struct model_Rigid* castle;
	undefined field_0x8[924];
};

//models on the stratmap (settlements, resources, etc)
struct stratMod {
	undefined field_0x0;
	undefined field_0x1;
	undefined field_0x2;
	undefined field_0x3;
};

//port
struct portBuildingStruct {
	undefined field_0x0[8];
	struct character* character; /* character on port (enemy or not, army or not) */
	int xCoord;
	int yCoord;
	undefined field_0x14[28];
	struct settlementStruct* settlement;
	undefined field_0x34[4];
	int tradeFleets;
	char pad_0040[8]; //0x0040
	struct stackStruct* occupantsArmy; /* if port block by army then it here */
	int32_t numTurnsBlocked; //0x004C
	int32_t N00008216; //0x0050
	int32_t N00008217; //0x0054
	int32_t rallyCoordX; //0x0058
	int32_t rallyCoordY; //0x005C
	void* rallyPoint; //0x0060
	struct factionStruct* fac; /* blockading faction becomes owner */
	undefined field_0x68[4];
	struct stackStruct* occupantsArmy2; /* if port block by army then it here */
	int fieldx70;
	struct stratPortModel* portStratModel;
	struct portDockStrat* portDock;
	undefined field_0x7c[4];
};


struct BuildingPicEntry
{
public:
	char* buildingPicPath; //0x0000
	char pad_0004[4]; //0x0004
}; //Size: 0x0008

//building draw info(pics, etc)
struct buildingLevel { /* (name, tga's, models, etc) */
	char* name;
	int32_t buildingLevelNameHash; //0x0004
	UNICODE_STRING*** buildingName[21]; //0x0008
	UNICODE_STRING*** buildingDescr[21]; //0x0084
	UNICODE_STRING*** buildingDescrShort[21]; //0x0100
	struct BuildingPicEntry buildingPic[7]; //0x017C
	char* GenericBuildingPic; //0x01B4
	int32_t GenericBuildingPicHash; //0x01B8
	struct BuildingPicEntry buildingPicConstructed[7]; //0x01BC
	char* GenericbuildingPicConstructed; //0x01F4
	int32_t GenericbuildingPicConstructedHash; //0x01F8
	struct BuildingPicEntry buildingPicConstruction[7]; //0x01FC
//	char* GenericbuildingPicConstruction; //0x0234
//	int32_t GenericbuildingPicConstructionHash; //0x0238
//	void* buildingLevelCondition; //0x023C
//	int16_t buildCost; //0x0240
//	uint8_t buildTime; //0x0242
//	char pad_0243[1]; //0x0243
//	uint32_t settlementMinLvl; //0x0244
//	int8_t cityOneCastleMinusOne; //0x0248
//	char pad_0249[19]; //0x0249
//	struct BuildingLvlCapability* capabilities; //0x025C
//	struct recruitPool* recruitPools; //0x0260
//	int32_t factionCapabilities; //0x0264
//	void* upgrades; //0x0268
	char* b_9[9];
};


struct BuildingLvlCapability
{
public:
	int32_t capabilityType; //0x0000
	int16_t capabilityLvl; //0x0004
	int16_t bonus; //0x0006
	int32_t capabilityID; //0x0008
	DWORD funcPointer;
	struct buildingLevel* buildingLevel;
	DWORD EDBpointer;
	void* buildingLevelCondition; //0x0018
	struct BuildingLvlCapability* nextCapability; //0x001C
}; //Size: 0x0020


struct recruitPool
{
public:
	int32_t capabilityType; //0x0000
	int32_t capabilityLvlorExp; //0x0004
	int32_t unitID; //0x0006
	float initialSize;
	float gainPerTurn;
	float maxSize;
	void* buildingLevelCondition; //0x0018
	struct recruitPool* nextPool; //0x001C
}; //Size: 0x0020


//siege engine
struct siegeEngine {
	undefined field_0x0[172];
	int type; /* 2-RAM,4-ladder,1-tower */
};

struct eventBuild
{
	int e1;
	struct edbEntry* edbEntry;
	struct building* building;
	struct settlementStruct* settlement;
	int_32 newLevel;
	int_32 oldLevel;
	int_32 cost;
	int_32 repairCost;
	int_32 points;
	int_32 complete;
	int_32 completePercent;
	int_16 turn;
	bool valid;
	bool frozen;
	int_32 costWithoutBonuses;
	int_32 pointsWithoutBonuses;

};

//building data
struct edbEntry { /* SETTLEMENT_CONDITION_SETTLEMENT_FACTION */
	char pad_0000[20];
	int32_t buildingID;
	int32_t classification;
	int8_t e_64[64];
	int8_t isWallBuilding;
	int8_t isPort;
	int8_t isCoreBuilding;
	int8_t isTemple;
//	int32_t religionID;
	int8_t isHinterland;
	int8_t isFarm;
	char pad_2[2];
	UNICODE_STRING** localizedName;
	char* type; /* type of building (core_building,barracks)  */
	int typeHash;
	struct buildingLevel* buildingLevel; /* name of building(stone_wall), tga's, etc */
	char pad_008C[4];
	int32_t buildingLevelCount;
	char pad_8[8];
};

//building
struct building { /* building structure */
	int b_11[11];
	struct edbEntry* edbEntry; /* many info (type, name, etc), exportDescrBuildingEntry */
	int8_t level;
	int8_t b_27[23];
	int factionID;
	int hp; /* health points of the building */
//	struct settlementStruct* settlement;
};

struct buildingInQueue { /* building in settlement queue */
	int someID;
	struct edbEntry* edbEntry;
	struct building* existsBuilding; /* 0 if building dont exist yet */
	struct settlementStruct* settlement;
	int currentLevel;
	int pastLevel;
	int buildCost;
	int something2;
	int turnsToBuild;
	int buildTurnsPassed;
	int percentBuild;
	int8_t turnNumber;
	char pad[3];
	int buildCost2;
	int turnsToBuild2;
	void* texture;
};

struct buildingsQueue {
	struct buildingInQueue items[6];
	int firstIndex;
	int lastIndex;
	int buildingsInQueue;
	int currentBuildingIndex;
};

struct hiddenResource
{
public:
	char* hiddenResName; //0x0000
	int32_t hiddenResNameHash; //0x0004
}; //Size: 0x0008

struct buildingsArray
{
public:
	struct edbEntry buildings[32]; //0x0000
};

struct buildingListPointer
{
public:
	struct buildingsArray* buildingsArray; //0x0000
	struct buildingListPointer* nextBuildingsListPointer; //0x0004
	struct buildingListPointer* prevBuildingsListPointer; //0x0008
	int32_t arraySize; //0x000C
	int32_t arrayCount; //0x0010
}; //Size: 0x0014

struct exportDescrBuildings
{
public:
	struct hiddenResource hiddenResources[64]; //0x0000
	int32_t hiddenResourceCount; //0x0200
	char pad_0204[68]; //0x0204
	struct edbEntry* cityPort; //0x0248
	struct edbEntry* castlePort; //0x024C
	struct edbEntry* coreCityBuilding; //0x0250
	struct edbEntry* coreCastleBuilding; //0x0254
	char pad_0258[40]; //0x0258
	struct buildingListPointer buildingsList; //0x0280
	char pad_0294[188]; //0x0294
}; //Size: 0x0350


struct oneSiege {
	void* vtable;
	struct siegeS* siege;
};

struct unitRQ {
public:
	struct eduEntry* eduEntry; //0x0000
	int32_t FourtySeven; //0x0004
	struct settlementStruct* settlement; //0x0008
	int8_t N0001082F; //0x000C
	int8_t recruitType; //0x000D
	int8_t experience; //0x000E
	int8_t armourUpg; //0x000F
	int8_t weaponUpgrade; //0x0010
	int8_t Minus1; //0x0011
	int8_t turnsTrainedAlready; //0x0012
	int8_t percentFinished; //0x0013
	int8_t costUpkeep; //0x0014
	int8_t turnsToTrain; //0x0015
	int16_t cost; //0x0016
	int16_t soldierCount; //0x0018
	int16_t turnNumber; //0x001A
	int8_t fieldx1C; //0x001C
	int8_t isNotFrozen; //0x001D
	int16_t recruitmentPoolSizeBeforeOrRetrainingNumbersBefore; //0x001E
	int8_t isRetraining; //0x0020
	char pad_0021[3]; //0x0021
}; //Size: 0x0024


struct RallyPointSundry {
	undefined field0_0x0[4];
	void* object;
	undefined field2_0x8[56];
	void* object2;
	undefined field4_0x44[16];
};

struct settlementCapability
{
public:
	int16_t value; //0x0000
	int16_t bonus; //0x0002
}; //Size: 0x0004

struct recruitCapRome
{
public:
	char pad[8];
}; //Size: 0x0008

struct recruitmentCapability
{
public:
	int32_t eduIndex; //0x0000
	int32_t xp; //0x0004
	float initialSize; //0x0008
	float replenishRate; //0x000C
	float maxSize; //0x0010
}; //Size: 0x0014

struct settlementRecruitmentPool
{
public:
	int32_t eduIndex; //0x0000
	float availablePool; //0x0004
}; //Size: 0x0008


struct recruitRome
{
	char pad[8];
};

enum buildingCapabilities
{
	population_growth_bonus = 0,
	population_loyalty_bonus = 1,
	population_health_bonus = 2,
	trade_base_income_bonus = 3,
	trade_level_bonus = 4,
	trade_fleet = 5,
	taxable_income_bonus = 6,
	mine_resource = 7,
	farming_level = 8,
	road_level = 9,
	gate_strength = 10,
	gate_defences = 11,
	wall_level = 12,
	tower_level = 13,
	armour = 14,
	stage_games = 15,
	stage_races = 16,
	fire_risk = 17,
	weapon_simple = 18,
	weapon_missile = 19,
	weapon_bladed = 20,
	weapon_siege = 21,
	weapon_other = 22,
	upgrade_bodyguard = 23,
	recruits_morale_bonus = 24,
	recruits_exp_bonus = 25,
	happiness_bonus = 26,
	law_bonus = 27,
	construction_cost_bonus_military = 28,
	construction_cost_bonus_religious = 29,
	construction_cost_bonus_defensive = 30,
	construction_cost_bonus_other = 31,
	construction_time_bonus_military = 32,
	construction_time_bonus_religious = 33,
	construction_time_bonus_defensive = 34,
	construction_time_bonus_other = 35,
	recruitment_slots = 36,
};

struct capabilityStruct
{
public:
	struct settlementCapability settlementCapabilities[36]; //0x0000
	struct settlementCapability settlementCapabilitiesAgent[4]; //0x00E4
//	struct settlementCapability settlementCapabilitiesAgentLimit[6]; //0x00FC
	struct settlementCapability settlementCapabilitiesAncillaryROME[5]; //0x0114
	struct recruitRome settlementCapabilitiesRecruitROME[64]; //0x0124
	int32_t recruitCapabilityCount; //0x0324
//	struct recruitmentCapability recruitmentCapabilities[64]; //0x0328
//	int32_t recruitmentCapabilityCount; //0x0828

	int c_1;
	int c_2;

}; //Size: 0x082C


struct settlementStats
{
	struct settlementStruct* settlement;
	int32_t PopGrowthBaseFarm;
	int32_t PopGrowthFarms;
	int32_t FoodImports;
	int32_t PopGrowthHealth;
	int32_t PopGrowthBuildings;
	int32_t PopGrowthTaxBonus;
	int32_t UnitDisbands;
	int32_t SlavesGained;
	int32_t PopGrowthSqualor;
	int32_t PopGrowthPlague;
	int32_t PopGrowthTaxPenalty;
	int32_t Disasters;
	int32_t Riots;
	int32_t Extermination;
	int32_t UnitRecruits;
	int32_t SlavesLost;
	int32_t Population;
	int32_t PublicOrderGarrison;
	int32_t PublicOrderLaw;
	int32_t PublicOrderBuildingsEntertainment;
	int32_t PublicOrderGovernorInfluence;
	int32_t PublicOrderTaxBonus;
	int32_t PublicOrderTriumph;
	int32_t Wonder;
	int32_t PublicOrderPopulationBoom;
	int32_t PublicOrderEntertainment;
	int32_t PublicOrderHealth;
	int32_t PublicOrderSqualor;
	int32_t PublicOrderDistanceToCapital;
	int32_t CulturePenalty;
	int32_t PublicOrderNoGovernance;
	int32_t PublicOrderTaxPenalty;
	int32_t PublicOrderUnrest;
	int32_t Underpopulation;
	int32_t PublicOrderBesieged;
	int32_t PublicOrderBlockaded;
	int32_t Recession;
	int32_t GovernorReligionUnrest;
	int32_t FactionLeaderReligionUnrest;
	int32_t ChristianUnrest;
	int32_t PaganUnrest;
	int32_t ZoroastrianUnrest;
	int32_t PublicOrder;
	int32_t FarmsIncome;
	int32_t TaxesIncome;
	int32_t MiningIncome;
	int32_t TradeIncome;
	int32_t DiplomaticIncome;
	int32_t DemolitionIncome;
	int32_t LootingIncome;
	int32_t BuildingsIncome;
	int32_t AdminIncome;
	int32_t Wages;
	int32_t UpkeepExpense;
	int32_t ConstructionExpense;
	int32_t RecruitmentExpense;
	int32_t DiplomaticExpense;
	int32_t CorruptionExpense;
	int32_t EntertainmentExpense;
	int32_t DevastationExpense;
	int32_t TotalIncomeWithoutAdmin;
	int32_t s_50[50];

//	int32_t* religionPercentages;
//	int32_t religionPercentagesSize;
//	int32_t religionPercentagesNum;
//	int32_t majorityReligionID;
};

struct settlementStatsManager
{
	factionStruct* faction;
	settlementStruct* settlement;
	int32_t baseFertilityValue;
	int32_t rebelFactionChance;
//	int32_t turmoil;
	int32_t popGainedDisbands;
	int32_t popGainedSlaves;
	int32_t popLostRecruits;
	int32_t popLostDisaster;
	int32_t popLostRiots;
	int32_t popLostExtermination;
	int32_t popLostEnslaved;
	int32_t demolitionIncome;
	int32_t diplomacyIncome;
	int32_t lootingIncome;
	int32_t wages;
	int32_t upkeep;
	int constructionExpense;
	int recruitmentExpense;
	int diplomacyExpense;
	int disasterExpense;
	int entertainmentExpense;
	settlementStats settlementStatsLastTurn;
	settlementStats settlementStats;
	bool doingTempCalc;
	char pad[3]{};
//	void recalculate(bool recalculateFacEconomy);
//	void setPopulation(int newPop);
};

//settlement
struct settlementStruct {
	void* vTable;
	undefined field1_0x4[8];
	UINT32 xCoord; /* x coordinate */
	UINT32 yCoord; /* y coordinate */
	int s_7[7];
	float bannerPosX;
	float bannerPosZ;
	float bannerPosY;
	struct trackedPointerArmy_vtbl* trackedPointerArmyVtable;
	struct stackStruct* army; /* army on the settlement */
	struct oneSiege sieges[8];
	BYTE siegesNumber;
	undefined pad_3[3];
	int32_t maxHoldoutTurns;
	int32_t siegeDuration;
	int32_t siegeCasualties;
	int32_t populationSiegeStart;
	int32_t factionTradedFrom;
	int32_t plagueDuration;
	bool plagued;
	bool salliedOut;
	bool gatesAreOpened;
	bool readyToSurrender;
	struct descrRebelEntry* descrRebel;
	int32_t subFactionID;
	int s_51[51];
	int cultureID;
	float smthingPosX;
	float smthingPosY;
	portBuildingStruct* port;
	char* name; /* internal name of settlement */
	int nameCrypt;
	UNICODE_STRING** localizedName;
	struct factionStruct* faction; /* faction of the owner */
	int s64;
	int s65;
	int s66;
	int s67;
	int s68;
	int lastOwner;
	int s70;
	int level;
	int faction_creator;
	int lastHordeFaction;
	int16_t turnsOwned;
	char s_2[2];
	UINT32 regionID;
	int32_t factionID;
	int32_t yearFounded;
	int32_t triumph;	// minorSettlementIndex   
	int buildingQueueCost;
	int unitTrainingQueueCost;
	int unitRecruitmenttQueueCost;
	int s_201[201];
	struct building* buildingsByIndex[64];
	struct building* buildings[64];
	int buildingsNum;
	int32_t s_216[216];
	int32_t rallyPointX;
	int32_t rallyPointY;
	void* rallyPointPointer;
	struct aiProductionController* aiProductionController;
	int32_t plagueDeaths;
	int8_t scriptRebel;
	bool isProvokedRebellion;
	bool isMinorSettlement;
	int8_t pad3[1];
	int timeSinceLastRebellion;
	int entertainmentType;
	bool isCapital;
	bool isTradeBlocked;
	int8_t gamesMessage;
	int8_t racesMessage;
	int8_t governorLeft;
	int8_t pad4[3];
	int governorDuration;
	void* governorTrackedVtbl;
	struct character* governor;
	void* governorTrackedVtbl2;
	struct character* lastGovernor;
	void* governorTrackedVtbl3;
	struct character* portAdmiral;
	int32_t publicHealth;
	int32_t publicOrderLastTurn;
	int32_t lastPopulation;
	int32_t harvestSuccess;
	struct resourceStruct** resources;
	int32_t resourceSize;
	int resourcesNum;
	int32_t settlementTaxLevel;
	struct capabilityStruct capabilities;
	int8_t inEndOfRound;
	int8_t expandMessage;
	char pad_2[2];
	int s_18[18];
	settlementStatsManager stats;
public:
	void setPopulation(unsigned int newPopulation);
	stackStruct* createArmyInSettlement();
};

struct campaignDifficulty1
{
	int orderFromGrowth;
	int considerWarWithPlayer;
	float difficultyFloat1_unused;
	float brigandChanceAi;
	float brigandChancePlayer;
	int forceAttackDelay;
	float taxIncomeModifierPlayer;
	float farmingIncomeModifierPlayer;
	float incomeModifierAi;
	float playerRegionValueModifier;
};

struct campaignDifficulty2
{
public:
	int32_t popGrowthBonusAi; //0x0000
	int32_t publicOrderBonusAi; //0x0004
	int32_t experienceBonusAi; //0x0008
	int32_t difficultyInt4_unused; //0x000C
	int32_t incomeBonusAi; //0x0010
	int8_t wantsTargetPlayer; //0x0014
	int8_t wantsTargetPlayerNaval; //0x0015
	char pad_0016[6]; //0x0016
	int32_t autoAttackPlayerIfCrusadeTarget; //0x001C
	char pad_0020[32]; //0x0020
}; //Size: 0x0040



struct guild
{
	char* name; //0x0000
	DWORD nameHash; //0x0004
	uint8_t id; //0x0008
	char pad_0009[3]; //0x0009
	void* building; //0x000C
	int32_t level1Threshold; //0x0010
	int32_t level2Threshold; //0x0014
	int32_t level3Threshold; //0x0018
	char pad_001C[4]; //0x001C
	void* excludedGuildIds; //0x0020
	char pad_0024[40]; //0x0024
}; //Size: 0x004C

/* I_CompareCounter script command */
struct CompareCounter { /* I_CompareCounter script command */
	undefined field_0x0;
	undefined field_0x1;
	undefined field_0x2;
	undefined field_0x3;
	char* commandName; /* name of command(I_CompareCounter) */
	int operation;
	char* operandName; /* name of checked counter */
	int operandNameCrypt; /* maybe crypt of the counter name */
	int checkedValue; /* value for check */
};

//main character data(coordinates, etc)
struct character { /* character on the stratmap, who has a unit in a stack */
	undefined field1_4[4];
	void* obj;
	undefined field2_4[4];
	int xCoord; /* number of x-coord of unit fosition */
	int yCoord; /* number of y-coord of unit fosition */
	int g_25[25];
	struct namedCharacter* genChar; /* many important info about character */
	undefined field7_0x84[4];
	struct genMod* genType;
	int g_24[24];
//	undefined field9_0x8c[24];
//	uchar ifMarkedToKill;
//	undefined field11_0xa5[1];
//	int8_t inEnemyZOC; //0x00A6
//	char pad_00A7[17]; //0x00A7
//	int ambushState;
//	char pad_00B9[3]; //0x00B9
//	int32_t actionsThisTurn; //0x00BC
//	char pad_00C0[4]; //0x00C0
//	int8_t N000013B1; //0x00C4
//	int8_t doNotSpendMovePoints; //0x00C5
//	char pad_00C6[2]; //0x00C6
//	float movePointsCharacter;
//	undefined field15_0xcc[4];
//	uchar isStopCharacterNeeded; /* set to 1 if character moving now and he stops */
//	int32_t numTurnsIdle; //0x00D4
//	int32_t regionID; //0x00D8
//	float percentCharacterReligionInRegion; //0x00DC
//	float popConvertedThisTurn; //0x00E0
//	int32_t timeInRegion; //0x00E4
//	int32_t timeWithArmy; //0x00E8
//	char pad_00EC[20]; //0x00EC
	struct stackStruct* armyLeaded; /* army of the general */
	undefined field19_0x104[4];
	struct unit* bodyguards; /* unit of general */
	struct stackStruct* armyNotLeaded; /* army, if not leader */
	undefined field22_0x110[208];
	undefined field23_0x1e0[4];
	float movePointsModifier;
	float movePointsMax;
	float movePointsArmy;
	float movePointsMaxArmy; //0x01F0
	struct crusade* crusade; //0x01F4
	int32_t turnJoinedCrusade; //0x01F8
	int32_t currentTurn; //0x01FC
	float distanceToCrusadeTarget;
	float floatx204_startMinus1;
	float floatx208_startMinus1;
	float floatx20C_startMinus1;
	float floatx210_startMinus1;
	float floatx214_startMinus1;
	float floatx218_startMinus1;
	float floatx21C_startMinus1;
	float floatx220_startMinus1;
	float floatx224_startMinus1;
	int32_t disbandProgress;
	int8_t isCrusadeDisbandActive;
	int8_t bytex22D;
	char pad_0xx[2];
	char* ability;
	int32_t fieldx234;
	struct character* thisCharacter; //0x0238
	char pad_023C[16]; //0x023C
	struct character* thisCharacter2; //0x024C
	int32_t xCoordLast; //0x0250
	int32_t yCoordLast; //0x0254
	int32_t xCoordCurrent; //0x0258
	int32_t yCoordCurrent; //0x025C
	struct settlementStruct* besiegingSettlement; //0x0260
	char pad_0264[12]; //0x0264
	struct character* besiegingCharacter; //0x0270
	int32_t N00032B12; //0x0274
	int32_t N00032B00; //0x0278
	int32_t N00032B13; //0x027C
	int32_t N00032B14; //0x0280
	char pad_0284[296]; //0x0284
	void* someCoordStruct; //0x03AC
	int32_t someCoordStructSize; //0x03B0
	int32_t someCoordStructCount; //0x03B4
	struct movePath* multiTurnMovePaths; //0x03B8
	int8_t multiTurnMovePathsSize; //0x03BC
	int8_t multiTurnMovePathsCount; //0x03BD
	int8_t N00032E71; //0x03BE
	int8_t N00032E76; //0x03BF
};

//additional character data(name,label,traits, etc)
struct namedCharacter { /* many important info about character */
	UINT32 index; /* index of character */
	UNICODE_STRING** localizedFullName; /* displaying name */
	UNICODE_STRING** localizedNameForSave; /* saved to save file */
	UNICODE_STRING** localizedNextNameForSave; /* saved to save file */
	UNICODE_STRING** localizedNicknameForSave; /* saved to save file */
	char* shortName; /* not a full name) */ //0014
	int shortNameHash;
	char* lastName; //001C
	int lastNameHash;
	char* fullName;
	undefined field_4[4];
	/* main attributes */
	int32_t command;//0x002C
	int32_t influence;
	int32_t management;
	int32_t subterfuge;
	int32_t loyality;
	/* hidden attributes */ 
	int32_t troopMorale;
	int32_t movementPointsBonus;
	int32_t attack;
	int32_t defence;
	int32_t siegeAttack;
	int32_t siegeDefense;
	int32_t ambush;
	int32_t navalCommand;
	int32_t siegeEngineering;
	int32_t nightBattle;
	int32_t personalSecurity;
	int32_t publicSecurity;
	int32_t bribery;
	int32_t bribeResistance;
	int32_t electability;
	int32_t lineOfSight;
	int32_t trainingUnits;
	int32_t trainingAgents;
	int32_t construction;
	int32_t trading;
	int32_t localPopularity;
	int32_t footInTheDoor;
	int32_t negotiation;
	int32_t farming;
	int32_t mining;
	int32_t taxCollection;
	int32_t fertility;
	int32_t cavalryCommand;
	int32_t infantryCommand;
	int32_t combatVsCul0;
	int32_t combatVsCul1;
	int32_t combatVsCul2;
	int32_t combatVsCul3;
	int32_t combatVsCul4;
	int32_t combatVsCul5;
	int32_t combatVsCul6;
	int32_t combatVsSlaves;
	int32_t grainTrading;
	int32_t slaveTrading;
	int32_t health;
	int32_t squalor;
	int32_t unrest;
	int32_t law;
	int32_t looting;
	int32_t senateStanding;
	int32_t popularStanding;
	int32_t bodyguardValour;
	int32_t hitpoints;
	int32_t trainingAnimalUnits;
	int32_t battleSurgery;
	struct traitContainer* traits;
	undefined field_0x1e8[4];
	struct ancData** ancillaries; /* pointers to character ancillaries, names at  [item number] -0-0c-here) */
	undefined field_0x1f0[4];
	UINT32 ancNum; /* number of character  ancillaries */
	int nc_20[20];
	struct character* gen; /* on stratmap */
	undefined field_0x1fc[8];
	int yearOfBirth; /* yearOfBirth */
	int seasonOfBirth;
	int yearOfMaturity;
	int seasonOfMaturity;
	int32_t numberOfChildren;
	struct factionStruct* faction;
	int subFaction;
	undefined field_0x220[4];
	struct namedCharacter* parent; /* father */
	struct namedCharacter* spouse;
	struct namedCharacter* childs[4]; /* children, womens wont have children */
	int nc_3[3];
	int senateHistory;
//	int32_t deathType;
	deathTypes deathType;
	char* portrait;
	int portraitHash;
	char* portrait2;
	int portrait2Hash;
	int portraitIndex;
	char* portrait_custom; /* custom portrait name */
	int customPortraitHash;
	unsigned __int32 isAlive : 1;
	unsigned __int32 isMale : 1;
	unsigned __int32 isChild : 1;
	unsigned __int32 isFactionLeader : 1;
	unsigned __int32 isFactionHeir : 1;
	unsigned __int32 wasFactionLeader : 1;
	unsigned __int32 age : 7;
	unsigned __int32 kills : 3;
	unsigned __int32 isFamily : 1;
	unsigned __int32 isFamilyHead : 1;
	bool wasMarriageAlliance;
};

//ancillary of character
struct ancillary { /* structure of ancillary */
	UINT32 index;
	undefined field_0x4;
	undefined field_0x5;
	undefined field_0x6;
	undefined field_0x7;
	undefined field_0x8;
	undefined field_0x9;
	undefined field_0xa;
	undefined field_0xb;
	char* ancName;
	undefined field_0x10;
	undefined field_0x11;
	undefined field_0x12;
	undefined field_0x13;
	char* patchToAncImage;
	char pad_0018[4]; //0x0018
	int8_t isUnique; //0x001C
	char pad_001D[23]; //0x001D
	uint32_t excludedCultures; //0x0034
};

struct trait { /* traits of the character */
	struct traitEntry* traitEntry;
	struct traitLevel* level; /* level of trait */
	int traitPoints;
	int someInt;
	int somePointer;
};

struct traitEffect
{
	int32_t effectID;
	int32_t value;
};

struct traitLevel
{
	int32_t level;
	struct UNICODE_STRING*** localizedName;
	struct UNICODE_STRING*** localizedDescription;
	struct UNICODE_STRING*** localizedEpithetDescription;
	struct UNICODE_STRING*** localizedGainDescription;
	struct UNICODE_STRING*** localizedLoseDescription;
	int32_t threshold;
	struct traitEffect* effects;
	int32_t effectsSize;
	int32_t effectsCount;
	struct UNICODE_STRING*** localizedEffectsDescription;
};

struct traitEntry { /* char* at 0x4 */
	int32_t index;
	char* name;
	int32_t nameHash;
	struct traitLevel levels[10];
	int32_t levelCount;
	struct traitEntry* antiTraits[20];
	int32_t antiTraitCount;
	int32_t characterTypeNum;
	uint32_t characterType;
	int32_t noGoingBackLevel;
	int32_t excludeCulturesNum;
	uint32_t excludeCulturesStart;
	int32_t hidden;
	struct stringWithHash antiTraitNames[20];
	int32_t antiTraitNameCount;
};

struct traitContainer {
	struct trait* trait;
	struct traitContainer* prev;
	struct traitContainer* next;
	int hasEpithet;
};

struct trackedPointerUnit {
	undefined field_0x0[4];
	struct unit* unit;
	undefined field_0x8[88];
};

struct engineRecord {
	undefined field_0x0[4];
	char* type;
	undefined field_0x8[172];
	int classID;
	undefined field_0xb8[564];
};

struct soldierInBattle {
//	undefined field_0x0[8];
	int s;
//	int32_t unitCategory; //0x0008
//	int16_t someFlags; //0x000C
//	int8_t N00008AC5; //0x000E
//	int8_t N00008AC7; //0x000F
	float mass; //0x0010
	float inverseMass; //0x0014
	float xCoord;
	float zCoord;
	float yCoord;
	struct soldierInBattle* self; //0x0024
	float someRadius1; //0x0028
	float someRadius2; //0x002C
	float someRadius3; //0x0030
	float markerRadius; //0x0034
	float height; //0x0038
	char pad_003C[8]; //0x003C
	int16_t rotation; //0x0044
	char pad_0046[2]; //0x0046
	float velocity1;
	float velocity2;
	float velocity3;
	char pad_0054[196]; //0x0054
	struct soldierInBattle* self2; //0x0118
	char pad_011C[4]; //0x011C
	float speed; //0x0120
	char pad_0124[4]; //0x0124
	float xCoord_writable;
	float zCoord_writable;
	float yCoord_writable;
	uint16_t angle_writable; //0x0134
	int8_t N0000713A; //0x0136
	int8_t N00009525; //0x0137
	float velocityModifier; //0x0138
	int32_t currentStateGroupID; //0x013C
	int32_t currentStateStateID; //0x0140
	int32_t pendingStateGroupID; //0x0144
	int32_t pendingStateStateID; //0x0148
	char pad_014C[4]; //0x014C
	float xCoord_destination;
	float zCoord_destination;
	float yCoord_destination;
	int16_t destinationAngle; //0x015C
	int16_t thisIsAngleCauseTwoByteMaybe; //0x015E
	float destinationRadius; //0x0160
	char pad_0164[16]; //0x0164
	int16_t N00001DC6; //0x0174
	char pad_0176[2]; //0x0176
	int32_t targetStateGroupID; //0x0178
	int32_t targetStateStateID; //0x017C (One = Standing, 2 = Walking, 3 = running)
	int32_t moveStateGroupID; //0x0180
	int32_t moveStateStateID; //0x0184 (2 = walking, 3 = running)
	int32_t finishStateGroupID; //0x0188
	int32_t finishStateStateID; //0x018C
	int32_t options; //0x0190
	int32_t pendingAction; //0x0194
	float stoppingModifier; //0x0198
	float slideRotation; //0x019C
	int32_t numTicks; //0x01A0
	char pad_01A4[20]; //0x01A4
	int32_t surfaceID; //0x01B8
	int16_t pathHistoryAndObstacleDirection; //0x01BC
	int16_t unk; //0x01BE
	char pad_01C0[16]; //0x01C0
	int16_t waypoint; //0x01D0
	char pad_01D2[18]; //0x01D2
	int16_t cone; //0x01E4
	int16_t directionOffset; //0x01E6
	int16_t blockedCounter; //0x01E8
	int16_t N0000954E; //0x01EA
	float radiusModifier; //0x01EC
	float speedModifier; //0x01F0
	int32_t deflectionCounter; //0x01F4
	float stoppingDistance; //0x01F8
	float externalModifier; //0x01FC
	uint32_t locomotionFlags; //0x0200
	char pad[960]; //0x01D2

};

struct generalInfo
{
public:
	char** generalModelName; //0x0000
	struct unit* unit; //0x0004
	struct namedCharacter* namedChar; //0x0008
	char pad_000C[48]; //0x000C
	int8_t N00010FEA; //0x003C
	char pad_003D[43]; //0x003D
	struct soldierInBattle* soldier; //0x0068
	int8_t isCharacter; //0x006C
	int8_t alive; //0x006D
	char pad_006E[2]; //0x006E
	struct heroAbility* ability; //0x0070
	char pad_0074[144]; //0x0074
}; //Size: 0x0104

struct floatPosData
{
public:
	float rotStart; //0x0000
	float coord2_1; //0x0004
	float coord2_2; //0x0008
	float coord3_2; //0x000C
	float coord3_1; //0x0010
	float coord0_2; //0x0014
	float coord0_1; //0x0018
	float unk1; //0x001C
	float unk2; //0x0020
	float unk; //0x0024
	float rotation1; //0x0028
	float rotation2; //0x002C
	float coord1_1; //0x0030
	float coord1_2; //0x0034
	float val15; //0x0038
	float rotValue1; //0x003C
	float rotValue2; //0x0040
}; //Size: 0x0044

struct targetUnitStruct
{
public:
	char pad_0000[4]; //0x0000
	struct unit* target; //0x0004
	char pad_0008[4]; //0x0008
	int32_t targetUnitIndex; //0x000C
	char pad_0010[4]; //0x0010
}; //Size: 0x0014

struct targetPos
{
public:
	int32_t typeOrSomething; //0x0000
	int32_t N0001B8DA; //0x0004
	void* unitVerificationTable; //0x0008
	struct targetUnitStruct* targetUnit; //0x000C
	char pad_0010[4]; //0x0010
	float targetPosXStart; //0x0014
	float targetPosYStart; //0x0018
	char pad_001C[16]; //0x001C
	int32_t noDraggedFormation; //0x002C
	float N0001B8E5; //0x0030
	float N0001B8E6; //0x0034
	char pad_0038[4]; //0x0038
	float somethingDistanceRelated; //0x003C
	int32_t ranks; //0x0040
	float N0001B8EA; //0x0044
	char pad_0048[4]; //0x0048
	float N0001B8EC; //0x004C
	char pad_0050[4]; //0x0050
	int8_t N0001B8EE; //0x0054
	int8_t draggedFormation1; //0x0055
	int8_t N0003D819; //0x0056
	int8_t draggedFormation2; //0x0057
	int8_t N0001B8EF; //0x0058
	int8_t N0003D80B; //0x0059
	int8_t N0003D80E; //0x005A
	int8_t N0003D80C; //0x005B
	float targetPosXEnd; //0x005C
	float targetPosYEnd; //0x0060
	int8_t N0001B8F4; //0x0064
	int8_t N0003D7F4; //0x0065
	int8_t N0003D7F7; //0x0066
	int8_t N0003D7F5; //0x0067
	void* N0001B8F5; //0x0068
	int8_t N0001B8F6; //0x006C
	int8_t N0003D7EA; //0x006D
	int8_t N0003D7ED; //0x006E
	int8_t N0003D7EB; //0x006F
	float targetCoordXEngine; //0x0070
	float targetCoordZEngine; //0x0074
	float targetCoordYEngine; //0x0078
	struct siegeEngine* siegeEngine; //0x007C
	int32_t N0001B8FB; //0x0080
	int32_t N0001B8FC; //0x0084
	char pad_0088[8]; //0x0088
	float N0001B8FF; //0x0090
	char pad_0094[16]; //0x0094
	float N0003A5AB; //0x00A4
}; //Size: 0x00A8

struct battleMapPosition
{
public:
	int32_t positionIDMaybe; //0x0000
	int32_t numSoldiers; //0x0004
}; //Size: 0x0008

struct engagedUnit
{
public:
	struct unit* unit; //0x0000
	int32_t intValue; //0x0004
	int32_t intValue2; //0x0008
	int32_t intValue3; //0x000C
	int32_t intValue4; //0x0010
	int32_t intValue5; //0x0014
	float floatValue; //0x0018
}; //Size: 0x001C

struct firingUnit
{
public:
	struct unit* unit; //0x0000
	int32_t intValue; //0x0004
};

struct unitPositionData
{
public:
	struct engagedUnit* engagedUnits; //0x0000
	int32_t engagedUnitsSize; //0x0004
	int32_t engagedUnitsNum; //0x0008
	struct engagedUnit* engagedUnits2; //0x000C
	int32_t engagedUnits2Size; //0x0010
	int32_t engagedUnits2Num; //0x0014
	char pad_0018[16]; //0x0018
	struct unit* unit; //0x0028
	char pad_002C[4]; //0x002C
	void* N00002C71; //0x0030
	char pad_0034[4]; //0x0034
	struct unit* N00002C73; //0x0038
	float coord0; //0x003C
	float coord1; //0x0040
	float coord2; //0x0044
	float coord3; //0x0048
	float rotation; //0x004C
	struct battleMapPosition* isOnWalls; //0x0050
	int32_t isOnWallsSize; //0x0054
	int32_t isOnWallsCount; //0x0058
	struct battleMapPosition* isInTower; //0x005C
	int32_t isInTowerSize; //0x0060
	int32_t isInTowerCount; //0x0064
	struct battleMapPosition* isInGateHouse; //0x0068
	int32_t isInGateHouseSize; //0x006C
	int32_t isInGateHouseCount; //0x0070
	struct battleMapPosition* positions1; //0x0074
	int32_t positions1Size; //0x0078
	int32_t positions1Count; //0x007C
	struct battleMapPosition* positions2; //0x0080
	int32_t positions2Size; //0x0084
	int32_t positions2Count; //0x0088
	struct battleMapPosition* positions3; //0x008C
	int32_t positions3Size; //0x0090
	int32_t positions3Count; //0x0094
	struct battleMapPosition* positions4; //0x0098
	int32_t positions4Size; //0x009C
	int32_t positions4Count; //0x00A0
	char pad_00A4[12]; //0x00A4
	struct floatPosData floatPosData; //0x00B0
	char pad_00F4[4]; //0x00F4
	struct targetPos targetArray[16]; //0x00F8
	int32_t targetsDone; //0x0B78
	int32_t additionalTargetsOverOne; //0x0B7C
	int32_t targetsToGo; //0x0B80
	int8_t hasTargets; //0x0B84
	int8_t isHalted; //0x0B85
	char pad_0B86[6]; //0x0B86
	float lastTargetCoord1; //0x0B8C
	float lastTargetCoord2; //0x0B90
	char pad_0B94[20]; //0x0B94
	float N00002F68; //0x0BA8
	float N00002F69; //0x0BAC
	float N00002F6A; //0x0BB0
	float N00002F6B; //0x0BB4
	float N00002F6C; //0x0BB8
	float N00002F6D; //0x0BBC
	float N00002F6E; //0x0BC0
	float N00002F6F; //0x0BC4
	float N00002F70; //0x0BC8
	float N00002F71; //0x0BCC
	float N00002F72; //0x0BD0
	float N00002F73; //0x0BD4
	float N00002F74; //0x0BD8
	float N00002F75; //0x0BDC
	float N00002F76; //0x0BE0
	float N00002F77; //0x0BE4
	float N00002F78; //0x0BE8
	char pad_0BEC[20]; //0x0BEC
	void** towersUnderFireFrom; //0x0C00
	int32_t towersUnderFireFromSize; //0x0C04
	int32_t towersUnderFireFromCount; //0x0C08
	struct firingUnit* unitsUnderFireFrom; //0x0C0C
	int32_t unitsUnderFireFromSize; //0x0C10
	int32_t unitsUnderFireFromCount; //0x0C14
	void** underFireSomething2; //0x0C18
	int32_t underFireSomething2Size; //0x0C1C
	int32_t underFireSomething2Count; //0x0C20
	void** underFireSomething3; //0x0C24
	int32_t underFireSomething3Size; //0x0C28
	int32_t underFireSomething3Count; //0x0C2C
	char pad_0C30[8]; //0x0C30
	int32_t combatStatus; //0x0C38
}; //Size: 0x0C3C

struct rebelUnitName
{
public:
	char* unitName; //0x0000
	char pad_0004[20]; //0x0004
}; //Size: 0x0018

struct descrRebelEntry
{
public:
	int32_t index; //0x0000
	char* name; //0x0004
	int32_t nameHash; //0x0008
	int32_t category; //0x000C
	struct N00022A30* localizedName; //0x0010
	int32_t chance; //0x0014
	struct rebelUnitName unitNames[121]; //0x0018
	int32_t unitCount; //0x0B70
}; //Size: 0x0B74

//unit data
struct unit {
	int unitTest1;
	int unitTest2;
	int unitTest3;
	int unitTest4;
	int unitTest5;
	int unitTest6;
	int unitTest7;
	int unitTest8;
	int unitTest9;
	int unitTest10;
	int unitTest11;
	int unitTest12;
	int unitTest13;
	int unitTest14;
	int unitTest15;
	int unitTest16;
	struct stackStruct* army;
	int unitTest18;
	struct settlementStruct* trainsInSettlement;
	int unitTest20;
	struct eduEntry* eduEntry;
	int ID;
	int index;
	int alliance;
	int unitTest25;
	int unitTest26;
	int unitTest27;
	int unitTest28;
	int unitTest29;
	int unitTest30;
	int unitTest31;
	int unitTest32;
	int unitTest33;
	int unitTest34;
	int unitTest35;
	int unitTest36;
	int unitTest37;
	int unitTest38;
	int unitTest39;
	int unitTest40;
	int unitTest41;
	int unitTest42;
	int unitTest43;
	int unitTest44;
	int unitTest45;
	int unitTest46;
	int unitTest47;
	int unitTest48;
	int unitTest49;
	int unitTest50;
	int unitTest51;
	int unitTest52;
	int unitTest53;
	int unitTest54;
	int unitTest55;
	int unitTest56;
	int unitTest57;
	int unitTest58;
	int unitTest59;
	int unitTest60;
	int unitTest61;
	int unitTest62;
	int unitTest63;
	int unitTest64;
	int unitTest65;
	int unitTest66;
	int unitTest67;
	int unitTest68;
	int unitTest69;
	int unitTest70;
	int unitTest71;
	int unitTest72;
	int unitTest73;
	int unitTest74;
	int unitTest75;
	int unitTest76;
	int unitTest77;
	int unitTest78;
	int unitTest79;
	int unitTest80;
	int unitTest81;
	int unitTest82;
	int unitTest83;
	int unitTest84;
	int unitTest85;
	int unitTest86;
	int unitTest87;
	int unitTest88;
	int unitTest89;
	int unitTest90;
	int unitTest91;
	int unitTest92;
	int unitTest93;
	int unitTest94;
	int unitTest95;
	int unitTest96;
	int unitTest97;
	int unitTest98;
	int unitTest99;
	int unitTest100;
	int unitTest101;
	int unitTest102;
	int unitTest103;
	int unitTest104;
	int unitTest105;
	int unitTest106;
	int unitTest107;
	int unitTest108;
	int unitTest109;
	int unitTest110;
	int unitTest111;
	int unitTest112;
	int unitTest113;
	int unitTest114;
	int unitTest115;
	int unitTest116;
	int unitTest117;
	int unitTest118;
	int unitTest119;
	int unitTest120;
	int unitTest121;
	int unitTest122;
	int unitTest123;
	int unitTest124;
	int unitTest125;
	int unitTest126;
	int unitTest127;
	int unitTest128;
	int unitTest129;
	int unitTest130;
	int unitTest131;
	int unitTest132;
	int unitTest133;
	int unitTest134;
	int unitTest135;
	int unitTest136;
	int unitTest137;
	int unitTest138;
	int unitTest139;
	int unitTest140;
	int unitTest141;
	int unitTest142;
	int unitTest143;
	int unitTest144;
	int unitTest145;
	int unitTest146;
	int unitTest147;
	int unitTest148;
	int unitTest149;
	int unitTest150;
	int unitTest151;
	int unitTest152;
	int unitTest153;
	int unitTest154;
	int unitTest155;
	int unitTest156;
	int unitTest157;
	int expScreen; /* screen experience */
	struct character* general;
	float movePoints;
	int SoldierCountStrat; /* number of soldiers */
	int SoldierCountMaxStrat; /* number of soldiers on tactical map */
	int SoldierCountBattlemap; /* max number of soldiers */
	int soldierCountMaxBattlemap; /* max number of soldiers */
	unsigned __int32 unitUTTest_1;
	unsigned __int32 unitUTTest_2;
	unsigned __int32 unitUTTest_3;
	unsigned __int32 unitUTTest_4;
	unsigned __int32 unitUTTest_5;
	unsigned __int32 unitUTTest_6;
	unsigned __int32 unitUTTest_7;
	unsigned __int32 unitUTTest_8;
	unsigned __int32 unitUTTest_9;
	unsigned __int32 unitUTTest_10;
	unsigned __int32 unitUTTest_11;
	struct generalInfo* officer1;
	struct generalInfo* officer2;
	struct generalInfo* officer3;
	struct generalInfo* generalInfo;
	struct soldierInBattle* generalSoldier;
	struct soldierInBattle* officer1Soldier;
	struct soldierInBattle* officer2Soldier;
	struct soldierInBattle* officer3Soldier;
	int32_t numOfficer;
	int32_t numOfficerInBattle;
	unsigned __int32 unitUTTest_22;
	unsigned __int32 unitUTTest_23;
	unsigned __int32 unitUTTest_24;
	unsigned __int32 unitUTTest_25;
	unsigned __int32 unitUTTest_26;
	unsigned __int32 unitUTTest_27;
	unsigned __int32 unitUTTest_28;
	unsigned __int32 unitUTTest_29;
	unsigned __int32 avgAmmo : 8;
	unsigned __int32 avgWeaponUpg : 5;
	unsigned __int32 avgArmourUpg : 5;
	unsigned __int32 usingPrimary : 1;
	unsigned __int32 usingSecondary : 1;
	struct soldierInBattle** soldiersBattleArr; /* array of soldiers battle data */
	struct soldierData* soldiersArr; /* array of soldiers data */
	void* soldierIndices;
	struct generalInfo* generalArmy;
	int unitThings[407];
	struct UNICODE_STRING** alias;
public:
	void setExperience(uint8_t exp);
	battleStatus checkUnitBattleStatus();
};

struct attachedAncillary
{
	int count;
	int level;
};

struct sapPoint
{
	int something;
};

//army data
struct stackStruct { /* structure of stack */
	undefined field_0x0[76];
	int s_2[2];
	struct factionStruct* faction;
	int regionID;
	struct unit** units;
	int32_t unitsSize;
	int numOfUnits;
	struct unit** deadUnits;
	int deadUnitsSize;
	int deadUnitsNum;
	attachedAncillary ancillaries[5];
	int hiddenUnitCount;
	struct sapPoint** sapPointArray;
	int8_t ar_104[44];
	int8_t battleLadders;
	int8_t battleRams;
	int8_t battleTowers;
	int8_t battleSapPoints;
	int8_t ladders;
	int8_t rams;
	int8_t towers;
	int8_t sapPoints;
	int s_6[6];
	struct character* gen; /* 0 if in settlement/fort */
	struct unit* generalsUnit;
	struct generalInfo* generalInfo;
	float armyStrengthForAutoResolveMaybe;
	char pad_00E4[12];
	struct character** characters;
	undefined field_0xf4[4];
	int charactersNum;
	undefined field_0xfc[4];
	struct settlementStruct* settlement;
	undefined field_0x104[16];
	struct stackStruct* enemyArmy;
	int32_t inBattle;
	int8_t N00001BCA;
	int8_t N0003D211;
	uint16_t N0003D214;
	char pad_0120[4];
	int totalStrength;
	float reform_point_x;
	float reform_point_y;
	int32_t battleSide;
	char pad_0134[16];
	int32_t battleAllianceOrSomething; 
	int32_t battleDifficulty; 
	int8_t isHalfDestroyed; 
	char pad_014D[15];
	struct descrRebelEntry* descrRebel;
	int32_t subFactionID;
};

struct coords {
	int xCoord;
	int yCoord;
public:
	coords()                          : xCoord(0), yCoord(0) {}
	coords(int x, int y)              : xCoord(x), yCoord(y) {}
};

struct factionTileStruct {
	int8_t* tilesVisiblity;
	int tilesXBound;
	int tilesYBound;
	undefined field3_0xc[28];
	void* revealedTiles;
	int revealedTilesContainerAllocatedSize;
	int revealedTilesNumber;
	undefined field7_0x34[24];
};

struct factionEconomy
{
public:
	int32_t farmingIncome; //0x0000
	int32_t taxesIncome; //0x0004
	int32_t miningIncome; //0x0008
	int32_t tradeIncome; //0x000C
	int32_t merchantIncome; //0x0010
	int32_t constructionIncome; //0x0014
	int32_t otherIncome1; //0x0018
	int32_t otherIncome2; //0x001C
	int32_t diplomacyIncome; //0x0020
	int32_t tributesIncome; //0x0024
	int32_t adminIncome; //0x0028
	int32_t kingsPurseIncome; //0x002C
	int32_t wagesExpense; //0x0030
	int32_t upkeepExpense; //0x0034
	int32_t constructionExpenseBuildings; //0x0038
	int32_t constructionExpenseField; //0x003C
	int32_t recruitmentExpenseBuildings; //0x0040
	int32_t recruitmentExpenseMercs; //0x0044
	int32_t corruptionExpense; //0x0048
	int32_t diplomacyExpense; //0x004C
	int32_t tributesExpense; //0x0050
	int32_t otherExpense1; //0x0054
	int32_t otherExpense2; //0x0058
	int32_t devastationExpense; //0x005C
}; //Size: 0x0060

struct battleFactionCounter
{
public:
	int32_t battlesWon; //0x0000
	int32_t battlesLost; //0x0004
	int32_t wonLostRatio; //0x0008
}; //Size: 0x000C

struct factionDataStrategy
{
	int32_t intx0;
	int32_t intx4;
	int intx8;
	int intxC;
	int somethingSubterFugeTasks;
	float someOtherStrengthModifier;
	float strengthLimitModifier;
	int8_t atWar;
	int8_t notWantCeaseFire;
	int8_t canAttack;
	int8_t pad;
};

struct aiRegionData
{
	void* __vftable /*VFT*/;
	int fieldx4;
	bool boolx8;
	char pad1[3];
	int factionID;
	int regionID;
	bool boolx14;
	bool boolx15;
	char pad2[2];
	int regionValue;
	int fieldx1C;
	int hasNeighbouringEnemies;
	int hasNeighbouringOwnArmies;
	int fieldx28;
	int ownArmiesTotalStrength;
	int ownArmiesTotalCount;
	int enemyArmiesTotalStrength;
	int enemyArmiesTotalCount;
	int neutralArmiesTotalStrength;
	int neutralArmiesTotalCount;
	int neighbourRegionsOwnArmyStrength;
	int neighbourRegionsOwnArmyNum;
	int neighbourRegionsEnemyArmyStrength;
	int neighbourRegionsEnemyArmyNum;
	int neighbourRegionsNeutralArmyStrength;
	int neighbourRegionsNeutralArmyNum;
	int regionRisk;
	int fieldx60;
};

struct someStructInGS
{
	struct aiFaction* aiFaction;
	struct factionStruct* faction;
	void* arrayx8_objSize20;
	int32_t arrayx8Size;
	int32_t arrayx8Num;
	void* arrayx14_objSize20;
	int32_t arrayx14Size;
	int32_t arrayx14Num;
	void* arrayx20_objSize20;
	int32_t arrayx20Size;
	int32_t arrayx20Num;
	void* aiBrigandControllers;
	int32_t aiBrigandControllersSize;
	int32_t aiBrigandControllersNum;
	int32_t fieldx38;
	void* aiMilitaryControllerWorldWide;
};

struct aiPersonalityValues
{
	struct aiFaction* aiFaction;
	struct aiProductionController** aiProductionControllers;
	int32_t aiProductionControllersSize;
	int32_t aiProductionControllersNum;
	int32_t AIPersonalityType;
	int32_t AIPersonalityName;
	int32_t buildingValues[257];
	int32_t unkBiasCultural1;
	int32_t unkBiasCultural2;
	int32_t unkBiasCultural3;
	int32_t unkBiasCultural4;
	int32_t spyBiasLarge;
	int32_t assassinBiasLarge;
	int32_t diplomatBiasLarge;
	int32_t admiralBiasLarge;
	int32_t priestBiasLarge;
	int32_t merchantBiasLarge;
	int32_t recruitmentValuesLarge[11];
	int32_t populationBias;
	int32_t spyBias;
	int32_t assassinBias;
	int32_t diplomatBias;
	int32_t admiralBias;
	int32_t priestBias;
	int32_t merchantBias;
	int32_t recruitmentValues[11];
	int32_t balancedPolicyNum;
	int32_t financialPolicyNum;
	int32_t militaryPolicyNum;
	int32_t growthPolicyNum;
	int32_t culturalPolicyNum;
	struct settlementPolicies* settlementPolicies;
	int32_t settlementPoliciesSize;
	int32_t settlementPoliciesCount;
	int8_t autoManagedRecruitment;
	int8_t autoManagedConstruction;
	int8_t isAiControlled;
	char pad_01BB[9];
};

struct aiGlobalStrategyDirector
{
	void* _vftable /*VFT*/;
	struct aiFaction* aiFaction;
	struct factionStruct* faction;
	struct factionDataStrategy someFactionData[31];
	struct aiRegionData* ownRegions;
	int32_t ownRegionsSize;
	int32_t ownRegionsCount;
	struct aiRegionData* allNeighbourRegions;
	int32_t allNeighbourRegionsSize;
	int32_t allNeighbourRegionsCount;
	struct aiRegionData* targetRegions;
	int32_t targetRegionsSize;
	int32_t targetRegionsCount;
	struct aiRegionData targetRegionCrusade;
	void* arrayx474_objsize380_maybeNavalTargets;
	int32_t arrayx474Size;
	int32_t arrayx474Num;
	void* arrayx480_objsize180;
	int32_t arrayx480Size;
	int32_t freeShipsMaybe;
	void* regionControllers;
	int32_t arrayx48CSize;
	int32_t regionControllersNum;
	struct someStructInGS someStructInGS;
	void* aiNavalControllers;
	int32_t aiNavalControllersSize;
	int32_t aiNavalControllersNum;
	void* arrayx4F8_objsize20;
	int32_t arrayx4F8Size;
	int32_t arrayx4F8Num;
	int fieldx504_initMinusOne;
	int fieldx508;
	int fieldx50C_init31;
	int fieldx510_init31;
	void* crusadeController;
};

struct settlementPolicies
{
	int32_t regionID;
	int32_t autoManageBuildPolicy;
	int32_t secondaryPolicy;
	int8_t autoManagedConstruction;
	int8_t autoManagedRecruitment;
	char pad_000E[2];
};

struct aiProductionController
{
	void* __vftable /*VFT*/;
	struct aiFaction* aiFaction;
	int regionID;
	struct settlementStruct* settlement;
	int32_t autoManagePolicy;
	int secondaryPolicy;
	int regionRiskLevel1;
	int regionRiskLevel2;
	int regionRiskLevel3;
	int regionRiskLevel4;
	int increaseUnitBias5;
	int increaseTradeStuff;
	int increaseGrowthStuff;
	int increaseSpyBias;
	int increaseAssasinBias;
	int increasePriestBias;
	int increaseMerchantBias;
	int increaseDiplomatBias;
	int increaseShipBias;
	int generalBuildRecruitDesire;
	int minimumUnitValue;
	int fieldx54;
	int fieldx58;
	int startLevel;
	int controllerIndex;
	int8_t isAutoManaged;
	int8_t isAutoManagedRecruitment;
	int8_t isAutoManagedConstruction;
	int8_t isAutoManagedTaxes;
	int8_t hasGrowthBuildPolicy;
	char pad_x[3];
	int fieldx6C;
	int fieldx70;
	int fieldx74;
	int fieldx78;
	int fieldx7C;
	int fieldx80;
	int fieldx84;
	int fieldx88;
	int fieldx8C;
	int fieldx90;
	struct settlementStruct* settlement2;
	struct unitRQ unitInQueue;
	struct buildingInQueue buildingInQueue;
	int randomIncreaseLocation;
	int fieldxFC;
	bool isRandomIncreased;
	bool boolx101;
	char pad_102[2];
	int buildingBias[257];
	int fieldx1E8_unkBiasCultural;
	int fieldx1EC_unkBiasCultural;
	int fieldx1F0_unkBiasCultural;
	int fieldx1F4_unkBiasCultural;
	int spyBiasTurn;
	int assassinBiasTurn;
	int diplomatBiasTurn;
	int admiralBiasTurn;
	int priestBiasTurn;
	int merchantBiasTurn;
	int recruitBiasBoosted[11];
	int populationBoost;
	int8_t buildingQueueEmpty;
	int8_t manualConstruction;
	int8_t unitQueueEmpty;
	int8_t pad22;
	struct settlementStruct* settlement3;
	struct unitRQ unitInQueue2;
	struct buildingInQueue buildingInQueue2;
	int unitValue;
	int fieldx2AC;
	bool boolx2B0;
	bool boolx2B1;
	bool boolx2B2;
	bool boolx2B3;
	int spyBias;
	int assassinBias;
	int diplomatBias;
	int admiralBias;
	int priestBias;
	int merchantBias;
	int recruitBias[11];
};


struct militaryValuesLTGD
{
	int32_t totalPopulation; //0x0000
	int32_t tileCount; //0x0004
	int32_t averagePopulation; //0x0008
	int32_t productionValue; //0x000C
	int32_t nonAlliedBorderLength; //0x0010
	int32_t enemyBorderLength; //0x0014
	int32_t fleetCount; //0x0018
	int32_t navalPowerPerFleet; //0x001C
	int32_t navalStrength; //0x0020
	int32_t armyCount; //0x0024
	int32_t strengthPerArmy; //0x0028
	int32_t totalStrength; //0x002C
	int32_t freeStrength; //0x0030
	int32_t neighbourEnemyNum; //0x0034
	int32_t enemyStrength; //0x0038
	int32_t protectorateOf; //0x003C
};

struct strategyValuesLTGD
{
	int32_t borderTiles; //0x0000
	int32_t frontLineBalance; //0x0004
	int8_t hasAllianceAgainst; //0x0008
	int8_t isStrongestNeighbour; //0x0009
	int8_t isWeakestNeighbour; //0x000A
	char pad_000B[1]; //0x000B

};

struct dataLTGD
{
public:
	struct factionStruct* currentFaction; //0x0000
	char pad_0004[8]; //0x0004
	uint32_t N00024EDA; //0x000C
	char pad_0010[4]; //0x0010
	struct militaryValuesLTGD militaryValuesLTGD[31]; //0x0014
	struct strategyValuesLTGD strategyValuesLTGD[31][31]; //0x07D4
};


struct decisionValuesLTGD
{
public:
	int32_t defendType; //0x0000
	int32_t defendPriority; //0x0004
	int32_t invasionType; //0x0008
	int32_t invadePriority; //0x000C
	int8_t atWar; //0x0010
	int8_t wantPeace; //0x0011
	int8_t wantAlly; //0x0012
	int8_t wantBeProtect; //0x0013
	int8_t wantOfferProtect; //0x0014
	char pad_0015[3]; //0x0015
	int32_t allianceAgainst; //0x0018
	int32_t ptsDesire; //0x001C
	int32_t ptsAlliance; //0x0020
	int32_t N0002EF7A; //0x0024
	int32_t N0002EF7B; //0x0028
	int8_t canForceInvade; //0x002C
	char pad_002D[3]; //0x002D
}; //Size: 0x0030

struct aiLongTermGoalDirector
{
public:
	char pad_0000[4]; //0x0000
	struct aiFaction* aiFaction; //0x0004
	struct factionStruct* faction; //0x0008
	uint32_t trustedAllyEnemies; //0x000C --bitfield
	int32_t freeStrengthEnemy; //0x0010
	int32_t freeStrengthEnemyBalance; //0x0014
	int8_t consideringNavalInvasion; //0x0018
	char pad_0019[3]; //0x0019
	int32_t navalTargetRegionID;
	int32_t navalTargetRegionPriority;
	int32_t x24;
	struct decisionValuesLTGD longTermGoalValues[31]; //0x0028
	int32_t N0002EFB5; //0x05F8
	int32_t militaryBalanceLevel; //0x05FC
	char pad_0600[4]; //0x0600
}; //Size: 0x0604

struct aiFaction
{
public:
	char pad_0000[4]; //0x0000
	struct factionStruct* faction; //0x0004
	int32_t factionID; //0x0008
	char pad_000C[4]; //0x000C
	int8_t N00001E8C; //0x0010
	int8_t N0002F25A; //0x0011
	char pad_0012[14]; //0x0012
	struct aiLongTermGoalDirector* aiLongTermGoalDirector; //0x0020
	struct aiDiplomacyManager* aiDiplomacyManager; //0x0024
	struct aiActionRequestController* aiActionRequestController; //0x0028
	struct aiResourceManager* aiResourceManager; //0x002C
	struct AiFinanceManager* AiFinanceManager; //0x0030
	struct aiPersonalityValues* aiProductionControllers; //0x0034
	struct aiGlobalStrategyDirector* aiGlobalStrategyDirector; //0x0038
	struct aiSubterFugeController* aiSubterFugeController; //0x003C
	struct aiNamedCharacterController* aiNamedCharacterController; //0x0040
	struct aiPriestController* aiPriestController; //0x0044
	struct aiMerchantController* aiMerchantController; //0x0048
}; //Size: 0x0058


struct factionHordeInfo
{
	factionStruct* faction;
	int someFactionID;
	int xCoord;
	int yCoord;
	int hordeUnitCount;
	char field_14;
	char field_15;
	char field_16;
	char field_17;
	int amountTimesHorded;
	int array1c;
	int array1cSize;
	int array1cNum;
	char isHorde;
	char field_29;
	char field_2a;
	char field_2b;
	int hordeMinUnits2;
};

struct scoreRanks
{
	float score;
	float militaryStrength;
	float production;
	float regionsCount;
	float treasury;
	float population;
};

struct marriageOption 
{
	void* yesNoClass;
	bool madeChoice;
	bool accepted;
	bool stub_2[2];
	namedCharacter* possibleHusband;
	namedCharacter* wife;
};

struct adoptionOption
{
	void* yesNoClass;
	bool madeChoice;
	bool accepted;
	bool stub_2[2];
	namedCharacter* possibleSon;
	namedCharacter* father;
	character* someGeneral;
};

struct family
{
	factionStruct* faction;
	marriageOption* marriageOption;
	adoptionOption* adoptionOption;
};

//faction
struct factionStruct {
	int f_40[40];
	int dipNum; /* number of faction in diplomatic array */
	int cultureID;
	struct settlementStruct* capital; /* capital of the faction */
	struct namedCharacter* leader; /* faction leader */
	struct namedCharacter* heir; /* faction heir */
	struct factionStratMapDescrS* factSmDescr;
	int isPlayerControlled; /* is faction a controlled by player */
	struct aiFaction* aiFaction;
	int32_t AIPersonalityType;
	int32_t AIPersonalityName;
	int s_4[4];
	struct holdRegionsWinCondition* WinConditions;
	int32_t regionsOwnedStart;
	struct namedCharacter** charactersAll; /* all characters, died, alive, etc */
	int32_t namedCharactersSize;
	int numOfCharactersAll; /* all characters, died, alive, etc */
	struct character** characters; /* characters on stratmap */
	int32_t charactersSize;
	int numOfCharacters; /* characters on stratmap */
	struct stackStruct** stacks;
	int32_t armiesSize;
	int stackNum;
	int* regionsID;
	int32_t regionsSize;
	int regionsNum;
	struct settlementStruct** settlements;
	int32_t settlementsSize;
	int settlementsNum;
	struct fortStruct** forts;
	int32_t fortsSize;
	int fortsNum;
	struct watchTowerStruct** watchTowers;
	int32_t watchtowersSize;
	int watchtowersNum;
	struct portBuildingStruct** portBuildings; /* port buildings */
	int32_t portBuildingsSize;
	int portBuildingsNum;
	uint32_t neighBourFactionsBitmap;
	int* neighBourRegions;
	int32_t neighBourRegionsSize;
	int32_t neighBourRegionsNum;
	bool hasSeaAccess;
	bool groupPresent;
	bool inCivilWar;
	bool inEndGame;
	factionStruct* groupLeader;
	factionStruct** groupMembers;
	int32_t groupMembersSize;
	int32_t groupMembersNum;
	factionStruct** groupRebels;
	int32_t groupRebelsSize;
	int32_t groupRebelsNum;
	int unitsToMove;
	float timeStartTurn;
	int worldInfluence;
	int32_t deadStatus; // 3 means until resurrected 4 means until emerged
	int8_t reEmergent;
	char pad_3[3];
	factionTileStruct* tilesFac;
	struct mission** missions;
	int32_t missionsSize;
	int32_t missionCount;
	struct mission** pendingMissions;
	int32_t pendingMissionsSize;
	int32_t pendingMissionsCount;
	uint32_t triumphPoints;
	uint32_t triumphPoints2;
	uint32_t triumphPoints3;
	character** hostages;
	int32_t hostagesSize;
	int32_t hostagesCount;
	trackedCharacter* spottedCharacters;
	int32_t spottedCharactersSize;
	int32_t spottedCharactersCount;
	struct factionRanking* factionRankings;
	int32_t factionRankingsSize;
	int32_t factionRankingsCount;
	struct scoreRanks* scoreRank;
	int32_t scoreRanksSize;
	int32_t scoreRanksCount;
	int32_t triumphValue;
	int32_t wonderTimer;
	bool autoManageAll;
	bool autoManageRecruitment;
	bool autoManageBuildings;
	bool autoManageTaxes;
	float spendingLimit;
	struct capabilityStruct factionCapabilities;
	int8_t hasSettlementsProcessed;
	char pad_3_2[3];
	int32_t treasuryTurnStart;
	int f_2[2];
	bool isHorde;
	char pad_0A39[3];
	factionHordeInfo* factionHordeInfo;
	bool shadowSwitch;
	char pad_3_3[3];
	int f_15[15];
	factionStruct* factionEconomyOffset;
	int money; /* money of the faction */

	int f_225[225];

	struct family facFamily;
//	factionStruct* factionFamilyOffset;
//	marriageOption* marriageOption;
//	adoptionOption* adoptionOption;





//	int32_t incomeDoubled;
//	struct factionEconomy factionEconomyTable[10];
//	int32_t nextCounterEconomy;
//	int32_t counterEconomy;
//	int32_t maxTurnsTillReset;
//	int32_t upkeepModifier;
//	factionStruct* factionFamilyOffset;
//	void* marriageOption;
//	void* adoptionOption;
//	struct battleFactionCounter(*battlesWonVsFaction)[21];
//	int32_t factionCountStart;
//	int32_t otherFactionCount;
//	int32_t battlesWon;
//	int32_t battlesLost;
//	int32_t lastOpponentId;
public:
	UNICODE_STRING**& getLocalizedUnicodeName();
	std::string getLocalizedName();
	std::string getLocalizedNameAnsi();
};

struct animSetModelDB
{
public:
	char pad_0000[4]; //0x0000
	char *name; //0x0004
	char pad_0008[24]; //0x0008
}; //Size: 0x0020

struct modelDbAnims
{
public:
	char pad_0000[4]; //0x0000
	char N000028CE[4]; //0x0004
	char N000028CF[4]; //0x0008
	char pad_000C[20]; //0x000C
	char *N00022FB0; //0x0020
	char pad_0024[52]; //0x0024
	struct animSetModelDB *primaryAnim; //0x0058
	void *N0000092A; //0x005C
	void *N0000092B; //0x0060
	char pad_0064[4]; //0x0064
	struct animSetModelDB *secondaryAnim; //0x0068
	char pad_006C[12]; //0x006C
}; //Size: 0x0078


struct ModelDbEntry
{
public:
	char pad_0000[4]; //0x0000
	char N00002889[8]; //0x0004
	char pad_000C[8]; //0x000C
	int32_t nameLength; //0x0014
	char pad_0018[4]; //0x0018
	float scale; //0x001C
	char pad_0020[4]; //0x0020
	struct ModelDbMesh* mesh; //0x0024
	char pad_0028[12]; //0x0028
	struct ModelDbEntryTextures* textures; //0x0034
	char pad_0038[12]; //0x0038
	struct ModelDbEntryTextures* attTextures; //0x0044
	char pad_0048[12]; //0x0048
	struct modelDbAnims* animations; //0x0054
	char pad_0058[8]; //0x0058
	int32_t torchAttachBone; //0x0060
	float N00000857; //0x0064
	float N00000858; //0x0068
	float N00000859; //0x006C
	float N0000085A; //0x0070
	float N0000085B; //0x0074
	float N0000085C; //0x0078
	char pad_007C[4]; //0x007C
}; //Size: 0x0080


struct ArmourUpgModels
{
public:
	char* BaseModel; //0x0000
	int32_t BaseModelHash; //0x0004
	char* UpgradeOne; //0x0008
	int32_t UpgradeOneHash; //0x000C
	char* UpgradeTwo; //0x0010
	int32_t UpgradeTwoHash; //0x0014
	char* UpgradeThree; //0x0018
	int32_t UpgradeThreeHash; //0x001C
};

struct descrMountEntry
{
public:
	char *name; //0x0000
	char pad_0004[4]; //0x0004
	int32_t mountClass; //0x0008
	char *modelName; //0x000C
	char pad_0010[12]; //0x0010
	float radius; //0x001C
	float xRadius; //0x0020
	float yRadius; //0x0024
	float yOffset; //0x0028
	float height; //0x002C
	float mass; //0x0030
	float bannerHeight; //0x0034
	float bouyancyOffset; //0x0038
	float elephantRootNodeHeight; //0x003C
	float elephantAttackDelay; //0x0040
	float elephantDeadRadius; //0x0044
	float elephantTuskZ; //0x0048
	float elephantTuskRadius; //0x004C
	int32_t elephantNumberOfRiders; //0x0050
	float elephantRiderOffset1X; //0x0054
	float elephantRiderOffset1Y; //0x0058
	float elephantRiderOffset1Z; //0x005C
	char pad_0060[168]; //0x0060
	float rootNodeHeight; //0x0108
	float riderOffSetX; //0x010C
	float riderOffSetY; //0x0110
	float riderOffsetZ; //0x0114
	char pad_0118[8]; //0x0118
	char *waterTrailEffect; //0x0120
	char pad_0124[20]; //0x0124
}; //Size: 0x0138

struct mountEffect
{
	int mountClass;
	int mountIndex;
	int bonus;
};


//type of unit from EDU
struct eduEntry {
	char* Type;
	uint32_t typeHash;
	DWORD Index;
	DWORD UnitCreatedCounter;
	char* UnitCardTga;
	uint32_t unitcardHash;
	char* InfoCardTga;
	uint32_t unitInfoCardHash;
	UNICODE_STRING*** localizedName;
	UNICODE_STRING*** localizedDescr;
	UNICODE_STRING*** localizedDescrShort;
	unitCategory Category;
	unitClass Class;
	unitCategoryClass categoryClassCombinationForAI;
	DWORD VoiceType;
	DWORD Trained;
	DWORD StatMentalDicipline;
	int8_t Morale;
	int8_t StatHealth;
	int8_t StatHealthAnimal;
	int8_t StatHeat;
	int8_t StatGround1;
	int8_t StatGround2;
	int8_t StatGround3;
	int8_t StatGround4;
	ushort StatFood1;
	ushort StatFood2;
	ushort StatFireDelay;
	float ChargeDistance;
	mountEffect mountEffects[3];
	DWORD mountEffectCount;
	ushort eu_1;
	ushort recruitTime;
	ushort recruitCost;
	ushort upkeepCost;
	ushort weaponCost;
	ushort armourCost;
	ushort customBattleCost;
	int8_t formationHorde;
	int8_t formationColumn;
	int8_t formationSquare;
	int8_t formationWedge;
	int8_t formationSquareHollow;
	int8_t formationTestudo;
	int8_t formationPhalanx;
	int8_t formationSchiltrom;
	int8_t formationShieldWall;
	int8_t formationWall;
//	int8_t formationMovingThrough;
	char pad_00EE[2];
	uint32_t defaultRanks;
	float unitSpacingFrontToBackClose;
	float unitSpacingSideToSideClose;
	float unitSpacingFrontToBackLoose;
	float unitSpacingSideToSideLoose;
	char* soldier;
	int soldierHash;
	int modelIndex;
	void* modelGroup;
	int modelEntry;
	uint16_t soldierCount;
	uint16_t pad11a;
	float mass;
	float width;
	float height;
	char* e_79[79];

//public:
//	// Deep Copy Constructor
//	eduEntry(const eduEntry& obj) {
//		Type = new char;
//		*Type = *(obj.Type);
//
//
//
//		typeHash                                      = *new uint32_t;
//	 Index                                            = *new DWORD;
//	 UnitCreatedCounter                               = *new DWORD;
//	UnitCardTga                                      = new char;
//	 unitcardHash                                  = *new uint32_t;
//	InfoCardTga                                      = new char;
//	 unitInfoCardHash                              = *new uint32_t;
//	 localizedName                        = new UNICODE_STRING**;
//	 localizedDescr                       = new UNICODE_STRING**;
//	 localizedDescrShort                  = new UNICODE_STRING**;
//	 Category                                  = *new unitCategory;
//	 Class                                        = *new unitClass;
//	 categoryClassCombinationForAI        = *new unitCategoryClass;
//	 VoiceType                                        = *new DWORD;
//	 Trained                                          = *new DWORD;
//	 StatMentalDicipline                              = *new DWORD;
//	 Morale                                          = *new int8_t;
//	 StatHealth                                      = *new int8_t;
//	 StatHealthAnimal                                = *new int8_t;
//	 StatHeat                                        = *new int8_t;
//	 StatGround1                                     = *new int8_t;
//	 StatGround2                                     = *new int8_t;
//	 StatGround3                                     = *new int8_t;
//	 StatGround4                                     = *new int8_t;
//	 StatFood1                                       = *new ushort;
//	 StatFood2                                       = *new ushort;
//	 StatFireDelay                                   = *new ushort;
//	 ChargeDistance                                   = *new float;
//	 mountEffects[3]                            = *new mountEffect;
//	 mountEffectCount                                 = *new DWORD;
//	 eu_1                                            = *new ushort;
//	 recruitTime                                     = *new ushort;
//	 recruitCost                                     = *new ushort;
//	 upkeepCost                                      = *new ushort;
//	 weaponCost                                      = *new ushort;
//	 armourCost                                      = *new ushort;
//	 customBattleCost                                = *new ushort;
//	 formationHorde                                  = *new int8_t;
//	 formationColumn                                 = *new int8_t;
//	 formationSquare                                 = *new int8_t;
//	 formationWedge                                  = *new int8_t;
//	 formationSquareHollow                           = *new int8_t;
//	 formationTestudo                                = *new int8_t;
//	 formationPhalanx                                = *new int8_t;
//	 formationSchiltrom                              = *new int8_t;
//	 formationShieldWall                             = *new int8_t;
//	 formationWall                                   = *new int8_t;
//	pad_00EE[2]                                       = *new char;
//	 defaultRanks                                  = *new uint32_t;
//	 unitSpacingFrontToBackClose                      = *new float;
//	 unitSpacingSideToSideClose                       = *new float;
//	 unitSpacingFrontToBackLoose                      = *new float;
//	 unitSpacingSideToSideLoose                       = *new float;
//	soldier                                          = new char;
//	 soldierHash                                        = *new int;
//	 modelIndex                                         = *new int;
//	 modelGroup                                       = new void*;
//	 modelEntry                        = *new struct modelDbEntry*;
//	 soldierCount                                  = *new uint16_t;
//	 pad11a                                        = *new uint16_t;
//	 mass                                             = *new float;
//	 width                                            = *new float;
//	 height                                           = *new float;
//	e_79[79]                                         = new char;
//
//
//
//
//
//
//	};

};


/* из ЕОП для тестов с лимитом юнитов   
struct pseudoFile {
	char* _ptr;
	int _cnt;
	char* _base;
	int _flag;
	char* _file;
	char* _charbuf;
	int _bufsiz;
	char* _tmpfname;
};


//type of unit from EDU
struct eduEntry {
	char* Type;
	uint32_t typeHash;
	DWORD Index;
	DWORD UnitCreatedCounter;
	char* UnitCardTga;
	uint32_t unitcardHash;
	char* InfoCardTga;
	uint32_t unitInfoCardHash;
	char* cardPicDir;
	uint32_t cardPicDirHash;
	char* InfoPicDir;
	uint32_t infoPicDirHash;
	UNICODE_STRING*** localizedName;
	UNICODE_STRING*** localizedDescr;
	UNICODE_STRING*** localizedDescrShort;
	uint32_t Category;
	uint32_t Class;
	uint32_t categoryClassCombinationForAI;
	DWORD VoiceType;
	char* Accent;
	uint32_t accentHash;
	char* BannerFaction;
	char pad_0058[4];
	char* BannerUnit;
	char pad_0060[4];
	char* BannerHoly;
	char pad_0068[4];
	char* BannerMarine;
	char pad_0070[4];
	char* BannerSecondary;
	char pad_0078[12];
	DWORD Trained;
	DWORD StatMentalDicipline;
	int8_t MoraleLocked;
	int8_t Morale;
	int8_t StatHealth;
	int8_t StatHealthAnimal;
	int8_t StatHeat;
	int8_t StatGround1;
	int8_t StatGround2;
	int8_t StatGround3;
	int8_t StatGround4;
	char pad_0095[1];
	ushort StatFood1;
	ushort StatFood2;
	ushort StatFireDelay;
	DWORD StatStl;
	float ChargeDistance;
	DWORD mountEffectClass;
	char pad_00A8[4];
	DWORD mountEffectAmount2;
	DWORD mountEffectClass2;
	char pad_00B4[4];
	DWORD mountEffectAmount3;
	DWORD mountEffectClass3;
	char pad_00C0[4];
	DWORD mountEffectAmount4;
	DWORD MountEffectCount;
	ushort StatCost1;
	ushort StatCost2;
	ushort StatCost3;
	ushort StatCost4;
	ushort StatCost5;
	ushort StatCost6;
	ushort StatCost7;
	ushort StatCost8;
	DWORD CrusadingUpkeepModifier;
	DWORD RecruitPriorityOffsetTimes4;
	int8_t formationHorde;
	int8_t formationColumn;
	int8_t formationSquare;
	int8_t formationSquareHollow;
	int8_t formationWedge;
	int8_t formationPhalanx;
	int8_t formationSchiltrom;
	int8_t formationShieldWall;
	int8_t N000000AA;
	int8_t hasSquareFormation;
	char pad_00EE[2];
	uint32_t DefaultNubmerOfRanks;
	float UnitSpacingFrontToBackClose;
	float UnitSpacingSideToSideClose;
	float UnitSpacingFrontToBackLoose;
	float UnitSpacingSideToSideLoose;
	char* Soldier;
	char pad_0108[12];
	struct ModelDbEntry* ModelDBEntry;
	DWORD SoldierCount;
	float Mass;
	float Width;
	float Height;
	uint32_t StatPri;
	DWORD Ammunition;
	DWORD MissleRange;
	float MissleRangeSquared;
	DWORD HasPrimary;
	projectile* StatPriMissle;
	DWORD WeaponType;
	DWORD TechType;
	DWORD DamageType;
	DWORD SoundType;
	DWORD AttackMinDelay;
	char pad_0154[4];
	char WeaponShootEffect[20];
	char pad_016C[4];
	uint32_t StatSec;
	DWORD SecAmmunition;
	DWORD SecMissleRange;
	float SecMissleRangeSquared;
	DWORD HasSecondary;
	projectile* StatSecMissle;
	DWORD SecWeaponType;
	DWORD SecTechType;
	DWORD SecDamageType;
	DWORD SecSoundType;
	DWORD SecAttackMinDelay;
	char pad_019C[28];
	uint32_t StatPriArmour;
	char pad_01BC[4];
	char* FirstOfficier;
	void* N000000E0;
	char pad_01C8[8];
	void* N000000E3;
	char* SecondOfficier;
	void* N000000E5;
	char pad_01DC[8];
	void* N000000E8;
	char* ThirdOfficier;
	void* N000000EA;
	char pad_01F0[8];
	void* N000000ED;
	DWORD OfficierCount;
	char pad_0200[4];
	int8_t* ArmorUpgradeLevels;
	int8_t* ArmorUpgradesEnd;
	int8_t* ArmorUpgrade2;
	char pad_0210[4];
	struct ArmourUpgModels* ArmorUpgradeModels;
	int* ArmorUpgradeModelsEnd;
	int* ArmorUpgrade5;
	int extrasCount;
	void* N000000F8;
	char pad_0228[4];
	int8_t N000000FA;
	int8_t N000003B1;
	int8_t EngineMissleAttack;
	int8_t EngineMissleChargeBonus;
	DWORD EngineMissleAmmunition;
	DWORD EngineMissleRange;
	float EngineMissleRangeSquared;
	DWORD Unknown3;
	void* EngineMissle;
	DWORD EngineMissleWeaponType;
	DWORD EngineMissleTechType;
	DWORD EngineMissleDamageType;
	DWORD EngineMissleSoundType;
	DWORD EngineMissleAttackMinDelay;
	char pad_0258[48];
	void* N00000111;
	DWORD N00000112;
	DWORD N00000113;
	DWORD N00000114;
	DWORD N00000115;
	DWORD TerMissleAttackMinDelay;
	char pad_02A0[36];
	struct descrMountEntry* mount;
	struct ModelDbEntry* mountModel;
	DWORD StatSecAndSecArmour;
	char pad_02D0[68];
	DWORD notmount;
	char pad_0318[8];
	void* AnimalModel;
	void* AnimalSomething;
	char pad_0328[84];
	void* Ship;
	uint32_t ownership;
	int32_t eraAmount;
	void* eraOwnerships;
	void* N00000152;
	void* N00000153;
	float aiUnitValuePerSoldier;
	float aiUnitValue;
	char pad_039C[4];
	DWORD* Attributes;
	DWORD* EndOfAttributes;
	void* BytesBeforeNextAttributes;
	int8_t Attributes2;
	int8_t Attributes3;
	int8_t Attributes4;
	int8_t Attributes5;
	DWORD Attributes6;
	float MoveSpeedMod;
	DWORD AttributeAreaEffect;
	char pad_03BC[28];
	float PriSkeletonCompFactor;
	float SecSkeletonCompFactor;
	float TerSkeletonCompFactor;
};
*/



//pointer to ancillary
struct ancData { /* data of the ancillary */
	struct ancillary* dataAnc;
};

struct soldierData
{
	unsigned __int32 name : 6;
	unsigned __int32 years : 6;
	unsigned __int32 experience : 4;
	unsigned __int32 numKills : 4;
	unsigned __int32 scale : 3;
	unsigned __int32 armour : 3;
	unsigned __int32 weapon : 3;
public:
	int getName()
	{
		return name;
	}
	int getYears()
	{
		return years;
	}
	int getExperience()
	{
		return experience;
	}
	int getNumKills()
	{
		return numKills;
	}
	int getScale()
	{
		return scale;
	}
	int getArmour()
	{
		return armour;
	}
	int getWeapon()
	{
		return weapon;
	}
	void setName(int newName)
	{
		name = newName;
	}
	void setYears(int newYears)
	{
		years = newYears;
	}
	void setExperience(int newExp)
	{
		experience = newExp;
	}
	void setNumKills(int newKills)
	{
		numKills = newKills;
	}
	void setScale(int newScale)
	{
		scale = newScale;
	}
	void setArmour(int newArmour)
	{
		armour = newArmour;
	}
	void setWeapon(int newWeapon)
	{
		weapon = newWeapon;
	}
};



struct ltgdFactionValues
{
public:
	int32_t totalPopulation; //0x0000
	int32_t tileCount; //0x0004
	int32_t averagePopulation; //0x0008
	int32_t productionValue; //0x000C
	int32_t nonAlliedBorderLength; //0x0010
	int32_t enemyBorderLength; //0x0014
	int32_t fleetCount; //0x0018
	int32_t navalPowerPerFleet; //0x001C
	int32_t navalStrength; //0x0020
	int32_t armyCount; //0x0024
	int32_t strengthPerArmy; //0x0028
	int32_t totalStrength; //0x002C
	int32_t freeStrength; //0x0030
	int32_t neighbourEnemyNum; //0x0034
	int32_t enemyStrength; //0x0038
	int32_t protectorateOf; //0x003C
}; //Size: 0x0040

struct interFactionLTGD
{
public:
	int32_t borderTiles; //0x0000
	int32_t frontLineBalance; //0x0004
	int8_t hasAllianceAgainst; //0x0008
	int8_t isStrongestNeighbour; //0x0009
	int8_t isWeakestNeighbour; //0x000A
	char pad_000B[1]; //0x000B
}; //Size: 0x000C

struct ltgdGlobals
{
public:
	struct factionStruct* currentFaction; //0x0000
	char pad_0004[8]; //0x0004
	uint32_t N00024EDA; //0x000C
	char pad_0010[4]; //0x0010
	struct ltgdFactionValues ltgdFactionValues[31]; //0x0014
	struct interFactionLTGD interFactionLTGD[31][31]; //0x07D4
};


//fort
struct fortStruct {
public:
	void* fortVtable;
	struct character* gubernator;
	undefined field_0x8[4];
	UINT32 xCoord;
	UINT32 yCoord;
	undefined field_0x14[32];
	float bannerPosX;
	float bannerPosZ;
	float bannerPosY;
	struct trackedPointerArmy_vtbl* trackedPointerArmyVtable;
	struct stackStruct* army;
	struct oneSiege sieges[8];
	int8_t siegeNum; //0x0088
	char pad_0089[3]; //0x0089
	int32_t siegeHoldoutTurns;
	int32_t turnsSieged;
	int32_t fieldx94;
	int32_t populationSiegeStart;
	int32_t fieldx9C;
	int32_t somethingPlagueRelated;
	int8_t plagued;
	int8_t setZeroAfterInvaded; //0x00A5
	int8_t bytexA6;
	int8_t bytexA7;
	int32_t fieldxA8;
	struct descrRebelEntry* descrRebel; //0x00AC
	int32_t subFactionID; //0x00B0
	void* spyingInfoBase; //0x00B4
	int8_t spyingInfoFactions[31]; //0x00B8
	char pad_00D7[9]; //0x00D7
	struct stratFortMod* stratModel;
	int regionID;
	struct factionStruct* faction;
	int32_t factionID; //0x00EC
	int32_t cultureID; //0x00F0
	void* localString; //0x00F4
	char* fortType;
	char pad_00FC[4]; //0x00FC
	int32_t fortFortificationLevel; //0x0100
	char pad_0104[20]; //0x0104
};

struct traidingResource {
	char* name;
	int nameCrypt;
	int null1;
	struct model_Rigid* model;
	char* item;
	int itemCrypt;
	int null3;
	int trade_value;
	char* icon;
	int iconCrypt;
	int null4;//
};

struct tradingResources {
	struct traidingResource resources[27];
	char* mine;
	int mineCrypt;
};

struct console_command { /* structure of console command */
	bool(_stdcall** function)(const char*, char*);
	char* name;
	char* description;
	int type;
	int idk;
};

struct consoleCommands {
	struct console_command** commands;
	int reservedElements;
	int size;
};

struct battleCameraStruct
{
public:
	float x; //0x0000
	char pad_0004[4]; //0x0004
	float y; //0x0008
	char pad_000C[20]; //0x000C
	float z; //0x0020
}; //Size: 0x0024

struct settlementUiTextStruct
{
public:
	float ValueColumn; //0x0000
	char pad_0004[4]; //0x0004
	float yCoord; //0x0008
	char pad_000C[20]; //0x000C
	float zCoord; //0x0020
}; //Size: 0x0024


struct descr_sm_factions_list {
	struct factionStratMapDescrS* facDescrs;
	int capacity;
	int size;
};

struct uiManager
{
public:
	char pad_0000[12]; //0x0000
	char *N00009D87; //0x000C
	char pad_0010[32]; //0x0010
	void *dragObjectContainer; //0x0030
	struct stratUIStruct *stratUI; //0x0034
}; //Size: 0x00A0


// Settlement UI Stuff
struct stratUIStruct
{
public:
	char pad_0000[84]; //0x0000
	struct settlementInfoScroll *settlementInfoScroll; //0x0054
}; //Size: 0x0164


struct settlementInfoScroll
{
public:
	char pad_0000[40]; //0x0000
	uint32_t N000218A6; //0x0028
	char pad_002C[136]; //0x002C
	float N000218C9; //0x00B4
	float N000218CA; //0x00B8
	float N000218CB; //0x00BC
	float N000218CC; //0x00C0
	char pad_00C4[576]; //0x00C4
	struct settlementStruct *settlement; //0x0304
	char pad_0308[12]; //0x0308
	void *N00021961; //0x0314
	char pad_0318[16]; //0x0318
	void *uiTable; //0x0328
	void *uiTable2; //0x032C
	char pad_0330[12]; //0x0330
	void *uiSettlementFrame; //0x033C
	char pad_0340[4]; //0x0340
	void *characterInfoFrame; //0x0344
	void *uiCycleListTax; //0x0348
	void *uiCycleList0; //0x034C
	void *uiCycleList; //0x0350
	char pad_0354[16]; //0x0354
	void *uiCheckBox; //0x0364
	void *uiCheckBox2; //0x0368
	void *uiCheckBox3; //0x036C
	void *N00021978; //0x0370
	char pad_0374[16]; //0x0374
	void *settlementRenameElement; //0x0384
	struct settlementStatsTable *settlementStatsTable; //0x0388
}; //Size: 0x0840

struct settlementStatsTable
{
public:
	char pad_0000[76]; //0x0000
	struct settlementTextStrings *settlementTextStrings; //0x004C
}; //Size: 0x0844

struct settlementTextStrings
{
public:
	struct uiString *incomeString; //0x0000
	struct uiString *incomeValue; //0x0004
	struct uiString *publicOrderString; //0x0008
	struct uiString *publicOrderValue; //0x000C
	struct uiString *populationString; //0x0010
	struct uiString *populationValue; //0x0014
	struct uiString *populationGrowthString; //0x0018
	struct uiString *populationGrowthValue; //0x001C
}; //Size: 0x0020

struct uiString
{
public:
	char pad_0000[72]; //0x0000
	void *N00023379; //0x0048
	void *N0002337A; //0x004C
	char pad_0050[8]; //0x0050
	void *N0002337D; //0x0058
	char pad_005C[4]; //0x005C
	void *settlementText; //0x0060
	char pad_0064[4]; //0x0064
	uint8_t thickness; //0x0068
	uint8_t blue; //0x0069
	uint8_t green; //0x006A
	uint8_t red; //0x006B
	char pad_006C[36]; //0x006C
}; //Size: 0x0090

struct stratCursorPosition {
	int x, y;
};

struct battleCamera {
	float x, y, z;
};
#pragma pack(pop)

struct character_action
{
	int something;
};

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

enum actionType
{
	noneAction,
	selectAction,
	moveAction,
	movePlus,
	ignoreAction,
	merge,
	embark,
	disembark,
	garrison,
	attack,
	talk,
	talkBribe,
	spy,
	infiltrate,
	assassinate,
	mission,
	rallyPoint,
	rallyPointSelect,
};

enum mouseEvent
{
	noneMouse = -1,
	moveMouse = 0,
	leftDblClick = 1,
	leftDown = 2,
	leftUp = 3,
	midDblClick = 4,
	midDown = 5,
	midUp = 6,
	rightDblClick = 7,
	rightDown = 8,
	rightUp = 9,
	wheelForward = 10,
	wheelBackward
};

struct cursorAction
{
	actionType type;
	bool isAuto;
//	UNICODE_STRING* tooltip;
	UNICODE_STRING*** tooltip;
};

struct stratMapCursor 
{
	int smt_5[5];
	int cursorType;
	coords previousPosition;
	vector_3 currentView;
	vector_3 landscapeIntersection;
	bool smt_b1 : 1;
	bool smt_b2 : 1;
	bool visible : 1;
	bool mouseMoved : 1;
	bool show : 1;
	bool showNext : 1;
	bool smt_b3 : 1;
	bool enabled : 1;
	int lastUpdate;
	int_32 smt_int_32;
	coords intersection;
	cursorAction* action;
	int smt_int;
	int	smt_8[8];
	mouseEvent event;
};
extern stratMapCursor* gameCursor; 

struct descrFile
{
	char* buffer;
	char* end;
	UNICODE_STRING** file;
	mutable char* line1;
	mutable char* line2;
	mutable int	lineNumber;

public:
	descrFile(char* buf, char* end, UNICODE_STRING**& file, char* wal, char* start, int ln) : buffer(buf), end(end), file(file), line1(wal), line2(start), lineNumber(ln) {}
};

struct nameAndHash
{
	char* name;
	int hash;
};

struct scriptClass
{
	bool(_stdcall** function)();
};

struct formationType
{
	std::string buffer;
	std::string type[1500];
};
extern formationType eduFormation;

// Нужно для вызова callSaveCreate   
struct gameSaveStruct
{
	bool b1;
	undefined4 u1;
	undefined4 u2;
	undefined4 u3;
	undefined4 u4;
	int_32 i1;
	bool b2;
	undefined4 u5;
	undefined4 u6;
	undefined4 u7;
	int_32 i2;
	bool b3;
	undefined4 u8;
};

struct indexLookUp
{
	const char* name;
	int index;
public:
	indexLookUp(const char* n, int i) : name(n), index(i) {}
};

struct unitDb { /* structure with all edu entries */
	UINT32 qq;
	struct eduEntry unitEntries[500];
	UINT32 numberOfEntries;
	int maxEntryNum;
	struct indexLookUp* indexLookUps;
	char* pad_79960;
	char* smthingCmparedForTypeLookup;
	int32_t minusOne;
	int8_t fieldss;
	int arraysmething[1000];
	int32_t smthing;
	int32_t maxTypesAgainProb;
	void* N000237FD;
	char pad_7A91C[24];
	int32_t int7a934;
	uint32_t unitDbHash;
	uint16_t mostExpensiveInfantry;
	uint16_t N0002391D;
	uint16_t mostExpensiveCavalry;
	uint16_t N00023913;
	uint16_t mostExpensiveSiege;
	uint16_t N00023915;
	uint16_t leastExpensiveInfantry;
	uint16_t N00023917;
	uint16_t leastExpensiveCavalry;
	uint16_t N00023919;
	uint16_t leastExpensiveSiege;
	uint16_t N0002391B;
};

enum scriptResult
{
	unfinished,
	finished,
	monitorAdd,
	monitorRemove,
	monitorNo,
	pauseOn,
	pauseOff,
	suspend_during_battle_on,
	suspend_during_battle_off,
	removeScript
};

struct planSet
{
	nameAndHash	id;
	int levels[7];
	int defaultLevels;
	int locale;
	int index;
};



















