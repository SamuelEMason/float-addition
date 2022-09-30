#include <stdio.h>
#include "adder.h"


int main(int argc, char * argv[])
{

	float list[] = { 34.5, 1.25, 2.75e3, 256.0, 1.4e-3, 13.0, 7.491, 4.617e20, 9643.0, 1.237e-2, 25e37, 15e37 };

	for(int a = 0; a < 12; a+=2) {
		

FLOAT_UN float_32_s1, float_32_s2, float_32_rslt, fun_arg;

/**local helper variables**/

float	the_hardware_result, mant_res;
unsigned mant_s1, mant_s2, exp_s1, exp_s2;
int	i, j, k, shift_count;
/* Request two FP numbers */
float_32_s1.floating_value_in_32_bits = list[a];
float_32_s2.floating_value_in_32_bits = list[a + 1];
print_bits(float_32_s1, "Original pattern of Float 1: ");
print_bits(float_32_s2, "Original pattern of Float 2: ");

/* generate floating point hardware result */

the_hardware_result = float_32_s1.floating_value_in_32_bits + float_32_s2.floating_value_in_32_bits;


/* Get the mantissa and exponent components */
/*   into the helper variables */

mant_s1 = float_32_s1.f_bits.mantissa;
mant_s2 = float_32_s2.f_bits.mantissa;
exp_s1  = float_32_s1.f_bits.exponent;
exp_s2  = float_32_s2.f_bits.exponent;


// std::cout << exp_s1 << std::endl << exp_s2 << std::endl;
// std::cout << shift_count << std::endl;

/** check for normalization and slam in the **/
/** hidden bit if normalized **/



/** The rest is left to you */
int exp;
unsigned hidden = pow(2, 22);

if(exp_s1 > exp_s2) {
	exp = exp_s1 - 127;
	shift_count = exp_s1 - exp_s2;
	mant_s2 = mant_s2 >> 1;
	mant_s2 = mant_s2 | hidden;
	mant_s2 = mant_s2 >> (shift_count - 1);
}
else if(exp_s1 < exp_s2) {
	exp = exp_s2 - 127;
	shift_count = exp_s2 - exp_s1;
	mant_s1 = mant_s1 >> 1;
	mant_s1 = mant_s1 | hidden;
	mant_s1 = mant_s1 >> (shift_count - 1);
}
else if(exp_s1 == exp_s2){
	exp = exp_s2 - 127;
	shift_count = 0;
}

mant_res = adder(mant_s1, mant_s2);

float_32_rslt.floating_value_in_32_bits = (mant_res) * pow(2, exp);

print_bits(float_32_rslt, "Bit pattern of result: ");

std::cout << "EMULATED FLOATING RESULT FROM COUT ==>>> " 
			<< float_32_rslt.floating_value_in_32_bits << std::endl;
std::cout << "HARDWARE FLOATING RESULT FROM COUT ==>>> " 
			<< the_hardware_result << std::endl;
	}
	std::cout << std::endl;
}