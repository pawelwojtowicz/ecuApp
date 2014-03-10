#ifndef RUNTIME_CPOSIXMESSAGEQUEUE_H
#define RUNTIME_CPOSIXMESSAGEQUEUE_H

namespace Runtime
{
class CPOSIXMessageQueue: public IMessageQueue
{
public:
  CPOSIXMessageQueue();
  virtual ~CPOSIXMessageQueue();
  
private:
  /** implementation of Runtime::IMessageQueue */
  bool InitializeServer( const std::string& ownQueueName );
  bool ConnectToServer( const std::string& serverQueue );
  void Shutdown();
  
  bool IsValid();
  
  size_t SendData( const Int8* buffer, size_t bufferSize);
  size_t ReceiveData( Int8* buffer, size_t bufferSize );

private:
  mqd_t m_msgQueueHandle;
};
}
#endif
