// DialogMain.cpp: implementation of the DialogMain class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DialogMain.h"

VOID InitProcessListView(HWND hDlg)
{
	LV_COLUMN lv;								
	HWND hListProcess;
									
	//��ʼ��								
	memset(&lv,0,sizeof(LV_COLUMN));								
	//��ȡIDC_LIST_PROCESS���								
	hListProcess = GetDlgItem(hDlg,IDC_LIST_PROCESS);								
	//��������ѡ��								
	SendMessage(hListProcess,LVM_SETEXTENDEDLISTVIEWSTYLE,LVS_EX_FULLROWSELECT,LVS_EX_FULLROWSELECT);								
									
	//��һ��								
	lv.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;								
	lv.pszText = TEXT("����");				//�б���				
	lv.cx = 150;								//�п�
	lv.iSubItem = 0;								
	//ListView_InsertColumn(hListProcess, 0, &lv);								
	SendMessage(hListProcess,LVM_INSERTCOLUMN,0,(DWORD)&lv);								
	//�ڶ���								
	lv.pszText = TEXT("PID");								
	lv.cx = 100;								
	lv.iSubItem = 1;								
	//ListView_InsertColumn(hListProcess, 1, &lv);								
	SendMessage(hListProcess,LVM_INSERTCOLUMN,1,(DWORD)&lv);								
	//������								
	lv.pszText = TEXT("�����ַ");								
	lv.cx = 100;								
	lv.iSubItem = 2;								
	ListView_InsertColumn(hListProcess, 2, &lv);								
	//������								
	lv.pszText = TEXT("�����С");								
	lv.cx = 100;								
	lv.iSubItem = 3;								
	ListView_InsertColumn(hListProcess, 3, &lv);								

	EnumProcess(hListProcess);
}

VOID InitModulesListView(HWND hDlg)
{
	LV_COLUMN lv;								
	HWND hListProcess;
	
	//��ʼ��								
	memset(&lv,0,sizeof(LV_COLUMN));								
	//��ȡIDC_LIST_PROCESS���								
	hListProcess = GetDlgItem(hDlg,IDC_LIST_MOUDLE);								
	//��������ѡ��								
	SendMessage(hListProcess,LVM_SETEXTENDEDLISTVIEWSTYLE,LVS_EX_FULLROWSELECT,LVS_EX_FULLROWSELECT);

	//��һ��								
	lv.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;								
	lv.pszText = TEXT("ģ������");				//�б���				
	lv.cx = 200;								//�п�
	lv.iSubItem = 0;								
	//ListView_InsertColumn(hListProcess, 0, &lv);								
	SendMessage(hListProcess,LVM_INSERTCOLUMN,0,(DWORD)&lv);

	//�ڶ���								
	lv.pszText = TEXT("ģ��λ��");								
	lv.cx = 500;								
	lv.iSubItem = 1;								
	//ListView_InsertColumn(hListProcess, 1, &lv);								
	SendMessage(hListProcess,LVM_INSERTCOLUMN,1,(DWORD)&lv);
}

VOID EnumProcess(HWND hListProcess)
{
	LV_ITEM vitem;
	TCHAR ExeText[MAX_PATH];
	DWORD count = 0;
							
	//��ʼ��				
	memset(ExeText, 0, MAX_PATH);

	memset(&vitem,0,sizeof(LV_ITEM));						
	vitem.mask = LVIF_TEXT;	
	
	HANDLE handle;
	handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); //����CreatToolhelp32Snapshot����ȡ����,��THREADENTRY32����ȡ�߳���Ϣ�� �ͻ��õ�'tlHelp32.h'ͷ�ļ�

	PROCESSENTRY32* info = new PROCESSENTRY32;
	info->dwSize = sizeof(PROCESSENTRY32);
	Process32First(handle, info);

	while (Process32Next(handle, info) != FALSE)
	{	
		sprintf(ExeText, "%s", info->szExeFile);						// ��ȡ���̵�EXE����ע�ⲻ��ȫ·����
		vitem.pszText = ExeText;						
		vitem.iItem = count;						
		vitem.iSubItem = 0;												
		SendMessage(hListProcess, LVM_INSERTITEM,0,(DWORD)&vitem);
		
		sprintf(ExeText, "%x", info->th32ProcessID);					// ��ȡ����ID
		vitem.pszText = ExeText;						
		vitem.iItem = count;						
		vitem.iSubItem = 1;						
		ListView_SetItem(hListProcess, &vitem);

		DWORD Base = GetMoudleBaseAddr(info->th32ProcessID, info->szExeFile);
		sprintf(ExeText, "%x", Base);									// ��ȡ���̻�ַ
		vitem.pszText = ExeText;
		vitem.iItem = count;						
		vitem.iSubItem = 2;						
		ListView_SetItem(hListProcess, &vitem);	

		DWORD BaseSize = GetMoudleBaseSizeAddr(info->th32ProcessID, info->szExeFile);
		sprintf(ExeText, "%x", BaseSize);								// ��ȡ���̴�С
		vitem.pszText = ExeText;						
		vitem.iItem = count;						
		vitem.iSubItem = 3;						
		ListView_SetItem(hListProcess, &vitem);

		count++;
	}

	CloseHandle(handle);
}

