//'Hello World' netfilter hooks example
//For any packet, we drop it, and log fact to /var/log/messages

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>

#include <linux/init.h> 
#include <linux/skbuff.h>
#include <linux/ip.h>   
#include <linux/inet.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/fs.h>      // Needed by filp
#include <asm/uaccess.h>   // Needed by segment descriptors
MODULE_LICENSE("GPL");
static struct nf_hook_ops nfhoIn;         //struct holding set of hook function options
static struct nf_hook_ops nfhoOut;  
//default setting of the project
static char* IP_file="/proc/IP";
static char* Function_file="/proc/Function";
bool accept= true;
char IP[20];
char func[20];
char buff[20];
bool drop = false;
bool monitorIn = true;
bool monitorOut = true;
bool specificIP = false;
int hooknumber=0;

//return the length of a char array
unsigned int string_Length(char* data){
	int i;
	for(i=0;data[i];i++){
	}
	return i;
}


//compare two char array, ignore blank at tail
//Eg: "1 " is equal to "1"
bool string_Com(char* s1,char* s2){
	int i;
	for(i=0;s1[i]&&s2[i];i++){
		if(s1[i]!=s2[i]) return false;
	}
	return true;
}

//read to content in file path to temp
//return 0 if not read anything
unsigned int read(char *path) {
	int i,err;
	struct file *f;
	mm_segment_t oldfs;
	unsigned long long offset;
	// Init the buffer with 0
   	for(i=0;i<sizeof(buff);i++) buff[i] =0;
	err = 0;
   	oldfs = get_fs();
    	set_fs(get_ds());
    	f= filp_open(path, O_RDONLY, 0);
    	set_fs(oldfs);
    	if(IS_ERR(f)) {
        	err = PTR_ERR(f);
		filp_close(f,NULL);
        	return 0;
    	}
    	if(f == NULL) {
		filp_close(f,NULL);
		return 0;
	}
	offset=0;
	vfs_read(f, buff, 20, &offset);
    	set_fs(oldfs);
        //printk(KERN_INFO "read %s buf:%s %d\n",path,buff,string_Length(buff));
    	filp_close(f,NULL);
	return string_Length(buff);
}

//1.Monitor all Traffic
//2.Monitor Traffic to a specific IP address
//3.Monitor Traffic from a specific IP address
//4.Block all Traffic
//5.Block Traffic to a specific IP address
//6.Block Traffic from a specific IP address
unsigned int updatePara(int i){
	
//restore to default
	drop = false;
	monitorIn = true;
	monitorOut = true;
	specificIP = false;
	hooknumber=0;
	if(i>3){ // i being greater than 3 ==> we need to block some traffic
		drop=true;
		i=i-3;
	}
	
	//now let's set the details
	if(i==1){
		//default will suffice
	return 0;
	}
	
	specificIP=true;
	if(i==2){
		monitorOut=false;
		return 0;
	}
	if(i==3){
		monitorIn=false;
		return 0;
	}
	
	printk(KERN_INFO "invaild function number received");
	return 1;
}


//print package info
unsigned int printInfo(char* source, char* dest, struct sk_buff *skb) {
    	struct timeval t;
    	struct tm broken;
    	do_gettimeofday(&t);
    	time_to_tm(t.tv_sec, 0, &broken);
	
   	printk("\nTimestamp: %d:%d:%d:%ld", broken.tm_hour, broken.tm_min,broken.tm_sec, t.tv_usec);
    	//printk(KERN_INFO "From %s to %s\n is %d", source, dest, foo);
	printk(KERN_INFO "From %s to %s\n", source, dest);
    	printk(KERN_INFO "size of data:\t%d\n", string_Length(skb->data));
    	printk(KERN_INFO "data:\t%s\n", (skb->data));
	return 0;
}


//function to be called by hook
unsigned int hook_func(void *priv, struct sk_buff *skb, const struct nf_hook_state *state)
{	int r,f;
	struct iphdr* iph;
	char source[20], dest[20];
	//update IP
	r=read(IP_file);
	if(r!=0&&!string_Com(IP,buff)){
		printk("%s update IP to %s from %s\n",KERN_INFO,buff,IP);
		snprintf(IP, 20, "%s", buff);
	}
	//update func
	f=read(Function_file);
	if(f!=0&&!string_Com(func,buff)){
		printk("%s update func to %s from %s\n",KERN_INFO,buff,func);
		snprintf(func, 20, "%s", buff);
		updatePara(func[0]-'0');
	}
	//get send and destination address of package	
	iph = ip_hdr(skb);
    	snprintf(source, 20, "%pI4", &iph->saddr);
    	snprintf(dest, 20, "%pI4", &iph->daddr);
    	//if we are monitoring traffic only
    	if (monitorIn) {
        	if (!specificIP || string_Com(IP,source)) {
            		printInfo(source,dest,skb);
            		if (drop) {
                		printk(KERN_INFO "package dropped\n\n");
                		return NF_DROP;
            		}	
        	}
    	}
    	if (monitorOut) {
        	if (!specificIP || string_Com(IP,dest)) {
            		printInfo(source,dest,skb);
            		if (drop) {
                		printk(KERN_INFO "package dropped\n\n");
                		return NF_DROP;
            		}
        	}
    	}
    	return NF_ACCEPT;
	
}

//Called when module loaded using 'insmod'
int init_module()
{	
	//set the default IP
	snprintf(IP, 20, "%s", "127.0.1.1");
	snprintf(func, 20, "%s", "1");
	printk("%s %s\n", KERN_INFO, IP);   	

	nfhoIn.hook = hook_func;                       //function to call when conditions below met
	//NF_IP_PRE_ROUTING=0
	//NF_IP_LOCAL_IN=1
	nfhoIn.hooknum = 1;            //called right after packet recieved, first hook in Netfilter
	nfhoIn.pf = PF_INET;                           //IPV4 packets
  	nfhoIn.priority = NF_IP_PRI_FIRST;             //set to highest priority over all other hook functions
  	
	nfhoOut.hook = hook_func;                       //function to call when conditions below met
	//NF_IP_POST_ROUTING=4
	//NF_IP_LOCAL_OUT=3
	nfhoOut.hooknum = 3;            //called right after packet recieved, first hook in Netfilter
	nfhoOut.pf = PF_INET;
	nfhoOut.priority = NF_IP_PRI_FIRST; 
	nf_register_hook(&nfhoIn);                     //register hook
	nf_register_hook(&nfhoOut);
  	return 0;                                    //return 0 for success
}


//Called when module unloaded using 'rmmod'
void cleanup_module()
{
  	nf_unregister_hook(&nfhoIn);                     \
	nf_unregister_hook(&nfhoOut);                    //cleanup – unregister hook
}
