#include "global.h"
#include "code_80118A4.h"
#include "code_8012A18_1.h"
#include "code_80130A8.h"
#include "code_80130A8.h"
#include "code_801B3C0.h"
#include "code_8097670.h"
#include "code_8098BDC.h"
#include "constants/bg_music.h"
#include "constants/colors.h"
#include "constants/evolution_status.h"
#include "input.h"
#include "kecleon_bros4.h"
#include "luminous_cave.h"
#include "memory.h"
#include "menu_input.h"
#include "pokemon.h"
#include "random.h"
#include "text_util.h"
#include "text1.h"
#include "text2.h"

extern u8 gAvailablePokemonNames[]; // 202DF98
extern u8 gPlayerName[]; // 202E2B8

EWRAM_DATA_2 struct unkStruct_203B2B0 *gUnknown_203B2B0 = {0};

// data_80D47B8.s
extern const u8 *gUnknown_80D4934[];
extern const u8 *gUnknown_80D4970[];
extern const UnkTextStruct2 gUnknown_80DC9E8;
extern const UnkTextStruct2 gUnknown_80DCA00;
extern const u8 gUnknown_80DCA18[];
extern const u8 gUnknown_80DCA24[];
extern const u8 gUnknown_80DCA2C[];

#include "data/luminous_cave.h"

// code_8098BDC.s
extern void nullsub_104(void);

static void LuminousCave_AdvancetoFallbackState(void);
static bool8 LuminousCave_HasOnly1Member(void);
static void UpdateLuminousCaveDialogue(void);
static void UpdateLuminousCaveState(u32);

static void sub_8024804(void);
static void sub_8024CFC(void);
static void sub_8024D48(void);
static void sub_8024DBC(void);
static void sub_8024E30(void);
static void sub_8024E9C(void);
static void sub_8024F00(void);
static void sub_8024F70(void);
static void sub_8024FD4(void);
static void sub_8025058(void);
static void sub_80250EC(void);
static void sub_802515C(void);
static void sub_80251CC(void);
static void sub_80251E8(void);
static void sub_8025204(void);
static void sub_8025254(void);

enum
{
    LUMINOUS_CAVE_ENTRY,
    LUMINOUS_CAVE_ASK_EVOLVE,
    LUMINOUS_CAVE_EVOLVE_INFO,
    LUMINOUS_CAVE_SHALL_RETURN,
    LUMINOUS_CAVE_GIVE_ITEM_1 = 5,
    LUMINOUS_CAVE_GIVE_ITEM_2 = 10,
    LUMINOUS_CAVE_LACK_WHAT_NEEDED = 0xF,
    LUMINOUS_CAVE_ONLY_ONE_ITEM = 0x10,
    LUMINOUS_CAVE_LET_US_BEGIN = 0x11,
    LUMINOUS_CAVE_CHANGED_APPEARANCE = 0x12,
    LUMINOUS_CAVE_EVOLVED = 0x13,
    LUMINOUS_CAVE_PROMPT_NAME = 0x14,
    LUMINOUS_CAVE_FINISH_NAME = 0x15,
    LUMINOUS_CAVE_COME_ALONE = 0x16,
    LUMINOUS_CAVE_LACK_LEVEL = 0x17,
    LUMINOUS_CAVE_CANT_EVOLVE_ANYMORE = 0x18,
    LUMINOUS_CAVE_LACK_FRIEND_AREA = 0x19,
    LUMINOUS_CAVE_LACK_ROOM = 0x1A,
    LUMINOUS_CAVE_LACK_IQ = 0x1B,
    LUMINOUS_CAVE_LACK_ITEM = 0x1C,
    LUMINOUS_CAVE_CANT_EVOLVE_YET = 0x1D,
};

