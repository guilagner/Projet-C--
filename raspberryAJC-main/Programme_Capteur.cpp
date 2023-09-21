//INCLUSION DES LIBRAIRIES
#include <iostream>
#include <wiringPi.h>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <csignal>


//DEFINITION DE NOS VARIABLES GLOBALES CORRESPONDANT AUX GPIO
#define PIR 12
#define RED_LED 21
#define YELLOW_LED 20
#define GREEN_LED 16

using namespace std;

/*
 	signalHandler(int signum);
 
	Fonction permettant d'éteindre les diodes si un des signaux suivant est récupérés: 
	 - résilation
	 - instruction illégale 
         - avortation  
	 - intérruption
 */
void signalHandler(int signum)
{
	if (signum == SIGTERM 
		|| signum == SIGILL
		|| signum == SIGABRT
		|| signum == SIGINT)
	{
	 	digitalWrite(RED_LED, LOW);
		digitalWrite(YELLOW_LED, LOW);
		digitalWrite(GREEN_LED, LOW);
		exit(signum);
 	}
}


/*
	void capteur();

	Fonction permettant l'allumages des LEDS selon les conditions
       	précisées dans le cahier des charges.
	Elle envoie pour cela des signaux aux GPIO de notre carte.
*/
void capteur()
{
	/*
		Cette variable sert à déterminer le temps écoulé depuis le début 
		de la détection d'une présence par le capteur
	*/
	int compteur;
	
	compteur = 0;
	
	//Initialise wiringPi
	wiringPiSetupGpio();

	//initialisation du capteur de signaux
	signal(SIGINT, signalHandler);

	//Déclaration des fonctions de nos PINs
	pinMode(PIR, INPUT);
	pinMode(GREEN_LED, OUTPUT);
	pinMode(YELLOW_LED, OUTPUT);
	pinMode(RED_LED, OUTPUT);
	
	while(true)
	{
		//Condition remplie si le capteur ne détecte aucune présence
		if(digitalRead(PIR))
		{
			compteur = 0;
			digitalWrite(RED_LED, LOW);
			digitalWrite(YELLOW_LED, LOW);
			digitalWrite(GREEN_LED, HIGH);
		}
		//Condition remplie si le capteur détecte une présence
		else
		{
			digitalWrite(GREEN_LED, LOW);
			
			//Condition remplie si le capteur détecte une présence depuis plus de 1.5 seconde
			if(compteur >= 30)
			{
				digitalWrite(RED_LED, HIGH);
				digitalWrite(YELLOW_LED, LOW);
			}
			//Condition remplie si le capteur détecte une présence depuis moins de 1.5 seconde
			else
				digitalWrite(YELLOW_LED, HIGH);
		
			compteur++;
		}
		//Attente de 50ms entre l'exécution des commandes pour éviter de surcharger la mémoire vive
		this_thread::sleep_for(chrono::milliseconds(50));
	}
}

/* 
	int main();
	
	La fonction main reste la moins encombrée possible vide par respect de nomenclature	
*/
int main()
{
	capteur();

	return 0;
}
