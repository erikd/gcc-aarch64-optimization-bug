
#include <stdio.h>
#include <stdlib.h>

#include "aglib.h"

#define ARRAY_LEN(x)		((int) (sizeof (x) / sizeof ((x) [0])))
#define	OUTPUT_TEST_LEN		32
#define ALAC_FRAME_LENGTH	4096

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"


static uint16_t
fletcher16 (uint8_t const *data, size_t bytes)
{	uint16_t sum1 = 0xff, sum2 = 0xff;

	while (bytes)
	{	size_t tlen = bytes > 20 ? 20 : bytes;
		bytes -= tlen;
		do
		{	sum2 += sum1 += *data++;
        } while (--tlen);
		sum1 = (sum1 & 0xff) + (sum1 >> 8);
		sum2 = (sum2 & 0xff) + (sum2 >> 8);
		} ;
	/* Second reduction step to reduce sums to 8 bits */
	sum1 = (sum1 & 0xff) + (sum1 >> 8);
	sum2 = (sum2 & 0xff) + (sum2 >> 8);
	return sum2 << 8 | sum1;
}

int
main (void)
{	static int32_t input [16] =
		{ 0, 731, 2971, 6028, 9344, 4152, 6341, 8659, 10530, 11404, 10839
		, 8550, 4450, -1349, -8600, -16888
		} ;
	static uint8_t mWorkBuffer [4 * ALAC_FRAME_LENGTH] ;
	AGParamRec agParams = { 10, 10, 40, 14, 16383, 472, 16, 16, 255 } ;
	uint32_t 	chanBits = 20, bits1 ;
	uint16_t	checksum ;

	/* Drive the function with known inputs. */
	dyn_comp (&agParams, input, mWorkBuffer, ARRAY_LEN (input), chanBits, &bits1) ;

	/* Calculate the checksum of the output. */
	checksum = fletcher16 (mWorkBuffer, OUTPUT_TEST_LEN) ;

	printf ("\nChecksum value 0x%04x : %s\n\n", checksum,
		checksum == 0x1c1c
			? ANSI_COLOR_GREEN "Correct!" ANSI_COLOR_RESET
			: ANSI_COLOR_RED "Error, should be 0x1c1c!" ANSI_COLOR_RESET
			) ;

	return 0 ;
}
