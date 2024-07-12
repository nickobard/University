#include <stdio.h>

	int main(void){
	
		unsigned int numb = 0;
		
		printf("ml' nob:\n");
		
		//Read first occured one-digit number from 1 to 5
		if(scanf(" %1u",&numb)!=1 || numb >5 || numb ==0)
		{
			//If get smt else, print error message and end script 
			printf("luj\n");
			return 0;
		}
		
		
		//Print citation of chosen number [1-5]
		if	   (numb ==1){
			printf("Qapla'\nnoH QapmeH wo' Qaw'lu'chugh yay chavbe'lu' 'ej wo' choqmeH may' DoHlu'chugh lujbe'lu'.\n");
			}
		else if(numb ==2){
			printf("Qapla'\nQu' buSHa'chugh SuvwI', batlhHa' vangchugh, qoj matlhHa'chugh, pagh ghaH SuvwI''e'.\n");
			}
			
		else if(numb ==3){
			printf("Qapla'\nqaStaHvIS wa' ram loS SaD Hugh SIjlaH qetbogh loD.\n");
			}
			
		else if(numb ==4){
			printf("Qapla'\nHa'DIbaH DaSop 'e' DaHechbe'chugh yIHoHQo'.\n");
			}
			
		else{
			printf("Qapla'\nleghlaHchu'be'chugh mIn lo'laHbe' taj jej.\n");
			}
			
			return 0;
			
	}
