/*----------------------------------------------------------------------
# Periodic value generator
#-----------------------------------------------------------------------
#  @file         periodicGenerator.cpp
#  @author       Prathosh
------------------------------------------------------------------------
*/

#include "periodicGenerator.hpp"
#include <iostream>
#include <math.h>
#include <thread>
#include <chrono>
#include <functional>
#include <vector>
#include <time.h>

const std::vector<int> g_frequencyVec = {5000,10000};
const std::vector<int> g_amplitudeVec = {2,5};
const int g_milliSecondInterval = 16;



periodicGenerator::periodicGenerator(std::shared_ptr<commGenerator> ptr,int duration=1000):
        m_generationDuration(duration),m_pComm(ptr){
    std::cout<<"periodicGenerator()"<<std::endl;
}


periodicGenerator::~periodicGenerator(){
    std::cout<<"~periodicGenerator()"<<std::endl;
}


void periodicGenerator::startGeneration(){

    auto startTime = std::chrono::system_clock::now();
    std::thread([this,durationSeconds=m_generationDuration,startTime]() {
        while (true)
        {
            auto funcStartTime = std::chrono::system_clock::now();
            double pulseVal = generatePulse();
            auto currentTime = std::chrono::system_clock::now();
            auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime-startTime);
            auto funcElapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime-funcStartTime);
            std::cout<<"periodicGenerator::startGeneration : funcElapsedTime : "<< funcElapsedTime.count()<<std::endl;
            std::cout<<"periodicGenerator::startGeneration: elapsedTime : "<<elapsedTime.count()<<std::endl;

            if(!(m_pComm->updateValue(pulseVal))){
                std::cerr<<"periodicGenerator::startGeneration : updateValue failed"<<std::endl;
            }   
            
            if(elapsedTime.count() >= durationSeconds*1000){
                std::cout<<"periodicGenerator::startGeneration : Timer elapsed. Ending pulse generation!"<<std::endl;
                break;
            }
            
            if(funcElapsedTime.count() >= g_milliSecondInterval){
                std::cout<<"periodicGenerator::startGeneration : funcElapsedTime is greater than interval. Therefore no sleep! "<<funcElapsedTime.count()<<std::endl;
            } else{
                auto ms = (std::chrono::milliseconds)(g_milliSecondInterval)- funcElapsedTime;
                std::cout<<"periodicGenerator::startGeneration: Sleeping for : "<< ms.count() << std::endl;
                std::this_thread::sleep_for(ms);
            }
            
        }
    }).join();

}


double periodicGenerator::generatePulse(){
    double result = 0;
    time_t seconds = time(NULL);
    for(size_t  i=0; i<g_frequencyVec.size(); i++){
        auto val = g_amplitudeVec[i]*sin(2*3.14159*g_frequencyVec[i]*seconds);
        std::cout<<"periodicGenerator::generatePulse(): Initial vals : "<< val<<std::endl;
        result+=val;
    }
    std::cout<<"periodicGenerator::generatePulse() : generated pulse value : "<<result<<std::endl;
    return result;
}