#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#ifdef _WIN32
#include <windows.h>
#else
#include <dirent.h>
#include <sys/stat.h>
#endif

std::string openFileDialog() {
    std::string filePath;

#ifdef _WIN32
    OPENFILENAME ofn;
    char szFile[260] = { 0 };
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.lpstrFile = szFile;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = "All Files\0*.*\0Text Files\0*.TXT\0";
    ofn.nFilterIndex = 1;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

    if (GetOpenFileName(&ofn) == TRUE) {
        filePath = ofn.lpstrFile;
    }
#else
    gtk_init(0, nullptr);
    GtkWidget* dialog = gtk_file_chooser_dialog_new("Open File", nullptr, GTK_FILE_CHOOSER_ACTION_OPEN, "Cancel", GTK_RESPONSE_CANCEL, "Open", GTK_RESPONSE_ACCEPT, nullptr);
    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        char* selectedFilePath = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        filePath = selectedFilePath;
        g_free(selectedFilePath);
    }
    gtk_widget_destroy(dialog);
#endif

    return filePath;
}

std::string openFolderDialog() {
    std::string folderPath;

#ifdef _WIN32
    BROWSEINFO bi = { 0 };
    bi.lpszTitle = "Select Folder";
    LPITEMIDLIST pidl = SHBrowseForFolder(&bi);
    if (pidl != nullptr) {
        TCHAR selectedPath[MAX_PATH];
        if (SHGetPathFromIDList(pidl, selectedPath)) {
            folderPath = selectedPath;
        }
        CoTaskMemFree(pidl);
    }
#else
    gtk_init(0, nullptr);
    GtkWidget* dialog = gtk_file_chooser_dialog_new("Select Folder", nullptr, GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER, "Cancel", GTK_RESPONSE_CANCEL, "Select", GTK_RESPONSE_ACCEPT, nullptr);
    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        char* selectedFolderPath = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        folderPath = selectedFolderPath;
        g_free(selectedFolderPath);
    }
    gtk_widget_destroy(dialog);
#endif

    return folderPath;
}

void readSingleFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (file.is_open()) {
        std::cout << "Contents of " << filePath << ":" << std::endl;
        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << std::endl;
        }
        file.close();
    } else {
        std::cerr << "Unable to open file: " << filePath << std::endl;
    }
}

void readAllFilesInFolder(const std::string& folderPath) {
#ifdef _WIN32
    // Code for reading all files in a folder on Windows
    WIN32_FIND_DATA fileData;
    HANDLE hFind = FindFirstFile((folderPath + "\\*").c_str(), &fileData);
    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            if (!(fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                std::string filePath = folderPath + "\\" + fileData.cFileName;
                readSingleFile(filePath);
            }
        } while (FindNextFile(hFind, &fileData) != 0);
        FindClose(hFind);
    }
#else
    // Code for reading all files in a folder on Unix-like systems
    DIR *dir;
    struct dirent *entry;
    if ((dir = opendir(folderPath.c_str())) != NULL) {
        while ((entry = readdir(dir)) != NULL) {
            std::string filePath = folderPath + "/" + entry->d_name;
            struct stat fileStat;
            if (stat(filePath.c_str(), &fileStat) == 0 && S_ISREG(fileStat.st_mode)) {
                readSingleFile(filePath);
            }
        }
        closedir(dir);
    }
#endif
}

int main() {
    std::string choice;
    std::cout << "Do you want to read one file (enter '1') or read all files in a folder (enter '2')? ";
    std::getline(std::cin, choice);

    if (choice == "1") {
        std::string filePath = openFileDialog();
        if (!filePath.empty()) {
            readSingleFile(filePath);
        } else {
            std::cerr << "No file selected." << std::endl;
        }
    } else if (choice == "2") {
        std::string folderPath = openFolderDialog();
        if (!folderPath.empty()) {
            readAllFilesInFolder(folderPath);
        } else {
            std::cerr << "No folder selected." << std::endl;
        }
    } else {
        std::cout << "Invalid choice. Please enter either '1' or '2'." << std::endl;
    }

    return 0;
}
