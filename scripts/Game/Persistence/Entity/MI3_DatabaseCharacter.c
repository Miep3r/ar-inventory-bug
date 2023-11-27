class MI3_DatabaseCharacter : MI3_DbEntity
{
	private int m_iCharacterId;
	private string m_sFirstName;
	private string m_sLastName;
	private string m_sClassname = "C1";
	private float m_fBank = 0;
	private float m_fCash = 0;
	private ref MI3_PositionData m_Position;
	private ref MI3_InventoryDto m_Inventory;
	
	int GetId()
	{
		return m_iCharacterId;
	}
	
	void SetId(int id)
	{
		m_iCharacterId = id;
	}
	
	string GetFirstName()
	{
		return m_sFirstName;
	}
	
	void SetFirstName(string firstName)
	{
		m_sFirstName = firstName;
	}
	
	string GetLastName()
	{
		return m_sLastName;
	}
	
	void SetLastName(string lastName)
	{
		m_sLastName = lastName;
	}
	
	string GetClassname()
	{
		return m_sClassname;
	}
	
	float GetBank()
	{
		return m_fBank;
	}
	
	float GetCash()
	{
		return m_fCash;
	}
	
	MI3_PositionData GetPositionData()
	{
		return m_Position;
	}
	
	MI3_InventoryDto GetInventory()
	{
		return m_Inventory;
	}
	
	void SetInventory(MI3_InventoryDto inventory)
	{
		m_Inventory = inventory;
	}
	
	override bool SerializationLoad(BaseSerializationLoadContext loadContext)
	{
		if (!loadContext.IsValid())
			return false;
		
		loadContext.EnableTypeDiscriminator(string.Empty);
		
		loadContext.ReadValue("id", m_iCharacterId);
		loadContext.ReadValue("first_name", m_sFirstName);
		loadContext.ReadValue("last_name", m_sLastName);
		loadContext.ReadValue("classname", m_sClassname);
		loadContext.ReadValue("bank", m_fBank);
		loadContext.ReadValue("cash", m_fCash);
		loadContext.ReadValue("position", m_Position);
		loadContext.ReadValue("inventory", m_Inventory);
		
		loadContext.EnableTypeDiscriminator();
		
		Print("LOADED CHAR!");
		
		return true;
	}
	
	override bool SerializationSave(BaseSerializationSaveContext saveContext)
	{
		if (!saveContext.IsValid())
			return false;
		
		saveContext.WriteValue("id", m_iCharacterId);
		saveContext.WriteValue("first_name", m_sFirstName);
		saveContext.WriteValue("last_name", m_sLastName);
		saveContext.WriteValue("classname", m_sClassname);
		saveContext.WriteValue("bank", m_fBank);
		saveContext.WriteValue("cash", m_fCash);
		saveContext.WriteValue("position", m_Position);
		saveContext.WriteValue("inventory", m_Inventory);
		
		Print("SAVED CHAR!");
		
		return true;
	}
	
	/*
	static bool Extract(MI3_DatabaseCharacter instance, ScriptCtx ctx, SSnapSerializerBase snapshot)
	{
		// Fill a snapshot with values from an instance.
		snapshot.SerializeInt(instance.m_iCharacterId);
		snapshot.SerializeString(instance.m_sFirstName);
		snapshot.SerializeString(instance.m_sLastName);
		return true;
	}
	
	static bool Inject(SSnapSerializerBase snapshot, ScriptCtx ctx, MI3_DatabaseCharacter instance)
	{
		// Fill an instance with values from snapshot.
		snapshot.SerializeInt(instance.m_iCharacterId);
		snapshot.SerializeString(instance.m_sFirstName);
		snapshot.SerializeString(instance.m_sLastName);
		return true;
	}
	
	static void Encode(SSnapSerializerBase snapshot, ScriptCtx ctx, ScriptBitSerializer packet)
	{
		snapshot.EncodeInt(packet);    // m_Int
		snapshot.EncodeString(packet); // m_String
	}

	static bool Decode(ScriptBitSerializer packet, ScriptCtx ctx, SSnapSerializerBase snapshot)
	{
		snapshot.DecodeInt(packet);    // m_Int
		snapshot.DecodeString(packet); // m_String
		return true;
	}
	
	static bool SnapCompare(SSnapSerializerBase lhs, SSnapSerializerBase rhs , ScriptCtx ctx)
	{
		// Compare two snapshots and determine whether they are the same.
		// We have to compare properties one-by-one, but for properties with known
		// length (such as primitive types bool, int, float and vector), we do multiple
		// comparisons in single call. However, because we do not know length of string,
		// we use provided function which will determine number of bytes that need
		// to be compared from serialized data.
		return lhs.CompareSnapshots(rhs, 4)   // m_Int
		    && lhs.CompareStringSnapshots(rhs);  // m_String
	}
	
	static bool PropCompare(MI3_DatabaseCharacter instance, SSnapSerializerBase snapshot, ScriptCtx ctx)
	{
		// Determine whether current values in instance are sufficiently different from
		// an existing snapshot that it's worth creating new one.
		// For float or vector values, you could use some threshold to avoid creating too
		// many snapshots due to tiny changes in these values.
		return snapshot.CompareInt(instance.m_iCharacterId)
		    && snapshot.CompareString(instance.m_sFirstName)
			&& snapshot.CompareString(instance.m_sLastName);
	}
	*/
}