u32 sub_802465C(void)
{
    OpenedFile *faceFile;

    ResetUnusedInputStruct();
    sub_800641C(NULL, TRUE, TRUE);
    gUnknown_203B2B0 = MemoryAlloc(sizeof(struct unkStruct_203B2B0), 8);
    gUnknown_203B2B0->menuAction1 = 0;
    gUnknown_203B2B0->menuAction2 = 0;
    gUnknown_203B2B0->menuAction3 = 0;
    gUnknown_203B2B0->pokeStruct = GetPlayerPokemonStruct();
    gUnknown_203B2B0->pokeRenamed = IsPokemonRenamed(gUnknown_203B2B0->pokeStruct);
    gUnknown_203B2B0->evolutionComplete = FALSE;
    faceFile = GetDialogueSpriteDataPtr(MONSTER_GULPIN);
    gUnknown_203B2B0->unk104 = faceFile;
    gUnknown_203B2B0->unk108 = faceFile->data;
    gUnknown_203B2B0->unk110 = 0;
    gUnknown_203B2B0->unk111 = 0;
    gUnknown_203B2B0->unk112 = 0;
    gUnknown_203B2B0->unk10C = 2;
    gUnknown_203B2B0->unk10E = 8;
    UpdateLuminousCaveState(LUMINOUS_CAVE_ENTRY);
    return TRUE;
}

u32 sub_80246F0(void)
{
    switch (gUnknown_203B2B0->state) {
        case LUMINOUS_CAVE_ENTRY:
        case LUMINOUS_CAVE_ASK_EVOLVE:
            sub_8024E9C();
            break;
        case LUMINOUS_CAVE_GIVE_ITEM_1:
            sub_8024F00();
            break;
        case 6:
        case 7:
            sub_8024FD4();
            break;
        case 8:
            sub_80250EC();
            break;
        case 9:
            sub_80251CC();
            break;
        case LUMINOUS_CAVE_GIVE_ITEM_2:
            sub_8024F70();
            break;
        case 11:
        case 12:
            sub_8025058();
            break;
        case 13:
            sub_802515C();
            break;
        case 14:
            sub_80251E8();
            break;
        case LUMINOUS_CAVE_FINISH_NAME:
            sub_8025204();
            break;
        case 4:
            return 3;
        default:
            LuminousCave_AdvancetoFallbackState();
            break;
    }
    return 0;
}

bool8 HasEvolutionCompleted(void)
{
    return gUnknown_203B2B0->evolutionComplete;
}

void CleanLuminousCave(void)
{
    if (gUnknown_203B2B0 != NULL) {
        CloseFile(gUnknown_203B2B0->unk104);
        MemoryFree(gUnknown_203B2B0);
        gUnknown_203B2B0 = NULL;
    }
}

static void UpdateLuminousCaveState(u32 newState)
{
    gUnknown_203B2B0->state = newState;
    sub_8024804();
    UpdateLuminousCaveDialogue();
}

static void sub_8024804(void)
{
    s32 i;

    sub_8006518(gUnknown_203B2B0->unk114);

    switch (gUnknown_203B2B0->state) {
        case 8:
        case 13:
            gUnknown_203B2B0->unk114[2] = gUnknown_80DCA00;
            break;
        case LUMINOUS_CAVE_LET_US_BEGIN:
        case LUMINOUS_CAVE_CHANGED_APPEARANCE:
        case LUMINOUS_CAVE_EVOLVED:
        case LUMINOUS_CAVE_COME_ALONE:
        case LUMINOUS_CAVE_LACK_LEVEL:
        case LUMINOUS_CAVE_CANT_EVOLVE_ANYMORE:
        case LUMINOUS_CAVE_LACK_FRIEND_AREA:
        case LUMINOUS_CAVE_LACK_ROOM:
        case LUMINOUS_CAVE_LACK_IQ:
        case LUMINOUS_CAVE_LACK_ITEM:
            break;
        default:
            for (i = 0; i < 4; i++)
                gUnknown_203B2B0->unk114[i] = gUnknown_80DC9E8;
            break;
    }

    ResetUnusedInputStruct();
    sub_800641C(gUnknown_203B2B0->unk114, TRUE, TRUE);
}

