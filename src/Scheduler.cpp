/**************************************************
File Name: Scheduler.cpp
Author: Noman Ahmad
Purpose: CSCI 340 Home Project
Date Last Modified: 05/10/2020
Synopsis: Implementation for the CPU Scheduler
          class that uses round robin scheduling
          algorithm to give processes time
          in the Central Processing Unit.
************************************************/
#include <iostream>
#include "../include/Scheduler.hpp"
CpuScheduler::CpuScheduler(): mpCurrentlyUsing{nullptr}{}

void CpuScheduler::EnqueueProcess(Process *pProcess){
  // Store In RT Queue if RT Process
  if(pProcess->IsRealTime()){
    mRtQueue.push(pProcess);
    // std::cout << "Process Enqueued Into RT Level of Ready Queue" << std::endl;
  } else { // Store in Common Queue
    mCommonQueue.push(pProcess);
    // std::cout << "Process Enqueued Into Common Level of Ready Queue" << std::endl;
  }
  pProcess->ChangeStatus(IN_READY_QUEUE); // Update Status of Process
  UpdateScheduler(); // Update Status of Scheduler
}

Process *CpuScheduler::DequeueProcess(){
  Process *pProcess = mpCurrentlyUsing;
  mpCurrentlyUsing = nullptr; // remove currently using process
  UpdateScheduler(); // will add the next available process (if exists)
  pProcess->ChangeStatus(IDLE); // change status of process to IDLE
  // std::cout << "Process Is No Longer Using the CPU" << std::endl;
  return pProcess; // returns back to the System
}

void CpuScheduler::RoundRobin(){
  if(mpCurrentlyUsing != nullptr){ // if cpu isn't idle
    Process *pProcess = DequeueProcess(); // Dequeue Running Process
    EnqueueProcess(pProcess); // Enqueue it At the End
    // std::cout << "Round Robin Performed Successfully" << std::endl;
  } else {
    // std::cout << "CPU is idle, Round Robin cannot be performed" << std::endl;
  }
}

// STUB //
void CpuScheduler::UpdateScheduler(){
  // case one: no process using cpu (when idle or immediately after dequeue)
  if(mpCurrentlyUsing == nullptr) {
    if(!mRtQueue.empty()){ // if the RT queue is not empty
      Process *pProcess = mRtQueue.front();
      mRtQueue.pop(); // remove first process from RT queue
      mpCurrentlyUsing = pProcess;
      pProcess->ChangeStatus(USING_CPU); // process is now using CPU
    } else if(!mCommonQueue.empty()){ // RT Queue Empty but Not Common Queue
      Process *pProcess = mCommonQueue.front();
      mCommonQueue.pop(); // remove first process from Common Queue
      mpCurrentlyUsing = pProcess;
      pProcess->ChangeStatus(USING_CPU); // process is now using CPU
    } else {
    //   std::cout << "CPU is Idle and Ready Queues Are Empty, Nothing to Update" << std::endl;
    }
  } else if(!mpCurrentlyUsing->IsRealTime()){ // if currenlt using process is a common process
    if(!mRtQueue.empty()){ // if the rt queue has a process in it
      Process *pProcess = mRtQueue.front(); // get the process front of the RT Queue
      Process *pNormalProcess = mpCurrentlyUsing; // get the common process currently using CPU
      mRtQueue.pop(); // remove the rt process from queue
      mpCurrentlyUsing = pProcess;
      pProcess->ChangeStatus(USING_CPU); // rt process is now using the CPU
      std::queue<Process*> tmp_queue;
      tmp_queue.push(pNormalProcess);
      while(!mCommonQueue.empty()){
        tmp_queue.push(mCommonQueue.front());
        mCommonQueue.pop();
      }
      mCommonQueue = tmp_queue;
    }
  }
}

void CpuScheduler::ShowCpu() const{
  std::cout << "     CPU: "; // Print Process Currently Using CPU
  if(mpCurrentlyUsing == nullptr) {
    std::cout << "idle\n";
  } else {
    std::cout << "P" << mpCurrentlyUsing->GetPid() << std::endl;
  }
  std::cout << "     RT Queue: "; // Print All Processes in RT Queue
  if(mRtQueue.empty()){
    std::cout << "idle\n";
  } else {
    std::queue<Process*> TmpQueue = mRtQueue; // create a copy of rt qeueu
    while(!TmpQueue.empty()){ // algorithm to print out all processes in order
      Process *pProcess = TmpQueue.front();
      if(TmpQueue.size() != 1){
        std::cout << "P" << pProcess->GetPid() << " <- ";
      } else {
        std::cout << "P" << pProcess->GetPid() << "\n";
      }
      TmpQueue.pop();
    }
  }
  std::cout << "     Common Queue: "; // Print All Processes in Common Queue
  if(mCommonQueue.empty()){
    std::cout << "idle\n";
  } else {
    std::queue<Process*> TmpQueue = mCommonQueue; // same process as RT
    while(!TmpQueue.empty()){
      Process *pProcess = TmpQueue.front();
      if(TmpQueue.size() != 1){
        std::cout << "P" << pProcess->GetPid() << " <- ";
      } else{
        std::cout << "P" << pProcess->GetPid() << "\n";
      }
      TmpQueue.pop();
    }
  }
}


/* End Scheduling Implementation */
