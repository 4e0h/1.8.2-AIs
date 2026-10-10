#pragma once

struct FConfiguration
{
    static inline auto Playlist = L"/Game/Athena/Playlists/Playlist_DefaultSolo.Playlist_DefaultSolo";
    static inline auto MaxTickRate = 30;

    static inline auto bDisableStorm = false;

    static inline auto bUseMapStormTimes = true;

    static inline auto StormPhaseTimeScale = 1.f;

    static inline auto StormStartPhase = 1;

    static inline auto bStormLog = true;

    static inline auto StormLogIntervalSeconds = 5.f;

    static inline auto bBotLog = true;

    static inline auto bManageStormDamage = false;

    static inline auto StormDamageScale = 1.f;

    static inline auto bBotsFleeTheStorm = true;

    static inline auto BotZoneEntryFraction = 0.5f;

    static inline auto bRecordPlaceDump = true;

    static inline auto PlaceDumpHotkey = 0x73;

    // Loads the recorded places (built-in + the folder below). Bots no longer walk these as routes --
    // that "navmesh" is gone from their movement -- they are only used to find the hot-drop spot.
    static inline auto bUsePlaceDump = true;

    static inline auto PlaceDumpFolder = "C:\\4e0h\\Locations";

    static inline auto PlaceDumpIntervalSeconds = 0.1f;

    static inline auto PlaceDumpMinSpacing = 120.f;

    static inline auto bRecordBots = true;

    static inline auto PlaceDumpBotIntervalSeconds = 1.0f;

    static inline auto PlaceDumpBotMinSpacing = 300.f;

    static inline auto PlaceDumpHeightCeiling = 12000.f;

    static inline auto PlaceDumpMaxStep = 1200.f;

    static inline auto bBotCombatEnabled = true;

    static inline auto BotSprintSpeed = 510.f;

    static inline auto bBotsFaceTheirDirection = true;

    static inline auto BotFacingMinimumSpeed = 40.f;

    static inline auto bBotsNeverRunOutOfAmmo = true;

    static inline auto bDisableStormSurge = true;

    static inline auto bLockServerSpeed = true;

    static inline auto bAllBotsFight = true;

    static inline auto BotEngageRange = 12000.f;

    // How wide a bot's vision is, in degrees, total. 120 means 60 either side of where it is facing.
    static inline auto BotFieldOfView = 150.f;

    // Inside this, a bot notices you whichever way it happens to be facing -- it heard you.
    static inline auto BotHearingRange = 3000.f;

    // How long a bot keeps hunting somebody after losing sight of them, in ticks (30 a second).
    static inline auto BotMemoryTicks = 60;

    static inline auto BotHuntPlayerRange = 24000.f;

    static inline auto BotPlayerPreference = 0.35f;

    static inline auto bBotsFightEachOther = true;

    static inline auto bBotsFightRealPlayers = true;   // bots shoot you too -- but only visible + within range below

    // How close somebody -- a real player OR another bot -- must be before a bot will lock onto them and shoot.
    // 50 metres = 5000 Unreal units (1 metre = 100) -- back to 50 metres (it was 30, 3000, for a while).
    // Visibility (current line of sight, in front of the bot) is required on top of this for normal aggro.
    // If you shoot a bot from ANY distance, it notices you and will try to return fire (with reduced accuracy)
    // -- unless it is already locked onto somebody else: a bot fights the ONE target it locked onto until
    // that target or the bot dies. Whatever it is fighting, it only ever fires when it can see them.
    static inline auto BotShootRealPlayerRange = 5000.f;

    // When a bot is shot by a real player from beyond BotShootRealPlayerRange, it still engages that
    // player but with this much larger aim error. Halved along with BotAimErrorDegrees below (was 18), so long-range
    // return fire got the same "twice as accurate" as everything else.
    static inline auto BotLongRangeAimErrorDegrees = 9.6f;

    // How long (in ticks @ ~30/s) a bot stays aggroed on the human who shot it, even at long range.
    static inline auto BotShotAggroTicks = 180;  // ~6 seconds

