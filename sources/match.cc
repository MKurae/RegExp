/**
* match.cc, werkt de functies gerelateerd aan een matchen uit
* Luuk Daleman (3323560)
* Mirza (s3278395)
* Main
* 19/11/2022 
**/
#include "../headers/parser.h"

//match string with regex
//let op: NodeNr is 1 based en Nodes, adjList en mark zijn 0 based.
bool Automaat::match(std::string input){
    std::queue<std::tuple<int,std::string,int,int>> Queue;
    bool mark[Nodes.size()] = {false}; //init op false (maak zo lang als Nodes)
    Queue.push(Nodes.front()); //eerste node om de automaat te activeren
    auto adjList = sortNodes();//sorteer de nodes om makkelijk te kunnen zoeken
    
    char kar;
    try{
        kar = input.at(0);
    }
    catch(const std::out_of_range& e){ //als de string leeg is gebruik $
        kar = '$'; //empty string
    }
    while (!Queue.empty()){
        auto curState = Queue.front();//pak de voorste node
        Queue.pop(); //remove from queue
        //check mark
        if (mark[std::get<0>(curState)-1]){ //NodeNr-1 as index
            continue;
        }
        mark[std::get<0>(curState)-1] = true;

        //epsilon transistie
        if (std::get<1>(curState) == "-"){ 
            if (std::get<2>(curState) == 0){//accepting state
                if (kar == '$')
                    return true;
                mark[std::get<0>(curState)-1] = true;
            }
            else{
                //path 1 to queue
                Queue.push(adjList[std::get<2>(curState)-1]); 
                //path 2 to queue
                if (std::get<3>(curState) != 0)
                    Queue.push(adjList[std::get<3>(curState)-1]); 
            }
        }
        else if (std::get<1>(curState) == std::string(1, kar)){ 
            input.erase(0,1); 
            try{ //pak volgende char
                kar = input.at(0); 
            }
            catch(const std::out_of_range& e){
                kar = '$'; //empty string symbool
            }
            //als een letter is geaccepteerd, wordt de marked array geleegd.
            //Dit is zodat wel een loop kunnen maken, maar niet eeuwig in een
            //epsilon transitie loop blijven.
            Queue.push(adjList[std::get<2>(curState)-1]);
            for (size_t i = 0; i<Nodes.size(); i++){
                mark[i] = false;
            }
        }
    }
    return false; 
}
