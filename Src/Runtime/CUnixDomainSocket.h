#ifndef RUNTIME_CUNIXDOMAINSOCKET_H
#define RUNTIME_CUNIXDOMAINSOCKET_H

namespace Runtime
{
class CUnixDomainSocket: public IMessageQueue
{
public:
  CUnixDomainSocket();
  virtual ~CUnixDomainSocket();
  
private:
  /** implementation of Runtime::IMessageQueue */
  bool InitializeServer( const std::string& ownQueueName );
  bool ConnectToServer( const std::string& serverQueue );
  void Shutdown();
  
  bool IsValid();
  
  size_t SendData( const Int8* buffer, size_t bufferSize);
  size_t ReceiveData( Int8* buffer, size_t bufferSize );

private:
  Int32 m_socketfd;
  
  struct sockaddr_un m_address;
};
}
#endif
