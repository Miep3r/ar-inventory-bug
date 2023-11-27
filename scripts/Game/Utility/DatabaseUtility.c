class DatabaseUtility
{
	
	static string VectorToString(vector v)
	{
		return ("[" + v[0] + "," + v[1] + "," + v[2] + "]");
	}
	
	static string TransformToString(vector mat[4])
	{
		string result = "{";
		for (int i = 0; i < 3; i++)
		{
			result += "\"" + mat[i].ToString(false) + "\",";
		}
		result += "\"" + mat[3].ToString(false) + "\"}";
		
		return result;
	}
}
