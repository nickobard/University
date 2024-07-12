#include <stdio.h>
#include <math.h>

	int main (void){

			unsigned hh=0;
			unsigned mm=0;
			unsigned ss=0;
			unsigned ms=0;
			unsigned t1=0;
			unsigned t2=0;
			unsigned delta = 0;
		
		// CODE REVIEW poznamka
		// Resil jsem, aby to umelo spocitat rozdil i obracene, tedy pro t1-t2, proto jsem zavedl promennou delta. Jinak receno jsem spatne pochopil zadani, vubec to nevadilo, program umel vic nez bylo potreba. A jsem liny to predelavat aby to bylo vic vylizane :) 		
		
			printf("Zadejte cas t1:\n");
			
			//Naskenuj a zkontroluj, aby to byl hodinovy format
			if (scanf(" %u : %u : %u ,  %u",&hh,&mm,&ss,&ms)!=4 || hh >23 || mm>59 || ss >59 || ms > 999){
				printf("Nespravny vstup.\n");
				return 1;
			}
			
			//Preved cely cas na ms a secti to dohromady
				t1 = hh*3600*1000 + mm*60*1000 + ss*1000 + ms;
				
			
			//dalsi cas t2, stejne operace jako i u t1
			
			printf("Zadejte cas t2:\n");
			
			if (scanf(" %u : %u : %u , %u",&hh,&mm,&ss,&ms)!=4 || hh >23 || mm>59 || ss >59 || ms > 999){
				printf("Nespravny vstup.\n");
				return 1;
			}
			
				t2 = hh*3600*1000 + mm*60*1000 + ss*1000 + ms;

			//Pro pripad, kdybych to chtel pocitat i obracene
			//delta = t2 > t1 ? (t2-t1) : (t1-t2);
			
			//Zkontroluj jestli koncovy cas neni mensi nez zacatkovy
			if (t2>=t1){
				delta = t2-t1;
			}
			else{
				printf("Nespravny vstup.\n");
				return 1;
			}
			
			//Prosim, preved to zpatky do hodin, minut a sekund.
			
			hh = delta/3600000;
			mm = delta/60000 - hh*60;
			ss = delta/1000 - hh*3600 - mm*60;
			ms = delta - hh*3600000 - mm*60000-ss*1000;
			
			//Zobraz rozdilove hh, mm, ss a ms
			printf("Doba: %2u:%02u:%02u,%03u\n",hh,mm,ss,ms);
			
			return 0;
		}
		
		
		
