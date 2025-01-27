#ifndef GUARD_DUNGEON_AI_ITEMS_H
#define GUARD_DUNGEON_AI_ITEMS_H

#include "dungeon_entity.h"
#include "position.h"

void DecideUseItem(Entity *pokemon);
void FindStraightThrowableTargets(Entity *pokemon, s32 thrownAIFlag, Item *item, bool8 ignoreRollChance);
void FindRockItemTargets(Entity *pokemon, Item *item, Position potentialTargets[], bool8 ignoreRollChance);
void TargetThrownItem(Entity *pokemon, Entity *targetPokemon, Item *item, s32 targetingFlags, bool8 ignoreRollChance);

#endif
