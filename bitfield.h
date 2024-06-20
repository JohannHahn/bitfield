#include <cassert>
#include <cstdlib>
#include <cstring>
#include <math.h>
#include <inttypes.h>
typedef uint8_t byte;
typedef uint32_t u32;
typedef uint64_t u64;

inline bool byte_get_bit(byte chunk, byte bit_index) {
    assert(bit_index < 8 && "index too big");
    return (chunk >> bit_index) & (byte)1;
}

inline void byte_set_bit(byte& chunk, byte bit_index) {
    assert(bit_index < 8 && "index too big");
    chunk = (byte)1 << bit_index | chunk;
}

inline void byte_reset_bit(byte& chunk, byte bit_index) {
    assert(bit_index < 8 && "index too big");
    chunk = ~((byte)1 << bit_index) & chunk;
}

struct BitField {
public:
    BitField(u64 capacity_bytes, byte* data): data(data), capacity_bytes(capacity_bytes) {
	capacity_bits = capacity_bytes * 8;
	free_data = false;
    }
    ~BitField() {
	if(free_data) free(data);
    }
    BitField(u64 capacity_bits): capacity_bits(capacity_bits) {
	capacity_bytes = ceil((float)capacity_bits / 8.f);
	data = (byte*)malloc(capacity_bytes);
	memset(data, 0, capacity_bytes);
	free_data = true;
    }
    byte* data; 
    u64 capacity_bytes;
    u64 capacity_bits;
    bool get_bit(u64 bit_index) {
	assert(bit_index < capacity_bits && "index too big");
	u64 offset = bit_index / 8;
	byte* chunk = data + offset;
	u64 local_bit_index = bit_index - (offset * 8);
	return byte_get_bit(*chunk, local_bit_index);
    };
    void set_bit(u64 bit_index, bool value) {
	assert(bit_index < capacity_bits && "index too big");
	u64 offset = bit_index / 8;
	byte* chunk = data + offset;
	u64 local_bit_index = bit_index - (offset * 8);
	if (value) byte_set_bit(*chunk, local_bit_index);
	else byte_reset_bit(*chunk, local_bit_index); 
    };
private:
    bool free_data = false;
};
