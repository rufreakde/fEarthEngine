# fEarthEngine (flat Earth Engine)


## The Engine's Mission

fEarthEngine is a specialized, open-source `2D Real-Time Strategy (RTS)` game engine built on the high-performance Vulkan API. From a gamer for gamers.
![FratEarthEngine Icon](img/flatEarthEngine.png)

## Core Philosophy: RTS Specialization

The goal is to remove the common technical hurdles faced when developing 2D RTS games ala 'Warcraft' and 'Warwind'. The project is a `hobby project` and will take `ages to finish` I only work on it when I have time and "fun" with it. Feel free to contribute! I am a novice myself.

## Key Features

- ☒ c++ engine with golang bindings
- ☒ Cross Platform Vulkan-Powered 2D Rendering
- ☐ Focus on 2D RTS: The engine provides a foundation already tailored for top-down classic 2D RTS games.
- ☐ Multi-Window Support: Built-in support for multiple render targets, allowing developers to easily set up external displays for elements like minimaps, unit status panels, or spectator views on a secondary screen. Or even local 2 mouse multiplayer (not planned to be  supported though for now)

## Roadmap & Planned Features

The following features are prioritized to make fEarthEngine a comprehensive solution for 2D RTS development:
- ☐ Pixel Style Focus: Guaranteeing pixel-accurate scaling and rendering necessary for classic 2D RTS aesthetics.
- ☐ Camera Movement
  - ☐ Mouse
  - ☐ Keyboard
- ☐ Unit Selection
  - ☐ Box Selection
  - ☐ Click Selection
- ☐ Unit Selection Indicators
  - ☐ Square / Circle / Partly / Oval
  - ☐ filled / outlined
- ☐ Path finding
  - ☐ ground
  - ☐ water
  - ☐ air
- ☐ Fog of War
- ☐ Healthbars
  - ☐ Chunk / Normal / Light when Damaged
- ☐ Animation by Default:
  - ☐ Units
    - ☐ Idle
    - ☐ Walk
    - ☐ Attack
    - ☐ Damaged
    - ☐ Dead
  - ☐ Buildings
    - ☐ Idle
    - ☐ Damaged
    - ☐ Dead
- ☐ Default layer System
  - ☐ -2-under, -1-under, 0-ground, 1-floor ,2-floor, 3-flying

## Editor & Developer Tools

- ☐ Integrated Engine Editor: A graphical user interface to manage assets, scenes, and game logic.

- ☐ Entity Wizard System: Providing guided, specialized wizards within the editor to simplify the creation and configuration of key RTS entities:

- ☐ For each "important" entity a dedicated wizard will be available in the engine editor:
  - ☐ units
  - ☐ buildings
  - ☐ resources
  - ☐ abilities
  - ☐ technologies

## Multiplayer and Networking

- ☐ P2P Multiplayer Networking: Implementation of a robust peer-to-peer (P2P) networking solution
- ☐ out of the box "in sync" RTS matches

# 💝 Special thanks to:
-  [blurrypiano](https://github.com/blurrypiano) for his great tutorual and starting point [Project](https://github.com/blurrypiano/littleVulkanEngine)