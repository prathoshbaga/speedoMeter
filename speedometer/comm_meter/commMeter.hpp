/*----------------------------------------------------------------------
# interface with the pipe library to send values
#-----------------------------------------------------------------------
#  @file         commMeter.hpp
#  @author       Prathosh
------------------------------------------------------------------------
*/

#ifndef COMMMETER_HPP
#define COMMMETER_HPP


class commMeter{
    public:
        /**
         * @brief Construct a new commMeter object
         * 
         */
        commMeter();

        /**
         * @brief Destroy the commMeter object
         * 
         */
        ~commMeter();

        /**
         * @brief method to open the pipe with read permissions
         * 
         * @param mode - readonly
         * @return true - if successfully opening of the pipe
         * @return false - failure
         */
        bool openPipe(const int& mode);

        /**
         * @brief mthod to check if the pipe is empty
         * 
         * @return true - if pipe is empty
         * @return false - if pipe has data
         */
        bool isPipeEmpty();

        /**
         * @brief method to read value from pipe
         * 
         * @return double - value read from the pipe
         */
        double readData();

        /**
         * @brief method to close the pipe
         * 
         */
        void closePipe();

    private:

        /**
         * @brief pipe file descriptor
         * 
         */
        int m_pipeDescriptor;
};

#endif // COMMMETER_HPP
