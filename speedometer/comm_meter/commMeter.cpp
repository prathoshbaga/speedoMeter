/*----------------------------------------------------------------------
# interface with the pipe library to send values
#-----------------------------------------------------------------------
#  @file         commMeter.cpp
#  @author       Prathosh
------------------------------------------------------------------------
*/

#include "pipe.hpp"
#include "commMeter.hpp"
#include <iostream>



const std::string g_pipeName = "/tmp/ipc_pipe";
const int g_pipePermissions = 0666;
const int g_defaultSpeedVal = -9999;


commMeter::commMeter():m_pipeDescriptor(-1){
    std::cout<<"commMeter::commMeter()"<<std::endl;
}


commMeter::~commMeter(){
    std::cout<<"commMeter::~commMeter()"<<std::endl;
}


bool commMeter::openPipe(const int& mode){
    std::cout<<"commMeter::openPipe()"<<std::endl;
    m_pipeDescriptor = pipecomm::openPipe(g_pipeName,mode);
    if(m_pipeDescriptor<0){
        std::cerr<<"commMeter::openPipe() : failed!!"<<std::endl;
        return false;
    }

    std::cout<<"commMeter::openPipe() : m_pipeDescriptor : "<<m_pipeDescriptor<<std::endl;
    return true;
}


bool commMeter::isPipeEmpty(){
    std::cout<<"commMeter::isPipeEmpty()"<<std::endl;
    if(pipecomm::isPipeEmpty(g_pipeName.c_str())){
        std::cout<<"commMeter::isPipeEmpty() : pipe empty.!"<<std::endl;
        return true;
    }

    std::cout<<"commMeter::isPipeEmpty() : pipe has data"<<std::endl;
    return false;

}


double commMeter::readData(){
    std::cout<<"commMeter::readData()"<<std::endl;
    double val;
    bool result = pipecomm::readData(m_pipeDescriptor, val, sizeof(val));
    std::cout<<"commMeter::readData() : value read is : "<<val<<std::endl;
    if(!result){
        std::cerr<<"commMeter::readData() : failed!!"<<std::endl;
        return g_defaultSpeedVal;
    }
    return val;
}


void commMeter::closePipe(){
    std::cout<<"commMeter::updateValue()"<<std::endl;
    pipecomm::closePipe(m_pipeDescriptor, g_pipeName);
}