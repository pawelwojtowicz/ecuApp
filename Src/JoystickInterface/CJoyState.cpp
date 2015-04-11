#include "CJoyState.h"

namespace Joystick
{
CJoyState::CJoyState()
{
}

CJoyState::~CJoyState()
{
}

void CJoyState::SetAxisCount( const UInt8 count)
{
	m_axisValues.resize(count, 0);
}

void CJoyState::SetCrossCount( const UInt8 count)
{
	m_crossStates.resize(count, NONE);
}

void CJoyState::SetButtonCount( const UInt8 count)
{
	m_buttonsStates.resize(count,false);
}

const UInt8 CJoyState::GetAxisCount() const
{
	return m_axisValues.size();
}

const UInt8 CJoyState::GetCrossCount() const
{
	return m_crossStates.size();
}

const UInt8 CJoyState::GetButtonCount() const
{
	return m_buttonsStates.size();
}

const Int16 CJoyState::GetAxis( const UInt8 index ) const
{
	return m_axisValues[index];
}

const UInt8 CJoyState::GetCrossState( const UInt8 index ) const
{
	return m_crossStates[index];
}

const UInt8 CJoyState::GetButtonState( const UInt8 index ) const
{
	return m_buttonsStates[index];
}

void CJoyState::SetAxis( const UInt8 index, const UInt16 value )
{
	m_axisValues[index] = value;
}

void CJoyState::SetCrossState( const UInt8 index, const UInt8 value )
{
	m_crossStates[index] = value;
}

void CJoyState::SetButtonState( const UInt8 index, const UInt8 value )
{
	m_buttonsStates[index] = value;
}

bool CJoyState::ToByteStream()
{	
	bool retVal( true );
	UInt8 sizeOfCollection( static_cast<UInt8>(m_axisValues.size()));
	retVal = SetValue(sizeOfCollection);
	for (UInt8 count = 0 ; count < sizeOfCollection ; ++ count )
	{
		retVal &= SetValue(m_axisValues[count]);
	}
	
	sizeOfCollection = static_cast<UInt8>(m_crossStates.size()) ;
	retVal &= SetValue(sizeOfCollection);
	for (UInt8 count = 0 ; count < sizeOfCollection ; ++ count )
	{
		retVal &= SetValue(m_crossStates[count]);
	}
	
	sizeOfCollection = static_cast<UInt8>(m_buttonsStates.size() );
	retVal &= SetValue(sizeOfCollection);
	for (UInt8 count = 0 ; count < sizeOfCollection ; ++ count )
	{
		retVal &= SetValue(m_buttonsStates[count]);
	}

	return retVal;
}

bool CJoyState::FromByteStream()
{
	bool retVal( true );
	UInt8 sizeOfCollection( 0 );
	retVal = GetValue(sizeOfCollection);
	m_axisValues.resize(sizeOfCollection);
	for (UInt8 count = 0 ; count < sizeOfCollection ; ++ count )
	{
		retVal &= GetValue(m_axisValues[count]);
	}
	
	retVal = GetValue(sizeOfCollection);
	m_crossStates.resize(sizeOfCollection);
	for (UInt8 count = 0 ; count < sizeOfCollection ; ++ count )
	{
		retVal &= GetValue(m_crossStates[count]);
	}
	
	retVal = GetValue(sizeOfCollection);
	m_buttonsStates.resize(sizeOfCollection);
	for (UInt8 count = 0 ; count < sizeOfCollection ; ++ count )
	{
		retVal &= GetValue(m_buttonsStates[count]);
	}

	return retVal;
}

size_t CJoyState::GetStorageSize()
{
	size_t storageSize( 3 * sizeof(UInt8) );
	
	storageSize += m_axisValues.size() * sizeof(tAxisValues::value_type);
	storageSize += m_crossStates.size() * sizeof(tCrossStates::value_type);
	storageSize += m_buttonsStates.size() * sizeof(tButtonStates::value_type);
	
	return storageSize;
}
}
