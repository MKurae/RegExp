/**
* automaat.cc, uitwerking automaat klasse methodess
* Luuk Daleman (3323560)
* Mirza (s3278395)
* Main
* 19/11/2022
**/

#include "../headers/automaat.h"

Automaat::Automaat()
{
}

Automaat::~Automaat()
{    
}


//haalt bovenste node van de stack
void Automaat::pop()
{
    return Nodes.pop_back();
}

//returns de vector met nodes
std::vector<std::tuple<int,std::string,int,int>> & Automaat::getNodes()
{
    return Nodes;
}

Automaat Automaat::plus(Automaat Aut2)//of
{
    if (Aut2.Nodes.empty()){//als Auto2 leeg is
        return *this;
    }
    else if (Nodes.empty()){//als Auto1 leeg is
        return Aut2;
    }
    else{//zet Aut2 achter Aut1
        Nodes.insert(Nodes.end(), Aut2.Nodes.begin(), Aut2.Nodes.end());
        return *this;
    }
}

Automaat Automaat::concat(Automaat Aut2)//star
{
    if (!(Aut2.Nodes.empty() || Nodes.empty()))
        std::get<2>(Nodes.back()) = std::get<0>(Aut2.Nodes[0]);
    return plus(Aut2);
}

//Zet de dot notatie in een .dot file
void Automaat::writeDotWrap(std::string& file){
    std::ofstream output;
    if (file == "")
        output.open("dotFile.dot");
    
    else
        output.open(file);
    
    output << "digraph G {" << std::endl;
    output << "rankdir=\"LR\"" << std::endl;
    writeDot(output); //gaat de nodes af en vult output in
    output << "}";
    output.close();
}


void Automaat::writeDot(std::ofstream &output){
    for (size_t i = 0; i < Nodes.size(); i++){
        //output << nodeNr -> path 1 [label="var"] (als er een label nodig is)
        if (std::get<2>(Nodes[i]) != 0){ //path 1 != 0
            output << "\t" << std::get<0>(Nodes[i]) << "->" << std::get<2>(Nodes[i]);
            if (std::get<1>(Nodes[i]) != "-"){ 
                output << " [label=\"" << std::get<1>(Nodes[i]) << "\"]";
            }
            output << std::endl;
        }
        //output << nodeNr -> path2 (geen label)
        if (std::get<3>(Nodes[i]) != 0){ //path 2 != 0
            output << "\t" << std::get<0>(Nodes[i]) << "->" << std::get<3>(Nodes[i]) << std::endl;
        }
    }
}



//print de nodes van de automaat in volgorde van states
bool compareStates(std::tuple<int,std::string,int,int> i1, std::tuple<int,std::string,int,int> i2)
{
    return std::get<0>(i1) < std::get<0>(i2);
}   

std::vector<std::tuple<int,std::string,int,int>> Automaat::sortNodes()
{
    std::vector<std::tuple<int,std::string,int,int>> sortedNodes = Nodes;
    std::sort(sortedNodes.begin(), sortedNodes.end(), compareStates);
    return sortedNodes;
}

// de strepen van figuur 3 bij de nummers zijn vervangen door nullen:
//  6   →   6    
//  -   →   -
//  7   →   7
//  -   →   0
//print de gesorteerde automaat in de terminal
void Automaat::printAuto()
{
    std::cout << std::endl;
    std::vector<std::tuple<int,std::string,int,int>> tempVec = sortNodes();
    
    //print nodes op volgorde
    for (size_t i = 0; i < tempVec.size(); i++){
        if (std::get<0>(tempVec[i]) >= 10){
            std::cout << std::get<0>(tempVec[i]) << " ";
        }
        else{
            std::cout << std::get<0>(tempVec[i]) << "  ";
        }
    }
    std::cout << std::endl;
    for (size_t i = 0; i < tempVec.size(); i++){
        std::cout << "---";
    }
    std::cout << std::endl;
    //print var rij
    for (size_t i = 0; i < tempVec.size(); i++){
        std::cout << std::get<1>(tempVec[i]) << "  ";
    }
    std::cout << std::endl;
    //print primair pad rij
    for (size_t i = 0; i < tempVec.size(); i++){
        if (std::get<2>(tempVec[i]) >= 10){
            std::cout << std::get<2>(tempVec[i]) << " ";
        }
        else{
            std::cout << std::get<2>(tempVec[i]) << "  ";
        }
    }
    std::cout << std::endl;
    //print secondair pad rij
    for (size_t i = 0; i < tempVec.size(); i++){
        if (std::get<3>(tempVec[i]) >= 10){
            std::cout << std::get<3>(tempVec[i]) << " ";
        }
        else{
            std::cout << std::get<3>(tempVec[i]) << "  ";
        }
    }
    std::cout << std::endl;
}