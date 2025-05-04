#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "genpat.h"

char *inttostr(int inteiro)
{
    char *str;
    str = (char *)mbkalloc(32 * sizeof(char));
    sprintf(str, "%d", inteiro);
    return (str);
}

#define VH_MAXERR 50

int random_range(int min, int max) {
    return min + rand() % (max - min + 1);
}

int main() {
    int cur_vect = 0;
    int votos_A = 0;
    int votos_B = 0;
    int total_votos_A, total_votos_B;
    int i;

    srand(time(NULL));

    total_votos_A = random_range(5, 31);
    total_votos_B = random_range(5, 31);

    DEF_GENPAT("genpat_urna_result");

    DECLAR("votar", ":2", "B", IN, "","");
	  DECLAR("reset", ":2", "B", IN, "","");
    DECLAR("candidato", ":2", "B", IN, "","");
    DECLAR("Vdd", ":2", "B", IN, "","");
    DECLAR("Vss", ":2", "B", IN, "","");

    DECLAR("reg_A", ":2", "B", OUT, "4 down to 0","");
    DECLAR("reg_B", ":2", "B", OUT, "4 down to 0","");
    SETTUNIT("us");

	  AFFECT("0", "Vdd", "1");
    AFFECT("0", "Vss", "0");
    AFFECT("0", "reset", "0");
    AFFECT("0", "votar", "0");
    AFFECT("0", "candidato", "0");
    AFFECT(inttostr(cur_vect), "votar", "0");		
    AFFECT(inttostr(cur_vect), "reset", "1");
    cur_vect++;	
    AFFECT(inttostr(cur_vect), "votar", "1");  
    cur_vect++;
    AFFECT(inttostr(cur_vect), "reset", "0");
    
    AFFECT(inttostr(cur_vect), "votar", "0");
        cur_vect++;

    for(i = 0; i < 31; i++) {
      int voto = rand()%2;        
      cur_vect++;        

      if(voto == 0 && votos_A < 31) {
        AFFECT(inttostr(cur_vect), "candidato", "0");
        votos_A++;
        cur_vect++;
        AFFECT(inttostr(cur_vect), "votar", "1");
      } 
      else if (voto == 1 && votos_B < 31) {
        AFFECT(inttostr(cur_vect), "candidato", "1");
        votos_B++;
        cur_vect++;
        AFFECT(inttostr(cur_vect), "votar", "1");		
      }
   
      cur_vect++;
      AFFECT(inttostr(cur_vect), "votar", "0");
      cur_vect++;
			
      printf("Votos A: %d\n", votos_A);
      printf("Votos B: %d\n", votos_B);
    }

    AFFECT(inttostr(cur_vect), "votar", "0");
   	AFFECT(inttostr(cur_vect), "candidato", "1");
  	AFFECT(inttostr(cur_vect), "reg_A", inttostr(votos_A));
  	AFFECT(inttostr(cur_vect), "reg_B", inttostr(votos_B));
    cur_vect++;

    printf("Resultado da votação:\n");
    printf("Votos Candidato A: %d\n", votos_A);
    printf("Votos Candidato B: %d\n", votos_B);
    printf("Total de votos: %d\n", votos_A + votos_B);
	  printf("Teste genlib_elm: ");

    SAV_GENPAT();
    
    return 0;
}
