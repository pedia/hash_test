#ifndef ALLHASH_H__
#define ALLHASH_H__

#include <string>
#include <hash_map>

#include <boost/functional/hash.hpp>
#include <boost/crc.hpp>

#include "hash/doobs_hash.h"
#include "hash/md5.h"
#include "hash/MurmurHash1.h"
#include "hash/MurmurHash2.h"
#include "hash/MurmurHash3.h"
#include "hash/city.h"
#include "hash/citycrc.h"

// http://burtleburtle.net/bob/hash/doobs.html
uint32 doobs(const char* text, size_t length) {
  return doobs_hash(text, length);
}

#if 0
uint md5(const char* text, size_t length) {
  unsigned char digest[16];
  // MD5(digest, text, length);

	MD5Context ctx;
	MD5Init(&ctx);
	MD5Update(&ctx, (const unsigned char *)text, length);
	MD5Final(digest, &ctx);

  uint32 p = (digest[3] << 24)
    | (digest[2] << 16)
    | (digest[1] <<  8)
    | digest[0];
  return p;
}
#endif

uint32 crc32(const char* text, size_t length) {
  boost::crc_basic<32> crc(0x1021, 0xFFFF, 0, false, false);
  crc.process_bytes(text, length);
  return crc.checksum();
}


uint32 crc32_optima(const char* text, size_t length) {
  boost::crc_optimal<32, 0x1021, 0xFFFF, 0, false, false> crc;
  crc.process_bytes(text, length);
  return crc.checksum();
}

uint32 murmur1_32(const char* text, size_t length) {
  return MurmurHash1((const void *)text, length, 0);
}

uint32 murmur1a_32(const char* text, size_t length) {
	return MurmurHash1Aligned((const void *)text, length, 0);
}

uint32 murmur2_32(const char* text, size_t length) {
	return MurmurHash2((const void *)text, length, 0);
}

uint32 murmur2a_32(const char* text, size_t length) {
	return MurmurHash2A((const void *)text, length, 0);
}

uint32 murmur2n_32(const char* text, size_t length) {
	return MurmurHashNeutral2((const void *)text, length, 0);
}

uint32 murmur2na_32(const char* text, size_t length) {
	return MurmurHashAligned2((const void *)text, length, 0);
}

uint32 murmur3_32(const char* text, size_t length) {
	uint32_t ret(0);
	MurmurHash3_x86_32((const void *)text, length, 0, &ret);
	return ret;
}

uint32 boost_hash(const char* text, size_t length) {
	return boost::hash<std::string>()(std::string(text, length));
}

uint32 stdhash_32(const char* text, size_t length) {
	uint32 __h = 0;
	for (size_t i=0; i<length; ++i)
		__h = 5 * __h + text[i];
	return uint32(__h);
}


uint64 murmur2a_64(const char* text, size_t length) {
	return MurmurHash64A((const void *)text, length, 0);
}

uint64 murmur2b_64(const char* text, size_t length) {
	return MurmurHash64B((const void *)text, length, 0);
}

uint64 city_64(const char* text, size_t length) {
	return CityHash64(text, length);
}

uint64 stdhash_64(const char* text, size_t length) {
	uint64 __h = 0;
	for (size_t i=0; i<length; ++i)
		__h = 5 * __h + text[i];
	return uint64(__h);
}



#endif //ALLHASH_H__