VOID EunmModules(HWND hListModules, HWND hListProcess, WPARAM wParam, LPARAM lParam)
{
	DWORD dwRowId;
	DWORD MoudlePID = 0;
	DWORD NeedSize = 0;
	HMODULE ModuleArray[1024];
	TCHAR szPID[0x20];
	TCHAR szMoudleName[256];
	TCHAR ExeText[MAX_PATH];
	LV_ITEM lv;
	LV_ITEM vitem;

	SendMessage(hListModules, LVM_DELETEALLITEMS,  0,  0);

	//��ʼ��								
	memset(&vitem,0,sizeof(LV_ITEM));						
	vitem.mask = LVIF_TEXT;
	//��ʼ��								
	memset(&lv,0,sizeof(LV_ITEM));
	//��ʼ��								
	memset(szPID,0,0x20);
	//��ʼ��								
	memset(szMoudleName,0,256);
	//��ʼ��		
	memset(ExeText, 0, MAX_PATH);

	// ��ȡѡ����
	dwRowId = SendMessage(hListProcess, LVM_GETNEXTITEM, -1, LVNI_SELECTED);
	if (dwRowId == -1)
	{
		MessageBox(NULL, TEXT("��ѡ�����!"), TEXT("windows"), MB_OK);
		return ;
	}

	// ��ȡPID
	lv.iSubItem = 1;
	lv.pszText = szPID;
	lv.cchTextMax = 0x20;
	SendMessage(hListProcess, LVM_GETITEMTEXT, dwRowId, (DWORD)&lv);

	// ��ȡģ����
	lv.iSubItem = 0;
	lv.pszText = szMoudleName;
	lv.cchTextMax = 256;
	SendMessage(hListProcess, LVM_GETITEMTEXT, dwRowId, (DWORD)&lv);

	sscanf(szPID, "%x", &MoudlePID);

	//�򿪵�ǰ���̵ľ��
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, MoudlePID);
	
	if (NULL == hProcess)
	{
		return ;
	}

	HMODULE hModulePs = LoadLibrary("Psapi.dll");
	typedef DWORD(WINAPI *_EnumProcessModules)(HANDLE, HMODULE, DWORD, LPDWORD);
	_EnumProcessModules EnumProcessModules = (_EnumProcessModules)GetProcAddress(hModulePs, "EnumProcessModules");

	typedef DWORD(WINAPI *_GetModuleFileNameEx)(HANDLE, HMODULE, LPSTR, DWORD);
	_GetModuleFileNameEx GetModuleFileNameEx = (_GetModuleFileNameEx)GetProcAddress(hModulePs, "GetModuleFileNameExA");
	
	//ö�ٵ�ǰ���̵�ģ��
	if (EnumProcessModules(hProcess, (HINSTANCE)ModuleArray, sizeof(ModuleArray), &NeedSize))
	{
		for (int i = 0; i < (NeedSize) / sizeof(HMODULE); i++)
		{
			GetModuleFileNameEx(hProcess, ModuleArray[i], ExeText, sizeof(ModuleArray) / sizeof(TCHAR));

			int len = _tcslen(ExeText);
			for (int j = len - 1; j >= 0; j--)
			{
				if (ExeText[j] == '\\')
				{
					TCHAR FileName[MAX_PATH];
					_tcscpy(FileName, &ExeText[j + 1]);

					vitem.pszText = FileName;
					vitem.iItem = i;
					vitem.iSubItem = 0;
					SendMessage(hListModules, LVM_INSERTITEM, 0, (DWORD)&vitem);

					break;
				}
			}

			vitem.pszText = ExeText;
			vitem.iItem = i;
			vitem.iSubItem = 1;
			ListView_SetItem(hListModules, &vitem);

			memset(ExeText, 0, MAX_PATH);
		}
	}

	CloseHandle(hProcess);
}

//ͨ�^�M��ID�@ȡĳģ�K�Ļ�ַ
DWORD GetMoudleBaseAddr(DWORD dwPid, const TCHAR* szDllName)
{
	DWORD dwDllBase;
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); // �M�̿��վ��
	PROCESSENTRY32 pi = { sizeof(PROCESSENTRY32) }; // ����ӍϢ
	// ��v�M��

	while (Process32Next(hProcessSnap, &pi))
	{
		if (pi.th32ProcessID == dwPid)
		{
			HANDLE  hModuleSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pi.th32ProcessID);  // ģ�K���վ��
			MODULEENTRY32 me32 = { 0 };  // ģ�K���
			me32.dwSize = sizeof(MODULEENTRY32);  // ��Ո���g

			// ��ӡģ�K��
			while (::Module32Next(hModuleSnap, &me32))
			{
				if (_tcscmp(me32.szModule, szDllName) == 0)
				{
					dwDllBase = (DWORD)me32.modBaseAddr;
					return dwDllBase;
					break;
				}
			}
			return 0;
		}
	}
}

//ͨ�^�M��ID�@ȡĳģ�K�Ļ�ַ��С
DWORD GetMoudleBaseSizeAddr(DWORD dwPid, const TCHAR* szDllName)
{
	DWORD dwDllBaseSize;
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); // �M�̿��վ��
	PROCESSENTRY32 pi = { sizeof(PROCESSENTRY32) }; // ����ӍϢ
	// ��v�M��

	while (Process32Next(hProcessSnap, &pi))
	{
		if (pi.th32ProcessID == dwPid)
		{
			HANDLE  hModuleSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pi.th32ProcessID);  // ģ�K���վ��
			MODULEENTRY32 me32 = { 0 };  // ģ�K���
			me32.dwSize = sizeof(MODULEENTRY32);  // ��Ո���g

			// ��ӡģ�K��
			while (::Module32Next(hModuleSnap, &me32))
			{
				if (_tcscmp(me32.szModule, szDllName) == 0)
				{
					dwDllBaseSize = (DWORD)me32.modBaseSize;
					return dwDllBaseSize;
					break;
				}
			}
			return 0;
		}
	}
}
