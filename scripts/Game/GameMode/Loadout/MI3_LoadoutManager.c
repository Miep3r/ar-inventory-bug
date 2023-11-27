[EntityEditorProps(category: "GameScripted/GameMode", description: "temp loadout selection.", color: "0 0 255 255")]
class MI3_LoadoutManagerClass : SCR_LoadoutManagerClass
{
}

class MI3_LoadoutManager : SCR_LoadoutManager
{
	
	array<ref MI3_PlayerLoadout> GetPlayerLoadoutsNotIgnored()
	{
		array<ref MI3_PlayerLoadout> loadouts = new array<ref MI3_PlayerLoadout>();
		
		foreach (SCR_BasePlayerLoadout loadout : m_aPlayerLoadouts)
		{
			MI3_PlayerLoadout playerLoadout = MI3_PlayerLoadout.Cast(loadout);
			
			if (playerLoadout)
			{
				if (!playerLoadout.IsIgnored())
					loadouts.Insert(playerLoadout);
			}
		}
		
		return loadouts;
	}
	
	MI3_PlayerLoadout GetLoadoutByClassname(string classname)
	{
		return MI3_PlayerLoadout.GetPlayerLoadout(classname, m_aPlayerLoadouts);
	}
}
