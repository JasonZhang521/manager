/*
 * WinSocket.h
 *
 *  Created on: 2015Äê4ÔÂ20ÈÕ
 *      Author: euwyzbc
 */

#ifndef WINSOCKET_H_
#define WINSOCKET_H_

#include <winsock2.h>
namespace WinNetwork {

class WinSocket {
public:
  WinSocket();
  virtual ~WinSocket();
  void initialSocket() const;
  int createSocket(int af, int type, int protocol);
  int bind(int socketId, const struct sockaddr *name, int namelen);
private:
  LPWSADATA lpWSAData_;
  SOCKET socketId_;
};

} /* namespace WinNetwork */
#endif /* WINSOCKET_H_ */
