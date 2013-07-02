#include "CParameter.h"
#include "ConfigurationConst.h"
#include <cstdlib>

namespace Configuration
{
CParameter::CParameter()
: m_parameterType(eTypeInvalid)
{
}


CParameter::CParameter(const std::string& type, const std::string& value)
: m_parameterType(eTypeInvalid)
, m_parameterValue(value)
{
	if (0 == type.compare( sConst_ParamType_UInt8 ) )
	{
		m_parameterType = eTypeUInt8;
	}
	else if ( 0 == type.compare( sConst_ParamType_UInt16 ) )
	{
		m_parameterType = eTypeUInt16;
	}
	else if ( 0 == type.compare( sConst_ParamType_UInt32 ) )
	{
		m_parameterType = eTypeUInt32;
	}
	else if ( 0 == type.compare( sConst_ParamType_Int8 ) )
	{
		m_parameterType = eTypeInt8;
	}
	else if ( 0 == type.compare( sConst_ParamType_Int16 ) )
	{
		m_parameterType = eTypeInt16;
	}
	else if ( 0 == type.compare( sConst_ParamType_Int32 ) )
	{
		m_parameterType = eTypeInt32;
	}
	else if ( 0 == type.compare( sConst_ParamType_Real32 ) )
	{
		m_parameterType = eTypeReal32;
	}
	else if ( 0 == type.compare( sConst_ParamType_Real64 ) )
	{
		m_parameterType = eTypeReal64;
	}
	else if ( 0 == type.compare( sConst_ParamType_String ) )
	{
		m_parameterType = eTypeString;
	}



}

CParameter::~CParameter()
{
}

const Int8 CParameter::GetInt8( const Int8& value ) const
{
	if ( eTypeInt8 == m_parameterType )
	{
		Int32 tmp( atoi( m_parameterValue.c_str() ) );
		return static_cast<Int8>(tmp);
	}
	return value;
}

const Int16 CParameter::GetInt16( const Int16& value ) const
{
	if ( eTypeInt16 == m_parameterType )
	{
		Int32 tmp( atoi( m_parameterValue.c_str() ) );
		return static_cast<Int16>(tmp);
	}
	return value;
}

const Int32 CParameter::GetInt32( const Int32& value ) const
{
	if ( eTypeInt32 == m_parameterType )
	{
		return atoi( m_parameterValue.c_str() );
		
	}
	return value;
}

const UInt8 CParameter::GetUInt8( const UInt8& value ) const
{
	if ( eTypeUInt8 == m_parameterType )
	{
		UInt32 tmp( atoi( m_parameterValue.c_str() ) );
		return static_cast<UInt8>(tmp);
	}
	return value;
}

const UInt16 CParameter::GetUInt16( const UInt16& value ) const
{
	if ( eTypeUInt16 == m_parameterType )
	{
		UInt32 tmp( atoi( m_parameterValue.c_str() ) );
		return static_cast<UInt16>(tmp);
	}
	return value;
}

const UInt32 CParameter::GetUInt32( const UInt32& value ) const
{
	if ( eTypeUInt32 == m_parameterType )
	{
		return atoi( m_parameterValue.c_str() );
	}
	return value;
}

const Real32 CParameter::GetReal32(  const Real32& value ) const
{
	if ( eTypeReal32 == m_parameterType )
	{
		return atof( m_parameterValue.c_str() );
	}
	return value;
}

const Real64 CParameter::GetReal64(  const Real64& value ) const
{
	if ( eTypeReal64 == m_parameterType )
	{
		return atof( m_parameterValue.c_str() );
	}
	return value;
}

const std::string CParameter::GetString( const std::string& value) const
{
	if ( eTypeString == m_parameterType )
	{
		return m_parameterValue;
	}
	return value;
}

}
