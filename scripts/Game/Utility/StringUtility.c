class StringUtility
{
	
	static string LeftPad(string s, int amount, string with = " ")
	{
		int length = s.Length();
		// Length is greater than padded amount, skip
		if (length >= amount)
		{
			return s;
		}
		
		string result = "";
		for (int i = length; i < amount; i++)
		{
			result += with;
		}
		result += s;
		
		return result;
	}
	
	static string RightPad(string s, int amount, string with = " ")
	{
		int length = s.Length();
		// Length is greater than padded amount, skip
		if (length >= amount)
		{
			return s;
		}
		
		for (int i = 0; i < amount; i++)
		{
			s += with;
		}
		
		return s;
	}
}
