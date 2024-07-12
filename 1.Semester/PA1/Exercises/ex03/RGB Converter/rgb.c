#include <stdio.h>

	int main (void){
		
		printf("Zadejte barvu v RGB formatu:\n");
		
			//Declare integer variables to store rgb values of each color
		unsigned short int red = 0;
		unsigned short int green = 0;
		unsigned short int blue = 0;
		
			//Initialize char variable to store enclosing bracket at the end of scanf input
		char endBracket;
		
			//Input 3 numbers and check if it matchs the format , e.g. rgb=(255,255,255)
			//Check if the last bracket is in the input and there is nothing more
		if(scanf(" rgb ( %3hu , %3hu , %3hu %c",&red,&green,&blue,&endBracket) !=4 || red>255 || green>255 || blue >255 || endBracket !=')')
		{
		
			//print error if false and end the script
			printf("Nespravny vstup.\n");
			
			return 0;
		}
		
		//print input data in hexadecimal format
		//E.g. #3F25AF
		printf("#%.2X%.2X%.2X\n",red,green,blue);
	
		return 0;	
	}
