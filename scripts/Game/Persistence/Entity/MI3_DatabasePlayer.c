class MI3_DatabasePlayer : MI3_DbEntity
{
	private int m_iId;
	private string m_sGuid;
	private string m_sName;
	private int m_iAdminLevel;
	
	int GetId()
	{
		return m_iId;
	}
	
	override bool SerializationLoad(BaseSerializationLoadContext loadContext)
	{
		if (!loadContext.IsValid())
			return false;
		
		loadContext.ReadValue("id", m_iId);
		loadContext.ReadValue("guid", m_sGuid);
		loadContext.ReadValue("name", m_sName);
		loadContext.ReadValue("admin_level", m_iAdminLevel);
		
		return true;
	}
	
	string ToPrettyString()
	{
		return (string.Format("[id = %1, guid = '%2', name = '%3']", m_iId, m_sGuid, m_sName));
	}
}
