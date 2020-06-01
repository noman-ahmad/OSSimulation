/**************************************************
File Name: MemoryManager.cpp
Author: Noman Ahmad
Date Last Modified: 05/31/2020
Synopsis: Implementation for a Hard Disk class,
          RandomAccessMemory class which are
          used by MemoryManager class to perform
          Memory Related Tasks To OS Processes
************************************************/

#include <iostream>
#include "../include/MemoryManager.hpp"

/*  Begin Hard Disk Implementation */
HardDisk::HardDisk(size_t DiskNumber): mDiskNumber{DiskNumber}, mpDoingIo{nullptr} {}

void HardDisk::EnqueueProcess(Process *pProcess){
  if(pProcess == nullptr){   // cant enqueue a pointer to non-existing process
  } else if(mpDoingIo == nullptr && mIoQueue.empty()){ // if the disk is empty and disk queue is empty
    mpDoingIo = pProcess;
    pProcess->ChangeStatus(USING_DEVICE); // process starts using the device
  } else{   // if already a process using drive (queue cant be full and no process using disk)
    mIoQueue.push(pProcess);
    pProcess->ChangeStatus(IN_IO_QUEUE); // process gets inserted into the disk queue
  }
}

Process* HardDisk::DequeueProcess(){
  Process *p_process;
  if(mpDoingIo == nullptr && mIoQueue.empty()){ // case if hard disk is empty
    p_process = nullptr; // return a nullptr in that case
  } else if(mIoQueue.empty()){ // if theres a process running but the i/o queue is empty
    p_process = mpDoingIo;
    mpDoingIo = nullptr;
    p_process->ChangeStatus(IDLE); // process stops using the disk
  } else { // if disk is being used and the queue is not empty
    Process *pnext_up = mIoQueue.front();
    p_process = mpDoingIo;
    mpDoingIo = pnext_up;
    mIoQueue.pop(); // next process in queue gets disk
    p_process->ChangeStatus(IDLE); // old process stops using disk
  }
  return p_process;
}

void HardDisk::ShowDisk() const{
  if(mpDoingIo == nullptr && mIoQueue.empty()){ // if the disk is empty
    return;
  } else {
    std::cout << "     HDD " << mDiskNumber << ": P" << mpDoingIo->GetPid() << std::endl;
    std::queue<Process*> tmp_queue = mIoQueue; // create local copy of the io queue
    std::cout << "     I/O " << mDiskNumber << ": ";
    if(!tmp_queue.empty()){ // if queue is empty
      while(tmp_queue.size() != 1){
        Process *p_process = tmp_queue.front();
        std::cout << "P" << p_process->GetPid() << " <- ";
        tmp_queue.pop();
      }
      std::cout << "P" << tmp_queue.front()->GetPid() << std::endl;
    } else {
      std::cout << "idle" << std::endl;
    }
  }
}
/* End Hard Disk Implementation */

/* Begin Random Access Memory Implementation */

RandomAccessMemory::RandomAccessMemory(size_t maxSize): mBeginAddress{0}, mEndAddress{maxSize - 1}
{}


size_t RandomAccessMemory::GetMaxRange() const{
  return mEndAddress + 1;
}

void RandomAccessMemory::InsertProcess(Process *pProcess){
  if(pProcess == nullptr){
    return; // rare error case (just in case)
  } else if(mRangesFilled.empty()){ // if currently no processes in RAM
    MemRange to_add = {{0, pProcess->GetSize() - 1}, pProcess};
    mRangesFilled.push_back(to_add); // start this process from 0 address
  } else if(mRangesFilled[0].first.first != mBeginAddress // if first process currently in RAM doesnt begin at address 0
    && pProcess->GetSize() <= mRangesFilled[0].first.first ){ // and the new process can fit starting from address 0
      MemRange to_add = {{0, pProcess->GetSize()-1}, pProcess};
      mRangesFilled.emplace(mRangesFilled.begin(), to_add); // insert it at the beginning
  } else { // otherwise find the right position to insert it into
    bool checker = false; // if an adequete position was found
    for(size_t i = 0; i < mRangesFilled.size() - 1; ++i){
      MemRange first_mem = mRangesFilled[i];
      MemRange second_mem = mRangesFilled[i+1];
      size_t difference = (second_mem.first.first) - (first_mem.first.second) - 1; // compare adjacent process mem addresses
      if(pProcess->GetSize() <= difference){
        MemRange to_add = {{first_mem.first.second+1, first_mem.first.second+pProcess->GetSize()}, pProcess};
        mRangesFilled.emplace(mRangesFilled.begin() + i + 1, to_add); // insert at right position
        checker = true;
        break;
      }
    }
    if(!checker){ // if no position was found between currently stored processes
      size_t begin = mRangesFilled[mRangesFilled.size() - 1].first.second + 1;
      size_t end = mRangesFilled[mRangesFilled.size()-1].first.second + pProcess->GetSize();
        if (begin > mEndAddress || end > mEndAddress) {
            return; // process can't fit into RAM
        } else { // if doesn't exceed RAM capacity (rare case)
            MemRange to_add = {{begin, end}, pProcess};
            mRangesFilled.push_back(to_add); // insert at end
        }
    }
  }
}

