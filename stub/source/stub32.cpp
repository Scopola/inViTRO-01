/*
	MSVC
	URLDownloadToFileA as stub with markers
	by YANiS

	This code snippet is provided 'as is' without warranty of any kind.
	No malicious uses are allowed.
*/

#include <windows.h>
#include <urlmon.h>

#define URL_MARKER			"[url_marker......................................]"
#define FILE_PATH_MARKER	"[file_marker.....................................]"

void main() {

    URLDownloadToFileA(NULL,				// LPUNKNOWN pCaller,
                       URL_MARKER,			// LPCSTR szURL,
                       FILE_PATH_MARKER,	// LPCSTR szFileName,
                       0,					// DWORD dwReserved,
                       NULL);				// LPBINDSTATUSCALLBACK lpfnCB

    MessageBoxA(NULL,
                URL_MARKER,
                FILE_PATH_MARKER,
                MB_ICONINFORMATION);


    ExitProcess(0);
}

