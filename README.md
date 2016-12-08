The goal of this final project is to implement a Linux Kernel Module which monitors or filters network traffic. The project could be structurally broken up to two parts, namely the kernel module and the Netfilter. Kernel modules are runnable extensions that could be loaded and unload into the kernel. For our project, kernel modules are planted to implement certain functions such as reading and writing to proc files and filtering net traffic. Netfilter is a kernel-provided framework that provides the constants, structures and functions to monitor or drop communication to different IP addresses. 

## Function
1.Monitor all Traffic<br />
2.Monitor Traffic to a specific IP address<br />
3.Monitor Traffic from a specific IP address<br />
<br />
4.Block all Traffic<br />
5.Block Traffic to a specific IP address<br />
6.Block Traffic from a specific IP address<br />
<br />
## User Instruction
1. Clone this project sd<br />
	git clone https://github.com/yya007/TrafficMonitor.git<br />
	cd TrafficMonitor<br />
2. running the project<br />
	bash build.sh<br />
3. (Optional) Set target IP adress<br />
	eg. echo "127.168.1.1" >/proc/IP;<br />
4. (Optional) Set function<br />
	eg. echo "1" >/proc/Function <br />
	NO: "1" means Monitor all Traffic, other function see Function section<br />
	Illegal input will not change current funciton.<br />
5. Check the log file<br />
	cat <br />
