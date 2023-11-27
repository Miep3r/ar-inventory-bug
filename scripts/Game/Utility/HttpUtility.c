class HttpUtility
{
	private static const ref array<string> DEFAULT_CHARS_ARRAY = {
		"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z",
		"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z",
		"1","2","3","4","5","6","7","8","9","0"
	};
	private static ref set<string> DEFAULT_CHARS;
	
	static void Init()
	{
		DEFAULT_CHARS = new set<string>();
		
		foreach (string char : DEFAULT_CHARS_ARRAY)
		{
			DEFAULT_CHARS.Insert(char);
		}
	};
	
	static string EncodeUrl(string url)
	{
		if (!DEFAULT_CHARS)
			Init();
		
		for (int i = 0; i < url.Length(); i++)
		{
			string char = url.Get(i);
			if (!DEFAULT_CHARS.Contains(char))
			{
				// Char needs to be encoded
				string hex = MathUtility.IntToHex(char.ToAscii());
				
				int i2 = i + 1;
				
				string first = url.Substring(0, i);
				string last = url.Substring(i2, url.Length() - i2);
				
				url = first + "%" + hex + last;
			}
		}
		
		return url;
	};
};
