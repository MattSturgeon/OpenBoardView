#ifdef _WIN32

#include "platform.h"
#include "imgui.h"
#include <stdint.h>
#include <Windows.h>
#include <Shobjidl.h>
#include <atlbase.h>
#include <assert.h>

wchar_t *utf8_to_wide(const char *s) {
	size_t len = utf8len(s);
	wchar_t *buf = (wchar_t *)malloc(sizeof(wchar_t) * (1 + len));
	mbstowcs(buf, s, len);
	buf[len] = 0;
	return buf;
}

char *wide_to_utf8(const wchar_t *s) {
	size_t len = 0;
	wchar_t c;
	for (const wchar_t *ss = s; 0 != (c = *ss); ++ss) {
		if (c < 0x80) {
			len += 1;
		} else if (c < 0x800) {
			len += 2;
		} else if (c >= 0xd800 && c < 0xdc00) {
			// surrogate pair
			len += 4;
			++ss;
		} else if (c >= 0xdc00 && c < 0xe000) {
			// pair end -- invalid sequence
			return nullptr;
		} else {
			len += 3;
		}
	}
	char *buf = (char *)malloc(1 + len);
	wcstombs(buf, s, len);
	buf[len] = 0;
	return buf;
}

char *file_as_buffer(size_t *buffer_size, const char *utf8_filename) {
	wchar_t *wide_filename = utf8_to_wide(utf8_filename);
	HANDLE file = CreateFile(wide_filename, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
	                         OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	free(wide_filename);
	if (file == INVALID_HANDLE_VALUE) {
		*buffer_size = 0;
		return nullptr;
	}

	LARGE_INTEGER filesize;
	GetFileSizeEx(file, &filesize);
	uint32_t sz = (uint32_t)filesize.QuadPart;
	assert(filesize.QuadPart == sz);
	*buffer_size = sz;

	char *buf = (char *)malloc(sz);
	uint32_t numRead = 0;
	ReadFile(file, buf, sz, (LPDWORD)&numRead, NULL);
	assert(numRead == sz);

	return buf;
}

// Not used in this branch, kept for comparison
char *old_show_file_picker() {
	OPENFILENAME ofn;
	wchar_t filename[1024];
	filename[0] = 0;
	memset(&ofn, 0, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = (HWND)ImGui::GetIO().ImeWindowHandle;
	ofn.lpstrFilter = L"BRD Files\0*.brd\0All Files\0*.*\0\0";
	ofn.lpstrFile = filename;
	ofn.nMaxFile = 1024;
	if (GetOpenFileName(&ofn)) {
		return wide_to_utf8(filename);
	}
	return nullptr;
}

char *show_file_picker() {
	char *filename = nullptr;

	HRESULT hr;
	IFileOpenDialog *pDlg;
	COMDLG_FILTERSPEC fileTypes[] = {
		// This is kinda nice
		{ L"BRD files", L"*.brd" },
		{ L"All files", L"*.*" }
	};

	// Create the file-open dialog COM object.
	hr = CoCreateInstance(CLSID_FileOpenDialog,
	                 NULL,
	                 CLSCTX_INPROC_SERVER,
	                 IID_PPV_ARGS(&pDlg));

	if ( FAILED(hr) ) return nullptr;

	// Set the dialog's caption text and the available file types.
	// NOTE: Error handling omitted here for clarity.
	pDlg->SetFileTypes ( _countof(fileTypes), fileTypes );
	pDlg->SetTitle ( L"Open File" );

	// Show the dialog.
	hr = pDlg->Show ( NULL ); // `(HWND)ImGui::GetIO().ImeWindowHandle` breaks things

	// If the user chose a file, show a message box with the
	// full path to the file.
	if ( SUCCEEDED(hr) ) {
		IShellItem *pItem;

		hr = pDlg->GetResult ( &pItem );

		if ( SUCCEEDED(hr) ) {
			PWSTR pszFilePath = NULL;

			hr = pItem->GetDisplayName ( SIGDN_FILESYSPATH, &pszFilePath );

			if ( SUCCEEDED(hr) ) {
				filename = wide_to_utf8(pszFilePath);
				CoTaskMemFree ( pszFilePath );
			}
		}
	}
	return filename;
}

unsigned char *LoadAsset(int *asset_size, int asset_id) {
	HRSRC resinfo = FindResource(NULL, MAKEINTRESOURCE(asset_id), L"Asset");
	HGLOBAL res = LoadResource(NULL, resinfo);
	*asset_size = (int)SizeofResource(NULL, resinfo);
	unsigned char *data = (unsigned char *)LockResource(res);
	UnlockResource(res);
	return data;
}

ImTextureID TextureIDs[NUM_GLOBAL_TEXTURES];

#endif // _WIN32
