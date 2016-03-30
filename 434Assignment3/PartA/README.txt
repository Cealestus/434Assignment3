Matthew Eisler
mge987
11145250
CMPT 434 Assignment #3

To Run Part A

To run part A, there is only one system to be run. The makefile should first be ran to compile the file. This will
produce an executable labelled "System". At the current version of the software, this will produce warnings regarding
implicitly declared functions, although this is not affecting the functionality of the software at this time.

To start the simulation, simply type, "./System <K> <D>" into the terminal, replaing <K> and <D> with the desired values
for how many times each node should run, and how far they should travel each timestep.

The system will then run the simulation. Each node will output their saved datagram, evidenced by a line of text saying,
"NXX Hello" where the XX is replaced by that Node's number. The Nodes will display their current positions as they move
around the grid. The Hub will also display its initialization message.

The system will then automatically exit once all of the threads have completed running.

