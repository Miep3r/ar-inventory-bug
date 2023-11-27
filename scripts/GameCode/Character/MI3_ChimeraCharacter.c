modded class SCR_ChimeraCharacter
{
	protected SCR_InventoryStorageManagerComponent m_InventoryStorageManager;
	
	protected bool m_bHasSelectedCharacter = false;
	protected int m_iDatabaseId = -1;
	
	protected string m_sFirstName;
	protected string m_sLastName;
	
	void SetDatabaseId(int id)
	{
		m_iDatabaseId = id;
	}
	
	int GetDatabaseId(int id)
	{
		return m_iDatabaseId;
	}
	
	void SetFirstName(string firstName)
	{
		m_sFirstName = firstName;
	}
	
	void SetLastName(string lastName)
	{
		m_sLastName = lastName;
	}
	
	override void EOnInit(IEntity owner)
	{
		super.EOnInit(owner);
	}
	
	// Remote procedure call for requesting proper character
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	protected void RpcAsk_SetNewCharacter(int playerId, int loadoutIndex)
	{
		if (m_bHasSelectedCharacter)
			return;
		
		m_bHasSelectedCharacter = true;
		
		array<ref SCR_BasePlayerLoadout> loadouts = GetGame().GetLoadoutManager().GetPlayerLoadouts();
		
		PlayerController playerController = GetGame().GetPlayerManager().GetPlayerController(playerId);
		SCR_PlayerLoadoutComponent loadoutComponent = SCR_PlayerLoadoutComponent.Cast(playerController.FindComponent(SCR_PlayerLoadoutComponent));
		
		if (loadoutComponent)
		{
			loadoutComponent.RequestLoadout(loadouts.Get(loadoutIndex));
		}
	}
}
