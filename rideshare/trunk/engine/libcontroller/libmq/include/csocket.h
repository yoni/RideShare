/******************************************************************************
*  Copyright (C) 1992-2002 MapQuest.com/America Online/Time Warner, Inc.
*  All Rights Reserved.
*-----------------------------------------------------------------------------
*  This software is the confidential and proprietary information of
*  MapQuest.com and America Online ("Confidential Information"). You shall
*  not disclose such Confidential Information and shall use it only in
*  accordance with the terms of the license agreement you entered into with
*  MapQuest.com.
*-----------------------------------------------------------------------------
*  MAPQUEST.COM MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY
*  OF THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
*  THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
*  PURPOSE, OR NON-INFRINGEMENT.  MAPQUEST.COM SHALL NOT BE LIABLE FOR ANY
*  DAMAGES SUFFERED BY LICENSEE AS A RESULT OF USING, MODIFYING OR
*  DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.
*-----------------------------------------------------------------------------
*****************************************************************************/
#ifndef _CMQSOCKET_H_
// {secret}
#define _CMQSOCKET_H_

#ifndef MQWIN32

#ifndef SOCKET
#define SOCKET int
#endif

#ifndef INVALID_SOCKET
#define INVALID_SOCKET  (SOCKET)(~0)
#endif

#define SOCKET_ERROR    (-1)
#endif

#include "mq_os.h"
#include "cio.h"


/*
 * CMQSocket
 * Encapsulates WinSock functionality of reading, writing
 * and closing a connected socket.  All data receiving is
 * done in a standard blocking fashion using WinSock's
 * default blocking hook.  No asynchronous data receiving is
 * performed.
 */
class CMQSocket : public CMQIO
{
public:
   /**
    * Constructor
    */
   CMQSocket();

   /**
    * Destructor
    */
   virtual ~CMQSocket();

   CMQSocket(CMQIOFormatter& aIOFormatter);
   virtual void setFormatter(CMQIOFormatter& aIOFormatter);

   /**
    * Receives what ever data is currently held in the
    * socket up to the length specified.  This is just
    * a thin wrapper around the WinSock ::recv function.
    * @param buf  Pre-allocated buffer to receive the data into.
    * @param len  Length of the buffer or max amount of data to receive.
    * @param msg  Option flag to pass to the WinSock ::recv func.
    * @return Number of bytes received
    */
   int recv(void* buf, size_t len, int msg);

   /**
    * Closes an open socket.
    */
   void close();

   /**
    * Sets the amount of time that may pass for an
    * inactive socket when receiving data.
    * @param millisecs Time in milliseconds before the receive operation times-out.
    */
   void EnableTimeout(int millisecs) { m_iTimeout = millisecs; }

   /**
    * Gets the amount of time that may pass for an
    * inactive socket when receiving data.
    * @param millisecs Time in milliseconds before the receive operation times-out.
    */
   long GetTimeout() { return m_iTimeout; }

   /**
    * Disables timeout on receiving operations.
    */
   void DisableTimeout() { m_iTimeout = 0; }

   /**
    * Informs whether the socket receiving operation
    * timed-out.
    * @return true if the socket receiving operation timed-out, false if not.
    */
   bool TimedOut() { return m_bTimedOut; }

   /**
    * Returns the port which the socket is connected to.
    * @return The port number.
    */
   unsigned int GetPort() { return usPort; }

   /**
    * Returns the IP address of which the socket is connected to.
    * @return The IP address in numerical form.
    */
   long GetInetAddress() { return lServerAddr; }

   int ConnectTCP(char *szNewHost, char *szService);
   int ConnectTCP(char *szNewHost, unsigned short usNewPort);

protected:
   int ConnectSock(char *szNewHost, char *szService, const char *szProtocol);
   int ConnectSock(char *szNewHost, unsigned short usNewPort, const char *szProtocol);
   int ConnectSock(long lNewServerAddr, unsigned short usNewPort, const char *szProtocol);

   /**
    * Gets the specified amount of data from the socket
    * into a pre-allocated buffer.  Differs from receive
    * in the fact that it will keep trying to get all of
    * the data specified from the socket util it either
    * errors out or times-out.
    * @param buf Pre-allocated buffer to store the incoming socket data.
    * @param len The length of the data to receive into the
    *  buffer.  Make sure that this value does not
    *  exceed the size allocated for the buffer.
    * @return Number of bytes read.
    */
   virtual int llread(void* buf, size_t len);

   /**
    * write:
    * Sends the contents of the passed in buffer through
    * the socket.
    * @param buf Buffer containing the data to be sent across the socket.
    * @param len Length of the data to send held in the buffer.
    * @return Number of bytes written
    */
   virtual int llwrite(const void* buf, size_t len);

   SOCKET              fd;          // Socket descriptor
   long                lServerAddr; // Internet address of server
   unsigned int        usPort;      // Port number
   struct sockaddr_in  saddr;       // socket addr structure
   int                 saddrLen;    // length of socket addr struct

   char                szHost[ MAXHOSTNAMELEN ];     // server name

private:
   bool    m_bTimedOut;
   int     m_iTimeout;

protected:
   int     buffering(bool onOff);
   int     flush(void);

private:
   enum    {BUFFER_SIZE=4096};
   int     bufCnt;
   char    buffer[BUFFER_SIZE];
   int     useBuffering;
   int     nUnbuffered;
   int     bytesUnbuffered;
   int     nBuffered;
   int     bytesBuffered;

public:
   void ClearStatistics();
   void DumpStatistics(STD::ostream& out);
};
#endif   // _CMQSOCKET_H_


