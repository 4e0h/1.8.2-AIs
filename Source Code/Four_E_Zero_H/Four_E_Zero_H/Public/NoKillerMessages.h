#pragma once
#include <string>

// ---- what a death with nobody to credit says (round 4, a fifth line in round 5) -----------------------------------
//
// A player who dies with no real killer -- the storm, the hole under the chapter 1 map, anything with no damage from
// another player on record -- gives the elimination to nobody, and the line for it is one of these five.
//
// Both the gameserver (its log) and the 1.8.2 client DLL (its killfeed) pick the line from this header, from the player's
// name as the game stores it, so the line in the server's log is always the line on the player's screen.
namespace NoKillerMessages
{
    static const int Count = 5;

    // FNV-1a over the name's UTF-16 code units, up to the first terminator. The same on both sides because both hash the
    // name exactly as the game replicates it (APlayerState::PlayerName on 1.8.2).
    inline int PickFor(const wchar_t* Name, int MaxLength = 512)
    {
        unsigned int Hash = 2166136261u;

        if (Name)
        {
            for (int i = 0; i < MaxLength && Name[i] != L'\0'; i++)
            {
                Hash ^= (unsigned int)(unsigned short)Name[i];
                Hash *= 16777619u;
            }
        }

        return (int)(Hash % (unsigned int)Count);
    }

    inline std::wstring Line(int Which, const std::wstring& Name)
    {
        switch (((Which % Count) + Count) % Count)
        {
        case 0:
            return Name + L" had an oopsie";
        case 1:
            return Name + L" took the L";
        case 2:
            return Name + L" took the easy way out";
        case 3:
            return L"looks like we lost " + Name;
        default:
            return Name + L" paid the 500 dollars";
        }
    }

    // The killfeed's own lines mark the dead player's name with the <Victim> style (the red name), e.g.
    // "<Victim>KindKangaroo</> didn't stick the landing" -- the same name in the same style here.
    inline std::wstring LineForKillFeed(int Which, const std::wstring& Name)
    {
        return Line(Which, L"<Victim>" + Name + L"</>");
    }

    inline std::string LineUtf8(int Which, const std::string& Name)
    {
        switch (((Which % Count) + Count) % Count)
        {
        case 0:
            return Name + " had an oopsie";
        case 1:
            return Name + " took the L";
        case 2:
            return Name + " took the easy way out";
        case 3:
            return "looks like we lost " + Name;
        default:
            return Name + " paid the 500 dollars";
        }
    }
}
