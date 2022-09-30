#include <iostream>
#include <vector>
#include <math.h>

typedef union float_32{
        float   floating_value_in_32_bits;
        int     arg_32;
        struct  sign_exp_mantissa{
                unsigned  mantissa:23;
                unsigned  exponent:8;
                unsigned      sign:1;
        } f_bits;
	struct single_bits{
		unsigned  b0 :1;
		unsigned  b1 :1;
		unsigned  b2 :1;
		unsigned  b3 :1;
		unsigned  b4 :1;
		unsigned  b5 :1;
		unsigned  b6 :1;
		unsigned  b7 :1;
		unsigned  b8 :1;
		unsigned  b9 :1;
		unsigned  b10:1;
		unsigned  b11:1;
		unsigned  b12:1;
		unsigned  b13:1;
		unsigned  b14:1;
		unsigned  b15:1;
		unsigned  b16:1;
		unsigned  b17:1;
		unsigned  b18:1;
		unsigned  b19:1;
		unsigned  b20:1;
		unsigned  b21:1;
		unsigned  b22:1;
		unsigned  b23:1;
		unsigned  b24:1;
		unsigned  b25:1;
		unsigned  b26:1;
		unsigned  b27:1;
		unsigned  b28:1;
		unsigned  b29:1;
		unsigned  b30:1;
		unsigned  b31:1;
	}bit;
} FLOAT_UN;

void create_bit_string(FLOAT_UN target, std::string& bit_string) {

	int i,j;

	for(i=0; i<42; i++){
		bit_string.append(" ");
	}
	bit_string[42] = '\0';

	bit_string[0] = target.bit.b31?'1':'0';

	bit_string[2] = target.bit.b30?'1':'0';
	bit_string[3] = target.bit.b29?'1':'0';
	bit_string[4] = target.bit.b28?'1':'0';
	bit_string[5] = target.bit.b27?'1':'0';

	bit_string[7] = target.bit.b26?'1':'0';
	bit_string[8] = target.bit.b25?'1':'0';
	bit_string[9] = target.bit.b24?'1':'0';
	bit_string[10] = target.bit.b23?'1':'0';

	bit_string[12] = target.bit.b22?'1':'0';
	bit_string[13] = target.bit.b21?'1':'0';
	bit_string[14] = target.bit.b20?'1':'0';

	bit_string[16] = target.bit.b19?'1':'0';
	bit_string[17] = target.bit.b18?'1':'0';
	bit_string[18] = target.bit.b17?'1':'0';
	bit_string[19] = target.bit.b16?'1':'0';

	bit_string[21] = target.bit.b15?'1':'0';
	bit_string[22] = target.bit.b14?'1':'0';
	bit_string[23] = target.bit.b13?'1':'0';
	bit_string[24] = target.bit.b12?'1':'0';

	bit_string[26] = target.bit.b11?'1':'0';
	bit_string[27] = target.bit.b10?'1':'0';
	bit_string[28] = target.bit.b9?'1':'0';
	bit_string[29] = target.bit.b8?'1':'0';

	bit_string[31] = target.bit.b7?'1':'0';
	bit_string[32] = target.bit.b6?'1':'0';
	bit_string[33] = target.bit.b5?'1':'0';
	bit_string[34] = target.bit.b4?'1':'0';

	bit_string[36] = target.bit.b3?'1':'0';
	bit_string[37] = target.bit.b2?'1':'0';
	bit_string[38] = target.bit.b1?'1':'0';
	bit_string[39] = target.bit.b0?'1':'0';
}


// A function to print out bits from a 32 bit container
// provided by the union FLOAT_UN above, and using 
// a text string as a label for the bit string
// as passed in the second argument

int print_bits(FLOAT_UN float_32, std::string text) {
	std::string bit_string;
	create_bit_string(float_32, bit_string);

	std::cout << text << "\t" << bit_string << std::endl;
	return 0;
}

int get_state(unsigned OP1, unsigned OP2, unsigned flag, unsigned carry) {
	unsigned state = 0;

	if(OP1 & flag) {
		state = state | 1;
	}

	if(OP2 & flag) {
		state = state | 0b10;
	}

	if(carry == 1) {
		state = state | 0b100;
	}
	return state;
}


float adder(unsigned mant_1, unsigned mant_2) {
	
	unsigned carry = 0, state = 0;
	float result = 0;

	for(int i = 1, j = 22; i < 23; i++, j--) {

		int flag = pow(2, i);
		state = get_state(mant_1, mant_2, flag, carry);
		switch (state)
		{
		case 0:
		case 5:
		case 6:
			break;
		case 1:
		case 2:
			result = result + pow(2, -j);
			break;
		case 3:
			carry = 1;
			break;
		case 4:
			result = result + pow(2, -j);
			carry = 0;
			break;
		case 7:
			result = result + pow(2, -j);
			carry = 1;
			break;
		default:
			break;
		}
	}
	return result + 1;
}