/*****************************************
File Name: main.cpp
Author: Noman Ahmad
Date Last Modified: 05/31/2020
Synopsis: driver code that runs our
          operating system simulation
*****************************************/
#include <iostream>
#include "../include/Simulation.hpp"
#include "../include/System.hpp"

using namespace std;

// the driving main function of our simulation
int main(int argc, char* argv[]){
  if(argc != 1){ // no command line arguments accepted
    cout << "No Command Line Arguments Allowed For This Program ... exiting" << endl;
    return -1;
  } else {
    cout << "Beginning Operating System Simulation" << endl;
    size_t mem_size, number_of_disks;
    cout << "Enter Size of RAM: ";
    cin >> mem_size;
    cout << "Enter Number of Hard Disks: ";
    cin >> number_of_disks;
    cin.clear(); cin.ignore(); // clear buffer
    OperatingSystem system(mem_size, number_of_disks); // initialize the OS object
    while(1){ // runs indefinetely until user manually decides to stop (Ctrl-C)
      string input;
      cout << ">> ";
      getline(cin, input);
      int command = ParseInput(input); // Parse the Inputted Command String
      HandleCommand(system, input, command); // Handle Whatever OS Command
    }
  }
}

/* End Simulation Driver Code */ 
