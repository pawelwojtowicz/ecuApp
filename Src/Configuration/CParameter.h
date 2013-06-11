#ifndef CONFIGURATION_CPARAMETER_H
#define CONFIGURATION_CPARAMETER_H

#include <GlobalTypes.h>

namespace Configuration
{
class CParameter
{
	typedef enum
	{
		eTypeInvalid,
		eTypeInt8,
		eTypeInt16,
		eTypeInt32,
		eTypeUInt8,
		eTypeUInt16,
		eTypeUInt32,
		eTypeReal32,
		eTypeReal64,
		eTypeString
	} tParameterType;
public:
	CParameter();
	CParameter(const std::string& type, const std::string& value);
	virtual ~CParameter();

	bool IsValid() const { return eTypeInvalid != m_parameterType; };
	bool GetInt8( Int8& value ) const;
	bool GetInt16( Int16& value ) const;
	bool GetInt32( Int32& value ) const;
	bool GetUInt8( UInt8& value ) const;
	bool GetUInt16( UInt16& value ) const;
	bool GetUInt32( UInt32& value ) const;
	bool GetReal32( Real32& value ) const;
	bool GetReal64( Real64& value ) const;
	bool GetString( std::string& value) const;
private:
	tParameterType m_parameterType;
	
	std::string m_parameterValue;
};
}
#endif
