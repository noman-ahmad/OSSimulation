/*****************************************************
File Name: FileManager.hpp
Author: Noman Ahmad
Date Last Modified: 7/11/2020
Synopsis: Abstraction for a File Manager class,
          which incorporates files and directories
          into an operating system.
*****************************************************/

#ifndef FILE_MANAGER
#define FILE_MANAGER

#include <string>
#include <set>

class File{
private:
  std::string mFileName;
  double mFileSize;
public:
  // File Constructor
  // @param1: name of file to be created
  // @param2: size of file (in bytes) to be created
  File(std::string FileName, double FileSize);
  // Method to get the name of a file
  std::string GetFileName() const;
  // Method to get the size of a file (in bytes)
  double GetFileSize() const;
  // Method to change the name of a file
  // @param1: new name of the file
  void RenameFile(std::string NewFileName);
  // Method to change the change the size of a file
  // @param1: new size of the file
  void ResizeFile(double NewSize);
  // Method to show the file and its info to the console
  void ShowFile() const;
};

class Directory{
private:
  std::string mDirectoryName;
  Directory *mpParentDirectory;
  std::set<Directory*> mSubDirectories;
  std::set<File*> mSubFiles;
public:
  // Directory Constructor
  // @param: name of directory
  Directory(std::string DirectoryName, Directory *pParentDirectory);
  // Method to get the name of the directory
  std::string GetDirectoryName() const;
  // Method to Get Parent Directory from Current Directory
  // @returns the parent directory
  Directory* GetParentDirectory() const;
  // Method to get the total size of the directory (bytes)
  double GetDirectorySize() const;
  // Method to change the name of the Directory
  void ChangeDirectoryName(std::string NewDirectoryName);
  // Method To Add A File To The Directory
  // @param: reference to a file to add to this directory
  // @pre: file object must already exist
  bool AddFile(File *pFileToAdd);
  // Method To Remove a File From the Directory
  // @param: name of file to remove from the directory
  // @post: file will only be removed if it can be found in current directory
  File* RemoveFile(std::string FileName);
  // Method To Add a SubDirectory within current Directory
  // @param: Reference to a directory to add
  // @post: a subdirectory will not be added if it's name is not unique
  // @returns the file removed
  bool AddSubDirectory(Directory *pDirectoryToAdd);
  // Method To remove a Subdirectory within current directory
  // @param: name of sub-directory to remove
  // @post: if subdirectory cannot be found, it will not be removed
  // @returns the removed sub-directory
  Directory* RemoveSubDirectory(std::string SubDirectoryName);
  // Method to show the contents of the directory to the console
  void ShowDirectory() const;
};

class FileManager{
private:
  Directory *mpRootDirectory; 
  Directory *mpCurrentDirectory;
public:
  // Constructor for the file manager class
  // initializes an empty root directory
  FileManager();
  //
}

#endif
