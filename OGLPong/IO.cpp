#include "IO.h"
#include <string>

#if _WIN32
#include <Windows.h>
#endif

#define MAX_PATH 260
std::string SEIO::absPath;
void SEIO::Init() {
	// TODO: Add code here for Linux and macOS cases
	// we get the path to the EXE and then take off the EXE file itself
	// to get the path to the folder where the EXE is

#if _WIN32
	HMODULE hMod = GetModuleHandleW(NULL);
	WCHAR path[MAX_PATH];
	GetModuleFileNameW(hMod, path, MAX_PATH);
	std::wstring ps(path);
	std::string p(ps.begin(), ps.end());
#endif
	absPath = p.substr(0, p.find_last_of('\\'));
}

std::string SEIO::GetContentPath(const std::string& in) {
	// returns a string which is the content path relative to the content directory
	// as an abs path
	return absPath + "\\Assets\\" + in;
}