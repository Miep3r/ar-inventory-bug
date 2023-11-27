// Used for monitoring task runtime, unfinished
class MI3_StopWatch
{
	protected ref map<string, ref MI3_StopWatchTask> m_mTasks;
	protected int m_iStartTick;
	protected int m_iStopTick;
	
	void MI3_StopWatch()
	{
		m_mTasks = new map<string, ref MI3_StopWatchTask>();
	}
	
	void Start()
	{
		m_iStartTick = System.GetTickCount();
	}
	
	void Stop()
	{
		m_iStopTick = System.GetTickCount();
	}
}
