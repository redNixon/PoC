#pragma once
#include <windows.h>
#include <wchar.h>
#include <string>

#define ALL_SHARING FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE
#define GENERIC_READ_WRITE GENERIC_READ|GENERIC_WRITE
#define InitializeObjectAttributes( p, n, a, r, s ) {    \
    (p)->uLength = sizeof( OBJECT_ATTRIBUTES );          \
    (p)->hRootDirectory = r;                             \
    (p)->uAttributes = a;                                \
    (p)->pObjectName = n;                                \
    (p)->pSecurityDescriptor = s;                        \
    (p)->pSecurityQualityOfService = NULL;               \
}
#define lock_ptr OpsMaster::FileOpLock*
#define USE_USER_TEMP_DIR 0x190
#define USE_SYSTEM_TEMP_DIR 0x1F4
#define USE_CUSTOM_TEMP_DIR 0x258

typedef void(*_UserCallback)();
class OpsMaster {

public:
	/// the constructor will be used to import native functions to make them ready to call
	OpsMaster();
	/// <summary>
	/// Get last error from a call using OpsMaster class
	/// </summary>
	/// <returns></returns>
	DWORD GetLastErr();
	/// <summary>
	/// convert NTSTATUS error code to DOS error code
	/// </summary>
	/// <param name="status">NTSTATUS error code to be converted</param>
	/// <returns></returns>
	DWORD NtStatusToDOS(NTSTATUS status);

	/// <summary>
	/// Move a file or directory using an existing handle with DELETE access
	/// </summary>
	/// <param name="hfile">A valid handle with delete access to a file or directory</param>
	/// <param name="target">A valid path to a directory which should not exceed MAX_PATH</param>
	/// <returns>if the function suceed it will return true, if not call OpsMaster::GetLastError to retrieve the error code</returns>
	bool MoveByHandle(HANDLE hfile, std::wstring target);
	/// <summary>
	/// Move a file or directory using an existing handle with DELETE access
	/// </summary>
	/// <param name="hfile">A valid handle with delete access to a file or directory</param>
	/// <param name="target">A valid path to a directory which should not exceed MAX_PATH</param>
	/// <returns>if the function suceed it will return true, if not call OpsMaster::GetLastError to retrieve the error code</returns>
	bool MoveByHandle(HANDLE hfile, std::string target);
	/// <summary>
	/// create a native symbolic link
	/// </summary>
	/// <param name="link">A valid path to a link, example: L"\\RPC CONTROL\\test"</param>
	/// <param name="target">A valid path DOS device path to the target file or directory, example:L"\\??\\C:\\test"</param>
	/// <returns>Return a HANDLE to the newly created symlink if succeeded, if not call OpsMaster::GetLastError to retrieve the error code</returns>
	HANDLE CreateNativeSymlink(std::wstring link, std::wstring target);
	/// <summary>
	/// create a native symbolic link
	/// </summary>
	/// <param name="link">A valid path to a link, example: L"\\RPC CONTROL\\test"</param>
	/// <param name="target">A valid path DOS device path to the target file or directory, example:L"\\??\\C:\\test"</param>
	/// <returns>Return a HANDLE to the newly created symlink if succeeded, if not call OpsMaster::GetLastError to retrieve the error code</returns>
	HANDLE CreateNativeSymlink(std::string link, std::string target);
	/// <summary>
	/// Retrive a HANDLE to directory
	/// </summary>
	/// <param name="directory">The name of the directory to be opened</param>
	/// <param name="access_mask">The desired access of the file to be opened, default is GENERIC_READ|GENERIC_WRITE</param>
	/// <param name="share_mode">The share mode, default is FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE</param>
	/// <param name="creation_disposition">The creation disposition this value can be CREATE_NEW or OPEN_EXISTING or OPEN_ALWAYS</param>
	/// <returns>if the function succeed the return value is a valid HANDLE to the target directory, call GetLastErr for extended info about the error</returns>
	HANDLE OpenDirectory(std::wstring directory,
		DWORD access_mask = MAXIMUM_ALLOWED,
		DWORD share_mode = ALL_SHARING, DWORD creation_disposition = OPEN_ALWAYS);
	/// <summary>
	/// Retrive a HANDLE to directory
	/// </summary>
	/// <param name="directory">The name of the directory to be opened</param>
	/// <param name="access_mask">The desired access of the file to be opened, default is GENERIC_READ|GENERIC_WRITE</param>
	/// <param name="share_mode">The share mode, default is FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE</param>
	/// <param name="creation_disposition">The creation disposition this value can be CREATE_NEW or OPEN_EXISTING or OPEN_ALWAYS</param>
	/// <returns>if the function succeed the return value is a valid HANDLE to the target directory, call GetLastErr for extended info about the error</returns>
	HANDLE OpenDirectory(std::string directory,
		DWORD access_mask = MAXIMUM_ALLOWED,
		DWORD share_mode = ALL_SHARING, DWORD creation_disposition = OPEN_ALWAYS);
	/// <summary>
	/// Retrive a HANDLE to directory
	/// </summary>
	/// <param name="directory">The name of the directory to be opened</param>
	/// <param name="access_mask">The desired access of the file to be opened, default is GENERIC_READ|GENERIC_WRITE</param>
	/// <param name="share_mode">The share mode, default is FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE</param>
	/// <param name="creation_disposition">For more info about this please visite https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-createfilew</param>
	/// <returns>if the function succeed the return value is a valid HANDLE to the target file, call GetLastErr for extended info about the error</returns>
	HANDLE OpenFileNative(std::wstring file,
		DWORD access_mask = MAXIMUM_ALLOWED,
		DWORD share_mode = ALL_SHARING, DWORD creation_dispostion = OPEN_ALWAYS);
	/// <summary>
	/// Retrive a HANDLE to directory
	/// </summary>
	/// <param name="directory">The name of the directory to be opened</param>
	/// <param name="access_mask">The desired access of the file to be opened, default is GENERIC_READ|GENERIC_WRITE</param>
	/// <param name="share_mode">The share mode, default is FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE</param>
	/// <param name="creation_disposition">For more info about this please visite https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-createfilew</param>
	/// <returns>if the function succeed the return value is a valid HANDLE to the target file, call GetLastErr for extended info about the error</returns>
	HANDLE OpenFileNative(std::string file,
		DWORD access_mask = MAXIMUM_ALLOWED,
		DWORD share_mode = ALL_SHARING, DWORD creation_dispostion = OPEN_ALWAYS);
	/// <summary>
	/// terminate a process by pid
	/// </summary>
	/// <param name="process_id">the pid of the process to be terminated</param>
	/// <returns>return true if the function succeed, if not call OpsMaster::GetLastError to will retrieve the error code</returns>

