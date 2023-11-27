class MI3_PlayerControllerClass : SCR_PlayerControllerClass
{
}

class MI3_PlayerController : SCR_PlayerController
{
	private MI3_CharacterPersistenceComponent m_CharacterPersistenceComponent;
	
	protected int m_iDatabaseId = -1;
	
	// -------------------------------- Logic -------------------------------- \\
	void SetDatabaseId(int id)
	{
		m_iDatabaseId = id;
	}
	
	int GetDatabaseId()
	{
		return m_iDatabaseId;
	}
	
	MI3_CharacterPersistenceComponent GetCharacterPersistenceComponent()
	{
		return m_CharacterPersistenceComponent;
	}
	
	// -------------------------------- Events -------------------------------- \\
	override void EOnInit(IEntity owner)
	{
		super.EOnInit(owner);
		
		m_CharacterPersistenceComponent	= MI3_CharacterPersistenceComponent.Cast(owner.FindComponent(MI3_CharacterPersistenceComponent));
	}
	
	// -------------------------------- RPC -------------------------------- \\
	// Remote procedure call for opening the character selection with given characters
	[RplRpc(RplChannel.Reliable, RplRcver.Owner)]
	protected void RpcDo_OpenCharacterSelectionMenu(string data)
	{
		GetGame().GetMenuManager().CloseAllMenus();
		
		SCR_JsonLoadContext loadContext = new SCR_JsonLoadContext();
		loadContext.ImportFromString(data);
		
		array<ref MI3_DatabaseCharacter> characters;
		loadContext.ReadValue("d", characters);
		
		if (!characters)
			return;
		
		MenuBase menu = GetGame().GetMenuManager().OpenMenu(ChimeraMenuPreset.MI3_CharacterSelectionMenu);
		
		MI3_CharacterSelectionMenu characterMenu = MI3_CharacterSelectionMenu.Cast(menu);
		if (characterMenu)
		{
			foreach (MI3_DatabaseCharacter character : characters)
			{
				characterMenu.AddCharacter(character);
			}
		}
	}
	
	void OpenCharacterSelection(array<ref MI3_DatabaseCharacter> entries)
	{
		SCR_JsonSaveContext saveContext = new SCR_JsonSaveContext();
		
		saveContext.WriteValue("d", entries);
		
		Rpc(RpcDo_OpenCharacterSelectionMenu, saveContext.ExportToString());
	}
	
	// -------------------------------- CTOR -------------------------------- \\
	void MI3_PlayerController(IEntitySource src, IEntity parent)
	{
	}
	
	void ~MI3_PlayerController()
	{
	}
}
