#ifndef JOYSTICK_CJOYSTATE_H
#define JOYSTICK_CJOYSTATE_H
#include <GlobalTypes.h>
#include <UCL/CSerializable.h>

namespace Joystick
{
class CJoyState : public UCL::CSerializable
{
public:

	typedef enum
	{
		NONE 	= 0x00,
		RIGHT	= 0x01,
		DOWN	= 0x02,
		LEFT	= 0x04,
		UP		= 0x08
	} tCrossState;
	
	typedef std::vector<UInt8> 	tCrossStates;
	typedef std::vector<Int16> 	tAxisValues;
	typedef std::vector<UInt8> 	tButtonStates;
	
public:
	
	CJoyState();
	virtual ~CJoyState();
	
	void SetAxisCount( const UInt8 count);
	void SetCrossCount( const UInt8 count);
	void SetButtonCount( const UInt8 count);
	
	const UInt8 GetAxisCount() const;
	const UInt8 GetCrossCount() const;
	const UInt8 GetButtonCount() const;
	
	const Int16 GetAxis( const UInt8 index ) const ;
	const UInt8 GetCrossState( const UInt8 index ) const;
	const UInt8 GetButtonState( const UInt8 index ) const;
	
	void SetAxis( const UInt8 index, const UInt16 value ) ;
	void SetCrossState( const UInt8 index, const UInt8 value ) ;
	void SetButtonState( const UInt8 index, const UInt8 value ) ;

public:
 /** Implementation of CSerializable pure virtual functions */
	virtual bool ToByteStream();
	virtual bool FromByteStream();
	virtual size_t GetStorageSize();	

private:
	tAxisValues			 	m_axisValues;
	tCrossStates 			m_crossStates;
	tButtonStates			m_buttonsStates;
};
}
#endif
