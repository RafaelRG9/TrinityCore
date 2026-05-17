#include "DBCStores.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "SpellMgr.h"

class AutoLearnPlayerScript : public PlayerScript {
public:
  AutoLearnPlayerScript() : PlayerScript("AutoLearnPlayerScript") {}

  void OnLevelChanged(Player *player, uint8 /*oldLevel*/) override {
    uint8 level = player->GetLevel();

    // 1. Hardcoded riding unlocks based on level milestones
    if (level >= 20)
      player->LearnSpell(33388, false); // Apprentice Riding
    if (level >= 40)
      player->LearnSpell(33391, false); // Journeyman Riding
    if (level >= 60)
      player->LearnSpell(34090, false); // Expert Riding
    if (level >= 70)
      player->LearnSpell(34091, false); // Artisan Riding
    if (level >= 77)
      player->LearnSpell(54197, false); // Cold Weather Flying

    // 2. Loop through global game data to automatically grant class spells
    for (uint32 i = 0; i < sSkillLineAbilityStore.GetNumRows(); ++i) {
      SkillLineAbilityEntry const *entry =
          sSkillLineAbilityStore.LookupEntry(i);
      if (!entry)
        continue;

      // Ensure the spell belongs to the player's specific class bitmask
      if (!(entry->ClassMask & player->GetClassMask()))
        continue;

      // Verify the spell is registered in the core's spell manager
      SpellInfo const *spellInfo = sSpellMgr->GetSpellInfo(entry->Spell);
      if (!spellInfo)
        continue;

      // Fetch the level requirement for this spell from game data
     if (spellInfo->SpellLevel > level)
         continue;

      // Grant the spell if the character doesn't already have it
      if (!player->HasSpell(entry->Spell)) {
        player->LearnSpell(entry->Spell, false);
      }
    }
  }
};

void AddSC_AutoLearnPlayerScript() { new AutoLearnPlayerScript(); }