static void UpdateLuminousCaveDialogue(void)
{
    u8 *monName;

    switch (gUnknown_203B2B0->state) {
        case LUMINOUS_CAVE_ENTRY:
            if (LuminousCave_HasOnly1Member())
                gUnknown_203B2B0->menuAction1 = 3;
            else
                gUnknown_203B2B0->menuAction1 = 1;

            sub_8024CFC();
            sub_8014248(sLuminousCaveSeekAwakening,0,gUnknown_203B2B0->menuAction1,gUnknown_203B2B0->unk34,gUnknown_203B2B0->unk74,4,0,0,5);
            break;
        case LUMINOUS_CAVE_ASK_EVOLVE:
            sub_8024CFC();
            sub_8014248(sLuminousCaveAskEvolution,0,gUnknown_203B2B0->menuAction1,gUnknown_203B2B0->unk34,gUnknown_203B2B0->unk74,4,0,0,5);
            break;
        case LUMINOUS_CAVE_EVOLVE_INFO:
            gUnknown_203B2B0->fallbackState = LUMINOUS_CAVE_ASK_EVOLVE;
            sub_80141B4(sLuminousCaveEvolutionInfo,0,0,0x105);
            break;
        case LUMINOUS_CAVE_SHALL_RETURN:
            gUnknown_203B2B0->fallbackState = 4;
            xxx_call_fade_in_new_bgm(MUS_FILE_SELECT,0x3c);
            sub_80141B4(sLuminousCaveYeShallReturn,0,0,0x305);
            break;
        case LUMINOUS_CAVE_GIVE_ITEM_1:
            sub_8024D48();
            sub_8014248(sLuminousCaveGiveItem,0,gUnknown_203B2B0->menuAction2,gUnknown_203B2B0->unk34,gUnknown_203B2B0->unk74,4,0,0,5);
            break;
        case 6:
            sub_801A5D8(2,3,NULL,10);
            break;
        case 7:
            sub_801A8D0(TRUE);
            break;
        case LUMINOUS_CAVE_GIVE_ITEM_2:
            sub_8024DBC();
            sub_8014248(sLuminousCaveGiveAnotherItem,0,gUnknown_203B2B0->menuAction2,gUnknown_203B2B0->unk34,gUnknown_203B2B0->unk74,4,0,0,5);
            break;
        case 11:
            sub_801A5D8(2,3,NULL,10);
            sub_801AEE4(gUnknown_203B2B0->evoItem1_InvIndex,1);
            sub_801A9E0();
            break;
        case 12:
            sub_801A8D0(TRUE);
            sub_801AEE4(gUnknown_203B2B0->evoItem1_InvIndex,1);
            sub_801A9E0();
            break;
        case 8:
        case 13:
            sub_801A9E0();
            sub_8024E30();
            sub_8012D60(&gUnknown_203B2B0->unk84,gUnknown_203B2B0->unk34,0,gUnknown_203B2B0->unk74,
                        gUnknown_203B2B0->menuAction3,2);
            break;
        case 9:
        case 14:
            sub_801B3C0(&gUnknown_203B2B0->chosenItem);
            break;
        case LUMINOUS_CAVE_LACK_WHAT_NEEDED:
            gUnknown_203B2B0->fallbackState = LUMINOUS_CAVE_GIVE_ITEM_1;
            sub_80141B4(sLuminousCaveLackWhatIsNeeded,0,0,0x105);
            break;
        case LUMINOUS_CAVE_ONLY_ONE_ITEM:
            gUnknown_203B2B0->fallbackState = LUMINOUS_CAVE_GIVE_ITEM_2;
            sub_80141B4(sLuminousCaveOnlyOneItem,0,0,0x105);
            break;
        case LUMINOUS_CAVE_LET_US_BEGIN:
            sub_8025254();

            if((gUnknown_203B2B0->evolveStatus.evolutionConditionStatus & EVOLUTION_GOOD))
                gUnknown_203B2B0->fallbackState = LUMINOUS_CAVE_CHANGED_APPEARANCE;
            else if(gUnknown_203B2B0->evolveStatus.evolutionConditionStatus == EVOLUTION_NO_MORE)
                gUnknown_203B2B0->fallbackState = LUMINOUS_CAVE_CANT_EVOLVE_ANYMORE;
            else if(gUnknown_203B2B0->evolveStatus.evolutionConditionStatus == EVOLUTION_LACK_LEVEL)
                gUnknown_203B2B0->fallbackState = LUMINOUS_CAVE_LACK_LEVEL;
            else if(gUnknown_203B2B0->evolveStatus.evolutionConditionStatus == EVOLUTION_LACK_IQ)
                gUnknown_203B2B0->fallbackState = LUMINOUS_CAVE_LACK_IQ;
            else if(gUnknown_203B2B0->evolveStatus.evolutionConditionStatus == EVOLUTION_LACK_FRIEND_AREA)
                gUnknown_203B2B0->fallbackState = LUMINOUS_CAVE_LACK_FRIEND_AREA;
            else if(gUnknown_203B2B0->evolveStatus.evolutionConditionStatus == EVOLUTION_LACK_ROOM)
                gUnknown_203B2B0->fallbackState = LUMINOUS_CAVE_LACK_ROOM;
            else if(gUnknown_203B2B0->evolveStatus.evolutionConditionStatus == EVOLUTION_LACK_ITEM)
                gUnknown_203B2B0->fallbackState = LUMINOUS_CAVE_LACK_ITEM;
            else
                gUnknown_203B2B0->fallbackState = LUMINOUS_CAVE_CANT_EVOLVE_YET;
            xxx_call_fade_out_bgm(0x3c);
            sub_80141B4(sLuminousCaveLetUsBegin,0,0,0x105);
            break;
        case LUMINOUS_CAVE_CHANGED_APPEARANCE:
            PrintColoredPokeNameToBuffer(gPlayerName,gUnknown_203B2B0->pokeStruct, COLOR_CYAN);
            PlaySound(0x1ff);
            gUnknown_203B2B0->fallbackState = LUMINOUS_CAVE_EVOLVED;
            sub_80141B4(sLuminousCaveChangedAppearance,0,0,0x105);
            break;
        case LUMINOUS_CAVE_EVOLVED:
            monName = GetMonSpecies(gUnknown_203B2B0->pokeStruct->speciesNum);
            strcpy(gAvailablePokemonNames,monName);
            monName = GetMonSpecies(gUnknown_203B2B0->evolveStatus.targetEvolveSpecies);
            strcpy(gAvailablePokemonNames + 0x50,monName);
            gUnknown_203B2B0->evolutionComplete = TRUE;
            sub_80977D0();
            sub_808F734(gUnknown_203B2B0->pokeStruct,gUnknown_203B2B0->evolveStatus.targetEvolveSpecies);
            nullsub_104();
            gUnknown_203B2B0->pokeStruct = GetPlayerPokemonStruct();
            if (gUnknown_203B2B0->evoItem1_InvIndex != INVENTORY_SIZE) {
                ClearItemSlotAt(gUnknown_203B2B0->evoItem1_InvIndex);
            }
            if (gUnknown_203B2B0->evoItem2_InvIndex != INVENTORY_SIZE) {
                ClearItemSlotAt(gUnknown_203B2B0->evoItem2_InvIndex);
            }
            FillInventoryGaps();
            xxx_call_stop_fanfare_se(0x1ff);
            PlaySound(0xd2);
            if (gUnknown_203B2B0->pokeRenamed) {
                    BoundedCopyStringtoBuffer(gUnknown_203B2B0->pokeStruct->name,GetMonSpecies(gUnknown_203B2B0->pokeStruct->speciesNum),POKEMON_NAME_LENGTH);
            }
            gUnknown_203B2B0->fallbackState = LUMINOUS_CAVE_SHALL_RETURN;
            sub_80141B4(sLuminousCaveEvolved,0,0,0x105);
            break;
        case LUMINOUS_CAVE_COME_ALONE:
            gUnknown_203B2B0->fallbackState = LUMINOUS_CAVE_SHALL_RETURN;
            sub_80141B4(sLuminousCaveComeAlone,0,0,0x105);
            break;
        case LUMINOUS_CAVE_LACK_LEVEL:
            gUnknown_203B2B0->fallbackState = LUMINOUS_CAVE_SHALL_RETURN;
            sub_80141B4(sLuminousCaveLackLevel,0,0,0x105);
            break;
        case LUMINOUS_CAVE_CANT_EVOLVE_ANYMORE:
            gUnknown_203B2B0->fallbackState = LUMINOUS_CAVE_SHALL_RETURN;
            sub_80141B4(sLuminousCaveCantEvolveAnymore,0,0,0x105);
            break;
        case LUMINOUS_CAVE_LACK_FRIEND_AREA:
            gUnknown_203B2B0->fallbackState = LUMINOUS_CAVE_SHALL_RETURN;
            sub_80141B4(sLuminousCaveLackFriendArea,0,0,0x105);
            break;
        case LUMINOUS_CAVE_LACK_ROOM:
            gUnknown_203B2B0->fallbackState = LUMINOUS_CAVE_SHALL_RETURN;
            sub_80141B4(sLuminousCaveLackRoom,0,0,0x105);
            break;
        case LUMINOUS_CAVE_LACK_IQ:
            gUnknown_203B2B0->fallbackState = LUMINOUS_CAVE_SHALL_RETURN;
            sub_80141B4(sLuminousCaveLackIQ,0,0,0x105);
            break;
        case LUMINOUS_CAVE_LACK_ITEM:
            gUnknown_203B2B0->fallbackState = LUMINOUS_CAVE_SHALL_RETURN;
            sub_80141B4(sLuminousCaveLackItem,0,0,0x105);
            break;
        case LUMINOUS_CAVE_CANT_EVOLVE_YET:
            gUnknown_203B2B0->fallbackState = LUMINOUS_CAVE_SHALL_RETURN;
            sub_80141B4(sLuminousCaveCantEvolveYet,0,0,0x105);
            break;
        case LUMINOUS_CAVE_PROMPT_NAME:
            xxx_call_fade_in_new_bgm(8,0x3c);
            gUnknown_203B2B0->fallbackState = LUMINOUS_CAVE_FINISH_NAME;
            sub_80141B4(sLuminousCaveGiveName,0,0,0x105);
            break;
        case LUMINOUS_CAVE_FINISH_NAME:
            if (gUnknown_203B2B0->pokeRenamed) {
                    BoundedCopyStringtoBuffer(gUnknown_203B2B0->pokeStruct->name,GetMonSpecies(gUnknown_203B2B0->pokeStruct->speciesNum),POKEMON_NAME_LENGTH);
            }
            sub_801602C(0,gUnknown_203B2B0->pokeStruct->name);
            break;
        default:
            break;
    }
}

