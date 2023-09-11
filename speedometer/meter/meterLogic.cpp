/*----------------------------------------------------------------------
# meter logic
#-----------------------------------------------------------------------
#  @file         meterLogic.cpp
#  @author       Prathosh
------------------------------------------------------------------------
*/

#include "meterLogic.hpp"
#include <iostream>
#include <math.h>
#include <thread>
#include <chrono>
#include <functional>
#include <time.h>
#include <iomanip>
#include <QWidget>
#include <QApplication>

const int g_milliSecondInterval = 16; // to ensure 60fps
const double minSpeed = -6.0;
const double maxSpeed = 6.0;


meterLogic::meterLogic(std::shared_ptr<commMeter> ptr,std::shared_ptr<QWidget> qWdgtPtr, int duration=1000):
        m_pComm(ptr),m_displayDuration(duration){
            m_pSpeedoMeterUI = std::make_shared<SpeedometerUI>(qWdgtPtr);
    std::cout<<"meterLogic::meterLogic()"<<std::endl;
}


meterLogic::~meterLogic(){
    std::cout<<"meterLogic::~meterLogic()"<<std::endl;
}

void meterLogic::startGuiDisplay(){

    
    m_pSpeedoMeterUI->show();
    auto startTime = std::chrono::system_clock::now();
    double gaugeVal = 0;
    std::thread([this,durationSeconds=m_displayDuration,startTime, &gaugeVal]() {
        while (true)
        {
            auto funcStartTime = std::chrono::system_clock::now();

            gaugeVal = m_pComm->readData();
            QMetaObject::invokeMethod(m_pSpeedoMeterUI.get(), "setSpeed", Qt::QueuedConnection, Q_ARG(double, gaugeVal));
            //emit m_pSpeedoMeterUI->setSpeed(gaugeVal);
            showTerminalRange(gaugeVal);

            auto currentTime = std::chrono::system_clock::now();
            auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime-startTime);
            auto funcElapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime-funcStartTime);
            std::cout<<"meterLogic::startGuiDisplay : funcElapsedTime : "<< funcElapsedTime.count()<<std::endl;
            std::cout<<"meterLogic::startGuiDisplay: elapsedTime : "<<elapsedTime.count()<<std::endl;
  
            
            if(elapsedTime.count() >= durationSeconds*1000){
                std::cout<<"meterLogic::startGuiDisplay : Timer elapsed. Ending speedometer display!"<<std::endl;
                break;
            }
            
            if(funcElapsedTime.count() >= g_milliSecondInterval){
                std::cout<<"meterLogic::startGuiDisplay : funcElapsedTime is greater than interval. Therefore no sleep! "<<funcElapsedTime.count()<<std::endl;
            } else{
                auto ms = (std::chrono::milliseconds)(g_milliSecondInterval)- funcElapsedTime;
                std::cout<<"meterLogic::startGuiDisplay : Sleeping for : "<< ms.count() << std::endl;
                std::this_thread::sleep_for(ms);
            }
            
        }
    }).join();

}

void meterLogic::showTerminalRange(double speed) {
    const int gaugeWidth = 50;
    const int numDivisions = 10;
    const char gaugeChar = '-';
    const char needleChar = '^';

    // Ensure speed is within the valid range
    speed = std::min(std::max(speed, minSpeed), maxSpeed);

    // Calculate position of the needle
    int position = static_cast<int>((speed - minSpeed) / (maxSpeed - minSpeed) * gaugeWidth);

    // Clear the console
    system("clear");

    // Draw the gauge
    std::cout << "Speedometer (-6.0 to 6.0):" << std::endl;

    // Draw divisions and the needle
    for (int i = 0; i <= gaugeWidth; ++i) {
        if (i == position)
            std::cout << needleChar;
        else if (i % (gaugeWidth / numDivisions) == 0)
            std::cout << '|';
        else
            std::cout << gaugeChar;
    }

    std::cout << std::endl;
}

