#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;
using namespace std;

void listFiles(const string& path) {
    cout << "\nContents of: " << path << "\n";
    for (const auto& entry : fs::directory_iterator(path)) {
        cout << (entry.is_directory() ? "[DIR] " : "[FILE] ") << entry.path().filename() << '\n';
    }
}

void viewFile(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Cannot open file." << endl;
        return;
    }
    cout << "\nContents of " << filename << "\n-----------------\n";
    string line;
    while (getline(file, line)) {
        cout << line << '\n';
    }
    file.close();
}

void createDirectory(const string& dirname) {
    if (fs::create_directory(dirname)) {
        cout << "Directory created: " << dirname << endl;
    } else {
        cerr << "Error: Failed to create directory." << endl;
    }
}

void copyFile(const string& src, const string& dest) {
    try {
        fs::copy(src, dest);
        cout << "File copied to " << dest << endl;
    } catch (fs::filesystem_error& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

void moveFile(const string& src, const string& dest) {
    try {
        fs::rename(src, dest);
        cout << "File moved to " << dest << endl;
    } catch (fs::filesystem_error& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

void deleteFile(const string& filename) {
    if (fs::remove(filename)) {
        cout << "Deleted: " << filename << endl;
    } else {
        cerr << "Error: Unable to delete." << endl;
    }
}

void renameFile(const string& oldname, const string& newname) {
    try {
        fs::rename(oldname, newname);
        cout << "Renamed to " << newname << endl;
    } catch (fs::filesystem_error& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

void showFileProperties(const string& filename) {
    try {
        auto ftime = fs::last_write_time(filename);
        auto fsize = fs::file_size(filename);
        cout << "File: " << filename << "\nSize: " << fsize << " bytes" << endl;
    } catch (fs::filesystem_error& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

int main() {
    string command, path1, path2;
    cout << "Simple File Manager - Commands: list, view, mkdir, copy, move, del, rename, props, exit" << endl;
    while (true) {
        cout << "\n> ";
        cin >> command;
        
        if (command == "list") {
            cin >> path1;
            listFiles(path1);
        } else if (command == "view") {
            cin >> path1;
            viewFile(path1);
        } else if (command == "mkdir") {
            cin >> path1;
            createDirectory(path1);
        } else if (command == "copy") {
            cin >> path1 >> path2;
            copyFile(path1, path2);
        } else if (command == "move") {
            cin >> path1 >> path2;
            moveFile(path1, path2);
        } else if (command == "del") {
            cin >> path1;
            deleteFile(path1);
        } else if (command == "rename") {
            cin >> path1 >> path2;
            renameFile(path1, path2);
        } else if (command == "props") {
            cin >> path1;
            showFileProperties(path1);
        } else if (command == "exit") {
            break;
        } else {
            cout << "Invalid command!" << endl;
        }
    }
    return 0;
}
