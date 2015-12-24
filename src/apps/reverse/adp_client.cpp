#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "adp_client.h"
#include "pub_base.h"
#include "log.h"

/*
 *
 *  ��������: ADP�ͻ��˵Ĺ��캯��
 *
 */
AdpClient::AdpClient( char *hostIp, int hostPort, bool useBalance )
{
   m_Error = NO_ERR;
   m_Balance = useBalance;
   m_Server = -1;

   if( useBalance == true )
   {
      strcpy( m_HostIp[0], hostIp );
      m_HostPort[0] = hostPort;
   }
   else
   {
      strcpy( m_HostIp[1], hostIp );
      m_HostPort[1] = hostPort;
   }
   /*
    *  ����Apache ͨѶ��
    */
   if ( apr_pool_create(&context, NULL) != APR_SUCCESS ) 
   {
      /*
      fprintf( stderr,"create apache poll error[%s]\n", 
                       apr_strerror(stat, msgbuf, sizeof(msgbuf) ) );
      */
      LOG4C(( LOG_FATAL,"create apache poll error[%s]\n", 
                       apr_strerror(stat, msgbuf, sizeof(msgbuf) ) ));
      m_Error = ADPCLI_GEN_APR_POOL_ERR;
   }
   sock=NULL;
}

/*
 *
 *  ��������: ADP�ͻ��˵���������
 *
 */
AdpClient::~AdpClient( void )
{
   /*ֹͣ����SOCKET */
   if( sock!=NULL )
   {
      if (apr_socket_close(sock) != APR_SUCCESS)  
      {
         /*
         fprintf(stderr, "Could not close socket\n");
         */
         LOG4C((LOG_FATAL, "Could not close socket\n"));
         m_Error =ADPCLI_SHUTDOWN_SOCK_ERR;
      }
   }
   apr_pool_destroy( context );
}

/*
 *
 *  ��������: ADP�ͻ��˵ĳ�ʼ������,��δʹ�ø��ؾ��������£�û���ô�
 *
 */
int AdpClient::init( char *sysName )
{
   apr_interval_time_t timeout = apr_time_from_sec(5);
   apr_size_t length;

   /** �����ʹ��ƽ�⸺���򲻳�ʼ��ƽ�⸺�ط����� **/
   if( !m_Balance )
   {
      return 0;
   }

   stat=apr_sockaddr_info_get( &remote_sa, m_HostIp[0], 
                           APR_INET, m_HostPort[0], 0, context );
   if( stat!=APR_SUCCESS )
   {
      /*
      fprintf(stderr, "Address resolution failed for %s: %s\n",
                m_HostIp[0], apr_strerror(stat, msgbuf, sizeof(msgbuf)));
      */
      LOG4C((LOG_FATAL, "Address resolution failed for %s: %s\n",
                m_HostIp[0], apr_strerror(stat, msgbuf, sizeof(msgbuf))));
      m_Error = ADPCLI_GET_SOCKADDR_INFO_ERR;
      return -1;
   }

   stat = apr_socket_create( &sock, APR_INET, SOCK_STREAM, APR_PROTO_TCP,
                             context );
   if ( stat != APR_SUCCESS )
   {
      /*
      fprintf(stderr, "Couldn't create socket\n");
      */
      LOG4C((LOG_FATAL, "Couldn't create socket\n"));
      m_Error = ADPCLI_GEN_SOCKET_ERR;
      return -1;
   }
   stat = apr_socket_timeout_set( sock, timeout );
   if ( stat != APR_SUCCESS ) 
   {
      /*
      fprintf(stderr, "Problem setting timeout: %d\n", stat);
      */
      LOG4C((LOG_FATAL, "Problem setting timeout: %d\n", stat));
      m_Error = ADPCLI_SET_TIMEOUT_ERR;
      return -1;
   }

   stat = apr_socket_connect(sock, remote_sa);
   if (stat != APR_SUCCESS) 
   {
      /*
      fprintf(stderr, "adp_client:Could not connect: %s (%d)\n",
              apr_strerror(stat, msgbuf, sizeof(msgbuf)), stat);
      */
      LOG4C((LOG_FATAL, "adp_client:Could not connect: %s (%d)\n",
              apr_strerror(stat, msgbuf, sizeof(msgbuf)), stat));
      fflush(stderr);
      apr_socket_close(sock);
      m_Error = ADPCLI_CONNECT_ERR;
      return -1;
   }

   length = strlen( sysName );
   if ((stat = apr_socket_send(sock, sysName, &length) != APR_SUCCESS)) 
   {
      /*
      fprintf(stderr, "Problem sending data: %s (%d)\n",
          apr_strerror(stat, msgbuf, sizeof(msgbuf)), stat);
      */
      LOG4C((LOG_FATAL, "Problem sending data: %s (%d)\n",
          apr_strerror(stat, msgbuf, sizeof(msgbuf)), stat));
      apr_socket_close(sock);
      m_Error = ADPCLI_SEND_ERR;
      return -1;
   }

   char recvBuf[32];
   int i;

   memset( recvBuf, 0, sizeof(recvBuf) );

   if ((stat = apr_socket_recv(sock, recvBuf, &length)) != APR_SUCCESS) 
   {
      /*
      fprintf(stderr, "Problem receiving data: %s (%d)\n",
                apr_strerror(stat, msgbuf, sizeof(msgbuf)), stat);
      */
      LOG4C((LOG_FATAL, "Problem receiving data: %s (%d)\n",
                apr_strerror(stat, msgbuf, sizeof(msgbuf)), stat));
      apr_socket_close(sock);
      m_Error = ADPCLI_RECV_ERR;
      return -1;
   }

   /** ��ƽ�⸺�ط��������ص�ַ�� "flag(1)ip port" ��ʽ���� **/
   /** flag Ϊ 0 ��ʾ��Ϣ����                               **/
   if( recvBuf[0] != '0' )
   {
      m_Error = ADPCLI_NO_AVILAVLE_SERVER;
      return -1;
   }
   i = 1;
   while( i < sizeof(recvBuf) )
   {
      if( recvBuf[i] == ' ' )
      {
         recvBuf[i] = 0;
         i++;
         break;
      }
      i++;
   }

   strcpy( m_HostIp[1], &recvBuf[1] );
   m_HostPort[1] = atoi(&recvBuf[i]);

   return 0;
}

