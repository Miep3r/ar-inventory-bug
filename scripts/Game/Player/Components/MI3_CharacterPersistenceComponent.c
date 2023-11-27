class MI3_CharacterPersistenceComponentClass : MI3_PlayerControllerComponentClass
{
}

class MI3_CharacterPersistenceComponent : MI3_PlayerControllerComponent
{
	protected ref InventoryUtility m_InventoryUtils;
	protected SCR_RespawnComponent m_RespawnComponent;
	
	private ref Logger m_Logger;
	private ref map<int, ref array<ref MI3_DatabaseCharacter>> m_mPlayerCharacters;
	private int m_CharacterId = -1;
	private bool m_bSpawned;
	private ref MI3_DatabaseCharacter m_ActiveCharacter;
	
	// -------------------------------- Logic -------------------------------- \\
	int GetId()
	{
		return m_CharacterId;
	}
	
	void HandleDatabaseCharacterResponse(array<ref MI3_DbEntity> data)
	{
		array<ref MI3_DatabaseCharacter> result = {};
		
		foreach (MI3_DbEntity ent : data)
		{
			MI3_DatabaseCharacter char = MI3_DatabaseCharacter.Cast(ent);
			
			if (char)
			{
				result.Insert(char);
			}
		}
		
		m_mPlayerCharacters.Set(m_Controller.GetDatabaseId(), result);
		
		m_Controller.OpenCharacterSelection(result);
	}
	
	void FetchCharacters()
	{
		SCR_JsonLoadContext loadContext = new SCR_JsonLoadContext();
		bool loaded = loadContext.LoadFromFile("Data/inv.json");
		
		MI3_InventoryDto inventory;
		if (loaded)
		{
			inventory = new MI3_InventoryDto();
			inventory.SerializationLoad(loadContext);
		}
		
		MI3_DatabaseCharacter char1 = new MI3_DatabaseCharacter();
		char1.SetId(-1);
		char1.SetFirstName("Test");
		char1.SetLastName("Character");
		char1.SetInventory(inventory);
		
		array<ref MI3_DbEntity> characters = {char1};
		
		HandleDatabaseCharacterResponse(characters);
	}
	
	void CreateCharacter(string firstName, string lastName, string classname)
	{
	}
	
	void SaveCharacter()
	{	
		SCR_ChimeraCharacter entity = SCR_ChimeraCharacter.Cast(m_Controller.GetControlledEntity());
		
		if (!entity)
		{
			return;
		}
		
		vector mat[4];
		entity.GetTransform(mat);
		
		MI3_PositionData positionData = new MI3_PositionData();
		positionData.Set(mat[3], entity.GetAngles());
		
		// Get character inventory
		SCR_InventoryStorageManagerComponent storageManager = SCR_InventoryStorageManagerComponent.Cast(entity.FindComponent(SCR_InventoryStorageManagerComponent));
		SCR_CharacterInventoryStorageComponent characterInventory = storageManager.GetCharacterStorage();
		
		m_InventoryUtils = new InventoryUtility(storageManager);
		
		MI3_InventoryDto inventory = m_InventoryUtils.SerializeCharacterInventory();
		SCR_JsonSaveContext saveContext = new SCR_JsonSaveContext();
		
		saveContext.EnableTypeDiscriminator();
		inventory.SerializationSave(saveContext);
		saveContext.SaveToFile("Data/inv.json");
	}
	
	void OnPlayerSpawn(SCR_SpawnRequestComponent requestComponent, IEntity entity)
	{
		m_Logger.Log("Spawn event caught for player '" + requestComponent.GetPlayerId() + "'!");
		
		if (m_bSpawned)
		{
			return;
		}
		
		m_bSpawned = true;
		
		if (m_ActiveCharacter)
		{
			//GetGame().GetCallqueue().CallLater(SpawnInventory, 200, false, entity);
			SpawnInventory(entity);
		}
	}
	
