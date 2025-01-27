#ifndef GUARD_TEXT_H
#define GUARD_TEXT_H

// size: 0x48
typedef struct UnkTextStruct1
{
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    u32 unkC;
    u32 unk10;
    u32 unk14;
    u32 *unk18;
    u32 *unk1C;
    s32 unk20;
    s32 unk24;
    u32 *unk28; // Somewhere in VRAM
    s32 unk2C;
    u32 *unk30; // Somewhere in VRAM?
    u32 *unk34;
    s32 unk38;
    u32 *unk3C;
    u32 *unk40;
    u8 unk44;
    bool8 unk45;
    u8 unk46;
} UnkTextStruct1;

// size: 0x4
typedef struct UnkTextStruct2_sub
{
    // I haven't found a func that reads these separately yet, but simply making an arr[2] will cause assignments to break.
    // Some funcs only match with this union for some reason even though they don't access the variables separately...
    // The first func to break is currently sub_801A5D8 in kecleon_bros4.c
    // The first func I matched that uses the array is sub_8006554 in text2.c (using the separated fields doesn't match or get even close)
    union {
        struct {
        s16 unk0;
        s16 unk2;
        } separate;
        s16 arr[2];
    } unk0;
} UnkTextStruct2_sub;

// size: 0x18
typedef struct UnkTextStruct2
{
    u8 unk0;
    u8 fill1[0x4 - 0x1];
    s32 unk4;
    UnkTextStruct2_sub unk8;
    s16 unkC;
    s16 unkE;
    s16 unk10;
    s16 unk12;
    const u8 *unk14;
} UnkTextStruct2;

#endif // GUARD_TEXT_H