/*
 *
 *  ��������: ���ͽ�Ҫ���õķ���ͷ��Ϣ���������ơ������롢��ʱ
 *            �������˽��кϷ���У�� 
 *            ���з�������64λ,������20λ,��ʱ5λ ,��Ϊ�Ҷ��룬�󲹿ո�
 *            
 */
int AdpClient::sendSvcHead( char *pczSvcHead )
{
   char aczRsp[5];
   apr_size_t iLength;
   
   iLength=strlen( pczSvcHead );

   if ( (stat = apr_socket_send(sock, pczSvcHead, &iLength) != APR_SUCCESS) ) 
   {
       /*
       fprintf(stderr, "Problem sending data: %s (%d)\n",
               apr_strerror(stat, msgbuf, sizeof(msgbuf)), stat);
       */
       LOG4C((LOG_FATAL, "Problem sending data: %s (%d)\n",
               apr_strerror(stat, msgbuf, sizeof(msgbuf)), stat));
       apr_socket_close(sock);
       m_Error = ADPCLI_SEND_ERR;
       return -1;
   }

   iLength = RECV_LEN;

   memset( aczRsp, 0, sizeof(aczRsp) );

   if ((stat = apr_socket_recv(sock, aczRsp, &iLength)) != APR_SUCCESS) 
   {
       /*
       fprintf(stderr, "Problem receiving data: %s (%d)\n",
               apr_strerror(stat, msgbuf, sizeof(msgbuf)), stat);
       */
       LOG4C((LOG_FATAL, "Problem receiving data: %s (%d)\n",
               apr_strerror(stat, msgbuf, sizeof(msgbuf)), stat));
       apr_socket_close(sock);
       m_Error = ADPCLI_RECV_ERR;
       return -1;
   }
   if( memcmp( aczRsp, "0000", 4 ) != 0 )
   {
      return -1;
   }

   return 0;
}

/*
 *
 *  ��������: ����ͨѶ���ĳ���
 *            
 */
int AdpClient::sendDataSize( int iLen )
{
   /*Ϊ��ֹ��ͬϵͳ���������ͱ�ʾ��һ��,����ת��Ϊ�ַ����ٷ���*/
   char aczLen[12], aczRsp[5];
   apr_size_t iLength;

   sprintf( aczLen, "%11d", iLen );

   iLength=strlen( aczLen );
   if ((stat = apr_socket_send(sock, aczLen, &iLength) != APR_SUCCESS)) 
   {
       apr_socket_close(sock);
       /*
       fprintf(stderr, "Problem sending data: %s (%d)\n",
               apr_strerror(stat, msgbuf, sizeof(msgbuf)), stat);
       */
       LOG4C((LOG_FATAL, "Problem sending data: %s (%d)\n",
               apr_strerror(stat, msgbuf, sizeof(msgbuf)), stat));
       m_Error = ADPCLI_SEND_ERR;
       return -1;
   }

   iLength = RECV_LEN;

   memset( aczRsp, 0, sizeof(aczRsp) );

   if ((stat = apr_socket_recv(sock, aczRsp, &iLength)) != APR_SUCCESS) 
   {
       apr_socket_close(sock);
       /*
       fprintf(stderr, "Problem receiving data: %s (%d)\n",
               apr_strerror(stat, msgbuf, sizeof(msgbuf)), stat);
       */
       LOG4C((LOG_FATAL, "Problem receiving data: %s (%d)\n",
               apr_strerror(stat, msgbuf, sizeof(msgbuf)), stat));
       m_Error = ADPCLI_RECV_ERR;
       return -1;
   }
   aczRsp[4] = 0;

   if( strncmp( aczRsp, "0000", 4 ) != 0 )
   {
      m_Error = ADPCLI_DATA_LEN_OVERFLOW;
      return -1;
   }
   return 0;
}

