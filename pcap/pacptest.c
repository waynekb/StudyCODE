#include <pcap.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <bits/types.h>

// int main(int argc,char** argv){
//     char *dev,errbuf[1024];
//     pcap_t *handle;
//     struct in_addr addr;
//     struct bpf_program filter;
//     bpf_u_int32 mask,net;
//     dev=pcap_lookupdev(errbuf);

//     // handle=pcap_open_live(dev, 1514, 1, 500 ,errbuf);
//     char *nets,*msks;
//     pcap_lookupnet(dev,&net,&mask,errbuf);
//     addr.s_addr = net;
//     printf("%u\n",net);
//     nets = inet_ntoa(addr);
//     printf("network: %s\n", nets);
    
//     addr.s_addr = mask;
//     msks = inet_ntoa(addr);
//     printf("mask: %s\n", msks);
//     // net=inet_ntoa(addr);
//     // printf("net %u  mask %u\n",net,mask);
//     // printf("net %x  mask %x\n",net,mask);
//     printf("device name: %s\n",dev);
//     return 0;
// }



void printlen(char *user,struct pcap_pkthdr *pkthdr,u_char *pkt){
    printf("Jacked a packet with length of [%d]  \n", pkthdr->len);
}


#include <pcap.h>  
#include <stdio.h>  
int main()  
{  
pcap_t *handle; /* 会话句柄 */  
char *dev; /* 执行嗅探的设备 */  
char errbuf[PCAP_ERRBUF_SIZE]; /* 存储错误信息的字符串 */  
struct bpf_program filter; /* 已经编译好的过滤器 */  
char filter_app[] = "port 23"; /* 过滤表达式 */  
char* fil;
bpf_u_int32 mask; /* 所在网络的掩码 */  
bpf_u_int32 net; /* 主机的IP地址 */  
struct pcap_pkthdr header; /* 由pcap.h定义 */  
const char *packet; /* 实际的包 */  
/* Define the device */  
dev = pcap_lookupdev(errbuf);  
/* 探查设备属性 */  
pcap_lookupnet(dev, &net, &mask, errbuf);  
/* 以混杂模式打开会话 */  
handle = pcap_open_live(dev, BUFSIZ, 1, 0, errbuf);  
/* 编译并应用过滤器 */  
pcap_compile(handle, &filter, fil, 0, net);  
pcap_setfilter(handle, &filter);  
/* 截获一个包 */  
// packet = pcap_next(handle, &header);  

pcap_loop(handle,5,(pcap_handler)printlen,NULL);
/* 打印它的长度 */  
// printf("Jacked a packet with length of [%d]  \n", header.len);  
// printf("%s\n",packet);
/* 关闭会话 */  
pcap_close(handle);  
return(0);  
}  