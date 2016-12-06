#pragma once
#include <Global/GlobalTypes.h>
#include "ISerialPortHandler.h"
#include "IATLineConsumer.h"
#include <UCL/CThread.h>
#include <UCL/CSerialPort.h>
#include "CCircularATLineExtractor.h"
namespace ATProtocolEngine
{
class CSerialPortHandler 	: public ISerialPortHandler
													, public UCL::CThread
													, public IATLineConsumer
{
public:
	CSerialPortHandler();
	virtual ~CSerialPortHandler();

	bool Initialize();
	void Shutdown();

private:
	/** UCL::CThread*/
	void Run();

private:
	/** ISerialPortHandler */
	virtual bool SendCommand( const std::string& serializeCommand );

private:
	/** IATLineConsumer */
	virtual void NotifyATResponseExtracted( const std::string line );
	virtual void NotifyATPromptExtracted( const std::string line );

private:
	CSerialPortHandler( const CSerialPortHandler& );
	CSerialPortHandler& operator=(const CSerialPortHandler&);

	bool m_run;

	UCL::CSerialPort m_serialPort;

	CCircularATLineExtractor m_atLineExtrator;
};
}
