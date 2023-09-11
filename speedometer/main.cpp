/*----------------------------------------------------------------------
# speedometer main.cpp
#-----------------------------------------------------------------------
#  @file         main.cpp
#  @author       Prathosh
------------------------------------------------------------------------
*/

#include <iostream>
#include <memory>
#include "comm_meter/commMeter.hpp"
#include "meter/meterLogic.hpp"
#include <fcntl.h>
#include <QWidget>
#include <QApplication>

int main(int argc, char *argv[]){
    
    int durationVal = 100;
    /*std::cout<<"main():: Enter the duration for which you want the pulses to be genearted in seconds. eg: 100"<<std::endl;
    std::cin>>durationVal;*/
    QApplication app(argc, argv);

    std::shared_ptr<commMeter> commMeterPtr = std::make_shared<commMeter>();
    std::shared_ptr<QWidget> qWidgetPtr = std::make_shared<QWidget>();
    std::shared_ptr<meterLogic> meterLogicPtr = std::make_shared<meterLogic>(commMeterPtr, qWidgetPtr, durationVal);
    

    if(!(commMeterPtr->openPipe(O_RDONLY))){
        std::cerr<<"main():: openPipe not successful Successful!"<<std::endl;
        exit(-1);
    }
    
    meterLogicPtr->startGuiDisplay();

    std::cout<<"main():: dispaly completed. closing pipe."<<std::endl;

    commMeterPtr->closePipe();

    return app.exec();
}