    // ---- How badly the bots aim (within normal range). THIS IS THE ONE TO TUNE. ----
    // Bots used to point exactly at your head every tick, which is why they felt like aimbots. They
    // now aim up to this many degrees off, picked fresh every ~0.4s and held steady in between (so a burst
    // consistently misses instead of jittering back onto you and averaging out to a hit).
    //
    // 40% accuracy (round 4 -- it was 6 degrees, about 20%). A bot closes in to about 14 metres to fight
    // (PreferredRange in BotAI.cpp), where a player is 90 wide = +/-1.84 degrees from the shooter. An aim
    // spread evenly over +/-3.2 degrees lands 1.84 / 3.2 = 57.5% of the time, and BotAimMissChance below
    // throws 30% of those away: 57.5% x 0.7 = 40%. (At 6 degrees it was 1.84 / 6 x 0.7 = 21%.)
    // Each aim held for ~0.4s, by distance (old -> now):
    //    5 m 60% -> 70% | 10 m 30% -> 56% | 14 m 21% -> 40% | 20 m 12% -> 28% | 30 m 5% -> 19% | 50 m 2% -> 7%
    //   Want them even worse?  raise it (6 = the old 20%, 10-12 = very sloppy).
    //   Want them sharper?     lower it (2 = dangerous, 0 = the old aimbot).
    static inline auto BotAimErrorDegrees = 3.2f;

    // Vertical error as a fraction of the above. Kept smaller so they still shoot roughly at body
    // height rather than at the sky or the dirt.
    static inline auto BotAimErrorPitchScale = 0.5f;

    // ---- Fewer hits, on top of the aim error above ----
    // This share of a bot's aims (each one held for ~0.4s, like the error above) is a deliberate clean
    // miss: off to one side by more than half your width at that distance. 0.30 = about 30% fewer hits
    // than the aim error alone gives, at every distance (it applies to long-range return fire too).
    //   More misses: raise it (0.5 = half the hits).   As before: 0.
    static inline auto BotAimMissChance = 0.30f;

    // ---- The one wall a bot puts up when it gets shot ----
    // It goes on the grid line nearest to this far in front of the bot (toward whoever it is fighting),
    // in Unreal units: 512 = one tile = 5 metres. 1024 = two tiles out, where the front wall has always
    // gone (8-13 metres away). 512 = one tile out (3-8 metres). Lower = hugging the bot.
    static inline auto BotWallDistance = 1024.f;

    // No longer used (round 4): a kill only goes to somebody who really damaged the victim -- never to "the nearest
    // player to the body" within this range, which is how you were getting kills for bots you never touched.
    static inline auto ElimCreditRange = 25000.f;

    static inline auto BotShieldMinimum = 25.f;

    static inline auto BotShieldMaximum = 100.f;

    static inline auto GrapplerClipSize = 999;

    static inline auto bGodModeForRealPlayer = false;

    static inline auto bLateGame = false;
    static inline auto LateGameZone = 3;
    static inline auto bLateGameLongZone = false;
    static inline auto bEnableCheats = true;
    static inline auto SiphonAmount = 50;
    static inline auto bInfiniteMats = true;
    static inline auto bInfiniteAmmo = true;
    static inline auto bForceRespawns = false;
    static inline auto bJoinInProgress = false;
    static inline auto bAutoRestart = false;

    static inline auto bKeepInventory = true;
    static inline auto AutoFillTargetPlayerCount = 100;

    // A place to send a crowd of bots to, by the name of the recorded POI file it came from.
    // Empty means no hot drop and everyone spreads out evenly as before.
    static inline auto HotDropPoi = "";

    // How many of them land there.
    static inline auto HotDropBots = 0;

    // How far around the middle of that place they are allowed to come down.
    static inline auto HotDropRadius = 9000.f;
    static inline auto AutoFillBatchSize = 5;
    static inline auto AutoFillIntervalSeconds = 2;
    static inline auto Port = 7777;
    static inline auto bEnableIris = true;

    static inline auto bSpawnBossesAndHenchmen = false;

    static inline auto HenchmenPerPOI = 6;

    static inline auto bForceBossAtEveryPOI = false;

    static inline auto MaxNPCs = 40;

    static inline auto bNPCLog = true;
    static inline constexpr auto bGUI = false;
    static inline constexpr auto bCustomCrashReporter = true;
    static inline constexpr auto bUseStdoutLog = false;
    static inline constexpr auto WebhookURL = "";
};
