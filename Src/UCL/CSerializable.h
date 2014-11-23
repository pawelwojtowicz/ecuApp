#ifndef UCL_CSERIALIZABLE_H
#define UCL_CSERIALIZABLE_H
#include "GlobalTypes.h"

namespace UCL
{

class CSerializable
{
public:
	CSerializable();
	virtual ~CSerializable();
	
	size_t Serialize(Int8* buffer, size_t bufferSize);
	bool Deserialize(Int8* buffer, size_t bufferSize);
	
	virtual bool ToByteStream() = 0;
	virtual bool FromByteStream() = 0;
	
protected:
	
	bool SetValue(const UInt8& value);
	bool GetValue(UInt8& value);	
	bool SetValue(const UInt16& value);
	bool GetValue(UInt16& value);	
	bool SetValue(const UInt32& value);
	bool GetValue(UInt32& value);	
	bool SetValue(const Int8& value);
	bool GetValue(Int8& value);	
	bool SetValue(const Int16& value);
	bool GetValue(Int16& value);	
	bool SetValue(const Int32& value);
	bool GetValue(Int32& value);
	bool SetValue(const Real32& value);
	bool GetValue(Real32& value);	
	bool SetValue(const Real64& value);
	bool GetValue(Real64& value);	
	bool SetValue(const std::string& value);
	bool GetValue(std::string& value);	

private:
	template<typename TYPE> bool SetValueImpl(const TYPE& value );
	template<typename TYPE> bool GetValueImpl( TYPE& value );
		
private:
	size_t m_bufferSize;
	Int8* m_buffer;
	Int8* m_serializerPosition;

};

}
#endif