static void sub_8024CFC(void)
{
    s32 loopMax = 0;

    MemoryFill16(gUnknown_203B2B0->unk74, 0, sizeof(gUnknown_203B2B0->unk74));

    gUnknown_203B2B0->unk34[loopMax].text = gUnknown_80DCA18;
    gUnknown_203B2B0->unk34[loopMax].menuAction = 3;

    loopMax += 1;
    gUnknown_203B2B0->unk34[loopMax].text = *gUnknown_80D4970;
    gUnknown_203B2B0->unk34[loopMax].menuAction = 2;

    loopMax += 1;
    gUnknown_203B2B0->unk34[loopMax].text = *gUnknown_80D4934;
    gUnknown_203B2B0->unk34[loopMax].menuAction = 1;

    loopMax += 1;
    gUnknown_203B2B0->unk34[loopMax].text = NULL;
    gUnknown_203B2B0->unk34[loopMax].menuAction = 1;
}

static void sub_8024D48(void)
{
    s32 index;
    s32 loopMax;

    loopMax = 0;
    MemoryFill16(gUnknown_203B2B0->unk74, 0, sizeof(gUnknown_203B2B0->unk74));
    gUnknown_203B2B0->unk34[loopMax].text = gUnknown_80DCA24;
    gUnknown_203B2B0->unk34[loopMax].menuAction = 4;
    loopMax += 1;
    gUnknown_203B2B0->unk34[loopMax].text = gUnknown_80DCA2C;
    gUnknown_203B2B0->unk34[loopMax].menuAction = 5;
    loopMax += 1;
    gUnknown_203B2B0->unk34[loopMax].text = *gUnknown_80D4934;
    gUnknown_203B2B0->unk34[loopMax].menuAction = 1;
    loopMax += 1;
    gUnknown_203B2B0->unk34[loopMax].text = NULL;
    gUnknown_203B2B0->unk34[loopMax].menuAction = 1;

    for (index = 0; index < loopMax; index++) {
        if (gUnknown_203B2B0->unk74[index] == 0) {
            if (gUnknown_203B2B0->unk34[index].menuAction == gUnknown_203B2B0->menuAction2)
                return;
        }
    }

    gUnknown_203B2B0->menuAction2 = 4;
}

