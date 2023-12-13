#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Directory
{
public:
    unordered_map<string, unordered_map<string, string>> dir;
};

class FileSystemMemory
{
public:
    string currentDirectory = "/";
    Directory root;

    FileSystemMemory()
    {
        currentDirectory = "/";
        root.dir[currentDirectory];
    }

    void mkdir(string directoryName)
    {
        // If we are at the root of the file system.
        string path = currentDirectory;
        if (path.size() == 1)
        {
            path += directoryName;
        }
        else
        {
            path += "/" + directoryName;
        }
        // cout << path << endl;
        root.dir[path];
        cout << "Directory created sucessfully." << endl;
    }

    void cd(string path)
    {
        if (path == ".." and currentDirectory == "/")
        {
            cout << "This is the root directory, Please try again." << endl;
            return;
        }
        else if (path == "..")
        {
            int pos = -1;
            for (int i = 0; i < currentDirectory.size(); i++)
            {
                if (currentDirectory[i] == '/')
                {
                    pos = i;
                }
            }
            if (pos == 0)
            {
                // We are back to root repository.
                currentDirectory = "/";
            }
            else
            {
                string temp = currentDirectory.substr(0, pos);
                // cout << temp << endl;
                currentDirectory = temp;
                // cout << currentDirectory << endl;
            }
        }
        else
        {
            // path is some directory name.
            if (currentDirectory.size() == 1)
            {
                auto checkString = currentDirectory + path;
                if (root.dir.find(checkString) == root.dir.end())
                {
                    cout << "No Such Directory Exists." << endl;
                    return;
                }
                else
                {
                    currentDirectory += path;
                }
            }
            else
            {
                auto checkString = currentDirectory + "/" + path;
                if (root.dir.find(checkString) == root.dir.end())
                {
                    cout << "No Such Directory Exists." << endl;
                    return;
                }
                else
                {
                    currentDirectory += "/" + path;
                }
            }
            // cout << currentDirectory << endl;
        }
    }

    void ls()
    {
        auto vec = root.dir[currentDirectory];
        if (vec.size() == 0)
        {
            cout << "No Files." << endl;
            return;
        }
        for (auto it : vec)
        {
            cout << it.first << "  ";
        }
        cout << endl;
    }

    // Display the contents of the files within the directory.
    void cat(string FileName)
    {
        if (root.dir[currentDirectory].find(FileName) == root.dir[currentDirectory].end())
        {
            cout << "No Such File Exists." << endl;
        }
        else
        {
            cout << root.dir[currentDirectory][FileName] << endl;
        }
    }

    void touch(string fileName)
    {
        root.dir[currentDirectory][fileName] = " ";
        cout << "File Created Successfully." << endl;
    }

    void echo(string fileName, string content)
    {
        if (root.dir[currentDirectory].find(fileName) == root.dir[currentDirectory].end())
        {
            cout << "No such file exists." << endl;
            return;
        }
        root.dir[currentDirectory][fileName] = content;
        cout << "Content Added Successfully." << endl;
    }

    // // // Moving a file or directory from one location to another.
    void mv(string sourcePath, string destinationPath)
    {
        bool file = false;
        int pos = -1;
        int n = sourcePath.size();
        for (int i = 0; i < n; i++)
        {
            if (sourcePath[i] == '/')
            {
                pos = i;
            }
            if (sourcePath[i] == '.')
            {
                file = true;
            }
        }

        string dirName = sourcePath.substr(0, pos);
        string fileName = sourcePath.substr(pos + 1, n);

        if (root.dir.find(dirName) == root.dir.end())
        {
            cout << "Source Directory Doesn't Exists" << endl;
            return;
        }
        if (root.dir.find(destinationPath) == root.dir.end())
        {
            cout << "Destination Directory Doesn't Exists" << endl;
            return;
        }

        // If we are shifting file from one location to another.
        if (file == true)
        {
            if (root.dir[dirName].find(fileName) == root.dir[dirName].end())
            {
                cout << "Source File Doesn't Exists" << endl;
                return;
            }
            else
            {
                pair<string, string> p;
                for (auto it : root.dir[dirName])
                {
                    if (it.first == fileName)
                    {
                        p.first = it.first;
                        p.second = it.second;
                        break;
                    }
                }
                root.dir[dirName].erase(p.first);
                root.dir[destinationPath][p.first] = p.second;
                cout << "File Moved Successfully." << endl;
            }
        }
        else
        {
            // Shifting a directory from one location to another.
            root.dir.erase(sourcePath);
            destinationPath += "/" + fileName;
            root.dir[destinationPath];
            cout << "Directory Moved Successfully." << endl;
        }
    }

