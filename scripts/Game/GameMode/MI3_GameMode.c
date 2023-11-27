#define MI3_DEBUG
#define MI3_DEBUG_AUDIT

class MI3_GameModeClass : SCR_BaseGameModeClass
{
}

class MI3_GameMode : SCR_BaseGameMode
{
	private static MI3_GameMode m_Instance;
	
	private ref Logger m_Logger;
	
	// Authority Code
	// Called when client is fully authenticated
	void LoadPlayerData(int playerId)
	{
		m_Logger.Log("==== CLIENT INIT START ====");
		
		MI3_PlayerController controller = MI3_PlayerController.Cast(GetGame().GetPlayerManager().GetPlayerController(playerId));
		
		string name = GetGame().GetPlayerManager().GetPlayerName(playerId);
		
		m_Logger.Log("Player audit success: " + name);
		
		MI3_CharacterPersistenceComponent characterPersistenceComponent = controller.GetCharacterPersistenceComponent();
		characterPersistenceComponent.FetchCharacters();
	}
	
	void HandlePlayerAuditSuccess(int playerId)
	{
		#ifndef MI3_DEBUG_AUDIT
		LoadPlayerData(playerId);
		#endif
	}
	
	void HandlePlayerConnected(int playerId)
	{
		string name = GetGame().GetPlayerManager().GetPlayerName(playerId);
		m_Logger.Log("Player connected: " + name);
		
		#ifdef MI3_DEBUG_AUDIT
		LoadPlayerData(playerId);
		#endif
	}
	
	void HandlePlayerDisconnected(int playerId, KickCauseCode cause, int timeout)
	{
		m_Logger.Log("Player disconnected: " + playerId);
		
		MI3_PlayerController controller = MI3_PlayerController.Cast(GetGame().GetPlayerManager().GetPlayerController(playerId));
		
		MI3_CharacterPersistenceComponent characterPersistenceComponent = controller.GetCharacterPersistenceComponent();
		characterPersistenceComponent.SaveCharacter();
	}
	
	// -------------------------------- Events -------------------------------- \\
	override void EOnInit(IEntity owner)
	{
		super.EOnInit(owner);
		
		if (IsMaster())
		{
			// Authority code
			m_Logger.Log("Performing authority initialization...");
			
			m_OnPlayerConnected.Insert(HandlePlayerConnected);
			m_OnPlayerDisconnected.Insert(HandlePlayerDisconnected);
			m_OnPlayerAuditSuccess.Insert(HandlePlayerAuditSuccess);
			
			m_Logger.Log("Authority initialized!");
		}
	}
	
	override void OnPlayerSpawnFinalize_S(SCR_SpawnRequestComponent requestComponent, SCR_SpawnHandlerComponent handlerComponent, SCR_SpawnData data, IEntity entity)
	{
		super.OnPlayerSpawnFinalize_S(requestComponent, handlerComponent, data, entity);
		
		MI3_PlayerController controller = MI3_PlayerController.Cast(requestComponent.GetPlayerController());
		controller.GetCharacterPersistenceComponent().OnPlayerSpawn(requestComponent, entity);
		
		m_Logger.Log("Player spawned: " + requestComponent.GetPlayerId());
	}
	
	override void OnGameModeStart()
	{
		super.OnGameModeStart();
		
		m_Logger.Log("Started!");
	}
	
	override void OnGameEnd()
	{
		super.OnGameEnd();
		
		m_Logger.Log("Ending...");
		
		PlayerManager playerManager = GetGame().GetPlayerManager();
		
		array<int> players = new array<int>();
		playerManager.GetPlayers(players);
		
		foreach (int playerId : players)
		{
			MI3_PlayerController controller = MI3_PlayerController.Cast(playerManager.GetPlayerController(playerId));
			
			MI3_CharacterPersistenceComponent characterPersistenceComponent = controller.GetCharacterPersistenceComponent();
			characterPersistenceComponent.SaveCharacter();
		}
		
		m_Logger.Log("Ended!");
	}
	
	// -------------------------------- CTOR -------------------------------- \\
	void MI3_GameMode(IEntitySource src, IEntity parent)
	{
		m_Instance = this;
		m_Logger = LoggerFactory.GetForClass(MI3_GameMode);
		m_Logger.Log("Constructed!");
	}
	
	void ~MI3_GameMode()
	{
		m_Logger.Log("Deconstructed!");
	}
	
	// -------------------------------- Static -------------------------------- \\
	static MI3_GameMode Get()
	{
		return m_Instance;
	}
}
