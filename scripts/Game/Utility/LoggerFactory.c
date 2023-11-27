class LoggerFactory
{
	private static ref array<Logger> m_aLoggers = new array<Logger>();
	private static ref map<string, Logger> m_mLoggers = new map<string, Logger>();
	
	static array<Logger> GetLoggers()
	{
		return m_aLoggers;
	}
	
	static Logger GetForClass(typename clazz)
	{
		string loggerName = clazz.ToString();
		
		if (m_mLoggers.Get(loggerName))
			return m_mLoggers.Get(loggerName);
		
		Logger logger = new Logger(string.Format("[%1] ", loggerName));
		
		m_mLoggers.Set(loggerName, logger);
		
		return logger;
	}
};
