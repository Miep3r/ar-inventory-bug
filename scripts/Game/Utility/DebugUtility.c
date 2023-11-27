class DebugUtility
{
	static ref array<string> DEBUG_GUID_ARRAY = {"19a0a555-87c6-476d-ab74-bf23478c5b64", "b9695ce9-0c31-494a-a408-224f3f0d92b6", "d9da4e73-ec8c-4ec6-9c0b-d0b3dcb4e4be"};
	static int currentGUID = 0;
	
	static string GetGUID()
	{
		return DEBUG_GUID_ARRAY[currentGUID++];
	}
};