static void sub_8024DBC(void)
{
    s32 index;
    s32 loopMax;

    loopMax = 0;
    MemoryFill16(gUnknown_203B2B0->unk74, 0, sizeof(gUnknown_203B2B0->unk74));
    gUnknown_203B2B0->unk34[loopMax].text = gUnknown_80DCA24;
    gUnknown_203B2B0->unk34[loopMax].menuAction = 4;
    loopMax += 1;
    gUnknown_203B2B0->unk34[loopMax].text = gUnknown_80DCA2C;
    gUnknown_203B2B0->unk34[loopMax].menuAction = 5;
    loopMax += 1;
    gUnknown_203B2B0->unk34[loopMax].text = *gUnknown_80D4934;
    gUnknown_203B2B0->unk34[loopMax].menuAction = 1;
    loopMax += 1;
    gUnknown_203B2B0->unk34[loopMax].text = NULL;
    gUnknown_203B2B0->unk34[loopMax].menuAction = 1;

    for(index = 0; index < loopMax; index++)
    {
        if(gUnknown_203B2B0->unk74[index] == 0)
        {
            if(gUnknown_203B2B0->unk34[index].menuAction == gUnknown_203B2B0->menuAction2)
                return;
        }
    }

    gUnknown_203B2B0->menuAction2 = 4;
}