void RandomAccessMemory::ShowRam() const{
  std::vector<MemRange> tmp = mRangesFilled; // copy the ram vector
  if(tmp.empty()){
    std::cout << "    " << mBeginAddress << "-" << mEndAddress << " Empty" << std::endl; // all empty addresses
  } else {
    if(tmp[0].first.first != 0){
      std::cout << "      0-" << tmp[0].first.first - 1 << " Empty" << std::endl; // initial empty addresses
    }
    for(size_t i = 0; i < tmp.size(); ++i){
      MemRange current_mem_range = tmp[i];
      std::cout << "      " << current_mem_range.first.first << "-" << current_mem_range.first.second;
      std::cout << " P" << current_mem_range.second->GetPid() << std::endl; // all filled addresses
      if( (i != tmp.size() - 1) && (tmp[i].first.second+1 != tmp[i+1].first.first)){
        std::cout << "      " << tmp[i].first.second+1 << "-" << tmp[i+1].first.first-1 << " Empty " << std::endl;
      } else if( (i == tmp.size() - 1) && (tmp[i].first.second < mEndAddress)){
        std::cout << "      " << tmp[i].first.second+1 << "-" << mEndAddress << " Empty "<< std::endl;
      }
    }
  }
}

Process* RandomAccessMemory::RemoveProcess(Process *pProcess){
  Process *pto_return;
  if(pProcess == nullptr){
    pto_return = nullptr; // return nullptr if invalid process
  } else {
    for(size_t i = 0; i < mRangesFilled.size(); ++i){
      MemRange current_mem = mRangesFilled[i];
      if(current_mem.second == pProcess){ // once process found, remove from RAM
        pto_return = mRangesFilled[i].second;
        mRangesFilled.erase(mRangesFilled.begin() + i);
      }
    }
  }
  return pto_return; // return removed process
}

/* End Random Access Memory Implementation */

/* Begin Memory Manager Implementation */
/* Most of these methods call inner component (RAM and Disk) Implementation Functions */

// Constructor
MemoryManager::MemoryManager(size_t maxMem, size_t numDisks): mRam{maxMem}{
  mDisks.reserve(numDisks); // reserve enough space for all disks so push_back doesnt allocate each time
  for(size_t i = 0; i < numDisks; ++i){
    mDisks.push_back(HardDisk(i)); // calling hard disk constructor here
  }
}

void MemoryManager::InsertDiskProcess(Process *pProcess, size_t diskNum){
  if(!(pProcess == nullptr || diskNum < 0 || diskNum >= mDisks.size())){
    mDisks[diskNum].EnqueueProcess(pProcess);
  }
}

Process* MemoryManager::RemoveDiskProcess(size_t diskNum){
  if(!(diskNum < 0 || diskNum >= mDisks.size())){
    Process *p_process = mDisks[diskNum].DequeueProcess();
    return p_process;
  } else return nullptr; //error case
}

void MemoryManager::InsertToRam(Process *pProcess){
  if( (pProcess != nullptr) && (pProcess->GetSize() < mRam.GetMaxRange()) ){
    mRam.InsertProcess(pProcess); // call RAM method
  } else{ // rare error case, will probably not go this way (but inserted in case)
    return;
  }
}

Process* MemoryManager::RemoveFromRam(Process *pProcess){
  Process *pto_return;
  if(pProcess != nullptr){
    pto_return = mRam.RemoveProcess(pProcess); // call RAM method
    if(pto_return != pProcess){ // rare error case handling (just in case)
      // std::cout << "mismatching process returned from desired" << std::endl;
      pto_return = nullptr;
    }
  } else{
    pto_return = nullptr;
  }
  return pto_return;
}

void MemoryManager::ShowRam() const{
  mRam.ShowRam();
}

void MemoryManager::ShowHardDisks() const{
  for(size_t i = 0; i < mDisks.size(); ++i){
    mDisks[i].ShowDisk();
  }
}

/* End Memory Manager Implementation */
