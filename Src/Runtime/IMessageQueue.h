#ifndef RUNTIME_IMESSAGEQUEUE_H
#define RUNTIME_IMESSAGEQUEUE_H
#include <GlobalTypes.h>

namespace Runtime
{
class IMessageQueue
{
public:
  IMessageQueue() {} ;
  virtual ~IMessageQueue() {} ;
  
  bool InitializeServer( const std::string& ownQueueName ) = 0;
  bool ConnectToServer( const std::string& serverQueue ) = 0;
  void Shutdown() = 0;
  
  bool IsValid() = 0;
  
  size_t SendData( const Int8* buffer, size_t bufferSize) = 0;
  size_t ReceiveData( Int8* buffer, size_t bufferSize ) = 0;
private:
  IMessageQueue( const IMessageQueue&);
  IMessageQueue& operator=( const IMessageQueue& );
};
}
#endif
