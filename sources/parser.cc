/**
* parser.cc, tokenized en parsed de input tot een Automaat object.
* Luuk Daleman (3323560)
* Mirza (s3278395)
* Main
* 19/11/2022 
**/



#include "../headers/parser.h"

Parser::Parser()
{   //constructor
    stateCount = 1;
    noCPAR = false;
    noVarPar = false;
}

Parser::~Parser()
{
}

//maakt tokens aan van de invoer
bool Parser::tokenizer(std::string input)
{
    for (size_t i = 0; i<input.length(); i++){
        int Tok;
        char kar = input[i];
        switch (kar){
            case '|':
                Tok = Tokens::BAR;
                break;

            case '*':
                Tok = Tokens::STAR;
                break;

            case '(':
                Tok = Tokens::OPAR;
                break;

            case ')':
                Tok = Tokens::CPAR;
                break;

            default:
                if (isspace(kar))
                    continue; //sla pair over
                if (kar >= 'a' && kar <= 'z')
                    Tok = Tokens::VAR;
                else //invalid character
                    return false;
                break;
        }
        //maak pair aan met enum van token en de char
        //(1, kar) nodig om letter te printen ipv ascii
        tokenDeq.push_back(std::make_pair(Tok,std::string(1, kar)));
    }
    return true;
}

//verwijdert het eerste element van de deque
void Parser::consumeToken()
{
    tokenDeq.pop_front();
}

//Recursieve decent parser
Automaat Parser::Expr()
{
    Automaat Aut1 = Term();//naar Term
    
    Automaat Aut2;
    if (!(tokenDeq.empty()) && tokenDeq.front().first == Tokens::BAR)
    { //als er een | is
        consumeToken();
        Aut2 = Expr(); 

        //wijs laatste states van | naar eind state
        std::get<2>(Aut1.getNodes().back()) = stateCount+1;
        std::get<2>(Aut2.getNodes().back()) = stateCount+1;

        //extra nodes voor |, 1 voor de of cirkel, 1 na.
        //voeg node helemaal vooraan toe die wijzen naar de splitsing
        Aut1.getNodes().insert(Aut1.getNodes().begin(),std::make_tuple(stateCount,"-",
        std::get<0>(Aut1.getNodes().front()),std::get<0>(Aut2.getNodes().front())));
        
        stateCount++;
        Aut2.getNodes().push_back(std::make_tuple(stateCount,"-",0,0));
        stateCount++;
    }
    return Aut1.plus(Aut2);//voeg de 2 automaten samen
}

Automaat Parser::Term()
{
    Automaat Aut1 = Fact();
    Automaat Aut2;
    if (!(tokenDeq.empty()) && (tokenDeq.front().first == Tokens::VAR || 
                                tokenDeq.front().first == Tokens::OPAR)){
        Aut2 = Term();
    }
    return Aut1.concat(Aut2);//verbind de 2 automaten
}

Automaat Parser::Fact()
{ 
    Automaat Aut;
    if (!(tokenDeq.empty()) && tokenDeq.front().first == Tokens::OPAR)
    {//als er een haakje open is
        consumeToken();
        Aut = Expr() ;
        if (!(tokenDeq.empty()) && tokenDeq.front().first == Tokens::CPAR)
            consumeToken();//haakje sluiten
        
        else{//er is geen sluit haakje
            noCPAR = true;
            tokenDeq.clear();
            return Aut;
        }
    }
    else if (!(tokenDeq.empty()) && tokenDeq.front().first == Tokens::VAR)
    {   //als er een letter is
        Aut = Lett();
        consumeToken();
    }
    else{//er is geen letter of haakje open
        noVarPar = true;
        tokenDeq.clear();
        return Aut;
    }

    if (!(tokenDeq.empty()) && tokenDeq.front().first == Tokens::STAR)
    {
        std::get<2>(Aut.getNodes().back()) = std::get<0>(Aut.getNodes().front());//wijs de laatste state naar de begin state van Term()
        std::get<3>(Aut.getNodes().back()) = stateCount+1;//wijs de laatste state naar de laatste state van Term()
        
        //extra nodes voor *, 1 voor de * cirkel, 1 na.
        //insert node voor het hele gebeuren van Term(), zelfde states wijzen als de laatste node van Term()
        Aut.getNodes().insert(Aut.getNodes().begin(),(std::make_tuple(stateCount,"-",
        std::get<2>(Aut.getNodes().back()),std::get<3>(Aut.getNodes().back()))));
        stateCount++;
        //maak een eind state van Term()
        Aut.getNodes().push_back(std::make_tuple(stateCount,"-",0,0));
        stateCount++;
        consumeToken();
    }
    return Aut;
}

//maakt een node aan van een letter
Automaat Parser::Lett()
{
    Automaat Aut;
    std::string kar = tokenDeq.front().second;//pak letter van eerste token
    //push node dat wijst naar state+1
    Aut.getNodes().push_back(std::make_tuple(stateCount,kar,stateCount+1,0));
    stateCount++;
    //push volgende node van letter
    Aut.getNodes().push_back(std::make_tuple(stateCount,"-",0,0));
    stateCount++;
    return Aut;
}

//Wanneer errors voorkomen
bool Parser::errorHandling() const
{
    if (noVarPar){
        std::cout << "Eerste karakter van expressie" <<
        " (eerste letter of na \"(\" of \"|\") is geen var of haakje openen" << std::endl;
        return true;
    }
    if (noCPAR){
        std::cout << "Geen haakje sluiten na haakje openen" << std::endl;
        return true;
    }
    return false;
}