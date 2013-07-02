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
	const Int8 GetInt8( const Int8& value ) const;
	const Int16 GetInt16( const Int16& value ) const;
	const Int32 GetInt32( const Int32& value ) const;
	const UInt8 GetUInt8( const UInt8& value ) const;
	const UInt16 GetUInt16( const UInt16& value ) const;
	const UInt32 GetUInt32( const UInt32& value ) const;
	const Real32 GetReal32( const Real32& value ) const;
	const Real64 GetReal64( const Real64& value ) const;
	const std::string GetString( const std::string& value) const;
private:
	tParameterType m_parameterType;
	
	std::string m_parameterValue;
};
}
#endif
