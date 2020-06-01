/*****************************************
File Name: Process.cpp
Author: Noman Ahmad
Purpose: CSCI 340 Home Project
Date Last Modified: 05/10/2020
Synopsis: Implementation for a Process class
          which defines a process with
          elements such as pid, status,
          and bytes of memory used.
*****************************************/
#include <iostream>
#include "../include/Process.hpp"

// Initializer List Updates static variable before assigning pid
Process::Process(size_t mem, bool type): mPid{++Process::msCurrentPid}, mBytes{mem}, mType{type} {}
// Initialize static pid variable to 0
size_t Process::msCurrentPid = 0;
/* Simple returning of data members used in accessor methods */
size_t Process::GetPid() const {
  return mPid;
}

size_t Process::GetSize() const{
  return mBytes;
}

Status Process::GetStatus() const{
  return mCurrentStatus;
}

bool Process::IsRealTime() const{
  return mType;
}
/* End Accessor Method Implementation */
// Simple Assignment Used for Mutator Method Implementation
void Process::ChangeStatus(Status newStatus){
  this->mCurrentStatus = newStatus;
}


/* End Process Class Implementation */
