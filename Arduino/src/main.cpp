/* 
 * Auteurs: Jean-Samuel Lauzon    
 * Date: Fevrier 2022
*/

/*------------------------------ Librairies ---------------------------------*/
#include <Arduino.h>
#include <ArduinoJson.h>

/*------------------------------ Constantes ---------------------------------*/

#define BAUD 9600        // Frequence de transmission serielle

/*---------------------------- Variables globales ---------------------------*/

volatile bool shouldSend_ = false;  // Drapeau prêt à envoyer un message
volatile bool shouldRead_ = false;  // Drapeau prêt à lire un message


int pinLED = 38;


/*------------------------- Prototypes de fonctions -------------------------*/
void sendMsg(); 
void readMsg();
void serialEvent();
/*---------------------------- Fonctions "Main" -----------------------------*/

void setup() {
  Serial.begin(BAUD);               // Initialisation de la communication serielle
  pinMode(pinLED, OUTPUT);
  digitalWrite(pinLED, 1);

  pinMode(22, INPUT_PULLUP);
}

/* Boucle principale (infinie) */
void loop() {

  StaticJsonDocument<500> doc;
  if(digitalRead(22) == HIGH)
  {
    while(digitalRead(22) == HIGH){delay(10);}
    
    // Serialisation
    doc["droit"] = "HIGH";
    serializeJson(doc, Serial);

    // Envoie
    Serial.println();
  }

  if(digitalRead(23) == HIGH)
  {
    while(digitalRead(23) == HIGH){delay(10);}
    
    // Serialisation
    doc["haut"] = "HIGH";
    serializeJson(doc, Serial);

    // Envoie
    Serial.println();
  }

  if(digitalRead(24) == HIGH)
  {
    while(digitalRead(24) == HIGH){delay(10);}

    // Serialisation
    doc["gauche"] = "HIGH";
    serializeJson(doc, Serial);

    // Envoie
    Serial.println();
  }

  if(digitalRead(25) == HIGH)
  {
    while(digitalRead(25) == HIGH){delay(10);}

    // Serialisation
    doc["bas"] = "HIGH";
    serializeJson(doc, Serial);

    // Envoie
    Serial.println();
  }


  //Serial.println(potValue);          // debug
  delay(10);  // delais de 10 ms
}

/*---------------------------Definition de fonctions ------------------------*/

void serialEvent() { shouldRead_ = true; }


/*---------------------------Definition de fonctions ------------------------
Fonction d'envoi
Entrée : Aucun
Sortie : Aucun
Traitement : Envoi du message
-----------------------------------------------------------------------------*/
void sendMsg() {
  StaticJsonDocument<500> doc;
  // Elements du message
  doc["time"] = millis();

  // Serialisation
  serializeJson(doc, Serial);

  // Envoie
  Serial.println();
  shouldSend_ = false;
}

/*---------------------------Definition de fonctions ------------------------
Fonction de reception
Entrée : Aucun
Sortie : Aucun
Traitement : Réception du message
-----------------------------------------------------------------------------*/
void readMsg(){
  // Lecture du message Json
  StaticJsonDocument<500> doc;
  JsonVariant parse_msg;

  // Lecture sur le port Seriel
  DeserializationError error = deserializeJson(doc, Serial);
  shouldRead_ = false;

  // Si erreur dans le message
  if (error) {
    Serial.print("deserialize() failed: ");
    Serial.println(error.c_str());
    return;
  }
  
  // Analyse des éléments du message message
  parse_msg = doc["led"];
  if (!parse_msg.isNull()) {
    // mettre la led a la valeur doc["led"]
    digitalWrite(pinLED,doc["led"].as<bool>());
  }
}