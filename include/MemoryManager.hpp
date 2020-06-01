/**************************************************
File Name: MemoryManager.hpp
Author: Noman Ahmad
Date Last Modified: 05/31/2020
Synopsis: Abstraction for a Hard Disk class,
          RandomAccessMemory class which are
          used by MemoryManager class to perform
          Memory Related Tasks To OS Processes
************************************************/
#ifndef MEMORY_MANAGER
#define MEMORY_MANAGER

#include "../include/Process.hpp"
#include <queue>
#include <vector>
#include <utility>


class HardDisk{
private:
  size_t mDiskNumber;
  std::queue<Process*> mIoQueue;
  Process *mpDoingIo;
public:
  // Hard Disk Constructor
  // @param is the disk nmber to be assigned
  HardDisk(size_t DiskNumber);
  // Method To Enqueue a Process Into Hard Disk
  // @param: pointer to process to be enqueued
  void EnqueueProcess(Process *pProcess);
  // Method to Dequeue Process Currently doing I/O
  // @returns pointer to process that finished I/O
  Process* DequeueProcess();
  // Method To Show Status of the Disks
  // if no process in disk and queue is empty, will not print out anything
  void ShowDisk() const;
};


class RandomAccessMemory{
private:
  size_t mBeginAddress; // will always be 0
  size_t mEndAddress; // depends on user input, will be (max bytes - 1)
  // first pair holds a pair and a pointer to a process
  // inner pair stores begin and end addresses of that process (in RAM)
  typedef std::pair<std::pair<size_t,size_t>, Process*> MemRange;
  std::vector<MemRange> mRangesFilled;
public:
  // RAM constructor
  // @param: max amount of bytes the RAM can hold
  RandomAccessMemory(size_t maxSize);
  // Method to Insert Process Into RAM
  // @param: pointer to process to insert into RAM
  void InsertProcess(Process *pProcess);
  // Method To Remove a Process From RAM
  // @param: pointer to process to remove from RAM
  // this is used when a process terminates and no longer needs to be in RAM
  Process* RemoveProcess(Process *process);
  // Method to show current state of RAM
  // shows all processes in RAM and the addresses they currently fill
  void ShowRam() const;
  // This Destructor will be used to clear the RAM and all the ranges
  // Default okay since no dynamic memory being used here
  ~RandomAccessMemory() = default;
  // Method To Get the Max Range in RAM (end address + 1)
  // Useful for Enqueing and Dequeing Processes from RAM
  size_t GetMaxRange() const;
};


class MemoryManager{
private:
  // Array to Hold the Hard Disks in the System
  std::vector<HardDisk> mDisks;
  // RAM component of the system
  RandomAccessMemory mRam;
public:
  // Memory Manager Constructor
  // @param1: max # of bytes ram can hold
  // @param2: number of disks in the system
  MemoryManager(size_t maxMem, size_t numDisks);
  // Method To Insert Process Into Disk
  // @param1: pointer to process to insert
  // @param2: number of disk to insert to
  void InsertDiskProcess(Process *pProcess, size_t diskNum);
  // Method To Remove a Process from Disk
  // @param: number of disk to remove from
  Process* RemoveDiskProcess(size_t diskNum);
  // Method To Insert a Process Into RAM
  // @param: pointer to process to insert into RAM
  void InsertToRam(Process *pProcess);
  // Method to Remove a Process from RAM
  // @param: pointer to process to remove from RAM
  Process* RemoveFromRam(Process *pProcess);
  // Method to Show Current State of RAM
  void ShowRam() const;
  // Method To Show Current State of All Hard Disks that are in use
  void ShowHardDisks() const;
  // The Destructor will deallocate all the components of memory manager
  // and then the memory manager itself
  ~MemoryManager() = default;
};

#endif
