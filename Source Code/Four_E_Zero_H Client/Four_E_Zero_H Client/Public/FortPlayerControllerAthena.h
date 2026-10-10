#pragma once
#include "../../pch.h"
#include "FortCheatManager.h"

class ABuildingPlayerPrimitivePreview : public AActor
{
public:
    UCLASS_COMMON_MEMBERS(ABuildingPlayerPrimitivePreview);

    // F7 turbo building: a preview the game has hidden is not a spot it would build on.
    DEFINE_BITFIELD_PROP(bHidden);
};

class AFortPlayerControllerAthena : public AActor
{
public:
    UCLASS_COMMON_MEMBERS(AFortPlayerControllerAthena);

    DEFINE_BITFIELD_PROP(bBuildFree);
    DEFINE_BITFIELD_PROP(bInfiniteAmmo);
    DEFINE_PROP(CheatManager, UFortCheatManager*);
    DEFINE_PROP(CheatClass, TSubclassOf<UObject>);
    DEFINE_PROP(TargetedBuilding, AActor*);

    // F7 turbo building (1.8.2): the build preview the player sees, the piece they have selected, and whether it is mirrored.
    DEFINE_PROP(BuildPreviewMarker, ABuildingPlayerPrimitivePreview*);
    DEFINE_BITFIELD_PROP(bBuildPreviewMirrored);
};
