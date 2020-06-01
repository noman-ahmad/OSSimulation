/**************************************************
File Name: Simulation.cpp
Author: Noman Ahmad
Date Last Modified: 05/31/2020
Synopsis: A few functions used for reading
          and parsing the input from user and handling
          proper functions based on input
*///////////////////////////////////////////////////
#include <iostream>
#include <string>
#include <sstream>
#include "../include/Simulation.hpp"

/**** Begin Simulation Only Methods **/

size_t GetNumericalValue(const std::string &rSubString){
  size_t to_return;
  std::stringstream finding_num(rSubString);
  finding_num >> to_return;
  return to_return;
}

int ParseInput(std::string &rInput){
  int command;
  for(size_t i = 0; i < rInput.length(); i++){
    if(rInput[i] == ' '){ // get rid of all whitespaces in the input
      rInput.erase(rInput.begin() + i);
      --i;
    }
  }
  // this all decides which # command to give to each process
  if(rInput == "Q"){
    command = 2;
  } else if(rInput == "t"){
    command = 3;
  } else if(rInput == "Sr"){
    command = 6;
  } else if(rInput == "Si"){
    command = 7;
  } else if(rInput == "Sm"){
    command = 8;
  } else if(rInput.substr(0,2) == "AR" || rInput[0] == 'A' || rInput[0] == 'd' || rInput[0] == 'D'){
    std::string rest;
    if(rInput.substr(0,2) == "AR") {
      rest = rInput.substr(2);
    } else {
      rest = rInput.substr(1);
    }
    bool all_digits = true;
    for(const char c: rest){ // checking if # in AR, A , d , and D is a valid #
      if(!isdigit(c)){
        all_digits = false;
        break;
      }
    }
    if(all_digits && rInput.substr(0,2) == "AR"){
      command = 1;
    } else if(all_digits && rInput[0] == 'A' && isdigit(rInput[1])){
      command = 0;
    } else if(all_digits && rInput[0] == 'd'){
      command = 4;
    } else if(all_digits && rInput[0] == 'D'){
      command = 5;
    } else {
      command = -1;
    }
  } else {
    command = -1;
  }
  return command;
}

// calls appropriate OS method based on given input
void HandleCommand(OperatingSystem &rSys, const std::string &rInput, int command){
  if(command <= -1 || command >= 9){
    std::cout << "Invalid Input ... please try again" << std::endl;
  } else if(command == 0){
    size_t num_of_bytes = GetNumericalValue(rInput.substr(1));
    rSys.CreateProcess(num_of_bytes, false); // A size
  } else if(command == 1){
    size_t num_of_bytes = GetNumericalValue(rInput.substr(2));
    rSys.CreateProcess(num_of_bytes, true); // AR size
  } else if(command == 2){
    rSys.EndTimeSlice(); // Q
  } else if(command == 3){
    rSys.EndProcess(); // t
  } else if(command == 4){
    size_t disk_num = GetNumericalValue(rInput.substr(1));
    rSys.RequestHardDisk(disk_num); // d num
  } else if(command == 5){
    size_t disk_num = GetNumericalValue(rInput.substr(1));
    rSys.FinishHardDisk(disk_num); // D num
  } else if(command == 6){
    rSys.ShowCpu(); // S r
  } else if(command == 7){
    rSys.ShowHardDisks(); // S i
  } else {
    rSys.ShowMemory(); // S m
  }
}

/*** End Simulation Methods **/
