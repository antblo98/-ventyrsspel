#include "place.h"
#include "map.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "item.h"
#define MAX_PLACE_COUNT 100
typedef struct map
{
	PLACE* places[MAX_PLACE_COUNT];
}MAP;

/**
* Allokera en ny, tom, MAP på heapen.
*/
MAP* create_map()
{
	MAP* map = malloc( sizeof( MAP ) );
	if(map == NULL){
		printf("finns inte nog med uttryme för map"); //Kollar så det gick att allokera minnet
		return NULL;
	}
	for (int i = 0; i < MAX_PLACE_COUNT; ++i) //Loopar igenom max antalrum och ger alla platser i vår array värdet NULL;
		{
	map->places[i] = NULL;
		}
return map; 
}

/**
* Ladda en karta från en textfil.
*
* @param m Pekare till en tom karta.
* @param filename Filnamnet som vi ska läsa från.
*
* @return 0 om allt gick bra. 1 om filen inte hittades. 2 om det
* blev något annat fel under läsning.
* */
int load_map( MAP *m, char *filename )
{	
	FILE* infile = NULL;
	if ((infile = fopen(filename, "r")) == NULL) { // om det inte gick att allokera minne så retunerar vi ett
		return 1;
	}
	
	int i = 0;
	char line[1000];

	while(fscanf(infile, "%s\n", line) != EOF){ //Medan vi inte läser in ett slutvärde(EOF) så ska loope gå
		m->places[i] = read_place(infile); //placerar rummet på position "i" i vår map mapstruct, så vi att vi kan komma åt rummen
		if(m->places[i] == NULL){ //Om en positionen i listan blev noll så lyckades inte read_place att allokera minne, så vi retunerar 2.
			return 2;
		}
		++i;
	}
	fclose(infile); //Stänger sedan filen vi läser in ifrån.
	return 0;
	
}

/**
* Försök flytta på spelaren
*
* @param m En karta
* @param p En plats i kartan
* @param dir Riktning
*
* @return Pekare till den nya platsen. (Samma som p om det inte
* gick att gå åt det hållet.)
*/
PLACE * go_to( MAP *m, PLACE *p, int dir )
{
	if(p == NULL){
		return m->places[dir];
	}
	int x = exit_index(p, dir); //Om exit_index retuenrar -1 så vet vi att vi inte får gå till det rummet.
	if(x == -1){
		printf("\nYou can't do that!\n");
		print_place(p); //skriver ut rummet igen
		return p;
	}
	else{
	print_place(m->places[x-1]); //Skriver ut den nya platsen vi hamnar på. X ger oss id på rummet, vilket ligger på en poistion bakot i vår map struct array. rum ID 1 ligger på plats 0 i vår array
	return m->places[x-1]; //retunerar den nya platsen
	}
}



