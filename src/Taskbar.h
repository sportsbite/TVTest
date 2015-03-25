#ifndef TVTEST_TASKBAR_H
#define TVTEST_TASKBAR_H


#include <vector>
#include <map>


class CTaskbarManager
{
public:
	CTaskbarManager();
	~CTaskbarManager();
	bool Initialize(HWND hwnd);
	void Finalize();
	bool HandleMessage(UINT uMsg,WPARAM wParam,LPARAM lParam);
	bool SetRecordingStatus(bool fRecording);
	bool SetProgress(int Pos,int Max);
	bool EndProgress();
	bool UpdateJumpList();
	bool ClearJumpList();

private:
	struct JumpListItem
	{
		TVTest::String Title;
		TVTest::String Args;
		TVTest::String Description;
		TVTest::String IconPath;
		int IconIndex;
	};
	typedef std::vector<JumpListItem> JumpListItemList;

	struct ChannelIconInfo
	{
		FILETIME UpdatedTime;

		ChannelIconInfo() {}
		ChannelIconInfo(const FILETIME &Time) : UpdatedTime(Time) {}
	};

	static DWORD ChannelIconMapKey(WORD NetworkID,WORD ServiceID) {
		return ((DWORD)NetworkID<<16) | ServiceID;
	}

	struct CommandIconInfo
	{
		int Command;
		int Icon;
	};

	static const CommandIconInfo m_CommandIconList[];

	HWND m_hwnd;
	UINT m_TaskbarButtonCreatedMessage;
	interface ITaskbarList3 *m_pTaskbarList;
	TVTest::String m_AppID;
	bool m_fJumpListInitialized;
	std::map<DWORD,ChannelIconInfo> m_ChannelIconMap;

	HRESULT InitializeJumpList();
	HRESULT AddTaskList(interface ICustomDestinationList *pcdl);
	HRESULT CreateAppShellLink(
		PCWSTR pszArgs,PCWSTR pszTitle,PCWSTR pszDescription,
		PCWSTR pszIconPath,int IconIndex,
		IShellLink **ppShellLink);
	HRESULT CreateSeparatorShellLink(IShellLink **ppShellLink);
	HRESULT AddJumpListCategory(
		interface ICustomDestinationList *pcdl,
		PCWSTR pszTitle,const JumpListItemList &ItemList);
	HRESULT AddRecentChannelsCategory(interface ICustomDestinationList *pcdl);
	int GetCommandIcon(int Command) const;
};


#endif
