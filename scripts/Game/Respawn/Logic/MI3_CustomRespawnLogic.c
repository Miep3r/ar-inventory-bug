[BaseContainerProps(category: "Respawn")]
class MI3_CustomRespawnLogic : SCR_SpawnLogic
{
	[Attribute("", uiwidget: UIWidgets.EditBox, category: "Respawn", desc: "Default faction for players to spawn with.")]
	protected FactionKey m_sFaction;
	
	protected Faction m_Faction;
	protected ref Logger m_Logger;
	protected ref set<int> m_DisconnectingPlayers = new set<int>();
	
	//------------------------------------------------------------------------------------------------
	override void OnPlayerRegistered_S(int playerId)
	{
		super.OnPlayerRegistered_S(playerId);
		
		// In cases where we pushed provided player into disconnecting ones, but never resolved it,
		// ensure that this player is no longer marked as disconnecting
		int indexOf = m_DisconnectingPlayers.Find(playerId);
		if (indexOf != -1)
		{
			m_DisconnectingPlayers.Remove(indexOf);
		}
	}
	
	//------------------------------------------------------------------------------------------------
	override void OnPlayerEntityLost_S(int playerId)
	{
		super.OnPlayerEntityLost_S(playerId);
		Spawn(playerId);
	}

	//------------------------------------------------------------------------------------------------
	override void OnPlayerSpawnFailed_S(int playerId)
	{
		super.OnPlayerSpawnFailed_S(playerId);
		
		m_Logger.Error("Spawning player '" + playerId + "' failed!");
	}
	
	//------------------------------------------------------------------------------------------------
	override void OnInit(SCR_RespawnSystemComponent owner)
	{
		super.OnInit(owner);
		
		m_Faction = GetGame().GetFactionManager().GetFactionByKey(m_sFaction);
		m_Logger = LoggerFactory.GetForClass(MI3_CustomRespawnLogic);
	}

	//------------------------------------------------------------------------------------------------
	override void OnPlayerDisconnected_S(int playerId, KickCauseCode cause, int timeout)
	{
		super.OnPlayerDisconnected_S(playerId, cause, timeout);
		m_DisconnectingPlayers.Insert(playerId);
	}
	
	//------------------------------------------------------------------------------------------------
	protected void Spawn(int playerId)
	{
		// Player is disconnecting (and disappearance of controlled entity started this feedback loop).
		// Simply ignore such requests as it would create unwanted entities.
		int indexOf = m_DisconnectingPlayers.Find(playerId);
		if (indexOf != -1)
		{
			m_DisconnectingPlayers.Remove(indexOf);
			return;
		}
		
		SCR_SpawnPoint point = SCR_SpawnPoint.GetRandomSpawnPointForFaction(m_Faction.GetFactionKey());
		if (!point)
		{
			m_Logger.Log("Missing spawnpoint!");
			OnPlayerSpawnFailed_S(playerId);
			return;
		}
		
		SCR_PlayerLoadoutComponent loadoutComponent = GetPlayerLoadoutComponent_S(playerId);
		SCR_BasePlayerLoadout loadout = loadoutComponent.GetLoadout();
		if (!loadout)
		{
			m_Logger.Log("Missing loadout!");
			OnPlayerSpawnFailed_S(playerId);
			return;
		}
		
		SCR_SpawnPointSpawnData data = new SCR_SpawnPointSpawnData(loadout.GetLoadoutResource(), point.GetRplId());
		if (GetPlayerRespawnComponent_S(playerId).CanSpawn(data))
			DoSpawn(playerId, data);
		else
			OnPlayerSpawnFailed_S(playerId);
	}
	
	protected void DoSpawn(int playerId, SCR_SpawnData data)
	{
		if (!GetPlayerRespawnComponent_S(playerId).RequestSpawn(data))
		{
			// Try again later
		}
	}
}
