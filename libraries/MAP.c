#include "STD_TYPES_H.h"
#include "MAP.h"

f64 MAP(f64 copy_f64InputRangeMin, f64 copy_f64InputRangeMax,
		f64 copy_f64OutputRangeMin, f64 copy_f64OutputRangeMax, f64 copy_f64InputValue)
{
	f64 Local_f64InputRange,Local_f64OutputRange;
	Local_f64InputRange = copy_f64InputRangeMax -copy_f64InputRangeMin;
	Local_f64OutputRange = copy_f64OutputRangeMax - copy_f64OutputRangeMin;
	return (((copy_f64InputValue - copy_f64InputRangeMin)*Local_f64OutputRange)/Local_f64InputRange)+copy_f64OutputRangeMin;

}
