/**
* main.cc
* Luuk Daleman (3323560)
* Mirza (s3278395)
* Main
* 19/11/2022 
**/
#include "../headers/parser.h"


//Menu functie met parameter debugMode. Deze functie wordt aangeroepen in main.
//Als debugMode false is krijgt de gebruiker een menu te zien.
//Opties in de menu worden aangeroepen door de eerste argument van de invoer.
void menu(bool debugMode){
    std::string invoer;
    Automaat automaat;
    if (!debugMode){//men te zien als debugMode false is
        std::cout <<"Menu opties:\n"
        <<"--de laatst ingelezen expressie wordt voor de rest van de opties gebruikt--\n"
        <<"-exp <expressie>\n"
        <<"-print\n"
        <<"-dot\n"
        <<"-mat <string>\n"
        <<"-end\n" 
        <<"uw invoer: "<<std::endl;
    }
    while (getline(std::cin, invoer)){ //leest de invoer van de gebruiker
        //deze variablen worden elke loop opnieuw gemaakt zodat er geen rare dingen achterblijven
        std::stringstream ss;//stringstream om de invoer te splitsen
        std::string arg1;
        std::string arg2;
        ss << invoer;
        ss >> arg1;
        ss >> arg2;
        if (arg1 == "exp" && !(arg2.empty())){//maakt nieuw parser object aan
            Parser parser;
            if (! parser.tokenizer(arg2)){//maakt tokens aan
                std::cerr << "Error: Ongeldige exp Invoer " << std::endl;
            }
            else{
                automaat = parser.Expr();//maakt automaat aan
                if (parser.errorHandling()){
                    automaat = Automaat(); //maak een nieuwe Automaat om te resetten
                }
            }
        }
        //als er geen object/boom is
        else if (automaat.getNodes().empty() && (arg1 == "print" || arg1 == "dot" || arg1 == "mat")){
            std::cout <<"voer eerst een regex in voordat " << arg1 
            << " wordt aangeroepen" <<std::endl;
            continue;
        }

        else if (arg1 == "print"){//print de regex
            automaat.printAuto();
            std::cout << std::endl;
        }
        
        else if (arg1 == "dot"){//print de regex in dot formaat
            automaat.writeDotWrap(arg2);
        }
            
        else if (arg1 == "mat"){//kijkt of de regex matcht met de string
            if (arg2.empty()){
                std::cout << "geen string meegegeven" << std::endl;
                continue;
            }

            if (automaat.match(arg2)){
                std::cout << "match" << std::endl;
            }
            else{
                std::cout << "geen match" << std::endl;
            }
        }

        else if (arg1 == "end"){//eindigt het programma
            break;
        }

        else if (arg1 != "") { //als de invoer niet leeg is
            std::cout << arg1 << std::endl;
            std::cout << "Error: Verkeerde invoer, zie menu" << std::endl;
        }
    }
}


//main functie
//als er argumenten zijn wordt debugMode true
//blijkbaar telt '< .txt' niet als argument
//dus debug is altijd true
int main(int argc, char** argv){
    bool debugMode = true;
    std::string textfile;
    if(argc < 2){
        debugMode = false;
    }
    menu(debugMode);
    return 0;
}
