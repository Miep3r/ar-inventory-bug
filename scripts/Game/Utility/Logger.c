class Logger
{
	private string m_sPrefix;
	
	void Log(string message)
	{
		Print(m_sPrefix + message);
	}
	
	void LogFormat(string message, void param1 = NULL, void param2 = null, void param3 = null, void param4 = null, void param5 = null, void param6 = null, void param7 = null, void param8 = null, void param9 = null)
	{
		Log(string.Format(message, param1, param2, param3, param4, param5, param6, param7, param8, param9));
	}
	
	void Error(string message)
	{
		Debug.Error(m_sPrefix + message);
	}
	
	string GetPrefix()
	{
		return m_sPrefix;
	}
	
	//=====================================================================\\
	Logger Logger(string prefix)
	{
		m_sPrefix = prefix;
		return this;
	}
	
	void ~Logger()
	{
	}
};
