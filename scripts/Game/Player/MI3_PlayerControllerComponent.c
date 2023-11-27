class MI3_PlayerControllerComponentClass : ScriptComponentClass
{
}

class MI3_PlayerControllerComponent : ScriptComponent
{
	protected MI3_PlayerController m_Controller;
	
	void MI3_PlayerControllerComponent(IEntityComponentSource src, IEntity ent, IEntity parent)
	{
		m_Controller = MI3_PlayerController.Cast(ent);
	}
}
