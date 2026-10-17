# Project Retailification (WotLK 3.3.5a Engine Conversion)

> A systems-level architectural overhaul of the TrinityCore 3.3.5a game server engine, re-engineering a monolithic MMO into an autonomous, offline squad-based action RPG. Forked from [TrinityCore](https://github.com/TrinityCore/TrinityCore).

## Project Overview
This repository serves as a practical software engineering lab demonstrating concurrent systems programming in C++, relational database design in MariaDB, and game engine modernization. The goal is to eliminate legacy friction while maintaining authentic encounter dynamics through autonomous AI companions rather than artificial stat-scaling.

## Key Engineered Systems
- **Automated Living Economy:** Integrated asynchronous market simulation (AHBot) maintaining active listings across factions to validate crafting and economic progression.
- **Dynamic Spell & Riding Progression:** Implemented `AutoLearnPlayerScript` hooking `OnLevelChanged` to grant class skills automatically, utilizing bitmask checks for race preservation and dynamic talent-store scanning to prevent tree corruption.
- **Modern Resource Pacing (In Progress):** Re-engineering combat mana regeneration in `StatSystem.cpp` to emulate retail pacing (+500% for Tanks/DPS, vanilla scaling for Healers).
- **Squad AI Framework (Upcoming):** Integrating `mod-playerbots` using a Trigger-Action-Strategy (TAS) architecture for proactive tank peeling and automated dungeon group population.

## Technology Stack
- **Languages:** C++20, SQL
- **Build System:** CMake, MSVC (Visual Studio 2022)
- **Database:** MariaDB
- **Target Expansion Baseline:** Wrath of the Lich King (Branch 3.3.5)