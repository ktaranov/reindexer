#include "customhash.h"
#include "customlocal.h"
#include "utf8cpp/utf8.h"

namespace reindexer {

static const uint32_t seed = 3339675911UL;

inline uint32_t unaligned_load(const char* p) {
	uint32_t result;
	__builtin_memcpy(&result, p, sizeof(result));
	return result;
}

// Implementation of Murmur hash for 32-bit size_t.
uint32_t _Hash_bytes(const void* ptr, uint32_t len) {
	const uint32_t m = 0x5bd1e995;
	uint32_t hash = seed ^ len;
	const char* buf = static_cast<const char*>(ptr);

	// Mix 4 bytes at a time into the hash.
	while (len >= 4) {
		uint32_t k = unaligned_load(buf);
		k *= m;
		k ^= k >> 24;
		k *= m;
		hash *= m;
		hash ^= k;
		buf += 4;
		len -= 4;
	}

	// Handle the last few bytes of the input array.
	if (len >= 3) {
		hash ^= static_cast<unsigned char>(buf[2]) << 16;
	}
	if (len >= 2) {
		hash ^= static_cast<unsigned char>(buf[1]) << 8;
	}
	if (len >= 1) {
		hash ^= static_cast<unsigned char>(buf[0]);
		hash *= m;
	}

	// Do a few final mixes of the hash.
	hash ^= hash >> 13;

	hash *= m;

	hash ^= hash >> 15;

	return hash;
}

uint32_t _Hash_bytes_collate_ascii(const void* ptr, uint32_t len) {
	const uint32_t m = 0x5bd1e995;
	uint32_t hash = seed ^ len;
	const char* buf = static_cast<const char*>(ptr);

	// Mix 4 bytes at a time into the hash.
	while (len >= 4) {
		uint32_t k = unaligned_load(buf);
		k |= 0x40404040;

		k *= m;
		k ^= k >> 24;
		k *= m;
		hash *= m;
		hash ^= k;
		buf += 4;
		len -= 4;
	}

	// Handle the last few bytes of the input array.
	if (len >= 3) {
		hash ^= static_cast<unsigned char>(buf[2] | 0x40) << 16;
	}
	if (len >= 2) {
		hash ^= static_cast<unsigned char>(buf[1] | 0x40) << 8;
	}
	if (len >= 1) {
		hash ^= static_cast<unsigned char>(buf[0] | 0x40);
		hash *= m;
	}

	// Do a few final mixes of the hash.
	hash ^= hash >> 13;

	hash *= m;

	hash ^= hash >> 15;

	return hash;
}

uint32_t _Hash_bytes_collate_utf8(const void* ptr, uint32_t len) {
	const uint32_t m = 0x5bd1e995;
	uint32_t hash = seed ^ len;
	const char* buf = static_cast<const char*>(ptr);
	const char* begin = buf;

	while (begin + len != buf) {
		uint32_t k = utf8::unchecked::next(buf);

		k = ToLower(k);

		k *= m;
		k ^= k >> 24;
		k *= m;
		hash *= m;
		hash ^= k;
	}

	// Do a few final mixes of the hash.
	hash ^= hash >> 13;

	hash *= m;

	hash ^= hash >> 15;

	return hash;
}

uint32_t Hash(const wstring& s) noexcept { return _Hash_bytes(s.data(), s.length() * sizeof(wchar_t)); }
uint32_t collateHash(const string& s, CollateMode collateMode) noexcept {
	switch (collateMode) {
		case CollateASCII:
			return _Hash_bytes_collate_ascii(s.data(), s.length());
		case CollateUTF8:
		case CollateCustom:
			return _Hash_bytes_collate_utf8(s.data(), s.length());
		default:
			return std::hash<std::string>()(s);
	}
}

uint32_t HashTreGram(const wchar_t* ptr) noexcept { return _Hash_bytes(ptr, 3 * sizeof(wchar_t)); }
}  // namespace reindexer
