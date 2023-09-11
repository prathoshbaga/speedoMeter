/*----------------------------------------------------------------------
# speedometer logic
#-----------------------------------------------------------------------
#  @file         commMeter.hpp
#  @author       Prathosh
------------------------------------------------------------------------
*/
#ifndef METERLOGIC_HPP
#define METERLOGIC_HPP

#include <memory>
#include "../comm_meter/commMeter.hpp"
#include "../meterUI/SpeedometerUI.hpp"

class meterLogic{
    public:
        meterLogic(std::shared_ptr<commMeter> ptr, std::shared_ptr<QWidget> qWdgtPtr, int duration);
        ~meterLogic();
        void startGuiDisplay();
        void stopDisplay();

    
    private:
        std::shared_ptr<commMeter> m_pComm;
        std::shared_ptr<SpeedometerUI> m_pSpeedoMeterUI;
        int m_displayDuration;
        void showTerminalRange(double val);

};

#endif //METERLOGIC_HPP
