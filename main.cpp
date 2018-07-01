#include<allegro5\allegro5.h> 
#include<allegro5\allegro_native_dialog.h> 
#include<allegro5\allegro_primitives.h>
#include<allegro5/allegro_ttf.h> 
#include<allegro5/allegro_font.h> 
#include<allegro5\allegro_image.h>
#include<time.h>
#include<iostream>
#include<fstream>
#include<math.h>
#include<sstream>


enum KEYS{ UP, DOWN, LEFT, RIGHT};
int dimx=15,dimy=15; //dimensiune casuta
int x,y;
int mtx=54,mty=40;
int directie=LEFT,direct=RIGHT;
int viteza=8;
int mancarex=25,mancarey=20;
bool done = false;
int punctaj=0;




struct MATRICE // initializare un tip de structura MAT mt sub forma de tablou bidimensional 
{
int typ;  
}mt[70][50];

struct SARPE{
	int x;
	int y;
	SARPE *urm;
}*sarpe; // initializare un tip de structura sub forma de lista
void Init();				//init subprograme
void afis(); 				//init subprograme
void Miscare();				//init subprograme
void generaremancare();		//init subprograme
void citire();				//init subprograme
void citiretopscores();		//init subprograme
void salvarematrice();		//init subprograme

int main()
{
	int width = 810;
	int height = 600;
	
	

	int pos_x = width / 2;
	int pos_y = height / 2;
	int contor=1;
	int ax=1,ay=1,dimx=11,dimy=11;

	int FPS = 60;
	
	
	Init();

	
	ALLEGRO_DISPLAY *display = NULL;			//init fereastra	
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;	//init event (modificare/intamplare)
	ALLEGRO_TIMER *timer = NULL;				//init cronometru

	if(!al_init())										//initializeaza Allegro
		return -1;

	display = al_create_display(width, height);			//creaza our display 

	if(!display)										//testare display 
		return -1;

	al_hide_mouse_cursor(display);		//init ascunde cursor	
	al_install_keyboard();				//instaleaza tastatura
	al_init_image_addon();				//instaleaza utilizarea imaginior
    al_init_primitives_addon();		//instaleaza formele geometrice
	al_init_font_addon(); 			//instaleaza tip de text	
    al_init_ttf_addon();			//instaleaza tip de text
 // al_install_mouse();
	ALLEGRO_FONT *font = al_load_font("bin/font.ttf", 36, NULL);//init tip de text


	event_queue = al_create_event_queue();//init event
	timer = al_create_timer(1.0 / FPS);//init nr de fps

	al_register_event_source(event_queue, al_get_keyboard_event_source());// init tastatura in event_queue
	al_register_event_source(event_queue, al_get_display_event_source(display));// init display in event_queue
	al_register_event_source(event_queue, al_get_timer_event_source(timer));// init timpul in event_queue
	//al_register_event_source(event_queue, al_get_mouse_event_source());
	al_start_timer(timer);//pornim cronometru



	while(!done)//pornim jocul pana cand done =true
	{ 
																
		
		ALLEGRO_EVENT ev;
			al_wait_for_event(event_queue, &ev);//sea asteapta sa se intample ceva

			if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
			{
				switch(ev.keyboard.keycode)
				{									//primim una din taste si o punem in var directie
					case ALLEGRO_KEY_UP:
						if(direct!=UP)
						directie=UP;
						break;
					case ALLEGRO_KEY_DOWN:
						if(direct!=DOWN)
						directie=DOWN;
						break;
					case ALLEGRO_KEY_RIGHT:
						if(direct!=RIGHT)
						directie=RIGHT;
						break;
					case ALLEGRO_KEY_LEFT:
						if(direct!=LEFT)
						directie=LEFT;
						break;

					case ALLEGRO_KEY_S:
						if(direct!=DOWN)
						directie=DOWN;
						break;
					case ALLEGRO_KEY_W:
						if(direct!=UP)
						directie=UP;
						break;
					case ALLEGRO_KEY_A:
						if(direct!=LEFT)
						directie=LEFT;
						break;
					case ALLEGRO_KEY_D:
						if(direct!=RIGHT)
						directie=RIGHT;
						break;

					
				}
			}
			else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			{
				done = true; ///verificam daca nu a sa iesit din prog
			}
			else if(ev.type == ALLEGRO_EVENT_TIMER)
			{
				if(contor==viteza)	//setam viteza jocului
				{	contor=0;
				Miscare();}
				contor++;
				
			
			}
				
				
			
			afis();//afis
			    al_flip_display();// pune pe ecran toate primitivele sau fronturile
				al_clear_to_color(al_map_rgb(0,0,0));//afisam ecran negru pt a sterge afis anterioare

				


	}
	std::stringstream strn;																			//
	strn<<punctaj;																					//
	al_draw_text(font, al_map_rgb(44, 117, 255), 840/2-230 , 600/2-100, NULL, "Game Over");		   //afisam la sfarsit punctaju
	al_draw_text(font, al_map_rgb(44, 117, 255), 840/2-230 , 600/2+25, NULL, "Scor:");			   //
	al_draw_text(font, al_map_rgb(44, 117, 255), 840/2-40 , 600/2+25, NULL, strn.str().c_str());   //
	  al_flip_display();// pune pe ecran toate primitivele sau fronturile
	al_rest(4.5);// asteptam 4.5 secunde


	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_display(display);						//distrugem var init

	return 0;
}
void citire()
{
	std::ifstream fisier("matrice.out");
for(int i=0;i<mtx;i++)
{
		for(int j=0;j<mty;j++)
		{
			fisier>>mt[i][j].typ;
		
		}

}
//citim matricea de la tast

}
void afis() //afisam matrice
{	citire();
	
	for(int i=0;i<mtx;i++)
  {
      for(int j=0;j<mty;j++)
      {
		  if(mt[i][j].typ==2)
			  al_draw_filled_rectangle(dimx*i, dimy*j, dimx*i + 14, dimy*j + 14, al_map_rgb(128,255,255));

      }
      
  }//afisam harta

	al_draw_filled_rounded_rectangle(dimx*mancarex, dimy*mancarey, dimx*mancarex + 14, dimy*mancarey + 14,2,2, al_map_rgb(255,0,45));//afis capus sarpelui
	SARPE *nou;																														 //afis capus sarpelui
	nou=sarpe;																														 //afis capus sarpelui
																																	 //afis capus sarpelui
	mt[nou->x][nou->y].typ=1;																										 //afis capus sarpelui
	al_draw_filled_rounded_rectangle(dimx*nou->x, dimy*nou->y, dimx*nou->x + 14, dimy*nou->y + 14,3,3, al_map_rgb(255,255,2));		 //afis capus sarpelui
	nou=nou->urm;
	
	while(nou!=NULL)
	{
		mt[nou->x][nou->y].typ=1;
	al_draw_filled_rectangle(dimx*nou->x, dimy*nou->y, dimx*nou->x + 14, dimy*nou->y + 14, al_map_rgb(0,255,45));
	nou=nou->urm;
	}//restul sarpelui

}
void Init()
{
SARPE *nou;
sarpe = new SARPE;
nou = new SARPE;

sarpe->x=30;
sarpe->y=29;
sarpe->urm=nou;
nou->x=31;
nou->y=29;

nou = new SARPE;

sarpe->urm->urm=nou;
sarpe->urm->urm->x=32;
sarpe->urm->urm->y=29;
sarpe->urm->urm->urm=NULL;
//init sarpele primele 3 patratele


}
void Miscare()
{//miscam sarpele conform directiei
	bool g=true;
SARPE *nou;
nou = new SARPE;
switch(directie)
{ 
case UP:
			if(mt[sarpe->x][sarpe->y-1].typ!=0)
			done = true;
	        
			if(sarpe->x==mancarex && sarpe->y-1==mancarey)
			{
			g=false;
			}

		if(sarpe->y-1<0)
			nou->y=mty-1;
		else 
			nou->y=sarpe->y-1;

		nou->x=sarpe->x;
		direct=DOWN;
break;

case DOWN:




		if(sarpe->x==mancarex && sarpe->y+1==mancarey)
			{
			g=false;
			}

		
		if(sarpe->y+1>mty-1)
			nou->y=0;
		else
			nou->y=sarpe->y+1;

		if(mt[sarpe->x][sarpe->y+1].typ!=0)
			done = true;
		nou->x=sarpe->x;
		direct=UP;
break;

case LEFT:


				if(mt[sarpe->x-1][sarpe->y].typ!=0)
			done = true;
			if(sarpe->x-1==mancarex && sarpe->y==mancarey)
			{
			g=false;
			}


		if(sarpe->x-1<0)
			nou->x=mtx-1;
		else 
			nou->x=sarpe->x-1;

		nou->y=sarpe->y;
		direct=RIGHT;
break;

case RIGHT:

				if(mt[sarpe->x+1][sarpe->y].typ!=0)
			done = true;
			if(sarpe->x+1==mancarex && sarpe->y==mancarey)
			{
			g=false;
			}



		if(sarpe->x+1>mtx-1)
			nou->x=0;
		else
			nou->x=sarpe->x+1;

		nou->y=sarpe->y;
		direct=LEFT;
break;
}
nou->urm=sarpe;
sarpe=nou;



	while(nou->urm->urm!=NULL)
	{
	nou=nou->urm;
	}
	if(g==true)nou->urm=NULL;
	else generaremancare();
}
void generaremancare()
{
	srand (time(NULL));
	mancarex=rand()%mtx;
	mancarey=rand()%mty;
	punctaj=punctaj+10;
	//generam mancare pe harta
}