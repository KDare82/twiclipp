/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <cstdlib>
#include "HttpSocket.h"

HttpSocket::HttpSocket()
{
  int sock;
  int sockOptSize;

  if (0 > (sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)))
  {
    // Too bad - this is a network application!
    std::cerr << "Was not able to initialize socket. Quitting now." << std::endl;
    exit(1);
  }

  sockOptSize = sizeof(rcvBufferSize);
  if(0 > getsockopt(sock, SOL_SOCKET, SO_RCVBUF, &rcvBufferSize, (socklen_t*)&sockOptSize))
  {
    // This is not a critical error, so we'll set the buffer to 1024 byte
    rcvBufferSize = 1024;
  }

  close(sock);
}

long HttpSocket::resolveHostname(const std::string hostname)
{
  struct hostent *host;

  if(NULL == (host = gethostbyname(hostname.c_str())))
  {
    // Another critical error.
    std::cerr << "Could not resolve hostname.";
    return 0;
  }

  return *((unsigned long *) host->h_addr_list[0]);
}

int HttpSocket::getRcvBufferSize()
{
  return rcvBufferSize;
}

int HttpSocket::setAddress(const std::string hostname, const int hostport)
{
  if (0 == (srvAddr.sin_addr.s_addr = resolveHostname(hostname)))
    return -1;
  srvAddr.sin_port = htons(hostport);
  srvAddr.sin_family = AF_INET;

  return 0;
}

std::string HttpSocket::getHttpString(const std::string requestString)
{
  int sock;
  int bytes;
  char buffer[rcvBufferSize+1];

  std::string httpReturnString;

  sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (sock == -1)
  {
    std::cerr << "Socket initialization failed!" << std::endl;
    return 0;
  }

  // connect
  if(-1 == connect(sock, (struct sockaddr *)&srvAddr, sizeof(srvAddr)))
  {
    perror("connect() failed");
    std::cerr << "Connection could not be established!" << std::endl;
    return 0;
  }

  bytes=send(sock, requestString.c_str(), strlen(requestString.c_str()), 0);
  if(-1==bytes)
  {
    std::cerr << "send() failed" << std::endl;
    return 0;
  }

  while((bytes = recv(sock, buffer, rcvBufferSize, 0)) != 0){
    if (-1 == bytes)
      return 0;
    buffer[bytes] = '\0';
    httpReturnString.append(buffer);
  }
  close(sock);

  return httpReturnString;
}

HttpSocket::~HttpSocket()
{
  // TODO Auto-generated destructor stub
}
