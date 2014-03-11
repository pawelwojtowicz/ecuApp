#include "CPOSIXMessageQueue.h"
#include <fcntl.h>
#include <sys/stat.h>

#include <stdio.h>
#include <errno.h>
#include <string.h>

namespace Runtime
{
CPOSIXMessageQueue::CPOSIXMessageQueue()
: m_msgQueueHandle(-1)
{
}

CPOSIXMessageQueue::~CPOSIXMessageQueue()
{
}

bool CPOSIXMessageQueue::InitializeServer( const std::string& ownQueueName )
{
  mq_attr queueAttributes;
	queueAttributes.mq_flags = 0;
	queueAttributes.mq_maxmsg = MAX_QUEUE_SIZE;
	queueAttributes.mq_msgsize = MAX_MSG_SIZE;

  // set the umask suitable to be able to open the queues by other users ( ex. Apache plugins )
  mode_t omask;
  omask = umask(0);   /* use permissions as specified */
	m_ownQueueDescriptor = mq_open( ownQueueName.c_str() , O_RDWR|O_CREAT, 0666, &queueAttributes);

  //restore the original umask
  umask(omask);
  
  if ( 0 > m_msgQueueHandle )
  {
    printf("msg queue open error [%s]\n", strerror(errno));
    return false;
  }

  return true;
}

bool CPOSIXMessageQueue::ConnectToServer( const std::string& serverQueue )
{
		mq_attr queueAttributes;
		queueAttributes.mq_flags = 0;
		queueAttributes.mq_maxmsg = MAX_QUEUE_SIZE;
		queueAttributes.mq_msgsize = MAX_MSG_SIZE;

    // set the umask suitable to be able to open the queues by other users ( ex. Apache plugins )
    mode_t omask;
    omask = umask(0);   /* use permissions as specified */

		m_msgQueueHandle = mq_open( serverQueue.c_str() , O_WRONLY|O_CREAT|O_NONBLOCK, 0666, &queueAttributes);
    
    // restore the original umasl    
    umask(omask);
    
    if ( 0 > m_msgQueueHandle )
    {
      printf("msg queue open error [%s]\n", strerror(errno));
      return false;
    }

    return true;
}

void CPOSIXMessageQueue::Shutdown()
{
  mq_close( m_msgQueueHandle );
  m_msgQueueHandle = -1;
}

bool CPOSIXMessageQueue::IsValid()
{
  return ( -1 != m_msgQueueHandle );
}
  
size_t CPOSIXMessageQueue::SendData( const Int8* buffer, size_t bufferSize)
{
}

size_t CPOSIXMessageQueue::ReceiveData( Int8* buffer, size_t bufferSize )
{
}

}