/*
 *
 *  ��������: ����ͨѶ���ĳ���
 *            
 */
int AdpClient::recvDataSize( int iInitSize )
{
   char aczLen[13];
   int iLen;
   apr_size_t iLength;

   memset( aczLen, 0, sizeof(aczLen) );

   iLength=11;
   if ((stat = apr_socket_recv(sock, aczLen, &iLength)) != APR_SUCCESS) 
   {
      apr_socket_close(sock);
      /*
      fprintf(stderr, "Problem receiving data: %s (%d)\n",
                apr_strerror(stat, msgbuf, sizeof(msgbuf)), stat);
      */
      LOG4C((LOG_FATAL, "Problem receiving data: %s (%d)\n",
                apr_strerror(stat, msgbuf, sizeof(msgbuf)), stat));
      m_Error = ADPCLI_RECV_ERR;
      return -1;
   }
   /*��ӦΪ11λ*/
   aczLen[ 11 ]='\0';
   iLen = atoi(aczLen);

   return iLen;
}

/*
 *
 *  ��������: ���շ������ƣ������� ����SERVER��
 *            
 */
int AdpClient::call( char *svcName, char *tranCode, UDP req, 
                     UDP res, int timeout )
{
   int iBufSize, iDataLen, ret=0;
   char *pSend, sendBuf[MAX_BUFF_SIZE+1];
   char *pRecv, recvBuf[MAX_BUFF_SIZE+1];
   char funIndex[5];

   char aczSvcHead[ 100 ];

   apr_size_t iLength,iLen;

   pSend = sendBuf;
   pRecv = recvBuf;
   m_Error = NO_ERR;
   iBufSize = UDO_ValueSize( req );

   stat=apr_sockaddr_info_get( &remote_sa, m_HostIp[1],
                           APR_INET, m_HostPort[1], 0, context );
   if( stat!=APR_SUCCESS )
   {
      /*
      fprintf(stdout, "Address resolution failed for %s: %s\n",
                m_HostIp[0], apr_strerror(stat, msgbuf, sizeof(msgbuf)));
      */
      LOG4C((LOG_FATAL, "Address resolution failed for %s: %s\n",
                m_HostIp[0], apr_strerror(stat, msgbuf, sizeof(msgbuf))));
      m_Error = ADPCLI_GET_SOCKADDR_INFO_ERR;
      return -1;
   }

   stat = apr_socket_create( &sock, APR_INET, SOCK_STREAM, APR_PROTO_TCP,
                             context );
   if ( stat != APR_SUCCESS )
   {
      /*
      fprintf(stderr, "Couldn't create socket\n");
      */
      LOG4C((LOG_FATAL, "Couldn't create socket\n"));
      m_Error = ADPCLI_GEN_SOCKET_ERR;
      return -1;
   }

   stat = apr_socket_timeout_set(sock, apr_time_from_sec(timeout));
   if (stat)
   {
      /*
      fprintf(stderr, "Problem setting timeout: %d\n", stat);
      */
      LOG4C((LOG_FATAL, "Problem setting timeout: %d\n", stat));
      m_Error = ADPCLI_SET_TIMEOUT_ERR;
      return -1;
   }

   stat = apr_socket_connect(sock, remote_sa);
   if (stat != APR_SUCCESS) {
      apr_socket_close(sock);
      /*
      fprintf(stderr, "adp_client:Could not connect: %s (%d)\n",
                apr_strerror(stat, msgbuf, sizeof(msgbuf)), stat);
      */
      LOG4C((LOG_FATAL, "adp_client:Could not connect: %s (%d)\n",
                apr_strerror(stat, msgbuf, sizeof(msgbuf)), stat));
      fflush(stderr);
      m_Error = ADPCLI_CONNECT_ERR;
      return -1;
   }
   apr_socket_addr_get(&remote_sa, APR_REMOTE, sock);

   apr_sockaddr_ip_get(&remote_ipaddr, remote_sa);

   apr_socket_addr_get(&local_sa, APR_LOCAL, sock);

   apr_sockaddr_ip_get(&local_ipaddr, local_sa);

   iDataLen = UDO_ValueSize( req );
   if( iDataLen>sizeof( sendBuf ) );
   {
      /*������ʼ����ռ�����·���,�ݲ����Ƿ��䲻�ɹ������*/
      pSend=(char *)malloc( iDataLen+1 );
   }
   UDO_sprintf( req, pSend, &iDataLen );

   memset( aczSvcHead,0x00,sizeof( aczSvcHead ) );

   sprintf( aczSvcHead,"%64s%20s%5d",svcName,tranCode,timeout );

   aczSvcHead[ 89 ]='\0';


   if( sendSvcHead( aczSvcHead ) == -1 )
   {
      ret = -1;
      goto CALL_RET;
   }
   if( sendDataSize( iDataLen )== -1 )
   {
      ret = -1;
      goto CALL_RET;
   }
   iLength=iDataLen;
   iLen=0;

   /*
    *  ���ǵ�һ�η��ʹ�С���Ƶ�����(��������Ϊ128KBytes)������ѭ�����͵ķ�ʽ
    */
   do{
        iLength=iDataLen-iLen;
        if ((stat = apr_socket_send(sock, pSend+iLen, &iLength) != APR_SUCCESS))
        {
           apr_socket_close(sock);
           /*
           fprintf(stderr, "Problem sending data: %s (%d)\n",
                    apr_strerror(stat, msgbuf, sizeof(msgbuf)), stat);
           */
           LOG4C((LOG_FATAL, "Problem sending data: %s (%d)\n",
                    apr_strerror(stat, msgbuf, sizeof(msgbuf)), stat));
           m_Error = ADPCLI_SEND_ERR;
           ret = -1;
           goto CALL_RET;
      }
      iLen+=iLength;
   } while( iLen<iDataLen );

   /*������Ӧ����*/
   if( (iDataLen = recvDataSize( sizeof(recvBuf) )) == -1 )
   {
      m_Error = ADPCLI_RECV_ERR;
      ret = -1;
      goto CALL_RET;
   }
   /*���յİ����ȴ��ڳ�ʼ�������·���ռ�*/
   if( iDataLen>sizeof( recvBuf ) )
   {
      pRecv=(char *)malloc( iDataLen+1 );
   }
   iLength=iDataLen;
   iLen=0;
   do
   {
      iLength=iDataLen-iLen;
      if ((stat = apr_socket_recv(sock, recvBuf+iLen, &iLength)) != APR_SUCCESS) 
      {
          /*
          fprintf(stderr, "Problem receiving data: %s (%d)\n",
                   apr_strerror(stat, msgbuf, sizeof(msgbuf)), stat);
          */
          LOG4C((LOG_FATAL, "Problem receiving data: %s (%d)\n",
                   apr_strerror(stat, msgbuf, sizeof(msgbuf)), stat));
          apr_socket_close(sock);
          m_Error = ADPCLI_RECV_ERR;
          ret = -1;
          goto CALL_RET;
      }
      iLen+=iLength;
   } while( iLen<iDataLen );

   UDO_sscanf( recvBuf, iDataLen, res );

CALL_RET:
   if( pSend != sendBuf )
   {
      free( pSend );
   }
   if( pRecv != recvBuf )
   {
      free( pRecv );
   }

   return ret;
}

/*
 *
 * ͨѶ��װ���� ����APACHE�ײ㺯��ʵ��
 *
 */
int ADP_APR_UDOTrans( char *epczHost, int eiPort, char *req,  char *res,
                      char *epcFun, char *epcTranCode, int eiTime )
{
   int ret;

   if (apr_initialize() != APR_SUCCESS) 
   {
        /*
        fprintf(stderr, "Something went wrong\n");
        */
        LOG4C((LOG_FATAL, "Something went wrong\n"));
        return 9997;
   }
   atexit(apr_terminate);

   AdpClient client( epczHost, eiPort );

   ret = client.init( "system" );

   ret = client.call( epcFun, epcTranCode, req, res, eiTime );
   if( ret != 0 )
   {
      switch( client.getError( ) )
      {
      case 7:
      case 9:
         return 9999;
      default:
         return 9998;
      }
   }
   return 0;
}

/** ȡ������� **/
int AdpClient::getError( ) { return m_Error; }

   /** �ж��Ƿ���� **/
bool AdpClient::isAvilable( )
{
   return m_Error == NO_ERR;
}

/*
 end of file
*/