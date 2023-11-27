class MI3_InitialPlayer : IEntity
{
	protected RplComponent m_RplComponent;
	
	void MI3_InitialPlayer(IEntitySource src, IEntity parent)
	{
		m_RplComponent = RplComponent.Cast(FindComponent(RplComponent));
		
		Print("Initial player constructed!");
	}
	
	void ~MI3_InitialPlayer()
	{
	}
}
