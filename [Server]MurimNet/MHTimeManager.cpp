// MHTimeManager.cpp: implementation of the CMHTimeManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MHTimeManager.h"
#include "mmsystem.h"


DWORD gCurTime;
DWORD gTickTime;

#define TICK_PER_DAY 8640000		// 24 * 60 * 60 * 1000
#define TICK_PER_HOUR 3600000		// 60 * 60 * 1000
#define TICK_PER_MINUTE 60000		// 60 * 1000

#define DAY_PER_YEAR 360
#define DAY_PER_MONTH 30

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMHTimeManager::CMHTimeManager()
{
	m_MHDate = 0;
	m_MHTime = 0;

}

CMHTimeManager::~CMHTimeManager()
{

}

void CMHTimeManager::Init(DWORD mhDate,DWORD mhTime)
{
	m_MHDate = mhDate;
	m_MHTime = mhTime;
}

void CMHTimeManager::Process()
{
	static bool bFirst = true;
	static DWORD lasttime = 0;
	static DWORD curtime = 0;
	static int tempDay = 0;

	if( !bFirst )
	{
		curtime = timeGetTime();
		if( curtime < lasttime )		// DWORD 형의 한계를 넘어갔다
			gTickTime = curtime - lasttime + 4294967295; //( 2^32 - 1 )
		else
			gTickTime = curtime - lasttime;

		if( gTickTime == 0 ) return;
		
		lasttime = curtime;
		
		gCurTime += gTickTime;
		if( gTickTime > 2000 )
			int a = 0;

		
		//////////////////////////////////////////////////////////////////////////
		// 묵향력-_-a;
		m_MHTime += gTickTime;
		if(m_MHTime >= TICK_PER_DAY)
		{
			++m_MHDate;
			m_MHTime -= TICK_PER_DAY;
		}
	}	
	else
	{
		curtime = lasttime = timeGetTime();
		bFirst = false;
	}

}

DWORD CMHTimeManager::GetMHDate()
{
	return m_MHDate;
}
DWORD CMHTimeManager::GetMHTime()
{
	return m_MHTime;
}

void CMHTimeManager::GetMHDate(BYTE& year,BYTE& month,BYTE& day)
{
	year = (BYTE)(m_MHDate / DAY_PER_YEAR) + 1;
	month = (BYTE)((m_MHDate - year) / DAY_PER_MONTH) + 1;
	day = (BYTE)m_MHDate % DAY_PER_MONTH + 1;  // -_-a; 묵향에선 모든 달은 30일까지다 -_-	
}

void CMHTimeManager::GetMHTime(BYTE& hour,BYTE& minute)
{
	hour = (BYTE)m_MHTime / TICK_PER_HOUR;
	minute = (BYTE)(m_MHTime - hour) / TICK_PER_MINUTE;
}