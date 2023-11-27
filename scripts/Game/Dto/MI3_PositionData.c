class MI3_PositionData : Managed
{
	protected vector m_Position;
	protected vector m_Rotation;
	
	void Set(vector position, vector rotation)
	{
		m_Position = position;
		m_Rotation = rotation;
	}
	
	vector GetPosition()
	{
		return m_Position;
	}
	
	vector GetRotation()
	{
		return m_Rotation;
	}
	
	bool SerializationLoad(BaseSerializationLoadContext loadContext)
	{
		if (!loadContext.IsValid())
			return false;
		
		loadContext.ReadValue("pos", m_Position);
		loadContext.ReadValue("rot", m_Rotation);
		
		Print("POSITION READ!");
		
		return true;
	}
	
	bool SerializationSave(BaseSerializationSaveContext saveContext)
	{
		if (!saveContext.IsValid())
			return false;
		
		saveContext.WriteValue("pos", m_Position);
		saveContext.WriteValue("rot", m_Rotation);
		
		return true;
	}
}
