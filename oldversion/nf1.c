#include <linux/module.h>       
#include <linux/kernel.h>       
#include <linux/init.h>         

#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/skbuff.h>
#include <linux/ip.h>                  /* For IP header */

#include <linux/inet.h> /* For in_aton(); htonl(); and other related Network utility functions */ 


static struct nf_hook_ops nfho;
static char* defaultIP="192.168.001.010";

unsigned int nf_hookfn(void *priv, struct sk_buff *skb, const struct nf_hook_state *state)
{
	struct iphdr* iph = ip_hdr(skb);	
	//struct sk_buff *sb = *skb;
	iph->saddr=inet_pton(defaultIP);
	printk(KERN_INFO defaultIP "\n");
	
	//print result
	char source[16];
    	snprintf(defaultIP, 16, "%pI4", &ip_header->saddr); 
	printk(KERN_INFO source "\n");
    	return NF_ACCEPT;
}