static void sub_8024E30(void)
{
    s32 index;
    s32 loopMax;

    loopMax = 0;
    MemoryFill16(gUnknown_203B2B0->unk74, 0, sizeof(gUnknown_203B2B0->unk74));
    gUnknown_203B2B0->unk34[loopMax].text = gUnknown_80DCA2C;
    gUnknown_203B2B0->unk34[loopMax].menuAction = 5;
    loopMax += 1;
    gUnknown_203B2B0->unk34[loopMax].text = *gUnknown_80D4970;
    gUnknown_203B2B0->unk34[loopMax].menuAction = 2;
    loopMax += 1;
    gUnknown_203B2B0->unk34[loopMax].text = NULL;
    gUnknown_203B2B0->unk34[loopMax].menuAction = 1;

    for(index = 0; index < loopMax; index++)
    {
        if(gUnknown_203B2B0->unk74[index] == 0)
        {
            if(gUnknown_203B2B0->unk34[index].menuAction == gUnknown_203B2B0->menuAction3)
                return;
        }
    }

    gUnknown_203B2B0->menuAction3 = 5;
}

static void sub_8024E9C(void)
{
    s32 menuAction;
    if(sub_80144A4(&menuAction) == 0)
    {
        if(menuAction != 1) gUnknown_203B2B0->menuAction1 = menuAction;
        switch(menuAction)
        {
            case 3:
                if(LuminousCave_HasOnly1Member())
                    UpdateLuminousCaveState(LUMINOUS_CAVE_GIVE_ITEM_1);
                else
                    UpdateLuminousCaveState(LUMINOUS_CAVE_COME_ALONE);
                break;
            case 2:
                UpdateLuminousCaveState(LUMINOUS_CAVE_EVOLVE_INFO);
                break;
            case 1:
                UpdateLuminousCaveState(LUMINOUS_CAVE_SHALL_RETURN);
                break;
        }
    }
}

