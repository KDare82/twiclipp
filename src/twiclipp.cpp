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
#include <iomanip>
#include <memory>
#include <stack>
#include "HttpSocket.h"
#include "StatusData.h"
#include "tinyxml/tinyxml.h"
#include "util/base64.h"

#define TIXML_USE_STL

int main(int argc, char * argv[]) {
  if (argc < 3)
  {
    std::cout << "Usage: " << argv[0] << " <username> <password>" << std::endl;
    exit(1);
  }

  std::auto_ptr<HttpSocket> socket(new HttpSocket());

  std::string loginData;
  loginData.append(argv[1]);
  loginData.append(":");
  loginData.append(argv[2]);

  socket->setAddress("www.twitter.com");
  //std::cout << "Socket buffer size: " << socket->getRcvBufferSize() << " bytes." << std::endl;

  std::string httpRequest;
  httpRequest.append("GET /statuses/friends_timeline.xml HTTP/1.1\n");
  httpRequest.append("Authorization: Basic ");
  httpRequest.append(base64_encode(loginData));
  httpRequest.append("\nUser-Agent: twicli\nHost: twitter.com\nAccept: */*\n\n");
  std::string httpString(socket->getHttpString(httpRequest.c_str()));
  httpString.append("\n");

  unsigned int xmlStartPosition = httpString.find("<?xml version");
  if (std::string::npos == xmlStartPosition)
  {
    std::cout << "Was not able to separate XML data." << std::endl;
    exit(1);
  }
  httpString.replace(0, xmlStartPosition, "");


  TiXmlDocument* doc = new TiXmlDocument();
  doc->Parse(httpString.c_str(),0 ,TIXML_DEFAULT_ENCODING);
  if (doc->Error())
  {
    std::cout << "An error occured while parsing XML data." << std::endl;
    exit(1);
  }
  TiXmlElement* root=doc->RootElement();

  std::stack<StatusData> twits;
  int maxLen = 0;

  TiXmlNode* currentNode = root->FirstChild("status");
  do{
    twits.push(StatusData(*currentNode));
    int currentLen = twits.top().getScreenName().length();
    if (maxLen < currentLen)
      maxLen = currentLen;
  }while(NULL != (currentNode = currentNode->NextSibling()));

  while(!twits.empty())
  {
    std::cout << std::string("\e[4;32m")
      << std::setw(maxLen+7) << std::setiosflags(std::ios::left)
      << twits.top().getScreenName() + std::string("\e[0m") + std::string(":")
      << twits.top().getText() << std::endl;
    twits.pop();
  }

  return 0;
}
