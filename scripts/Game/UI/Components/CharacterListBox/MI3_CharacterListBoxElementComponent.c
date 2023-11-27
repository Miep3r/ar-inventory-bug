class MI3_CharacterListBoxElementComponent : SCR_ModularButtonComponent
{
	protected PanelWidget m_wBorder;
	protected SCR_InputButtonComponent m_wPlayButton;
	protected RichTextWidget m_wCharacterName;
	
	private ref MI3_DatabaseCharacter m_Character;
	
	override void HandlerAttached(Widget w)
	{
		super.HandlerAttached(w);
		
		m_wBorder = PanelWidget.Cast(w.FindAnyWidget("Border"));
		m_wPlayButton = SCR_InputButtonComponent.GetInputButtonComponent("PlayButton", w);
		m_wCharacterName = RichTextWidget.Cast(w.FindAnyWidget("CharacterName"));
		
		if (m_wBorder)
			m_wBorder.SetVisible(false);
		
		if (m_wPlayButton)
		{
			m_wPlayButton.SetVisible(false);
			m_wPlayButton.m_OnActivated.Insert(OnActivated);
		}
	}
	
	void OnActivated()
	{
		MI3_LoadoutManager loadoutManager = MI3_LoadoutManager.Cast(GetGame().GetLoadoutManager());
		
		MI3_PlayerLoadout loadout = loadoutManager.GetLoadoutByClassname(m_Character.GetClassname());
		
		MI3_PlayerController controller = MI3_PlayerController.Cast(GetGame().GetPlayerController());
		
		SCR_SpawnPoint point = SCR_SpawnPoint.GetRandomSpawnPointForFaction("PLR");
		
		vector pos;
		vector rot;
		point.GetPositionAndRotation(pos, rot);
		
		controller.GetCharacterPersistenceComponent().LoadCharacter_C(m_Character.GetId());
		GetGame().GetMenuManager().CloseMenuByPreset(ChimeraMenuPreset.MI3_CharacterSelectionMenu);
	}
	
	void SetCharacterName(string name)
	{
		if (m_wCharacterName)
			m_wCharacterName.SetText(name);
	}
	
	void SetCharacter(MI3_DatabaseCharacter character)
	{
		m_Character = character;
	}
	
	void SetSelected(bool state)
	{
		if (m_wBorder)
			m_wBorder.SetVisible(state);
		
		if (m_wPlayButton)
			m_wPlayButton.SetVisible(state);
	}
	
	override bool OnFocus(Widget w, int x, int y)
	{
		SetSelected(true);
		
		return super.OnFocus(w, x, y);
	}
	
	override bool OnFocusLost(Widget w, int x, int y)
	{
		SetSelected(false);
		
		return super.OnFocusLost(w, x, y);
	}
	
	override bool OnMouseEnter(Widget w, int x, int y)
	{
		SetSelected(true);
		
		return super.OnMouseEnter(w, x, y);
	}
	
	override bool OnMouseLeave(Widget w, Widget enterW, int x, int y)
	{
		SetSelected(false);
		
		return super.OnMouseLeave(w, enterW, x, y);
	}
}
