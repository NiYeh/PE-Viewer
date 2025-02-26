// DialogMain.cpp: implementation of the DialogMain class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DialogMain.h"

VOID InitProcessListView(HWND hDlg)
{
	LV_COLUMN lv;								
	HWND hListProcess;
									
	//初始化								
	memset(&lv,0,sizeof(LV_COLUMN));								
	//获取IDC_LIST_PROCESS句柄								
	hListProcess = GetDlgItem(hDlg,IDC_LIST_PROCESS);								
	//设置整行选中								
	SendMessage(hListProcess,LVM_SETEXTENDEDLISTVIEWSTYLE,LVS_EX_FULLROWSELECT,LVS_EX_FULLROWSELECT);								
									
	//第一列								
	lv.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;								
	lv.pszText = TEXT("进程");				//列标题				
	lv.cx = 150;								//列宽
	lv.iSubItem = 0;								
	//ListView_InsertColumn(hListProcess, 0, &lv);								
	SendMessage(hListProcess,LVM_INSERTCOLUMN,0,(DWORD)&lv);								
	//第二列								
	lv.pszText = TEXT("PID");								
	lv.cx = 100;								
	lv.iSubItem = 1;								
	//ListView_InsertColumn(hListProcess, 1, &lv);								
	SendMessage(hListProcess,LVM_INSERTCOLUMN,1,(DWORD)&lv);								
	//第三列								
	lv.pszText = TEXT("镜像基址");								
	lv.cx = 100;								
	lv.iSubItem = 2;								
	ListView_InsertColumn(hListProcess, 2, &lv);								
	//第四列								
	lv.pszText = TEXT("镜像大小");								
	lv.cx = 100;								
	lv.iSubItem = 3;								
	ListView_InsertColumn(hListProcess, 3, &lv);								

	EnumProcess(hListProcess);
}

VOID InitModulesListView(HWND hDlg)
{
	LV_COLUMN lv;								
	HWND hListProcess;
	
	//初始化								
	memset(&lv,0,sizeof(LV_COLUMN));								
	//获取IDC_LIST_PROCESS句柄								
	hListProcess = GetDlgItem(hDlg,IDC_LIST_MOUDLE);								
	//设置整行选中								
	SendMessage(hListProcess,LVM_SETEXTENDEDLISTVIEWSTYLE,LVS_EX_FULLROWSELECT,LVS_EX_FULLROWSELECT);

	//第一列								
	lv.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;								
	lv.pszText = TEXT("模块名称");				//列标题				
	lv.cx = 200;								//列宽
	lv.iSubItem = 0;								
	//ListView_InsertColumn(hListProcess, 0, &lv);								
	SendMessage(hListProcess,LVM_INSERTCOLUMN,0,(DWORD)&lv);

	//第二列								
	lv.pszText = TEXT("模块位置");								
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
							
	//初始化				
	memset(ExeText, 0, MAX_PATH);

	memset(&vitem,0,sizeof(LV_ITEM));						
	vitem.mask = LVIF_TEXT;	
	
	HANDLE handle;
	handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); //调用CreatToolhelp32Snapshot来获取快照,用THREADENTRY32来获取线程信息等 就会用到'tlHelp32.h'头文件

	PROCESSENTRY32* info = new PROCESSENTRY32;
	info->dwSize = sizeof(PROCESSENTRY32);
	Process32First(handle, info);

	while (Process32Next(handle, info) != FALSE)
	{	
		sprintf(ExeText, "%s", info->szExeFile);						// 获取进程的EXE名（注意不是全路径）
		vitem.pszText = ExeText;						
		vitem.iItem = count;						
		vitem.iSubItem = 0;												
		SendMessage(hListProcess, LVM_INSERTITEM,0,(DWORD)&vitem);
		
		sprintf(ExeText, "%x", info->th32ProcessID);					// 获取进程ID
		vitem.pszText = ExeText;						
		vitem.iItem = count;						
		vitem.iSubItem = 1;						
		ListView_SetItem(hListProcess, &vitem);

		DWORD Base = GetMoudleBaseAddr(info->th32ProcessID, info->szExeFile);
		sprintf(ExeText, "%x", Base);									// 获取进程基址
		vitem.pszText = ExeText;
		vitem.iItem = count;						
		vitem.iSubItem = 2;						
		ListView_SetItem(hListProcess, &vitem);	

		DWORD BaseSize = GetMoudleBaseSizeAddr(info->th32ProcessID, info->szExeFile);
		sprintf(ExeText, "%x", BaseSize);								// 获取进程大小
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

	//初始化								
	memset(&vitem,0,sizeof(LV_ITEM));						
	vitem.mask = LVIF_TEXT;
	//初始化								
	memset(&lv,0,sizeof(LV_ITEM));
	//初始化								
	memset(szPID,0,0x20);
	//初始化								
	memset(szMoudleName,0,256);
	//初始化		
	memset(ExeText, 0, MAX_PATH);

	// 获取选择行
	dwRowId = SendMessage(hListProcess, LVM_GETNEXTITEM, -1, LVNI_SELECTED);
	if (dwRowId == -1)
	{
		MessageBox(NULL, TEXT("清选择进程!"), TEXT("windows"), MB_OK);
		return ;
	}

	// 获取PID
	lv.iSubItem = 1;
	lv.pszText = szPID;
	lv.cchTextMax = 0x20;
	SendMessage(hListProcess, LVM_GETITEMTEXT, dwRowId, (DWORD)&lv);

	// 获取模块名
	lv.iSubItem = 0;
	lv.pszText = szMoudleName;
	lv.cchTextMax = 256;
	SendMessage(hListProcess, LVM_GETITEMTEXT, dwRowId, (DWORD)&lv);

	sscanf(szPID, "%x", &MoudlePID);

	//打开当前进程的句柄
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
	
	//枚举当前进程的模块
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

//通過進程ID獲取某模塊的基址
DWORD GetMoudleBaseAddr(DWORD dwPid, const TCHAR* szDllName)
{
	DWORD dwDllBase;
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); // 進程快照句柄
	PROCESSENTRY32 pi = { sizeof(PROCESSENTRY32) }; // 快照訊息
	// 遍歷進程

	while (Process32Next(hProcessSnap, &pi))
	{
		if (pi.th32ProcessID == dwPid)
		{
			HANDLE  hModuleSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pi.th32ProcessID);  // 模塊快照句柄
			MODULEENTRY32 me32 = { 0 };  // 模塊入口
			me32.dwSize = sizeof(MODULEENTRY32);  // 申請空間

			// 打印模塊名
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

//通過進程ID獲取某模塊的基址大小
DWORD GetMoudleBaseSizeAddr(DWORD dwPid, const TCHAR* szDllName)
{
	DWORD dwDllBaseSize;
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); // 進程快照句柄
	PROCESSENTRY32 pi = { sizeof(PROCESSENTRY32) }; // 快照訊息
	// 遍歷進程

	while (Process32Next(hProcessSnap, &pi))
	{
		if (pi.th32ProcessID == dwPid)
		{
			HANDLE  hModuleSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pi.th32ProcessID);  // 模塊快照句柄
			MODULEENTRY32 me32 = { 0 };  // 模塊入口
			me32.dwSize = sizeof(MODULEENTRY32);  // 申請空間

			// 打印模塊名
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
