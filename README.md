# TrafficMonitor
## This project is created for Operating System Final Project
This project has the ability to filter all incoming/outgoing traffic. <br />
This project has the ability to filter incoming/outgoing traffic from/to specific addresses. Read the specific addresses using whichever way you decided to communicate to/from the kernel module (the instructions in the list above, for instance, described using the /proc filesystem to do this). For example, when the user modifies the appropriate file in /proc, your module should re-read the file and make sure it's filtering what is currently specified. <br />
There is an entry in a log file, no more than 5MB, for each packet that is filtered. Include the address and timestamp. <br />
The filtering is implemented by having your module register netfilter hooks. Some existing modules, such as iptables, already allow we to do this (and we can use the corresponding iptables program to modify the settings), so in a sense, we're implementing similar but simplified functionality.<br />
In project report, we describe how the netfilter hooks work, what kinds of hooks there are, and how you would implement more advanced functionality, such as a stateful firewall (https://en.wikipedia.org/wiki/Stateful_firewall).<br />
Describe, with netfilter specific terms, how qw would enforce a "quota" on how much traffic a user can generate to/from a specific address.<br />

## Functiolityna
1.Monitor all Traffic<br />
2.Monitor all incoming Traffic<br />
3.Monitor all outgoing Traffic<br />
4.Monitor Traffic to a specific IP address<br />
5.Monitor Traffic from a specific IP address<br />
<br />
6.Block all Traffic<br />
7.Block all incoming Traffic<br />
8.Block all outgoing Traffic<br />
9.Block Traffic to a specific IP address<br />
10.Block Traffic from a specific IP address<br />
<br />
## User Instruction
1. Clone this project sd<br />
2. (Optional) Set target IP adress<br />
3. (Optional) Set function<br />
