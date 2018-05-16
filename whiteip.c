#include <types.h>




/*
	向入侵检测发送所有ip的函数
*/
static void sendAllIPsToDomain()
{
    char tempIP[255][20];
	uint16_t IpCount =0 ;
    unsigned char walltype = wall_type;
	struct RuleNode* p = listInput.list->next;

	uint8_t cmd = 14;
	while(p != NULL)
	{
		if(p->type == TYPE_IP)
		{
			strcpy(tempIP[IpCount++],p->arg1);
		}	
		p = p->next;
	}

	write(i_fd, &cmd, 1);   //发送操作命令给domain 
    write(i_fd, &walltype, 1);
	res = write(i_fd, &IpCount, 2);
	// printf("[%s],[%d] wall send ip_count result :%d\n",__FILENAME__,__LINE__,res);
	for(i = 0;i < count; i++)
	{
		len = strlen(tempIP[i]);
		// printf("[%s],[%d] wall send ip :%s\n",__FILENAME__,__LINE__,tempIP[i]);
		write(i_fd, &len, 1);
		write(i_fd, tempIP[i], len);
	}
	return;
}



/*  
    黑白名单ip更新
*/

void whitelistIPUpdated(int i_clientfd)
{
    memset(tcpPorts,0,MAX_PORTS *2);
    memset(udpPorts,0,MAX_PORTS *2);
    int i_readlen = 0;
    if ( ( i_readlen = recv( i_clientfd, &listType, 1, MSG_WAITALL) ) < 0 )
    {
        close(i_clientfd);
        return;
    }

    if ( ( i_readlen = recv( i_clientfd, &tcpPortLen, 2, MSG_WAITALL) ) < 0 )
    {
        close(i_clientfd);
        return;
    }

    if(tcpPortLen > 0)
    {
        if ( ( i_readlen = recv( i_clientfd, &tcpPorts, tcpPortLen * 2, MSG_WAITALL) ) < 0 )
        {
            close(i_clientfd);
            return;
        }
    }

        
    if ( ( i_readlen = recv( i_clientfd, &udpPortLen, 2, MSG_WAITALL) ) < 0 )
    {
        close(i_clientfd);
        return;
    }

    if(udpPortLen > 0)
    {
        if ( ( i_readlen = recv( i_clientfd, &udpPorts, udpPortLen * 2, MSG_WAITALL) ) < 0 )
        {
            close(i_clientfd);
            return;
        }
    }

    return;
    
}