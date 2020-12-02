Operating System Simulator: 
- This Project simulates an Operating System by using two of its main components, The CPU Scheduler and 
  the Memory Manager. These will perform various operations on different processes that enter the system. 
- The System can have large RAM sizes and many Input/Output Devices (HDDs) as per user desired input. 
- The System performs First-Fit Contiguous Memory Allocation Scheme. 
- The System uses Round-Robin CPU Scheduling Algorithm. 
- Below are instructions to compile and run this simulation. 

Compiling Foreword: Please Use Unix/Linux/Mac Operating Systems (or similar) that support g++11 and make 

Instructions On Compiling Program: 
1. make all  
2. ./bin/run_sim (must be done inside current directory, same as README.txt)
3. program executes 
4. remove object files and executables using make clean (if needed)

Instructions on Running Program:
1. Give desired RAM and Hard Disks to be simulated as asked (max size depends on size_t limit on architechture)
2. Start Inputting A Series of Following Commands To Simulate the OS (capitals matter): 
	a. A size (where size is a value within size_t ranges): create a new common process that needs to use "size" memory.
        b. AR size (where size is a value within size_t ranges): create a new real-time process that needs to use "size" memory. 
        c. Q : end time slice for currently running process. 
        d. t : terminate the current running process.
        e. d number (where number is a value within size_t ranges): The process that currently uses the 
                    CPU requests to use the Hard Disk that is numbered "number". 
        f. D number (where number is a value within size_t ranges): The process currently in Hard Disk 
                    numbered "number" has finished its work. 
        g. S r : show current state of CPU as well as both level's of the Ready Queue's (Common and RT).
        h. S i : show which processes are using which hard disks (no output if hard disk is idle). 
        i. S m : show's the current state of Memory and which Process's take up which ranges of addresses.
3. ctrl+C to end program (runs indefinetely as you need it to). 

Quick Guide On Project File Structure: 
 - bin     : will contain the executable "run_sim" once all object files have been linked (part of make all)
 - build   : will contain all object files once the source code has been compiled (part of make all)
 - include : contains header files for all the source files used in this project (class interfaces and function declerations)	
 - src     : contains all source files for this project (implementation for class functions and global methods)
 - docs    : contains a few short docs on sources and explanations for coding style and design choices 

Extra Notes: 
- Some Documentation can be found in the docs directory 
  - Includes explanations for deisgn and implementation choices made for this project.  
  - Includes docs and sources to coding style guides used throughout this project. 
  - Note: all source and header files have been commented thoroughly on their own. 

Future Plans: 
- Implement File Management System

Created By Noman Ahmad  
Programming Langauage Used: C++11 



