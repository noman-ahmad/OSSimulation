/*****************************************************
File Name: FileManager.cpp
Author: Noman Ahmad
Date Last Modified: 7/11/2020
Synopsis: Implementation for a File Manager class,
          which incorporates files and directories
          into an operating system.
*****************************************************/

#include <iostream>
#include "../include/FileManager.hpp"

// Begin File Implementation
File::File(std::string FileName, double FileSize): mFileName{FileName}, mFileSize{FileSize}
{}

std::string File::GetFileName() const{
  return mFileName;
}

double File::GetFileSize() const{
  return mFileSize;
}

void File::RenameFile(std::string NewFileName){
  mFileName = NewFileName;
}

void File::ResizeFile(double NewSize){
  mFileSize = NewSize;
}

void File::ShowFile() const{
  std::cout << mFileName << ": " << mFileSize << "b" << std::endl;
}

// End File Implementation

// Begin Directory Implementation

Directory::Directory(std::string DirectoryName, Directory *pParentDirectory):
mDirectoryName{DirectoryName}, mpParentDirectory{pParentDirectory} {}

std::string Directory::GetDirectoryName() const{
  return mDirectoryName;
}

Directory* Directory::GetParentDirectory() const{
  return mpParentDirectory;
}

double Directory::GetDirectorySize() const{
  double total_size = 0;
  for(const auto& directories: mSubDirectories){
    total_size += directories->GetDirectorySize();
  }
  for(const auto& files: mSubFiles){
    total_size += files->GetFileSize();
  }
  return total_size;
}

void Directory::ChangeDirectoryName(std::string NewDirectoryName){
  mDirectoryName = NewDirectoryName;
}

bool Directory::AddFile(File *pFileToAdd){
  if(pFileToAdd != nullptr){
    for(const auto &files: mSubFiles){
      if(files->GetFileName() == pFileToAdd->GetFileName()){
        return false;
      }
    }
    mSubFiles.insert(pFileToAdd);
    return true;
  }
  return false;
}

File* Directory::RemoveFile(std::string FileName){
  File* to_return = nullptr;
  for(auto itr = mSubFiles.begin(); itr != mSubFiles.end(); ++itr){
    if((*itr)->GetFileName() == FileName){
      to_return = *mSubFiles.erase(itr);
    }
  }
  return to_return;
}

bool Directory::AddSubDirectory(Directory *pDirectoryToAdd){
  if(pDirectoryToAdd != nullptr){
    for(const auto &directories: mSubDirectories){
      if(pDirectoryToAdd->GetDirectoryName() == directories->GetDirectoryName()){
        return false;
      }
    }
    mSubDirectories.insert(pDirectoryToAdd);
  }
  return false;
}

Directory* Directory::RemoveSubDirectory(std::string SubDirectoryName){
  Directory* to_remove = nullptr;
  for(auto itr = mSubDirectories.begin(); itr != mSubDirectories.end(); ++itr){
    if((*itr)->GetDirectoryName() == SubDirectoryName){
      to_remove = *mSubDirectories.erase(itr);
    }
  }
  return to_remove;
}

void Directory::ShowDirectory() const{
  for(auto itr = mSubDirectories.begin(); itr != mSubDirectories.end(); ++itr){
    std::cout << (*itr)->GetDirectoryName() << " ";
  }
  for(auto itr = mSubFiles.begin(); itr != mSubFiles.end(); ++itr){
    std::cout << (*itr)->GetFileName() << " ";
  }
  std::cout << "\n";
}
