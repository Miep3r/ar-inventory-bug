class MathUtility
{
	private static const ref array<string> HEX_DIGITS = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F"};
	
	static string IntToHex(int input)
	{
		if (input <= 0)
			return "0";
		
		string result = "";
		while (input > 0)
		{
			int digit = input % 16;
			result = (HEX_DIGITS.Get(digit)) + result;
			input = input / 16;
		}
		
		return result;
	}
};
