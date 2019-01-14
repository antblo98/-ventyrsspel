#include "item.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * vår datastrukturer som innehåler en sträng 
 * och en pekare till datastrukturen, detta gör att den blir en länkad lista.
 * */
typedef struct ITEMLIST
{
	char data[100];
	struct ITEMLIST *next;
}ITEM;

/**
 * Pushar ett element längst fram i den länkade listan,
 * Detta genom att skapa en ny nod, ge den värden och få den att peka på noden innan. 
 * parametrana är en pekare till min struct samt ett double värde.
 * Sedan retunerar vi denna nya nod, som nu är huvudet i vår länkade lista. 
 * */
ITEM* push(ITEM* stack, char *d)
{
	ITEM* new;
	new = malloc(sizeof(ITEM));
	strcpy(new->data, d);
	new->next = stack;
	return new;
}

//Skapar en pekare till min struct med värdet null. 
ITEM* create_stack()
{
	ITEM* new= NULL;
	return new;
	
}

/**Tar bort ett valt element i den länkade listan
 * Genom att kolla på vad structpekaren(noden) pekar på och en given position
 * Parameterar tar in en pekare till en item pekare och vilken postition i listan den ligger i.
 * retunerar ingenting då funktionen är av datatypen void. return används för att "bryta funktionen" 
 * */ 
void pop(ITEM** stack, int loops)
{
	if(*stack == NULL) //Om stacken är null, det finns ingenting att popa så retunerar vi ingenting.
	{
		return;
	}
		
	//Sparar ner stack noden.	
	ITEM *temp = *stack;
	if(loops == 1) //Om vår länkade lista bara inehåller ett element, tar bort huvudet
	{
		*stack = temp->next; //Byter ut huvudet
		free(temp); //Frigör minnet för det gammla huvudet
		return;
	}
	
	for(int i = 0; i<loops-2;++i) //Hittar noden som är innan den noden vi vill ta bort
	{
		temp = temp->next;
	}
	//Eftersom att temp->next ska tas bort så sparar vi den nodens pekare temp->next->next
	ITEM *temp2 = temp->next->next;
	free(temp->next); //Frigör minnet för noden som ska tas bort
	temp->next = temp2; //Av länkar den vi tagit bort ifrån listan
}
	


/**
 * Denna funktion går rekrusivt igenom vår länakde lista och för varje gång den slår så ökar vår räknare
 * Parametrarna är en pekaretill vår struct samt en sträng.
 * Om strängen är samma sak som den som finns i vår läkande lista så retunerar vi räknaren
 * */
int linked_position(ITEM* list,char* string ) 
{
	int counter = 1;

	
	if (list == NULL || !strcmp(list->data, string)) //Om listan är tom eller om strängen som finns i noden är samma sak som den strängen vi frågar efter så retunerar vi räknaren
	{
		return counter;
	}
	
	return 1 + linked_position(list->next, string); //Ökar värdet på funktionen med ett samt får den att rekrusivt slå igen.
}

/**
 * Denna funktion skriver ut alla element i vår länkade lista. 
 * Parametern tar in en pekare till vår struct.
 * om noden vi kollar på är tom så skriver vi inte ut något
 * om den innehåller nå data så skriver vi ut den. 
 * */
void print_list(ITEM *list) 
{
	if (list == NULL){}
	else
	{
		printf("\n%s\n",list->data);
		print_list(list->next);
	}
}
/**
 * Kollar om förmålet finns i vår Item struct.
 * Parametrarna tar en en item pekare samt en sträng.
 * med
 * returnerar 1 om den inte finns i vår lista
 * retunerar 0 om den finns i vir lista.
 * 
 * */
int checker(ITEM* list, char *string)
{
	
	if (list == NULL)
	{
		return 1;
	}
	
	if(!strcmp(list->data, string))
	{
		return 0;
	}
	
	return checker(list->next, string);
}

	
	
	

