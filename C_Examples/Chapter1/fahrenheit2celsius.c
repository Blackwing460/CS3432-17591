#include <stdio.h>

/* print Fahrenheit-Celsius table
	  for fahr = 0, 20, ..., 300 */

float convert(float temp){// Method that converts a float fahrenheit value to celsius

	temp = 5 *(temp-32)/9;//Formula for conversion
	return temp;//returns float value
}

int main() {
	  float f = 98.34; // Fahrenheit value
	  float converted_c; //Float that will contain the new celcius value
	  converted_c = convert(f);//Calls convert method and assigns it to converted_c
	  printf("Fahrenheit: %lf \n",f);//prints fahrenheit value
	  printf("Celsius %lf \n", converted_c); // prints celsius value
}


