/**************************************************
File Name: System.hpp
Author: Noman Ahmad
Date Last Modified: 05/31/2020
Synopsis: Abstraction for a Operating System class
          which provides an interface between user
          and the memory manager and cpu Scheduling
          components.
*///////////////////////////////////////////////////
#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include "../include/Process.hpp"
#include "../include/Scheduler.hpp"
#include "../include/MemoryManager.hpp"

#include <unordered_set>

class OperatingSystem{
private:
  MemoryManager mMemManager;
  CpuScheduler mScheduler;
  std::unordered_set<Process*> mProcessTable;
public:
  // Constructor
  // passes memSize and numDisks params to Memory Manager constructor
  // initializes all the components of the OS
  OperatingSystem(size_t memSize, size_t numDisks);
  // Method Used To Create A Process
  // @param1 : number of bytes the process uses
  // @param2 : whether or not the process is an RT process or common
  void CreateProcess(size_t bytes, bool isRt);
  // Terminates a Process and releases all memory for the process
  // calls cpu scheduler to release process from the CPU
  // calls Memory Manager to release process memory from RAM
  void EndProcess();
  // Calls Memory Manager to show current state of RAM
  // shows all empty and filled ranges in RAM
  void ShowMemory() const;
  // calls cpu scheduler to show current state of CPU and ready queues
  void ShowCpu() const;
  // calls memory manager to show current state of I/O Hard Disks
  // Only shows states for active hard disks
  void ShowHardDisks() const;
  // Sends Process Currently Using CPU to the I/O Queue of HDD with
  // given number, starts doing I/O immediately if I/O queue is empty
  void RequestHardDisk(size_t diskNum);
  // Sends process doing I/O in HDD with disk number back to CPU queues
  // if cpu queue is empty, the process begins using cpu immeidately
  void FinishHardDisk(size_t diskNum);
  // Performs Round Robin on the CPU Queue
  void EndTimeSlice();
  // Destructor to clear all OS Memory for Processes that havent been removed yet
  ~OperatingSystem(); 
};

#endif
