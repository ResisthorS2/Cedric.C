/* 
 * Auteurs: Jean-Samuel Lauzon    
 * Date: Fevrier 2022
 * Modif : Janvier 2023, Compatible VisualStudio, JpGouin
*/

/*------------------------------ Librairies ---------------------------------*/
#include <iostream>
#include <string>


/*-------------------------- Librairies externes ----------------------------*/

#include "include/serial/SerialPort.hpp"
#include "include/json.hpp"
using json = nlohmann::json;

/*------------------------------ Constantes ---------------------------------*/
#define BAUD 9600           // Frequence de transmission serielle
#define MSG_MAX_SIZE 1024   // Longueur maximale d'un message


/*------------------------- Prototypes de fonctions -------------------------*/
bool SendToSerial(SerialPort *arduino, json j_msg);
bool RcvFromSerial(SerialPort *arduino, std::string &msg);


/*---------------------------- Variables globales ---------------------------*/
SerialPort * arduino; //doit etre un objet global!

/*----------------------------- Fonction "Main" -----------------------------*/




#ifndef MAP_H
#include "C:\Users\cedri\OneDrive\Bureau\S2\project\Code\Cedric.C\PC\src\map.h"
#endif



int main(){
    
    #define TEST 0

    if (TEST == 0){
        
        char com[] = "\\\\.\\COM4"; 
        arduino = new SerialPort(com, BAUD);
        if(!arduino->isConnected()){
            std::cerr << "Impossible de se connecter au port "<< std::string(com) <<". Fermeture du programme!" <<std::endl;
            exit(1);
        }
        while(1)
        {
            
            json j_msg_rcv;
            std::string raw_msg;

            if(!RcvFromSerial(arduino, raw_msg))
            {
                std::cerr << "Erreur lors de la reception du message. " << std::endl;
            }

            if(raw_msg.size()>0)
            {
                //std::cout << "raw_msg: " << raw_msg << std::endl;  // debug
                // Transfert du message en json
                j_msg_rcv = json::parse(raw_msg);
                std::cout << "Message de l'Arduino: " << j_msg_rcv << std::endl;
            }

            
            if(j_msg_rcv["droit"] == "HIGH")
            {
                printf("droit\n");  
            }

            if(j_msg_rcv["haut"] == "HIGH")
            {
                printf("haut\n");  
            }

            if(j_msg_rcv["gauche"] == "HIGH")
            {
                printf("gauche\n");  
            }

            if(j_msg_rcv["bas"] == "HIGH")
            {
                printf("bas\n");  
            }

            Sleep(1000);
        }
        
    }

    if(TEST != 1)
    {
        Map map;
        std::string raw_msg;

        // Initialisation du port de communication
        /*std::string com;
        std::cout << "Entrer le port de communication du Arduino: ";
        cin >> com;
        arduino = new SerialPort(com.c_str(), BAUD);*/
        
        char com[] = "\\\\.\\COM4"; 
        arduino = new SerialPort(com, BAUD);
        if(!arduino->isConnected()){
            std::cerr << "Impossible de se connecter au port "<< std::string(com) <<". Fermeture du programme!" <<std::endl;
            exit(1);
        }
        
        // Structure de donnees JSON pour envoie et reception
        int led_state = 1;
        json j_msg_send, j_msg_rcv;

        // Boucle pour tester la communication bidirectionnelle Arduino-PC
        while(1)
        {
            if(!RcvFromSerial(arduino, raw_msg)){
                std::cerr << "Erreur lors de la reception du message. " << std::endl;
            }
            
            // Impression du message de l'Arduino si valide
            if(raw_msg.size()>0){
                //std::cout << "raw_msg: " << raw_msg << std::endl;  // debug
                // Transfert du message en json
                j_msg_rcv = json::parse(raw_msg);
                std::cout << "Message de l'Arduino: " << j_msg_rcv << std::endl;
            }

            if(j_msg_rcv["Charle"] == "22")
            {
                map.move180();  
            }

            if(j_msg_rcv["btn_up"] == "HIGH")
            {
                map.moveUp();
            }

            if(j_msg_rcv["btn_left"] == "HIGH")
            {
                map.moveLeft();
            }

            if(j_msg_rcv["btn_right"] == "HIGH")
            {
                map.moveRight();
            }
            
            map.printMap();
            Sleep(1000); // 1000ms
        }
    }

    if(TEST == 1)
    {
        Map map;
        std::cout << "Test de la classe Map" << std::endl;;
        

        while(true)
        {
            map.printMap();
            char input;
            
            std::cin>>input;
            std::cout<< "input "<<input<<std::endl;
            
            switch (input)
            {
            case 'p':
                std::cout<<"Coordonne X : "<<map.getCo_X()<<"\t Coordonne Y : "<<map.getCo_Y()<<"\t Orientation"<<map.getOrientation()<<std::endl;
                break;
            case 'w':
                map.moveUp();
                break;
            
            case 'a':
                map.moveLeft();
                break;
            
            case 's':
                map.move180();
                break;
            case 'd':
                map.moveRight();	
                break;
            }
            map.updateMap();
        }
        
        /*
        for(int y=0; y<map.hauteur; y++)
        {
            for(int i=0; i<map.largeur; i++)
            {
                std::cout << "Cellule [" << i << "][" << y << "] : " << std::endl;
                
                std::cout << "XXX" <<std::endl;
            }
        }*/
    }

    return 0;
}



/*---------------------------Definition de fonctions ------------------------*/
bool SendToSerial(SerialPort *arduino, json j_msg)
{
    // Return 0 if error
    std::string msg = j_msg.dump();
    bool ret = arduino->writeSerialPort(msg.c_str(), msg.length());
    return ret;
}


bool RcvFromSerial(SerialPort *arduino, std::string &msg){
    // Return 0 if error
    // Message output in msg
    std::string str_buffer;
    char char_buffer[MSG_MAX_SIZE];
    int buffer_size;

    msg.clear(); // clear std::string
    // Read serialport until '\n' character (Blocking)

    // Version fonctionnel dans VScode, mais non fonctionnel avec Visual Studio
/*  
    while(msg.back()!='\n'){
        if(msg.size()>MSG_MAX_SIZE){
            return false;
        }

        buffer_size = arduino->readSerialPort(char_buffer, MSG_MAX_SIZE);
        str_buffer.assign(char_buffer, buffer_size);
        msg.append(str_buffer);
    }
*/

    // Version fonctionnelle dans VScode et Visual Studio
    buffer_size = arduino->readSerialPort(char_buffer, MSG_MAX_SIZE);
    str_buffer.assign(char_buffer, buffer_size);
    msg.append(str_buffer);

    //msg.pop_back(); //remove '/n' from std::string

    return true;
}