	void SpawnInventory(IEntity entity)
	{
		// Load character inventory
		SCR_InventoryStorageManagerComponent storageManager = SCR_InventoryStorageManagerComponent.Cast(entity.FindComponent(SCR_InventoryStorageManagerComponent));
		
		m_InventoryUtils = new InventoryUtility(storageManager);
		if (m_InventoryUtils)
		{
			m_InventoryUtils.LoadInventoryForCharacter(m_ActiveCharacter.GetInventory());
		}
	}
	
	// -------------------------------- RPC -------------------------------- \\
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	protected void RpcAsk_LoadCharacterForPlayer(int playerId, int characterId)
	{
		MI3_PlayerController controller = MI3_PlayerController.Cast(GetGame().GetPlayerManager().GetPlayerController(playerId));
		
		m_Logger.Log("Loading character '" + characterId + "' for player '" + playerId + "'");
		
		array<ref MI3_DatabaseCharacter> playerCharacters = m_mPlayerCharacters.Get(controller.GetDatabaseId());
		MI3_DatabaseCharacter selectedCharacter;
		
		foreach (MI3_DatabaseCharacter character : playerCharacters)
		{
			if (character.GetId() == characterId)
			{
				selectedCharacter = character;
				break;
			}
		}
		
		// Spawn logic
		MI3_LoadoutManager loadoutManager = MI3_LoadoutManager.Cast(GetGame().GetLoadoutManager());
		
		MI3_GameMode gameMode = MI3_GameMode.Cast(GetGame().GetGameMode());
		if (gameMode)
		{
			m_ActiveCharacter = selectedCharacter;
			m_CharacterId = selectedCharacter.GetId();
			
			MI3_PlayerLoadout loadout = loadoutManager.GetLoadoutByClassname(selectedCharacter.GetClassname());
			
			SCR_PlayerLoadoutComponent loadoutComponent = SCR_PlayerLoadoutComponent.Cast(m_Controller.FindComponent(SCR_PlayerLoadoutComponent));
			
			MI3_PositionData positionData = selectedCharacter.GetPositionData();
			
			SCR_SpawnData spawnData;
			if (positionData)
			{
				spawnData = new SCR_FreeSpawnData(loadout.GetLoadoutResource(), positionData.GetPosition(), positionData.GetRotation());
			}
			else
			{
				SCR_SpawnPoint spawnPoint = SCR_SpawnPoint.GetRandomSpawnPointForFaction("PLR");
				spawnData = new SCR_SpawnPointSpawnData(loadout.GetLoadoutResource(), spawnPoint.GetRplId());
			}
			
			m_RespawnComponent = SCR_RespawnComponent.Cast(GetGame().GetPlayerManager().GetPlayerRespawnComponent(m_Controller.GetPlayerId()));
			if (m_RespawnComponent)
			{
				loadoutComponent.RequestLoadout(loadout);
				m_RespawnComponent.RequestSpawn(spawnData);
			}
		}
	}
	
	void LoadCharacter_C(int characterId)
	{
		Rpc(RpcAsk_LoadCharacterForPlayer, m_Controller.GetPlayerId(), characterId);
	}
	
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	protected void RpcAsk_CreateCharacter(string firstName, string lastName, string classname)
	{
		CreateCharacter(firstName, lastName, classname);
	}
	
	void CreateCharacter_C(string firstName, string lastName, string classname)
	{
		Rpc(RpcAsk_CreateCharacter, firstName, lastName, classname);
	}
	
	// -------------------------------- CTOR -------------------------------- \\
	void MI3_CharacterPersistenceComponent(IEntityComponentSource src, IEntity ent, IEntity parent)
	{
		m_Logger = LoggerFactory.GetForClass(MI3_CharacterPersistenceComponent);
		m_mPlayerCharacters = new map<int, ref array<ref MI3_DatabaseCharacter>>();
		
		m_Logger.Log("Initialized!");
	}
}
