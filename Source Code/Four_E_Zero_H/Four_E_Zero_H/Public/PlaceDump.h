#pragma once
#include "../../pch.h"

namespace PlaceDump
{
    void RecordTick();

    void Flush();

    void EnsureLoaded();

    int GetNodeCount();
    int GetConnectedNodeCount();

    bool IsUsable();

    bool GetNextWaypoint(void* Identity, const FVector& From, const FVector& To, FVector& OutWaypoint);

    void ForgetBot(void* Identity);

    bool GetRandomNearbyPlace(const FVector& Near, float WithinDistance, FVector& OutPlace);

    int GetSpreadLandingSpots(int Count, FVector* OutSpots);

    // The middle of a recorded "# POI" file, looked up by the name it was saved under.
    bool GetLandmark(const char* Name, FVector& Out);

    // Landing spots taken from the recorded places around a point.
    int GetPlacesNear(const FVector& Near, float WithinDistance, int Count, FVector* OutSpots);

    void ReportOnce();

    void AnnounceHotkey();
}
