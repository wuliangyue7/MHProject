//  [3/18/2015 wuliangyu]

#ifndef BytesUtils_h__
#define BytesUtils_h__

#include "../Common/MHComInc.h"

NS_BEGIN_MH

class BytesUtils
{
public:
	static MHUInt16 readUShort(MHUInt8* buff)
	{
		return (buff[1] << 8) + buff[0];
	}

	static void writeUShort(MHUInt8* buff, MHUInt16 val)
	{
		buff[0] = (MHUInt8)val;
		buff[1] = (MHUInt8)(val >> 8);
	}

	static MHUInt32 readUInt32(MHUInt8* buff)
	{
		return (buff[3] << 24) + (buff[2] << 16) + (buff[1] << 8) + buff[0];
	}

	static void writeUint32(MHUInt8* buff, MHUInt32 val)
	{
		buff[0] = (MHUInt8)val;
		buff[1] = (MHUInt8)(val >> 8);
		buff[2] = (MHUInt8)(val >> 16);
		buff[3] = (MHUInt8)(val >> 24);
	}
};


NS_END_MH
#endif // BytesUtils_h__