	/// <summary>
	/// Call NtWriteFile to write data to file
	/// </summary>
	/// <param name="hfile">HANDLE to a file with GENERIC_WRITE access</param>
	/// <param name="lpBuffer">The buffer to write to the file</param>
	/// <param name="nNumberOfBytesToWrite">Number of bytes to write, this parameter cannot be null</param>
	/// <param name="lpNumberOfBytesWritten">An optional pointer to a DWORD that receive the number of bytes written</param>
	/// <returns>Return true if succeed</returns>
	bool WriteFileNative(HANDLE hfile, PVOID lpBuffer, DWORD nNumberOfBytesToWrite,
		LPDWORD lpNumberOfBytesWritten = NULL);
	/// <summary>
	/// Call NtReadFile to read data from a file
	/// </summary>
	/// <param name="hFile">HANDLE to a file with GENERIC_READ access</param>
	/// <param name="lpBuffer">[OUT] The buffer that receive the data of the file</param>
	/// <param name="nNumberOfBytesToRead">Number of bytes to read, if not specified the entire file is going to be read</param>
	/// <param name="lpNumberOfBytesRead">An optional pointer to a DWORD that receive the number of bytes written</param>
	/// <returns></returns>
	bool ReadFileNative(HANDLE hFile, LPVOID lpBuffer,
		DWORD nNumberOfBytesToRead = NULL,
		LPDWORD lpNumberOfBytesRead = NULL);
	/// <summary>
	/// Call this function to cause a BSOD
	/// SeShutdownPrivilege is required to call this function
	/// if the function return it means that the function failed
	/// this function is mainly used to generate kernel crash dump file in c:\windows\memory.dmp
	/// </summary>
	void bsod();
	/// <summary>
	/// Open named pipe using native NtCreateFile function
	/// </summary>
	/// <param name="pipe_name">The name of the pipe to be opened</param>
	/// <param name="desired_access">Desired access to the pipe to be opened the default is GENERIC_READ</param>
	/// <param name="impersonation_level">Impersonation level, the default is SECURITY_IMPERSONATION for more please visite https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-createfilew </param>
	/// <returns>return a valid HANDLE if the function succeed, if not call OpsMaster::GetLastError to will retrieve the error code</returns>
	HANDLE OpenNamedPipe(std::wstring pipe_name, DWORD desired_access = GENERIC_READ,
		DWORD impersonation_level = SECURITY_IMPERSONATION);
	/// <summary>
	/// Open named pipe using native NtCreateFile function
	/// </summary>
	/// <param name="pipe_name">The name of the pipe to be opened</param>
	/// <param name="desired_access">Desired access to the pipe to be opened the default is GENERIC_READ</param>
	/// <param name="impersonation_level">Impersonation level, the default is SECURITY_IMPERSONATION for more please visite https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-createfilew </param>
	/// <returns>return a valid HANDLE if the function succeed, if not call OpsMaster::GetLastError to will retrieve the error code</returns>
	HANDLE OpenNamedPipe(std::string pipe_name, DWORD desired_access = GENERIC_READ,
		DWORD impersonation_level = SECURITY_IMPERSONATION);
	/// <summary>
	/// Create native hardlink to file
	/// </summary>
	/// <param name="link">the path to the link to be created</param>
	/// <param name="target">the path to the target file</param>
	/// <returns>return true if suceeded, if not call OpsMaster::GetLastError to will retrieve the error code</returns>
	bool CreateNativeHardLink(std::wstring link, std::wstring target);
	/// <summary>
	/// Create native hardlink to file
	/// </summary>
	/// <param name="link">the path to the link to be created</param>
	/// <param name="target">the path to the target file</param>
	/// <returns>return true if suceeded, if not call OpsMaster::GetLastError to will retrieve the error code</returns>
	bool CreateNativeHardLink(std::string link, std::string target);
	/// <summary>
	///  Create native hardlink to file
	/// </summary>
	/// <param name="hfile">A valid handle to the target file</param>
	/// <param name="target">the path to the target file</param>
	/// <returns>return true if suceeded, if not call OpsMaster::GetLastError to will retrieve the error code</returns>
	bool CreateNativeHardLink(HANDLE hfile, std::wstring target);
	/// <summary>
	///  Create native hardlink to file
	/// </summary>
	/// <param name="hfile">A valid handle to the target file</param>
	/// <param name="target">the path to the target file</param>
	/// <returns>return true if suceeded, if not call OpsMaster::GetLastError to will retrieve the error code</returns> 1
	bool CreateNativeHardLink(HANDLE hfile, std::string target);
	/// <summary>
	/// Create reparse point
	/// </summary>
	/// <param name="hdir">A valid handle to a directory with FILE_WRITE_DATA_ACCESS</param>
	/// <param name="target">the target of the reparse point</param>
	/// <param name="printname">optional, the reparse point print name</param>
	/// <returns>return true if suceeded, if not call OpsMaster::GetLastError to will retrieve the error code </returns>
	bool CreateMountPoint(HANDLE hdir, std::wstring target, std::wstring printname = L"");
	/// <summary>
	/// Create reparse point
	/// </summary>
	/// <param name="hdir">A valid handle to a directory with FILE_WRITE_DATA_ACCESS</param>
	/// <param name="target">the target of the reparse point</param>
	/// <param name="printname">optional, the reparse point print name</param>
	/// <returns>return true if suceeded, if not call OpsMaster::GetLastError to will retrieve the error code </returns>
	bool CreateMountPoint(HANDLE hdir, std::string target, std::string printname = "");
	/// <summary>
	/// Create reparse point
	/// </summary>
	/// <param name="dir">path to a directory, the caller must ensure that the directory is empty</param>
	/// <param name="target">the target of the reparse point</param>
	/// <param name="printname">optional, the reparse point print name</param>
	/// <returns>return true if suceeded, if not call OpsMaster::GetLastError to will retrieve the error code </returns>
	bool CreateMountPoint(std::wstring dir, std::wstring target, std::wstring printname = L"");
	/// <summary>
	/// Create reparse point
	/// </summary>
	/// <param name="dir">path to a directory, the caller must ensure that the directory is empty</param>
	/// <param name="target">the target of the reparse point</param>
	/// <param name="printname">optional, the reparse point print name</param>
	/// <returns>return true if suceeded, if not call OpsMaster::GetLastError to will retrieve the error code </returns>
	bool CreateMountPoint(std::string dir, std::string target, std::string printname = "");
	/// <summary>
	/// remove reparse point tag from a directory
	/// </summary>
	/// <param name="hdir">valid handle to a directory with FILE_WRITE_DATA access</param>
	/// <returns></returns>
	bool DeleteMountPoint(HANDLE hdir);
	/// <summary>
	/// remove reparse point tag from a directory
	/// </summary>
	/// <param name="dir">Target path to the reparse point</param>
	/// <returns></returns>
	bool DeleteMountPoint(std::wstring dir);
	/// <summary>
	/// remove reparse point tag from a directory
	/// </summary>
	/// <param name="dir">Target path to the reparse point</param>
	/// <returns></returns>
	bool DeleteMountPoint(std::string dir);
	/// <summary>
	/// read the data in a reparse point
	/// </summary>
	/// <param name="hdir">A valid HANDLE with GENERIC_READ to the target directory</param>
	/// <param name="">reserved must be L""</param>
	/// <returns>Return the data of the reparse point if succeeded</returns>
	std::wstring GetMountPointData(HANDLE hdir, std::wstring/*reserved specify L""*/);
	/// <summary>
	/// read the data in a reparse point
	/// </summary>
	/// <param name="hdir">A valid HANDLE with GENERIC_READ to the target directory</param>
	/// <param name="">reserved must be L""</param>
	/// <returns>Return the data of the reparse point if succeeded</returns>
	std::string GetMountPointData(HANDLE hdir, std::string/*reserved specify L""*/);
	/// <summary>
	/// read the data in a reparse point
	/// </summary>
	/// <param name="dir">The path to the directory</param>
	/// <returns>Return the data of the reparse point if succeeded</returns>
	std::wstring GetMountPointData(std::wstring dir);
	/// <summary>
	/// read the data in a reparse point
	/// </summary>
	/// <param name="dir">The path to the directory</param>
	/// <returns>Return the data of the reparse point if succeeded</returns>
	std::string GetMountPointData(std::string dir);
	/// <summary>
	/// Create a non persistent native directory in object manager
	/// </summary>
	/// <param name="dir">Path to the dir to be created</param>
	/// <returns></returns>
	HANDLE CreateObjDir(std::wstring dir);
	/// <summary>
	/// Create a non persistent native directory in object manager
	/// </summary>
	/// <param name="dir">Path to the dir to be created</param>
	/// <returns></returns>
	HANDLE CreateObjDir(std::string dir);
	/// <summary>
	/// Open HANDLE to object manager directory with MAXIMUM_ALLOWED access
	/// </summary>
	/// <param name="dir">Path to the dir to be opened</param>
	/// <returns></returns>
	HANDLE OpenObjDir(std::wstring dir);
	/// <summary>
	/// Open HANDLE to object manager directory with MAXIMUM_ALLOWED access
	/// </summary>
	/// <param name="dir">Path to the dir to be opened</param>
	/// <returns></returns>
	HANDLE OpenObjDir(std::string dir);

