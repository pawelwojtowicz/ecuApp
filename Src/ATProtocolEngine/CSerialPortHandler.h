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

	bool Initialize(const std::string& portName, std::string& portConfiguration);
	void RegisterATLineConsumer( IATLineConsumer* pConsumer);
	void Shutdown();

private:
	/** UCL::CThread*/
	void Run();

private:
	/** ISerialPortHandler */
	virtual bool OpenPort();
	virtual void ClosePort();

	virtual void StartProcessing();
	virtual void StopProcessing();
	virtual bool SendCommand( const std::string& serializeCommand );

private:
	/** IATLineConsumer */
	virtual void NotifyATResponseExtracted( const std::string line );
	virtual void NotifyATPromptExtracted( const std::string line );

private:
	CSerialPortHandler( const CSerialPortHandler& );
	CSerialPortHandler& operator=(const CSerialPortHandler&);

	std::string m_portName;
	std::string m_portConfiguration;

	bool m_run;

	UCL::CSerialPort m_serialPort;

	CCircularATLineExtractor m_atLineExtrator;

	IATLineConsumer* m_pATLineConsumer;
};
}
