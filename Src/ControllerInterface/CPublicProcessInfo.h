#ifndef CONTROLLER_CPUBLICPROCESSINFO_H
#define CONTROLLER_CPUBLICPROCESSINFO_H
#include <UCL/CSerializable.h>
#include "ControllerTypes.h"

#define PROCESS_COUNT 5;

namespace Controller
{

class CPublicProcessInfo : public UCL::CSerializable
{
public:
	struct ProcessInfoStruct
	{
	UInt32 ProcessID;
	std::string ProcessName;
	std::string VersionInformation;
	tProcessStatus UnitState;
	};
	
	typedef	std::vector<ProcessInfoStruct> tPublicProcessInfoList;
	typedef tPublicProcessInfoList::const_iterator tConstPublicProcessInfoIter;
	typedef tPublicProcessInfoList::iterator tPublicProcessInfoIter;
	
public:
	CPublicProcessInfo();
	virtual ~CPublicProcessInfo();

	tPublicProcessInfoList& GetProcessInfo() { return m_processInfos;};
	const tPublicProcessInfoList& GetProcessInfo() const { return m_processInfos;};

 /** Implementation of CSerializable pure virtual functions */
	virtual bool ToByteStream();
	virtual bool FromByteStream();
	virtual size_t GetStorageSize();

private:
	tPublicProcessInfoList m_processInfos;
};

}
#endif
