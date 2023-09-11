/*----------------------------------------------------------------------
# interface with the pipe library to send values
#-----------------------------------------------------------------------
#  @file         commGenerator.cpp
#  @author       Prathosh
------------------------------------------------------------------------
*/

#include "pipe.hpp"
#include "commGenerator.hpp"
#include <iostream>



const std::string g_pipeName = "/tmp/ipc_pipe";
const int g_pipePermissions = 0666;


commGenerator::commGenerator():m_pipeDescriptor(-1){
    std::cout<<"commGenerator::commGenerator()"<<std::endl;
}


commGenerator::~commGenerator(){
    std::cout<<"commGenerator::~commGenerator()"<<std::endl;
}


bool commGenerator::createPipe(){
    std::cout<<"commGenerator::createPipe()"<<std::endl;
    bool result = pipecomm::createPipe(g_pipeName,g_pipePermissions);
    if(!result){
        std::cerr<<"commGenerator::createPipe() : failed!!"<<std::endl;
        return false;
    }

    std::cout<<"commGenerator::createPipe() succesful "<<std::endl;
    return true;
}


bool commGenerator::openPipe(const int& mode){
    std::cout<<"commGenerator::openPipe()"<<std::endl;
    m_pipeDescriptor = pipecomm::openPipe(g_pipeName,mode);
    if(m_pipeDescriptor<0){
        std::cerr<<"commGenerator::openPipe() : failed!!"<<std::endl;
        return false;
    }

    std::cout<<"commGenerator::openPipe() : m_pipeDescriptor : "<<m_pipeDescriptor<<std::endl;
    return true;
}


bool commGenerator::isClientReady(){
    std::cout<<"commGenerator::isClientReady()"<<std::endl;
    if(pipecomm::isPipeWriteReady(g_pipeName)){
        std::cout<<"commGenerator::isClientReady() client ready!"<<std::endl;
        return true;
    }

    std::cout<<"commGenerator::isClientReady() client not ready!"<<std::endl;
    return false;
}


bool commGenerator::updateValue(double val){
    std::cout<<"commGenerator::updateValue()"<<std::endl;
    if(pipecomm::writeData(m_pipeDescriptor, val, sizeof(val))){
        std::cout<<"commGenerator::updateValue(): writeData successful."<<std::endl;
        return true;
    }

    std::cerr<<"commGenerator::updateValue() : writeData unsuccessful."<<std::endl;
    return false;

}


void commGenerator::closePipe(){
    std::cout<<"commGenerator::updateValue()"<<std::endl;
    pipecomm::closePipe(m_pipeDescriptor, g_pipeName);
}