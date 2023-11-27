[BaseContainerProps(configRoot: true), BaseContainerCustomTitleField("m_sLoadoutName")]
class MI3_PlayerLoadout : SCR_PlayerLoadout
{
	[Attribute("", UIWidgets.EditBox, params: "edds")]
	private string m_sLoadoutClassname;
	
	[Attribute("", UIWidgets.CheckBox, params: "edds")]
	private bool m_bIgnored;
	
	string GetLoadoutClassname()
	{
		return m_sLoadoutClassname;
	}
	
	bool IsIgnored()
	{
		return m_bIgnored;
	}
	
	static MI3_PlayerLoadout GetPlayerLoadout(string classname, array<ref SCR_BasePlayerLoadout> loadouts)
	{
		foreach (SCR_BasePlayerLoadout loadout : loadouts)
		{
			MI3_PlayerLoadout plrLoadout = MI3_PlayerLoadout.Cast(loadout);
			
			if (plrLoadout)
			{
				if (plrLoadout.GetLoadoutClassname() == classname)
					return plrLoadout;
			}
		}
		
		return null;
	}
}
