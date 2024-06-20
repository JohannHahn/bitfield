#include <iostream>
#include "bitfield.h"

int main() {
    BitField bit_field = BitField(100);
    for (int i = 0; i < 100; ++i) {
	bit_field.set_bit(i, 1);
    }
    for (int i = 0; i < bit_field.capacity_bits; ++i) {
	if (i % 8 == 0) std::cout << "\n\n";
	std::cout << bit_field.get_bit(i) << " ";	
    }
    std::cout << "\n";
    bit_field.set_bit(20, 0);
    for (int i = 0; i < bit_field.capacity_bits; ++i) {
	if (i % 8 == 0) std::cout << "\n\n";
	std::cout << bit_field.get_bit(i) << " ";	
    }
    std::cout << "\n";
    return 0;
}
