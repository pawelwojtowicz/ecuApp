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

bool CParameter::GetInt8( Int8& value ) const
{
	if ( eTypeInt8 == m_parameterType )
	{
		Int32 tmp( atoi( m_parameterValue.c_str() ) );
		value = static_cast<Int8>(tmp);
		return true;
	}
	return false;
}

bool CParameter::GetInt16( Int16& value ) const
{
	if ( eTypeInt16 == m_parameterType )
	{
		Int32 tmp( atoi( m_parameterValue.c_str() ) );
		value = static_cast<Int16>(tmp);
		return true;
	}
	return false;
}

bool CParameter::GetInt32( Int32& value ) const
{
	if ( eTypeInt32 == m_parameterType )
	{
		value = atoi( m_parameterValue.c_str() );
		return true;
	}
	return false;
}

bool CParameter::GetUInt8( UInt8& value ) const
{
	if ( eTypeUInt8 == m_parameterType )
	{
		UInt32 tmp( atoi( m_parameterValue.c_str() ) );
		value = static_cast<UInt8>(tmp);
		return true;
	}
	return false;
}

bool CParameter::GetUInt16( UInt16& value ) const
{
	if ( eTypeUInt16 == m_parameterType )
	{
		UInt32 tmp( atoi( m_parameterValue.c_str() ) );
		value = static_cast<UInt16>(tmp);
		return true;
	}
	return false;
}

bool CParameter::GetUInt32( UInt32& value ) const
{
	if ( eTypeUInt32 == m_parameterType )
	{
		value = atoi( m_parameterValue.c_str() );
		return true;
	}
	return false;
}

bool CParameter::GetReal32( Real32& value ) const
{
	if ( eTypeReal64 == m_parameterType )
	{
		value = atof( m_parameterValue.c_str() );
		return true;
	}
	return false;
}

bool CParameter::GetReal64( Real64& value ) const
{
	if ( eTypeReal64 == m_parameterType )
	{
		value = atof( m_parameterValue.c_str() );
		return true;
	}
	return false;
}

bool CParameter::GetString( std::string& value) const
{
	if ( eTypeString == m_parameterType )
	{
		value = m_parameterValue;
		return true;
	}
	return false;
}

}
