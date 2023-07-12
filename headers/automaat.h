/**
* automaat.h
* Luuk Daleman (3323560)
* Mirza (s3278395)
* Main
* 19/11/2022 
**/


#include <iostream>
#include <vector>
#include <deque> //used as queue with clear
#include <queue>
#include <string>
#include <tuple>
#include <algorithm> //sort
#include <sstream>
#include <fstream>

enum Tokens{//token types
    STAR,
    BAR,
    VAR,
    OPAR,
    CPAR,
    CAT
};

class Automaat{
public:
    Automaat();
    ~Automaat();

    //plakt simpelweg 2 achter 1
    Automaat plus(Automaat const Aut2);
    //zorgt ervoor dat de laatste node van Aut1 naar de eerste node van Aut2 wijst en plakt 2 achter 1
    Automaat concat(Automaat const Aut2);

    std::vector<std::tuple<int,std::string,int,int>> & getNodes();
    void pop(); //Nodes.pop_back()

    void printAuto();
    void writeDotWrap(std::string & file);
    void writeDot(std::ofstream & output);
    std::vector<std::tuple<int,std::string,int,int>> sortNodes();

    bool match(std::string input);

private:
    //tupel is figuur 3 van opdr
    //NodeNr, string(var), path 1, path 2
    std::vector<std::tuple<int,std::string,int,int>> Nodes;
};