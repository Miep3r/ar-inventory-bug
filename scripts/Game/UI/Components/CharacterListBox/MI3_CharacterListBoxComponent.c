class MI3_CharacterListBoxComponent : SCR_ScriptedWidgetComponent
{
	[Attribute("{320CAF26226BE1D9}UI/layouts/WidgetLibrary/CharacterListBox/CharacterListBoxElement.layout", UIWidgets.ResourceNamePicker, "List box element", "layout")]
	protected ResourceName m_sElementLayout;
	
	protected VerticalLayoutWidget m_wList;
	
	protected ref array<MI3_CharacterListBoxElementComponent> m_aElementComponents;
	
	void AddCharacter(MI3_DatabaseCharacter character)
	{	
		Widget widget = GetGame().GetWorkspace().CreateWidgets(m_sElementLayout, m_wList);
		
		MI3_CharacterListBoxElementComponent handler = MI3_CharacterListBoxElementComponent.Cast(widget.FindHandler(MI3_CharacterListBoxElementComponent));
		handler.SetCharacterName(character.GetFirstName() + " " + character.GetLastName());
		handler.SetCharacter(character);
		
		m_aElementComponents.Insert(handler);
	}
	
	override void HandlerAttached(Widget w)
	{
		super.HandlerAttached(w);
		
		m_wList = VerticalLayoutWidget.Cast(w.FindAnyWidget("List"));
	}
	
	void MI3_CharacterListBoxComponent()
	{
		m_aElementComponents = new array<MI3_CharacterListBoxElementComponent>();
	}
	
	static MI3_CharacterListBoxComponent GetCharacterListBoxComponent(string name, Widget parent, bool searchAllChildren = true)
	{
		auto comp = MI3_CharacterListBoxComponent.Cast(
				SCR_WLibComponentBase.GetComponent(MI3_CharacterListBoxComponent, name, parent, searchAllChildren)
			);
		return comp;
	}
}
