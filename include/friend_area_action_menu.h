#ifndef GUARD_FRIEND_AREA_ACTION_MENU_H
#define GUARD_FRIEND_AREA_ACTION_MENU_H

#include "menu.h"
struct unkStruct_203B2BC
{
    // size: 0x1E0
    u32 state;
    u32 fallbackState;
    s16 targetPoke;
    u16 unkA;
    u32 id;
    BulkItem itemToGive;
    BulkItem item2;
    PokemonStruct1 *pokeStruct;
    bool8 isTeamLeader;
    u32 moveIndex;  // some sort of move index
    u16 moveID;
    Move moves[8];
    u16 moveIDs[MAX_MON_MOVES];   // some list of move IDs
    u32 menuAction1;
    u32 menuAction2;
    u32 menuAction3;
    MenuStruct unk7C;
    u8 fill80[0xFD - 0xCC];
    u32 unkFD;
    u8 fill101[0x11C - 0x104];
    MenuItem menuItems[4];
    u8 fill120[0x16C - 0x13C];
    u16 unk16C[10];
    UnkTextStruct2 unk180[4];
};

enum FriendAreaActionMenuStates {
    FRIEND_AREA_ACTION_MENU_INIT,
    FRIEND_AREA_ACTION_MENU_MAIN,
    FRIEND_AREA_ACTION_MENU_MAIN_2,
    FRIEND_AREA_ACTION_MENU_SUMMARY = 4,
    FRIEND_AREA_ACTION_MENU_CHECK_IQ = 5,
    FRIEND_AREA_ACTION_MENU_SAY_FAREWELL_PROMPT = 8,
    FRIEND_AREA_ACTION_MENU_SAY_FAREWELL_CONFIRM,
    FRIEND_AREA_ACTION_MENU_EXIT = 0x11,
};

enum FriendAreaActionMenuActions {
    FRIEND_AREA_ACTION_MENU_ACTION_NONE = 1,
    FRIEND_AREA_ACTION_MENU_ACTION_YES,
    FRIEND_AREA_ACTION_MENU_ACTION_NO,
    FRIEND_AREA_ACTION_MENU_ACTION_INFO = 4,
    FRIEND_AREA_ACTION_MENU_ACTION_SUMMARY = 4,
    FRIEND_AREA_ACTION_MENU_ACTION_CHECK_IQ,
    FRIEND_AREA_ACTION_MENU_ACTION_JOIN_TEAM,
    FRIEND_AREA_ACTION_MENU_ACTION_STANDBY,
    FRIEND_AREA_ACTION_MENU_ACTION_MAKE_LEADER,
    FRIEND_AREA_ACTION_MENU_ACTION_SAY_FAREWELL,
    FRIEND_AREA_ACTION_MENU_ACTION_GIVE,
    FRIEND_AREA_ACTION_MENU_ACTION_TAKE,
    FRIEND_AREA_ACTION_MENU_ACTION_MOVES,
};

#endif
