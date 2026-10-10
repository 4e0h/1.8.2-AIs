#pragma once
#include "../../pch.h"
#include "../../FortniteGame/Public/FortPlayerControllerAthena.h"
#include "../../FortniteGame/Public/FortGameMode.h"

class AFortAthenaAIBotController : public AActor
{
public:
    UCLASS_COMMON_MEMBERS(AFortAthenaAIBotController);

    DEFINE_PROP(Inventory, AFortInventory*);
};

class AAIController : public AActor
{
public:
    UCLASS_COMMON_MEMBERS(AAIController);

    DEFINE_PROP(BrainComponent, UObject*);
    DEFINE_FUNC(Possess, void);

    DEFINE_FUNC(RunBehaviorTree, bool);

    DEFINE_FUNC(MoveToLocation, uint8_t);

    DEFINE_FUNC(SetControlRotation, void);

    // The engine's own "can this controller actually see that actor" check -- walls, floors and
    // everything else in the way. This is what gives a bot eyes instead of knowing where everyone
    // is through the terrain.
    DEFINE_FUNC(LineOfSightTo, bool);

    // Where the controller is actually pointed right now (read back to check the aim held).
    DEFINE_FUNC(GetControlRotation, FRotator);

    // Drops whatever walk it was on.
    DEFINE_FUNC(StopMovement, void);

    // The engine turns every AI controller towards its "focus" each frame, before the gun's automatic
    // shots go off -- so this is what keeps a whole burst pointed where the bot code aimed it.
    DEFINE_FUNC(K2_SetFocus, void);
    DEFINE_FUNC(K2_SetFocalPoint, void);
    DEFINE_FUNC(K2_ClearFocus, void);
};

class UFortAthenaAISpawnerDataComponent_Behavior : public UObject
{
public:
    UCLASS_COMMON_MEMBERS(UFortAthenaAISpawnerDataComponent_Behavior);

    DEFINE_PROP(BehaviorTree, UObject*);
};

class UAthenaAISpawner : public UObject
{
public:
    UCLASS_COMMON_MEMBERS(UAthenaAISpawner);

    DEFINE_FUNC(RequestSpawn, int32);
};

class UAthenaAISystem : public UObject
{
public:
    UCLASS_COMMON_MEMBERS(UAthenaAISystem);

    DEFINE_PROP(AISpawner, UAthenaAISpawner*);
};

class UFortAthenaAISpawnerDataComponentList : public UObject
{
public:
    UCLASS_COMMON_MEMBERS(UFortAthenaAISpawnerDataComponentList);
};

class UFortAthenaAISpawnerData : public UObject
{
public:
    UCLASS_COMMON_MEMBERS(UFortAthenaAISpawnerData);

    DEFINE_STATIC_FUNC(CreateComponentListFromClass, UFortAthenaAISpawnerDataComponentList*);
};

class AFortPoiVolume : public AActor
{
public:
    UCLASS_COMMON_MEMBERS(AFortPoiVolume);

    DEFINE_BITFIELD_PROP(bIsLargeGameVolume);

    DEFINE_PROP(LocationTags, FGameplayTagContainer);
};

class UAITask_MoveTo : public UObject
{
public:
    UCLASS_COMMON_MEMBERS(UAITask_MoveTo);

    DEFINE_STATIC_FUNC(AIMoveTo, UAITask_MoveTo*);
};

namespace BotAI
{
    int SpawnBots(const FVector& Origin, int Count, float ScatterRadius = 3000.f, const std::wstring& SpawnerDataAssetPath = L"");

    bool MoveSomeBotsToIsland(int MaxThisTick);

    void RegisterBotsAsAlive();

    void GameThreadTick();

    void RenameUnnamedBots();

    void DressUndressedBots();

    void CheckForVictory();

    bool ShouldGrantVictoryTo(AFortPlayerStateAthena* CandidateState, AFortPlayerStateAthena* DyingVictimState);

    bool MatchHasStarted();

    void SetBotSpawningPaused(bool bPaused);

    bool AreBotSpawnsPaused();

    bool BusMayLaunch();

    void ClearBusForLaunch(const char* Why);

    bool BusIsClearedForLaunch();

    void HoldTheWarmupClock(AFortGameStateAthena* GameState, AFortGameMode* GameMode, float Now);

    bool IsServerOwner(AFortPlayerControllerAthena* Controller);

    // Makes sure the grappler's 999-round data-table hotfix has landed before anything is handed out.
    void EnsureWeaponHotfixes();

    // Every elimination is decided exactly once, in BotAI.cpp (SettleElimination): who gets the kill (or nobody, with a
    // "no killer" line), the killfeed's cause, the "Eliminated <name>" popup. This is how the game's own death report
    // (ClientOnPawnDied) hands a death in. Returns true if somebody was credited with the kill.
    bool SettleEliminationFromGameReport(AFortPlayerStateAthena* Victim, AFortPlayerStateAthena* Killer, AFortPlayerPawnAthena* VictimPawn,
                                         AFortPlayerPawnAthena* KillerPawn, AActor* DamageCauser);

    // A line from the 1.8.2 client DLL ("cheat clientlog <text>"): what that player's own game showed -- the killfeed, the
    // "Eliminated" popup, the storm timer, F7 turbo building. Written to this log with the player's name.
    void LogFromClient(AFortPlayerControllerAthena* Controller, const char* Text);
}
