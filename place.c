/**
* \file place.c
*/
#include "place.h"
#include "item.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define PLACE_NAME_LENGTH 80
#define PLACE_DESC_LENGTH 1000
// Här kommer implementationen av struct place!
typedef struct place
{
unsigned int id;
char name[PLACE_NAME_LENGTH];
char desc[PLACE_DESC_LENGTH];
ITEM* items; // en lista av ITEM (se item.h)
int exits[10]; //north = 0, east = 1, south = 2, west = 3
}PLACE;

/**
* Läs in platsbeskrivning från fil.
*
* @param infile En öppnad fildeskriptor.
*
* @return En pekare till en ny plats. NULL om läsningen misslyckades,
* eller om det inte finns fler platser i infile.
*/
PLACE* read_place( FILE* infile )
{	
	
	PLACE *plats = malloc(sizeof(PLACE));
	if(plats == NULL){
		return NULL;
	}
	
	char line[1000];
	fscanf(infile, "%s\n", line);
	
	while(strcmp(line, "#ROOM_END")){

		if(!strcmp( line, "#ROOM_BEGIN" )){
			//printf("%s\n", line);
		}
		if(!strcmp( line, "id:" )){
			//printf("%s\n", line);
			fscanf(infile, "%u", &plats->id);
			//printf("%u\n", plats->id);	
		}
		if(!strcmp( line, "brief:" )){
			//printf("%s\n", line);
			fgets(plats->name, 1000, infile);
			
			//printf("%s\n", plats->name);
		}
		if(!strcmp( line, "full:" )){
			//printf("%s\n", line);
			//fgets ger en extra \n
			fgets(plats->desc, 1000, infile);
			
			//printf("%s\n", plats->desc);

			
		}if(!strcmp( line, "item:" )){
			//printf("%s\n", line);
			fscanf(infile, "%s\n", line);
			plats->items = push(plats->items, line);
			//print_list(plats->items);
			//printf("\n");

		}
		
		if(!strcmp( line, "exit:" )){
			fscanf(infile, "%s\n", line);			
			if(!strcmp( line, "h" )){
				fscanf(infile, "%d", &plats->exits[0]);
			}
			if(!strcmp( line, "s" )){
				fscanf(infile, "%d", &plats->exits[1]);
			}
			if(!strcmp( line, "y" )){
				fscanf(infile, "%d", &plats->exits[2]);
			}
			if(!strcmp( line, "n" )){
				fscanf(infile, "%d", &plats->exits[3]);
			}
			if(!strcmp( line, "t" )){
				fscanf(infile, "%d", &plats->exits[4]);
			}
			if(!strcmp( line, "n1" )){
				fscanf(infile, "%d", &plats->exits[5]);
			}
			if(!strcmp( line, "w1" )){
				fscanf(infile, "%d", &plats->exits[6]);
			}
			if(!strcmp( line, "b" )){
				fscanf(infile, "%d", &plats->exits[7]);
			}
		}
		fscanf(infile, "%s\n", line);
	}
	return plats;
}

/**
* Skriver ut beskrivning av en plats till stdout, samt eventuella
* saker som ligger på platsen.
*
* @param p En pekare till en plats.
*/
void print_place( PLACE *p)
{
	printf("\n\n\n\n\n");
	printf("\n\n%s\n%s", p->name, p->desc);
	//KOLLA PÅ DETTA
	if(p->items != NULL){
		printf("---------------------------------");
		printf("\nobjects in room:\n");
	}
	if(p->items!=NULL){	
		print_list(p->items);
	}
	printf("---------------------------------");
	printf("\nAction:\n");
	for(int i=0; i<8; ++i){
		if(p->exits[i] != 0){
			if( i==0 ){
				printf("\nHaru");
			}
			if( i==1 ){
				printf("\nSayuri");
			}
			if( i==2 ){
				printf("\nYuri");
			}
			if( i==3 ){
				printf("\nNext page");
			}
			if( i==5 ){
				printf("\nNorth");
			}
			if( i==6 ){
				printf("\nWest");
			}
			if( i==7 ){
				printf("\nback");
			}
			printf("\n");
		}
	}
}

/**
* Kollar vilket plats-ID man kommer till om man går från en plats.
*
* @param p En pekare till en plats.
* @param dir En riktning att gå till: 0=norr, 1=öst, 2=syd, 3=väst.
*
* @return Index på den plats man kommer till om man går i
* riktining dir från plats p. Om det inte går att gå åt det
* hållet returneras p:s index.
*/
int exit_index( PLACE *p, int dir )
{
	if(p->exits[dir] == 0 || dir > 7)
	{
		return -1;
	}
	
	return p->exits[dir];
}


/**
* Tar bort en sak från en plats.
*
* @param p En pekare till en plats.
* @param str En sträng med beskrivning av en sak.
*
* @return En pekare till saken. NULL om strängen str inte
* hittades bland de saker som ligger i p:s sak-lista.
*/


void remove_item( PLACE *p, char *str)
{
	int count = linked_position(p->items, str);
	pop(&(p->items),count);
}

void add_item( PLACE *p, char *object )
{
	p->items = push(p->items, object);
}

int roomchecker(PLACE *p,char *string)
{
	if(!checker(p->items,string))
	{
		return 0;
	}
	return 1;
	
}

