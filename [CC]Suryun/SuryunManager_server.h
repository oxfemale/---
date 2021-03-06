// SuryunManager.h: interface for the CSuryunManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SURYUNMANAGER_H__0D37128D_3D3A_458E_959C_D66C4D25E0CD__INCLUDED_)
#define AFX_SURYUNMANAGER_H__0D37128D_3D3A_458E_959C_D66C4D25E0CD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define SURYUNMGR	CSuryunManager::GetInstance()

#include "SuryunDefine.h"

class CPlayer;

class CSuryunManager  
{
	CSuryunManager();
	CYHHashTable<SURYUNMISSIONINFO> m_MissionInfo;
	CYHHashTable<SURYUNMONSTERINFO> m_MonsterInfo;
	CYHHashTable<SURYUNLEVELCHANGE> m_ChangeLevelTable;

	LEVELTYPE GetChangedLevel(LEVELTYPE adjustedLevel,BYTE sung);
public:
	MAKESINGLETON(CSuryunManager);

	~CSuryunManager();

	void NetworkMsgParse(DWORD dwConnectionIndex, BYTE Protocol,void* pMsg);
	
	void LoadSuryunInfo();
	void LoadMonsterInfo();

	void OnGoSuryunSyn(CPlayer* pPlayer,WORD MugongIdx);
	
	MONEYTYPE GetSuryunFee(SURYUNINFO* pInfo,CPlayer* pPlayer);

	SURYUNMISSIONINFO* GetMissionInfo(WORD MugongIdx) { return m_MissionInfo.GetData(MugongIdx); }
	SURYUNMONSTERINFO* GetMonsterInfo(LEVELTYPE Level) { return m_MonsterInfo.GetData(Level); }

	BOOL NeedSuryun(WORD MugongIdx,BYTE Sung,DWORD Exp);
};

#endif // !defined(AFX_SURYUNMANAGER_H__0D37128D_3D3A_458E_959C_D66C4D25E0CD__INCLUDED_)
