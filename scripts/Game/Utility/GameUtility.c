class GameUtility
{
	static ref array<string> DEBUG_GUID_ARRAY = {"19a0a555-87c6-476d-ab74-bf23478c5b64", "b9695ce9-0c31-494a-a408-224f3f0d92b6", "d9da4e73-ec8c-4ec6-9c0b-d0b3dcb4e4be"};
	static int currentGUID = 0;
	
	static ref map<int, string> m_mAssignedUIDs = new map<int, string>();
	
	private static string AssignUID(int playerId)
	{
		string uid = DEBUG_GUID_ARRAY[currentGUID++];
		m_mAssignedUIDs.Set(playerId, uid);
		
		Print("Assigning debug UID '" + uid + "' to player '" + playerId + "'!");
		
		return uid;
	}
	
	private static string GetAssignedUID(int playerId)
	{
		if (m_mAssignedUIDs.Contains(playerId))
			return m_mAssignedUIDs.Get(playerId);
		
		return "";
	}
	
	static string GetPlayerUID(int playerId)
	{
		#ifdef MI3_DEBUG_UID
		string uid = GetAssignedUID(playerId);
		if (uid.IsEmpty())
			uid = AssignUID(playerId);
		
		return uid;
		#else
		return GetGame().GetBackendApi().GetPlayerIdentityId(playerId);
		#endif
	}
}
