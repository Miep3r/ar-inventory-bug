# Reforger Inventory Bug



## Reproducing the bug

1. Open project
2. Load worlds/TestWorld.ent
3. Run world using Dedicated Server Tool (max 1 peer)
4. Select the Testing Character and hit "Play"
5. Check inventory for locally duped items

## Check temporary fix implementation

1. Define "MI3_INVENTORY_LATENCY" using scrDefine or in script definition
2. Restart Dedicated Server & Peer

## Implementation

Most of the implementation of the inventory loading / saving is done inside the scripts/Game/Utility/InventoryUtility.c file.
