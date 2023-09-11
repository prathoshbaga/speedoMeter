/*----------------------------------------------------------------------
# Periodic value generator
#-----------------------------------------------------------------------
#  @file         periodicGenerator.hpp
#  @author       Prathosh
------------------------------------------------------------------------
*/

#ifndef PERIODICGENERATOR_HPP
#define PERIODICGENERATOR_HPP

#include "../comm_generator/commGenerator.hpp"
#include <memory>

class periodicGenerator{
    public:
        /**
         * @brief Construct a new periodic Generator::periodic Generator object
         * 
         * @param duration - duration for which the pulses should be generated.
         *                   default value = 1000s ~ 17 mins
         */
        periodicGenerator(std::shared_ptr<commGenerator> ptr, int duration);

        /**
         * @brief Destroy the periodic Generator::periodic Generator object
         * 
         */
        ~periodicGenerator();

        /**
         * @brief method to trigger periodic generation of pulses
         * 
         */
        void startGeneration();

        /**
         * @brief method to stop generation
         * 
         */
        void stopGeneration();

    
    private:
        int m_generationDuration;
        std::shared_ptr<commGenerator> m_pComm;

        /**
         * @brief method to calculate the sum of sine wave for
         *        various amplitude and frequency.
         * 
         * @return double 
         */
        double generatePulse();


};

#endif //ERIODICGENERATOR_HPP