/*****************************************
File Name: Process.hpp
Author: Noman Ahmad
Date Last Modified: 05/31/2020
Synopsis: Abstraction for a Process class
          which defines a process with
          elements such as pid, status,
          and bytes of memory used.
*****************************************/
#ifndef PROCESS
#define PROCESS

// Enum Type to store current status of process
enum Status {
  IDLE, // i.e hasnt been sent to scheduler yet
  IN_READY_QUEUE, // waiting to use cpu
  USING_CPU, // currently using cpu
  IN_IO_QUEUE, // waiting in queue to use device
  USING_DEVICE // currently using a device
};

class Process{
private:
  size_t mPid;
  size_t mBytes;
  Status mCurrentStatus;
  bool mType; // true if rt, false if common
  static size_t msCurrentPid; // used to keep track of pid's
public:
  // Constructor used to create a process
  // @param1: number of bytes needed
  // @param2: 1 if rt, 0 if common
  Process(size_t mem, bool type);
  // Accessor Method Used to get the pid of object
  // @returns the pid of the process
  size_t GetPid() const;
  // Accessor Method Used to get the number of bytes
  // @returns the number of bytes the process uses
  size_t GetSize() const;
  // Accessor Method used to return the status of process
  // @returns the current status of the process
  Status GetStatus() const;
  // Accessor Method used to return the type of process
  // @returns 1 if is a rt process, 0 if it is a common
  bool IsRealTime() const;
  // Mutator Method to update status of the process
  // @param: new status of process
  void ChangeStatus(Status newStatus);
  // Default Destructor is okay since no dynamic memory in object
  ~Process() = default;
};

#endif