    // Copying a file or directory from sourcePath to destinationPath.
    void cp(string sourcePath, string destinationPath)
    {
        bool file = false;
        int pos = -1;
        int n = sourcePath.size();
        for (int i = 0; i < n; i++)
        {
            if (sourcePath[i] == '/')
            {
                pos = i;
            }
            if (sourcePath[i] == '.')
            {
                file = true;
            }
        }

        string dirName = sourcePath.substr(0, pos);
        string fileName = sourcePath.substr(pos + 1, n);

        if (root.dir.find(dirName) == root.dir.end())
        {
            cout << "Source Directory Doesn't Exists" << endl;
            return;
        }
        if (root.dir.find(destinationPath) == root.dir.end())
        {
            cout << "Destination Directory Doesn't Exists" << endl;
            return;
        }

        if (file == true)
        {
            if (root.dir[dirName].find(fileName) == root.dir[dirName].end())
            {
                cout << "Source File Doesn't Exists" << endl;
                return;
            }
            else
            {
                string content = root.dir[dirName][fileName];
                root.dir[destinationPath][fileName] = content;
                cout << "File Copied Successfully." << endl;
            }
        }
        else
        {
            if (root.dir.find(sourcePath) == root.dir.end())
            {
                cout << "Source Directory Doesn't Exists" << endl;
                return;
            }
            else
            {
                destinationPath += "/" + fileName;
                root.dir[destinationPath];
                cout << "Directory Copied Successfully." << endl;
            }
        }
    }

    // Remove a file or repository at specific path.
    void rm(string filePath)
    {
        bool file = false;
        int pos = -1;
        int n = filePath.size();
        for (int i = 0; i < n; i++)
        {
            if (filePath[i] == '/')
            {
                pos = i;
            }
            if (filePath[i] == '.')
            {
                file = true;
            }
        }

        string dirName = filePath.substr(0, pos);
        string fileName = filePath.substr(pos + 1, n);

        if (root.dir.find(dirName) == root.dir.end())
        {
            cout << "Directory Doesn't Exists" << endl;
            return;
        }

        if (file == true)
        {
            if (root.dir[dirName].find(fileName) == root.dir[dirName].end())
            {
                cout << "No Such File Exists" << endl;
                return;
            }
            else
            {
                for (auto it : root.dir[dirName])
                {
                    if (it.first == fileName)
                    {
                        // Erasing the file in the specific directory.
                        root.dir[dirName].erase(it.first);
                        cout << "File Deleted Successfully." << endl;
                        break;
                    }
                }
            }
        }
        else
        {
            // Erasing the directory.
            if (root.dir.find(filePath) == root.dir.end())
            {
                cout << "Directory Doesn't Exists" << endl;
                return;
            }
            else
            {
                root.dir.erase(filePath);
                cout << "Directory Deleted Successfully." << endl;
            }
        }
    }
};

void helpCommands()
{
    cout << endl;

    cout << "Here are the list of commands : " << endl;

    cout << endl;
    cout << "mkdir [dirName]" << endl;
    cout << "cd [dirName]" << endl;
    cout << "ls (Make sure you are at directory path first)" << endl;
    cout << "touch [fileName] (Make sure you are at directory path first)" << endl;
    cout << "cat [fileName] (Make sure you are at directory path first)" << endl;
    cout << "echo [fileName] [text with no spaces] (Make sure you are at directory path first)" << endl;
    cout << "mv [sourcePath] [destinationPath]" << endl;
    cout << "cp [sourcePath] [destinationPath]" << endl;
    cout << "rm [filePath]" << endl;

    cout << endl;
}

int main()
{
    FileSystemMemory *fs = new FileSystemMemory();

    cout << endl;
    cout << "====================================" << endl;
    cout << "WELCOME TO THE IN-MEMORY FILE SYSTEM" << endl;
    cout << "====================================" << endl;
    cout << endl;

    cout << "Type help to check a list of commands" << endl;
    cout << endl;

    string command = "";
    string filepath_a = "";
    string filepath_b = "";

    while (1)
    {
        cout << fs->currentDirectory << endl;
        cin >> command;
        if (command == "cd")
        {
            cin >> filepath_a;
            fs->cd(filepath_a);
        }
        else if (command == "help")
        {
            helpCommands();
        }
        else if (command == "mkdir")
        {
            cin >> filepath_a;
            fs->mkdir(filepath_a);
        }
        else if (command == "ls")
        {
            fs->ls();
        }
        else if (command == "cat")
        {
            cin >> filepath_a;
            fs->cat(filepath_a);
        }
        else if (command == "touch")
        {
            cin >> filepath_a;
            fs->touch(filepath_a);
        }
        else if (command == "echo")
        {
            cin >> filepath_a >> filepath_b;
            fs->echo(filepath_a, filepath_b);
        }
        else if (command == "mv")
        {
            cin >> filepath_a >> filepath_b;
            fs->mv(filepath_a, filepath_b);
        }
        else if (command == "cp")
        {
            cin >> filepath_a >> filepath_b;
            fs->cp(filepath_a, filepath_b);
        }
        else if (command == "rm")
        {
            cin >> filepath_a;
            fs->rm(filepath_a);
        }
        else if (command == "exit")
        {
            break;
        }
        else
        {
            cout << "Invalid Command" << endl;
        }
    }

    return 0;
}