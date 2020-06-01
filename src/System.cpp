/**************************************************
File Name: System.hpp
Author: Noman Ahmad
Date Last Modified: 05/31/2020
Synopsis: Implementation for a Operating System class
          which provides an interface between user
          and the memory manager and cpu Scheduling
          components.
*///////////////////////////////////////////////////
#include <iostream>
#include "../include/System.hpp"

/* Begin Operating System Implementation */

// constructors called here
OperatingSystem::OperatingSystem(size_t memSize, size_t numDisks): mMemManager{memSize, numDisks}{}

// process is created and sent to the CPU Scheduler and Inserted into RAM
void OperatingSystem::CreateProcess(size_t bytes, bool isRt){
  if(!(bytes <= 0)){
    Process *p_process = new Process(bytes, isRt);
    mProcessTable.insert(p_process);
    mScheduler.EnqueueProcess(p_process);
    mMemManager.InsertToRam(p_process);
  }
}
// Calls MemoryManager function
void OperatingSystem::ShowMemory() const{
  mMemManager.ShowRam();
}
// Calls CPU Scheduler function
void OperatingSystem::ShowCpu() const{
  mScheduler.ShowCpu();
}
// Dequeue's current process from cpu and insert's into disk queue (or disk)
void OperatingSystem::RequestHardDisk(size_t diskNum){
  Process *p_process = mScheduler.DequeueProcess();
  mMemManager.InsertDiskProcess(p_process, diskNum);
}
// Dequeu's process from disk and send back to scheduler
void OperatingSystem::FinishHardDisk(size_t diskNum){
  Process *p_process = mMemManager.RemoveDiskProcess(diskNum);
  mScheduler.EnqueueProcess(p_process);
}
// Calls MemoryManager function
void OperatingSystem::ShowHardDisks() const{
  mMemManager.ShowHardDisks();
}
// Terminates Currently Running Process and Deallocates its Memory
// note: only time in code where resources are being manually freed
// processes are the only resources that are dynamically allocated so they must be freed
void OperatingSystem::EndProcess(){
  Process *p_process = mScheduler.DequeueProcess();
  if(p_process != nullptr){
    Process *p2 = mMemManager.RemoveFromRam(p_process);
    if(p2 != p_process){ // rare error case (just in case)
      std::cout << "some error occured" << std::endl;
    }
    auto itr = mProcessTable.find(p_process);
    mProcessTable.erase(itr);
    delete p_process; // deallocate memory for process
    p_process = nullptr;
  }
}

void OperatingSystem::EndTimeSlice(){
  mScheduler.RoundRobin();
}
// takes care of any left over processes at end of program
OperatingSystem::~OperatingSystem(){
  for(Process *pPtr: mProcessTable){
    delete pPtr;
    pPtr = nullptr;
  }
}

/* End Operating System Implementation */
