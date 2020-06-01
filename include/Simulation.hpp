/**************************************************
File Name: Simulation.hpp
Author: Noman Ahmad
Purpose: CSCI 340 Home Project
Date Last Modified: 05/10/2020
Synopsis: A few function protypes used for reading
          and parsing the input from user and handling
          proper functions based on input
*///////////////////////////////////////////////////
#ifndef SIMULATION_HPP_
#define SIMULATION_HPP_

#include "../include/System.hpp"
#include <string>

// Funcions Used to Easily Handle Input From The User

// Converts a string variable to size_t type
// @param: string with ony digits
// @returns a size_t version of the number
size_t GetNumericalValue(const std::string&);
// Parses The Input and Returns appropriate command to do (0-8)
// @param: user input in format of string
// @returns a int (0-9) representing approriate command to take
// @returns -1 if invalid user input
int ParseInput(std::string&);
// Method Used to Select Approriate OS Method to Call based on Command
// @param1: Operating System Object to call commands on
// @param2: string representing the input
// @param3: int representing the command (after parsing)
void HandleCommand(OperatingSystem&, const std::string&, int);

#endif
