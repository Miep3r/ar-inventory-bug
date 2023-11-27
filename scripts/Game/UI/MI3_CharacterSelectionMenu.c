modded enum ChimeraMenuPreset
{
	MI3_CharacterSelectionMenu
}

class MI3_CharacterSelectionMenu : ChimeraMenuBase
{
	protected Widget m_wRoot;
	protected SCR_InputButtonComponent m_wBackButton;
	protected SCR_InputButtonComponent m_wCreateNew;
	protected MI3_CharacterListBoxComponent m_wCharacterListBox;
	
	private ref array<ref MI3_DatabaseCharacter> m_Characters;
	
	override void OnMenuOpen()
	{
		m_wRoot = GetRootWidget();
		
		m_Characters = new array<ref MI3_DatabaseCharacter>();
		
		m_wBackButton		= SCR_InputButtonComponent.GetInputButtonComponent("BackButton", m_wRoot);
		m_wCreateNew		= SCR_InputButtonComponent.GetInputButtonComponent("CreateNewButton", m_wRoot);
		m_wCharacterListBox = MI3_CharacterListBoxComponent.GetCharacterListBoxComponent("CharacterSelection", m_wRoot);
		
		if (m_wBackButton)
		{
			GetGame().GetWorkspace().SetFocusedWidget(m_wBackButton.GetRootWidget());
			m_wBackButton.m_OnActivated.Insert(OnBackButtonClick);
		}
		
		if (m_wCreateNew)
		{
			m_wCreateNew.m_OnActivated.Insert(OnCreateNewClick);
		}
	}
	
	void AddCharacter(MI3_DatabaseCharacter character)
	{
		if (m_wCharacterListBox)
		{
			m_wCharacterListBox.AddCharacter(character);
			m_Characters.Insert(character);
		}
	}
	
	void OnBackButtonClick()
	{
		SCR_HintManagerComponent.GetInstance().ShowCustomHint("This executes when pressing SendHint Button (Using OnClick)", "MY GUI", 3.0);
		
		MI3_PlayerController controller = MI3_PlayerController.Cast(GetGame().GetPlayerController());
		if (controller)
		{
			
		}
		
		Close();
	}
	
	void OnCreateNewClick()
	{
	}
}
