# Phase 1: Foundation (Config & SQL)

This document contains the required configuration changes for your `worldserver.conf` and the necessary SQL to finalize the Phase 1 setup.

## 1. Config Changes (`worldserver.conf`)

Add or modify the following lines in your `worldserver.conf`. 
*(Note: If your server uses a module for AutoLearn, these settings will apply. If you're using AzerothCore or a custom TrinityCore branch, these are the exact names needed.)*

```ini
###################################################################################################
# PHASE 1: CORE TWEAKS
###################################################################################################

# Enable auto-learning of spells on level up
AutoLearnSpells = 1

# Set the cost of unlearning talents to 0 (Free Respecs)
Rate.TalentRespec = 0

###################################################################################################
# PHASE 1: AUCTION HOUSE BOT SETTINGS (ACTIVE MARKET)
###################################################################################################

# Enable the Seller Bot (Generates items for players to buy)
AuctionHouseBot.Bind.No = 1
AuctionHouseBot.Bind.Equip = 1
AuctionHouseBot.Bind.Use = 1

# Boost the AH heavily on server restart
AuctionHouseBot.ItemsPerCycle.Boost = 2000
# Keep the market active with a high normal generation cycle
AuctionHouseBot.ItemsPerCycle.Normal = 50

# Amount of items to maintain on the Auction House by quality
AuctionHouseBot.Items.Amount.Gray = 0
AuctionHouseBot.Items.Amount.White = 500
AuctionHouseBot.Items.Amount.Green = 3000
AuctionHouseBot.Items.Amount.Blue = 1500
AuctionHouseBot.Items.Amount.Purple = 500
AuctionHouseBot.Items.Amount.Orange = 0
AuctionHouseBot.Items.Amount.Yellow = 0

# Enable the Buyer Bot (Buys items listed by players to inject gold into the economy)
AuctionHouseBot.Buyer.Enabled = 1
AuctionHouseBot.Buyer.Alliance.Enabled = 1
AuctionHouseBot.Buyer.Horde.Enabled = 1
AuctionHouseBot.Buyer.Neutral.Enabled = 1

# Make the buyer bot aggressive at checking and buying
AuctionHouseBot.Buyer.ChanceFactor = 3
AuctionHouseBot.Buyer.Recheck.Interval = 5
```

## 2. SQL Changes

Depending on your AHBot module, you may need an Auction House Bot character in your `characters` database to act as the owner of the bot auctions, or you may need to insert base configuration into the `world` database if your module is database-driven.

If your core requires an AHBot character (commonly GUID 32000 or similar), run this on your **characters** database:

```sql
-- Creates a dummy character for the AH Bot to use as the auctioneer
INSERT IGNORE INTO `characters` (`guid`, `account`, `name`, `race`, `class`, `gender`, `level`, `xp`, `money`, `playerBytes`, `playerBytes2`, `playerFlags`, `position_x`, `position_y`, `position_z`, `map`, `orientation`, `taximask`, `online`, `cinematic`, `totaltime`, `leveltime`, `logout_time`, `is_logout_resting`, `rest_bonus`, `resettalents_cost`, `resettalents_time`, `trans_x`, `trans_y`, `trans_z`, `trans_o`, `transguid`, `extra_flags`, `stable_slots`, `at_login`, `zone`, `death_expire_time`, `taxi_path`, `arenaPoints`, `totalHonorPoints`, `todayHonorPoints`, `yesterdayHonorPoints`, `totalKills`, `todayKills`, `yesterdayKills`, `chosenTitle`, `knownCurrencies`, `watchedFaction`, `drunk`, `health`, `power1`, `power2`, `power3`, `power4`, `power5`, `power6`, `power7`, `latency`, `talentGroupsCount`, `activeTalentGroup`, `exploredZones`, `equipmentCache`, `ammoId`, `knownTitles`, `actionBars`, `grantableLevels`, `creation_date`, `deleteInfos_Account`, `deleteInfos_Name`, `deleteDate`) VALUES
(32000, 1, 'AHBot', 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, '', '', 0, '', 0, 0, NOW(), NULL, NULL, NULL);
```

For the **world** database (Optional if you want to ensure the bot can post anything):
```sql
-- Clean up any strict item requirements or AHBot restrictors if present
DELETE FROM `item_template` WHERE `itemlevel` = 0 AND `class` IN (2, 4); 
```
*(Only apply world database changes if your specific repack/module documents it. The config changes are usually sufficient for standard modules).*
