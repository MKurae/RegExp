/**
* parser.h
* Luuk Daleman (3323560)
* Mirza (s3278395)
* Main
* 19/11/2022 
**/



#include "automaat.h"

class Parser
{
public:
    Parser();
    ~Parser();

    bool tokenizer(std::string const input);
    void consumeToken();
    
    Automaat Expr(); 
    Automaat Term();
    Automaat Fact();
    Automaat Lett();

    bool errorHandling() const;

private:
    int stateCount;//counter voor de states
    bool noCPAR; //true als er geen haakje sluiten is
    bool noVarPar; //geen var of haakje openen als eerste kar van (nieuwe) expr
    bool noBar; //geen bar maar wel nog een string over

    //vector met front operaties zoals pop_front()
    std::deque<std::pair<int,std::string>> tokenDeq;
};
