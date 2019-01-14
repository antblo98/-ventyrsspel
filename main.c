#include "map.h"
#include "place.h"
#include "item.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{	
	
	
	MAP* m = create_map();
	int fel;
	fel = load_map(m, "room.txt");
	if( fel == 1 ){
		printf("\nfile could not be retrieved\n");
		return 1;
	}
	if( fel == 2 ){
		printf("\nsomething went wrong when reading file\n");
		return 1;
	}
	PLACE* room = NULL;
	ITEM*bag = create_stack();
	printf("\n\n Welcome to DokiDoki2\n\n ");
	printf("\n This is a visual novel, a wonderful saga about love and loss, about happiness and sorrow and where your choices matter. The items you gather will allow you to act differently at the end and hopefully end up living happily ever after. \n");
	printf("\n if you need any help, type help\n");
	room = go_to(m, room, 0);
	print_place(room);

	//room 20 item usage
	PLACE* choice = NULL;
	choice = go_to(m, choice, 19);
	
	PLACE* genie = NULL;
	genie = go_to(m, genie, 6);
	
	PLACE* end = NULL;
	end = go_to(m,end,26);	

	int x = 0;
	
	while(!x){
		char action[100];
		char object[100];
		printf("^What do you want to do in this room?^\n\n");
		fscanf(stdin, "%s", action);
		for(int i = 0; action[i]; i++){
			action[i] = tolower(action[i]);
		}
		
		if(!strcmp(action, "n") || !strcmp(action, "yuri") || !strcmp(action, "sayuri") || !strcmp(action, "haru") || !strcmp(action, "help") || !strcmp(action, "north") || !strcmp(action, "west") || !strcmp(action, "back") || !strcmp(action, "use") || !strcmp(action, "drop") || !strcmp(action, "take") || !strcmp(action, "open")){
			if(!strcmp(action, "n") || !strcmp(action, "yuri") || !strcmp(action, "sayuri") || !strcmp(action, "haru") || !strcmp(action, "help") || !strcmp(action, "north") || !strcmp(action, "west") || !strcmp(action, "back")){
				
				if(!strcmp(action, "help")){
					printf("::: <n> is for new page\n\n");
					printf("::: <use> and then the item you want to use\n\n");
					printf("::: <drop> and then the item you want to drop, the item will be stashed in the room\n\n");
					printf("::: <take> and then the item, this will store it in your bag\n\n");
					printf("::: <open bag> will open your bag and showcase your items\n\n");
					printf("::: <back> will go to the previous page if the option exist\n\n");
					printf("::: <north/west> will go to north or west if the option exist\n\n");
				}
				if(!strcmp(action, "n")){
					room = go_to(m, room, 3);
				}
				if(!strcmp(action, "yuri")){
					room = go_to(m, room, 2);
				}
				if(!strcmp(action, "sayuri")){
					room = go_to(m, room, 1);
				}
				if(!strcmp(action, "haru")) {
					room = go_to(m, room, 0);
				}
				if(!strcmp(action, "north")) {
					room = go_to(m, room, 5);
				}
				if(!strcmp(action, "west")) {
					room = go_to(m, room, 6);
				}
				if(!strcmp(action, "back")) {
					room = go_to(m, room, 7);
				}
			}
			else{
				fscanf(stdin, "%s", object);
				for(int i = 0; object[i]; i++){
					object[i] = tolower(object[i]);
				}
				if(!strcmp(action, "take")){
					if(!roomchecker(room,object)){
						remove_item(room, object);
						bag = push(bag, object);
						if(!strcmp(object, "genie") && room == genie){
							room = go_to(m, room, 4);
						}
					}
				else{
					printf("%s do not exist in the room\n",object);
				}
				}
				
				if(!strcmp(action, "drop")){
					if(!checker(bag, object)){
						add_item(room, object);
						int loops = linked_position(bag, object);
						pop(&bag, loops);

					}
					else{
					printf("You don*t have %s in your bag!\n",object);
					}
				}
				if(!strcmp(action, "use")){
					if(!checker(bag, object)){
						if(!strcmp(object, "genie") && room == room){
							int loops = linked_position(bag, object);
							pop(&bag, loops);
							room = go_to(m, room, 4);
						}
						
						else if(!strcmp(object, "sword") && room == end){
							int loops = linked_position(bag, object);
							pop(&bag, loops);
							printf("\n\n\nYou draw your sword, but it is no match for the big green ogre. He grabs the sword from your hands and breaks it into a thousand pieces. He is now standing just a few centimeters away from you. His bad breath knocks you out. You wake up shivering, you think to yourself, *Where am I?*, after looking through the room you realise you've seen this before in a fifty shades of grey movie. Is this fifty shades of green? You finally understand! You remember the phrase from before. He is indeed love, He is in indeed life. You finally understand the meaning of life.\n \n  ");
							x = 1;
						}
						
						else if(!strcmp(object, "pistol") && room == end){
							int loops = linked_position(bag, object);
							pop(&bag, loops);
							printf("\n\n\nYou draw your glock! You start shooting like a madman against the green wonderful being! For a second you see a tear in his eyes and then he seems to win the Oscar's for acting and faints! You realise this is your only time to escape. You start running like Usain Bolt out of the cave. Once outside the cave you feel empty, you are nothing without Shrek. You put the gun to your head.... \n \n ");
							x=1;
						}
						
						else if(!strcmp(object, "balls") && room == end){
							int loops = linked_position(bag, object);
							pop(&bag, loops);
							printf("\n\n\nAs he is charging at you he seems kind of hungry! So remember you have balls in your bag. So throw it at him with a mighty force. You knock him over, and now he has blood gushing from his head. The monster seems happy now and pulls out some ravioli out of his pocket and eats it with the tomatosauce and meatballs. You run out of the cave and you feel empty, your dungeon run didn't end up in jewels, you actually lost your jewels... but you escaped...\n\n ");
							x=1;
						}
						else if(!strcmp(object, "he-man-form") && room == end){
							int loops = linked_position(bag, object);
							pop(&bag, loops);
							printf("\n\nJerry suddenly turns into a tiger with a saddle and you become a muscular greek god of gods of war. You are now equal in power with the green beauty. You lunge into a battle. The fight lasts 9 to 11 years, you haven't eaten in 3 days. You took fika pauser during the fights. What started as a brawl slowly but surely changed. For each strike, for each sweat, for each breath, for each touch, love grew. You stare into the ogres eyes, it's all ogre now, you think to yourself. You were straight out of Compton now you bent like a banana for Shrek. You leave the cave holding hands, but you squeeze Shrek's hand too hard because of all of your muscles. You say sorry to Shrek while staring deeply into his eyes. Shrek says, no problem and leans in....");
							x=1;
						}
						
						else if(!strcmp(object, "jerry") && room == end){
							if(!checker(bag, "sword")){
								int loops = linked_position(bag, object);
								pop(&bag, loops);
								int loops2 = linked_position(bag, "sword");
								pop(&bag, loops2);
								printf("\n\n\nYou whip out Jerry. He starts looking around he must've caught scent of something? HE JUMPS ON TOP OF YOU, starts humping? NO, he is looking through your bag and finds his legendary diamond sword. You see stormy clouds start to form in the cave, thunder strikes, flowers grow and volcanoes erupt. He must've sensed it's aura. Jerry, has a great broad smile on his face, but suddenly it turns into a frown. *How did a lousy two legged traveler like you have this. THE POWER FROM THIS SWORD IS OVER 9000 and only the memeedgelords can wield this hammer, I mean sword. You should've been blown to pieces. Yet here you stand erect,* You are the chosen one, one of the lightning bolts hit your bag. \n*He-man-form has been added to your bag* \n\n");
								bag = push(bag, "he-man-form");
								
							}
							else{
								int loops = linked_position(bag, object);
								pop(&bag, loops);
								printf("\n\n\nYou whip out Jerry. He clenches his fists and lets out a mighty roar, he has gathered all the chakra needed to perform the shadow clone jutsu. Suddenly 100 copies of Jerry appear, called Ben. NOW THE BEN MINIONS ATTACK. While they attack you escape with Jerry and live happily ever after in the kingdom of Avalon. \n\n");
								x =1;
							}
						}
						
						else if(!strcmp(object, "knowledge") && room == end){
							int loops = linked_position(bag, object);
							pop(&bag, loops);
							printf("\n\n\nIn the distant past you had memories of a scar on Haru's hand. You yell into the cave something about the scar, the acouistics bring forth your voice. Nothing seems to happen at first and Shrek is getting closer... and closer. In the last mili, no nano, NO PICO second you see glaring eyes from the shadows in the cave. Red gleaming eyes. Ninjas come to your aid. A clash between immense chakras. *CHIDORI!!!!!* the ninjas yell, *RASENGAN!!!!* Shrek yells. This seems to be their ultimate moves. There is still one more ninja hiding in the shadows and with the ninja escorting you, you leave the cave safely holding deformed hands and live happily ever after with the ninja \n\n");
							x =1;
						}
						
						
						//Sayuri's story and items
						else if(!strcmp(object, "pee") && room == room){
							int loops = linked_position(bag, object);
							pop(&bag, loops);
							printf("You're splashing your pee around the place, it's disgusting, it smells and now you have a raccoon king as your friend\n*Jerry has been added to your inventory*\n");
							bag = push(bag, "jerry");
						}
						
						else if(!strcmp(object, "pistol") && room == room){
							add_item(room, object);
							int loops = linked_position(bag, object);
							pop(&bag, loops);
							printf("\n\nYou're staring up in the ceiling and realise how unsignificant you are in this life. Your last thought is accompanied with a tinnitus, because you shot yourself and now you can't hear anything for the rest of the game. jk you lose :) game over");
							x = 1;
						}
						
						//Haru's story and items
						else if(!strcmp(object, "knowledge") && room == room){
							int loops = linked_position(bag, object);
							pop(&bag, loops);
							printf("You are like a mighty tree descending but no one is there to hear you fall, cause no one cares\n*nothing has been added to your inventory and knowledge is also removed cause lol*\n");
						}
						
						//alone story, debuff
						else if(!strcmp(object, "sadness") && room == room){
							int loops = linked_position(bag, object);
							pop(&bag, loops);
							for(int i=0; i<=100; ++i){
								bag = push(bag, "die");
							}
							printf("\n*one hundred die has been added to your inventory*\n");
						}
						else if(!strcmp(object, "die") && room == room){
							add_item(room, object);
							int loops = linked_position(bag, object);
							pop(&bag, loops);
							printf("\n\nYour crippling depression takes over, game over");
							x = 1;
						}
						
						//Yuri's story and items
						else if(!strcmp(object, "vasectomi") && room == room){
							int loops = linked_position(bag, object);
							pop(&bag, loops);
							printf("You remember that you always keep a bottle of vodka on you, so you perform a fast vasectomi on yourself\n*Balls have been added to your inventory*\n"); 
							bag = push(bag, "balls");
						}
						
						else{
							printf("%s has no effect\n", object);
						}
					}
					else{
					printf("You dont have %s in your bag!\n",object);
					}	
				}
				if(!strcmp(action, "open")){
					if(!strcmp(object, "bag")){
						print_list(bag);
					}
					else{
						printf("You can't open %s\n\n", object);
					}
				}
			}
		}
		else{
		}
	}
	printf("\n\n\nCreator: Anton & Timor\n\n\n\n fin \n\n\n");
	free(m);
	return 0;
}