static void sub_8024F00(void)
{
    s32 menuAction;
    if(sub_80144A4(&menuAction) == 0)
    {
        if(menuAction != 1) gUnknown_203B2B0->menuAction2 = menuAction;
        switch(menuAction)
        {
            case 4:
                gUnknown_203B2B0->evoItem1_InvIndex = INVENTORY_SIZE;
                gUnknown_203B2B0->evoItem2_InvIndex = INVENTORY_SIZE;
                UpdateLuminousCaveState(LUMINOUS_CAVE_LET_US_BEGIN);
                break;
            case 5:
                if(GetNumberOfFilledInventorySlots() == 0)
                    UpdateLuminousCaveState(LUMINOUS_CAVE_LACK_WHAT_NEEDED);
                else
                    UpdateLuminousCaveState(0x6);
                break;
            case 1:
                UpdateLuminousCaveState(LUMINOUS_CAVE_ASK_EVOLVE);
                break;
        }
    }
}

static void sub_8024F70(void)
{
    s32 menuAction;
    if(sub_80144A4(&menuAction) == 0)
    {
        if(menuAction != 1) gUnknown_203B2B0->menuAction2 = menuAction;
        switch(menuAction)
        {
            case 4:
                UpdateLuminousCaveState(LUMINOUS_CAVE_LET_US_BEGIN);
                break;
            case 5:
                if(GetNumberOfFilledInventorySlots() < 2)
                    UpdateLuminousCaveState(LUMINOUS_CAVE_ONLY_ONE_ITEM);
                else
                    UpdateLuminousCaveState(0xB);
                break;
            case 1:
                UpdateLuminousCaveState(LUMINOUS_CAVE_ASK_EVOLVE);
                break;
        }
    }
}

static void sub_8024FD4(void)
{
    switch(sub_801A6E8(TRUE))
    {
        case 3:
            gUnknown_203B2B0->evoItem1_InvIndex = sub_801A8AC();
            gUnknown_203B2B0->evoItem2_InvIndex = INVENTORY_SIZE;
            gUnknown_203B2B0->chosenItem = gTeamInventoryRef->teamItems[gUnknown_203B2B0->evoItem1_InvIndex];
            UpdateLuminousCaveState(8);
            break;
        case 4:
            gUnknown_203B2B0->chosenItem = gTeamInventoryRef->teamItems[sub_801A8AC()];
            sub_8099690(0);
            UpdateLuminousCaveState(9);
            break;
        case 2:
            sub_801A928();
            UpdateLuminousCaveState(LUMINOUS_CAVE_GIVE_ITEM_1);
            break;
    }
}

static void sub_8025058(void)
{
    switch(sub_801A6E8(TRUE))
    {
        case 3:
            if(gUnknown_203B2B0->evoItem1_InvIndex != sub_801A8AC())
            {
                gUnknown_203B2B0->evoItem2_InvIndex = sub_801A8AC();
                gUnknown_203B2B0->chosenItem = gTeamInventoryRef->teamItems[gUnknown_203B2B0->evoItem2_InvIndex];
                UpdateLuminousCaveState(0xD);
            }
            else
                PlayMenuSoundEffect(2);
            break;
        case 4:
            gUnknown_203B2B0->chosenItem = gTeamInventoryRef->teamItems[sub_801A8AC()];
            sub_8099690(0);
            UpdateLuminousCaveState(0xE);
            break;
        case 2:
            sub_801A928();
            UpdateLuminousCaveState(0xA);
            break;
    }
}