	/// Thanks to James Forshaw this wouldn't be possible without him
	/// I actually copied the entire class with some minor changes
	/// I am planning to to possibility to give an argument to the callback function
	/// It's easy but I still have a lot to do
	static class FileOpLock
	{
	public:

		typedef void(*UserCallback)();
		static FileOpLock* CreateLock(HANDLE h, FileOpLock::UserCallback cb);
		void WaitForLock(UINT Timeout);

		~FileOpLock();
	private:

		HANDLE g_hFile;
		OVERLAPPED g_o;
		REQUEST_OPLOCK_INPUT_BUFFER g_inputBuffer;
		REQUEST_OPLOCK_OUTPUT_BUFFER g_outputBuffer;
		HANDLE g_hLockCompleted;
		PTP_WAIT g_wait;
		UserCallback _cb;

		FileOpLock(UserCallback cb);

		static void CALLBACK WaitCallback(PTP_CALLBACK_INSTANCE Instance,
			PVOID Parameter, PTP_WAIT Wait,
			TP_WAIT_RESULT WaitResult);

		void DoWaitCallback();

		bool BeginLock(HANDLE h);

	};
	/// <summary>
	/// this function will create and wait the lock to trigger
	/// </summary>
	/// <param name="file">A path to the file to be locked, if it doesn't exist it will be created</param>
	/// <param name="cb">Call back function</param>
	/// <param name="IsDirectory">The file to be opened is it directory or not</param>
	/// <returns>return true if suceeded, if not call OpsMaster::GetLastError to will retrieve the error code</returns>
	bool CreateAndWaitLock(std::wstring file, _UserCallback cb = NULL, bool IsDirectory = false);
	/// <summary>
	/// this function will create and wait the lock to trigger
	/// </summary>
	/// <param name="file">A path to the file to be locked, if it doesn't exist it will be created</param>
	/// <param name="cb">Call back function</param>
	/// <param name="IsDirectory">The file to be opened is it directory or not</param>
	/// <returns>return true if suceeded, if not call OpsMaster::GetLastError to will retrieve the error code</returns>
	bool CreateAndWaitLock(std::string file, _UserCallback cb = NULL, bool IsDirectory = false);
	/// <summary>
	/// this function will create and wait the lock to trigger
	/// </summary>
	/// <param name="h">A valid HANDLE to the file to be locked, if it doesn't exist it will be created</param>
	/// <param name="cb">Call back function</param>
	/// <returns>return true if suceeded, if not call OpsMaster::GetLastError to will retrieve the error code</returns>
	bool CreateAndWaitLock(HANDLE h, _UserCallback cb);
	/// <summary>
	/// Create lock to the appropriate file and will return a lock_ptr
	/// </summary>
	/// <param name="h">Valid HANDLE to the file to be locked</param>
	/// <param name="cb">Call back function</param>
	/// <returns>return a valid lock_ptr if succeeded</returns>
	lock_ptr CreateLock(HANDLE h, _UserCallback cb = NULL);
	/// <summary>
	/// Create lock to the appropriate file and will return a lock_ptr
	/// </summary>
	/// <param name="file">Valid file path</param>
	/// <param name="cb">Call back function</param>
	/// <param name="IsDirectory">Is the target file directory</param>
	/// <returns>return a valid lock_ptr if succeeded</returns>
	lock_ptr CreateLock(std::wstring file, _UserCallback cb = NULL, bool IsDirectory = false);
	/// <summary>
	/// Create lock to the appropriate file and will return a lock_ptr
	/// </summary>
	/// <param name="file">Valid file path</param>
	/// <param name="cb">Call back function</param>
	/// <param name="IsDirectory">Is the target file directory</param>
	/// <returns>return a valid lock_ptr if succeeded</returns>
	lock_ptr CreateLock(std::string file, _UserCallback cb = NULL, bool IsDirectory = false);
	/// <summary>
	/// Move file to a temp directory
	/// </summary>
	/// <param name="h">A HANDLE to a file with DELETE access</param>
	/// <param name="temp_location">The path to be used to move the file this can be either USE_USER_TEMP_DIR or USE_SYSTEM_TEMP_DIR or USE_CUSTOM_TEMP_DIR</param>
	/// <param name="loc">If USE_CUSTOM_TEMP_DIR specified this one must a path to the temp location to be used</param>
	/// <returns></returns>
	bool MoveFileToTempDir(HANDLE h, DWORD temp_location = USE_USER_TEMP_DIR, std::wstring loc = L"");
	/// <summary>
	/// Move file to a temp directory
	/// </summary>
	/// <param name="file">A valid path to directory or file</param>
	/// <param name="temp_location">The path to be used to move the file this can be either USE_USER_TEMP_DIR or USE_SYSTEM_TEMP_DIR or USE_CUSTOM_TEMP_DIR</param>
	/// <param name="loc">If USE_CUSTOM_TEMP_DIR specified this one must a path to the temp location to be used</param>
	/// <param name="IsDirectory">The path specified is it a directory or file, the default is file</param>
	/// <returns></returns>
	bool MoveFileToTempDir(std::wstring file, bool IsDirectory = false, DWORD temp_location = USE_USER_TEMP_DIR, std::wstring loc = L"");
	/// <summary>
	/// Move file to a temp directory
	/// </summary>
	/// <param name="file">A valid path to directory or file</param>
	/// <param name="temp_location">The path to be used to move the file this can be either USE_USER_TEMP_DIR or USE_SYSTEM_TEMP_DIR or USE_CUSTOM_TEMP_DIR</param>
	/// <param name="loc">If USE_CUSTOM_TEMP_DIR specified this one must a path to the temp location to be used</param>
	/// <param name="IsDirectory">The path specified is it a directory or file, the default is file</param>
	/// <returns></returns>
	bool MoveFileToTempDir(std::string file, bool IsDirectory = false, DWORD temp_location = USE_USER_TEMP_DIR, std::string loc = "");
	bool DeleteChild(HANDLE root, std::wstring child);
	bool RRemoveDirectory(std::wstring dir);
	bool RRemoveDirectory(std::string dir);

	bool TerminateProcessById(DWORD process_id);
	HANDLE SetTokenDosDevice(std::wstring device_path, HANDLE htoken = GetCurrentProcessToken(), bool impersonate = false);
	HANDLE SetTokenDosDevice(std::string device_path, HANDLE htoken = GetCurrentProcessToken(), bool impersonate = false);
	std::wstring GenerateRandomStr(int lenght = 64);
};


