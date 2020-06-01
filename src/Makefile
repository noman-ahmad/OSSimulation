CXX = g++
CXXFLAGS = -std=c++11 -Wall -g
BUILD = ../build/
INCLUDE = ../include/
BIN = ../bin/
#compile, link, and move approriate executable and object files to directories
all: build bin
#compile main and its dependencies
main: main.cpp $(INCLUDE)System.hpp $(INCLUDE)Simulation.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp
#compile Simulation and its dependencies
Simulation: Simulation.cpp $(INCLUDE)Simulation.hpp $(INCLUDE)System.hpp
	$(CXX) $(CXXFLAGS) -c Simulation.cpp
#compile System and it's dependencies
System: System.cpp $(INCLUDE)MemoryManager.hpp $(INCLUDE)Scheduler.hpp $(INCLUDE)Process.hpp
	$(CXX) $(CXXFLAGS) -c System.cpp
#compile MemoryManager and it's dependencies
MemoryManager: MemoryManager.cpp $(INCLUDE)MemoryManager.hpp $(INCLUDE)Process.hpp
	$(CXX) $(CXXFLAGS) -c MemoryManager.cpp
#compile Scheduler and it's dependencies
Scheduler: Scheduler.cpp $(INCLUDE)Process.hpp
	$(CXX) $(CXXFLAGS) -c Scheduler.cpp
#compile Process and it's dependencies
Process: Process.cpp $(INCLUDE)Process.hpp
	$(CXX) $(CXXFLAGS) -c Process.cpp
#move all object files to build directory
move: main.o Simulation.o System.o MemoryManager.o Scheduler.o Process.o
	mv *.o $(BUILD)
#link all appropriate object files and create an executable
link: $(BUILD)main.o $(BUILD)Simulation.o $(BUILD)System.o $(BUILD)MemoryManager.o $(BUILD)Scheduler.o $(BUILD)Process.o
	$(CXX) $(CXXFLAGS) $(BUILD)*.o -o $(BUILD)run_sim
#move executable to bin directory
move2: $(BUILD)run_sim
	mv $(BUILD)run_sim $(BIN)
#build and move files
build: main Simulation System MemoryManager Scheduler Process move
#link and move executable
bin: link move2
#clean the directories
clean: $(BUILD)*.o $(BIN)run_sim
	rm $(BUILD)*.o $(BIN)run_sim
