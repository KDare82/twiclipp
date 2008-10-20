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

#ifndef HTTPSOCKET_H_
#define HTTPSOCKET_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

class HttpSocket
{
private:
  struct sockaddr_in srvAddr;
  int rcvBufferSize;

  long resolveHostname(const std::string hostname);

public:
  HttpSocket();
  int setAddress(const std::string hostname, const int hostport = 80);
  std::string getHttpString(const std::string requestString);
  int getRcvBufferSize();

  virtual
  ~HttpSocket();
};

#endif /* HTTPSOCKET_H_ */
