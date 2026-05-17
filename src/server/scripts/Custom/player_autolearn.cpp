#include "ScriptMgr.h"
#include "Player.h"
#include "SpellMgr.h"
#include "DBCStores.h"

class AutoLearnPlayerScript : public PlayerScript
{
public:
    AutoLearnPlayerScript() : PlayerScript("AutoLearnPlayerScript") {}

    // Completely self-contained helper using the core's native DBC array name 'SpellRank'
    bool IsTalentSpell(uint32 spellId)
    {
        for (uint32 i = 0; i < sTalentStore.GetNumRows(); ++i)
        {
            if (TalentEntry const* talent = sTalentStore.LookupEntry(i))
            {
                for (int rank = 0; rank < 5; ++rank)
                {
                    if (talent->SpellRank[rank] == spellId)
                        return true;
                }
            }
        }
        return false;
    }

    void OnLevelChanged(Player* player, uint8 /*oldLevel*/) override
    {
        uint8 level = player->GetLevel();

        // 1. Hardcoded riding unlocks based on level milestones
        if (level >= 20) player->LearnSpell(33388, false); // Apprentice Riding
        if (level >= 40) player->LearnSpell(33391, false); // Journeyman Riding
        if (level >= 60) player->LearnSpell(34090, false); // Expert Riding
        if (level >= 70) player->LearnSpell(34091, false); // Artisan Riding
        if (level >= 77) player->LearnSpell(54197, false); // Cold Weather Flying

        // 2. Loop through global game data to automatically grant class spells
        for (uint32 i = 0; i < sSkillLineAbilityStore.GetNumRows(); ++i)
        {
            SkillLineAbilityEntry const* entry = sSkillLineAbilityStore.LookupEntry(i);
            if (!entry)
                continue;

            // Ensure the spell belongs to the player's specific class bitmask
            if (!(entry->ClassMask & player->GetClassMask()))
                continue;

            // Verify race compliance (Prevents learning other races' traits/racials)
            if (entry->RaceMask && !(entry->RaceMask & player->GetRaceMask()))
                continue;

            // Protect talent calculations by skipping any spell found in the talent trees
            if (IsTalentSpell(entry->Spell))
                continue;

            // Verify the spell is registered in the core's spell manager
            SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(entry->Spell);
            if (!spellInfo)
                continue;

            // Skip if the spell requirement is higher than current level
            if (spellInfo->SpellLevel > level)
                continue;

            // Grant the spell if the character doesn't already have it
            if (!player->HasSpell(entry->Spell))
            {
                player->LearnSpell(entry->Spell, false);
            }
        }
    }
};

void AddSC_AutoLearnPlayerScript()
{
    new AutoLearnPlayerScript();
}
