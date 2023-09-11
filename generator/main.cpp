/*----------------------------------------------------------------------
# Periodic value generator application main.cpp
#-----------------------------------------------------------------------
#  @file         main.cpp
#  @author       Prathosh
------------------------------------------------------------------------
*/

#include <iostream>
#include <memory>
#include "comm_generator/commGenerator.hpp"
#include "value_generator/periodicGenerator.hpp"
#include <fcntl.h>

int main(){
    
    int durationVal = 100;
    /*std::cout<<"main():: Enter the duration for which you want the pulses to be genearted in seconds. eg: 100"<<std::endl;
    std::cin>>durationVal;*/

    std::shared_ptr<commGenerator> commGeneratorPtr = std::make_shared<commGenerator>();
    std::shared_ptr<periodicGenerator> periodGenPtr = std::make_shared<periodicGenerator>(commGeneratorPtr,durationVal);

    if(!(commGeneratorPtr->createPipe())){
        std::cerr<<"main():: createPipe not Successful!"<<std::endl;
        exit(-1);
    }

    if(!(commGeneratorPtr->openPipe(O_WRONLY))){
        std::cerr<<"main():: openPipe not successful Successful!"<<std::endl;
        exit(-1);
    }
    
    std::cout<<"main():: Waiting for client to start reading. !"<<std::endl;
    while(!(commGeneratorPtr->isClientReady()));

    std::cout<<"main():: client ready. Starting generation !"<<std::endl;
    periodGenPtr->startGeneration();


    std::cout<<"main():: generation completed. closing pipe."<<std::endl;

    commGeneratorPtr->closePipe();

    return 0;
}