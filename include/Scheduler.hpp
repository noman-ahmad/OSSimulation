/**************************************************
File Name: Scheduler.hpp
Author: Noman Ahmad
Date Last Modified: 05/31/2020
Synopsis: Abstraction for a CPU Scheduler
          class that uses round robin scheduling
          algorithm to give processes time
          in the Central Processing Unit.
************************************************/
#ifndef SCHEDULER
#define SCHEDULER

#include "../include/Process.hpp"
#include <queue>

class CpuScheduler{
private:
  // pointer to process currently using the CPU
  Process *mpCurrentlyUsing;
  // Real-Time Process Level of the CPU Ready Queue
  // Stores Pointers to Processes
  std::queue<Process*> mRtQueue;
  // Common Process Level of the CPU Ready Queue
  // Stores Pointers to Processes
  std::queue<Process*> mCommonQueue;
  // Method Used To Update Scheduler After an Operation
  // private because it is only necessary for the inner workings of object
  void UpdateScheduler();
public:
  CpuScheduler();
  // Method Used to Enqueue a Process into the CPU Queue
  void EnqueueProcess(Process *pProcess);
  // Method To Deqeue the Process Currently Using CPU
  // Returns a Reference to that Object
  Process *DequeueProcess();
  // Method To Perform Round Robin on the CPU Ready Queue (at end of time slice)
  void RoundRobin();
  // Method to Show both levels of the CPU Ready Queues & The CPU
  void ShowCpu() const;
};

#endif
