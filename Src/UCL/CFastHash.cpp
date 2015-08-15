#include "CFastHash.h"

namespace UCL
{
// Compression function for Merkle-Damgard construction.
// This function is generated using the framework provided.
#define mix(h) ({					\
			h ^= (h) >> 23;		\
			h *= 0x2127599bf4325c37ULL;	\
			h ^= (h) >> 47; })


UInt64 CFastHash::CalculateHash64(const void *buf, size_t len, UInt64 seed)
{
	const UInt64    m = 0x880355f21e6d1965ULL;
	const UInt64 *pos = (const UInt64 *)buf;
	const UInt64 *end = pos + (len / 8);
	const unsigned char *pos2;
	UInt64 h = seed ^ (len * m);
	UInt64 v;

	while (pos != end) {
		v  = *pos++;
		h ^= mix(v);
		h *= m;
	}

	pos2 = (const unsigned char*)pos;
	v = 0;

	switch (len & 7) {
	case 7: v ^= (UInt64)pos2[6] << 48;
	case 6: v ^= (UInt64)pos2[5] << 40;
	case 5: v ^= (UInt64)pos2[4] << 32;
	case 4: v ^= (UInt64)pos2[3] << 24;
	case 3: v ^= (UInt64)pos2[2] << 16;
	case 2: v ^= (UInt64)pos2[1] << 8;
	case 1: v ^= (UInt64)pos2[0];
		h ^= mix(v);
		h *= m;
	}

	return mix(h);
} 

UInt32 CFastHash::CalculateHash32(const void *buf, size_t len, UInt32 seed)
{
	// the following trick converts the 64-bit hashcode to Fermat
	// residue, which shall retain information from both the higher
	// and lower parts of hashcode.
        UInt64 h = CalculateHash64(buf, len, seed);
	return h - (h >> 32);
}

UInt64 CFastHash::CalculateHash64( const std::string& text, UInt64 seed)
{
	return CalculateHash64( text.c_str(), text.length() , seed );
}

UInt32 CFastHash::CalculateHash32( const std::string& text, UInt32 seed)
{
	return CalculateHash32( text.c_str(), text.length() , seed );
}


}