static void sub_80250EC(void)
{
    s32 menuAction;
    menuAction = 0;
    sub_801A6E8(FALSE);

    if(!sub_8012FD8(&gUnknown_203B2B0->unk84))
    {
        sub_8013114(&gUnknown_203B2B0->unk84, &menuAction);
        if(menuAction != 1) gUnknown_203B2B0->menuAction3 = menuAction;
    }
    switch(menuAction)
    {
        case 5:
            sub_801A928();
            UpdateLuminousCaveState(0xA);
            break;
        case 2:
            sub_8099690(0);
            UpdateLuminousCaveState(0x9);
            break;
        case 1:
            UpdateLuminousCaveState(0x7);
            break;
    }
}

static void sub_802515C(void)
{
    s32 menuAction;
    menuAction = 0;
    sub_801A6E8(FALSE);

    if(!sub_8012FD8(&gUnknown_203B2B0->unk84))
    {
        sub_8013114(&gUnknown_203B2B0->unk84, &menuAction);
        if(menuAction != 1) gUnknown_203B2B0->menuAction3 = menuAction;
    }
    switch(menuAction)
    {
        case 5:
            sub_801A928();
            UpdateLuminousCaveState(LUMINOUS_CAVE_LET_US_BEGIN);
            break;
        case 2:
            sub_8099690(0);
            UpdateLuminousCaveState(0xE);
            break;
        case 1:
            UpdateLuminousCaveState(0xC);
            break;
    }
}

static void sub_80251CC(void)
{
    switch(sub_801B410())
    {
        case 2:
        case 3:
            sub_801B450();
            UpdateLuminousCaveState(0x7);
            break;
        case 0:
        case 1:
            break;
    }
}

static void sub_80251E8(void)
{
    switch(sub_801B410())
    {
        case 2:
        case 3:
            sub_801B450();
            UpdateLuminousCaveState(0xC);
            break;
        case 0:
        case 1:
            break;
    }
}

static void sub_8025204(void)
{
    switch(sub_8016080())
    {
        case 3:
            sub_80160D8();
            gUnknown_203B2B0->pokeRenamed = IsPokemonRenamed(gUnknown_203B2B0->pokeStruct);
            UpdateLuminousCaveState(LUMINOUS_CAVE_SHALL_RETURN);
            break;
        default:
            break;
    }
}

static void LuminousCave_AdvancetoFallbackState(void)
{
    s32 temp;
    if(sub_80144A4(&temp) == 0)
    {
        UpdateLuminousCaveState(gUnknown_203B2B0->fallbackState);
    }
}

static void sub_8025254(void)
{
    if(gUnknown_203B2B0->evoItem1_InvIndex == INVENTORY_SIZE)
        gUnknown_203B2B0->evolveStatus.evoItem1 = 0;
    else
    {
        gUnknown_203B2B0->evolveStatus.evoItem1 = gTeamInventoryRef->teamItems[gUnknown_203B2B0->evoItem1_InvIndex].id;
    }
    if(gUnknown_203B2B0->evoItem2_InvIndex == INVENTORY_SIZE)
        gUnknown_203B2B0->evolveStatus.evoItem2 = 0;
    else
    {
        gUnknown_203B2B0->evolveStatus.evoItem2 = gTeamInventoryRef->teamItems[gUnknown_203B2B0->evoItem2_InvIndex].id;
    }

    gUnknown_203B2B0->evolveStatus.unk6 = RandInt(0xFF);
    sub_808F468(gUnknown_203B2B0->pokeStruct, &gUnknown_203B2B0->evolveStatus, 1);
}

static bool8 LuminousCave_HasOnly1Member(void)
{
    s32 memberCount;
    s32 index;
    PokemonStruct1 *preload;

    preload = &gRecruitedPokemonRef->pokemon[0];
    memberCount = 0;
    for(index = 0; index < NUM_MONSTERS; index++, preload++)
    {
        if((preload->unk0 >> 1) & 1)
            memberCount++;
    }

    if(memberCount == 1)
        return TRUE;
    else
        return FALSE;
}