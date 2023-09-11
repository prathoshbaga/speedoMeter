/*----------------------------------------------------------------------
# interface with the pipe library to send values
#-----------------------------------------------------------------------
#  @file         commGenerator.hpp
#  @author       Prathosh
------------------------------------------------------------------------
*/

#ifndef COMMGENERATOR_HPP
#define COMMGENERATOR_HPP


class commGenerator{
    public:
        
        /**
         * @brief Construct a new commGenerator::commGenerator object
         * 
         */
        commGenerator();

        /**
         * @brief Destroy the commGenerator object
         * 
         */
        ~commGenerator();

        /**
         * @brief method to create the Pipe
         * 
         * @return true - if pipe was successfully created.
         * @return false - if pipe was not created.
         */
        bool createPipe();

        /**
         * @brief method to open the pipe
         * 
         * @param mode - write only
         * @return true - pipe opened successfully 
         * @return false - failure
         */
        bool openPipe(const int& mode);

        /**
         * @brief method to check if the client is ready and waiting to read
         * 
         * @return true - if client is read to read
         * @return false - if client is not available 
         */
        bool isClientReady();

        /**
         * @brief method to wirte the value into the pipe
         * 
         * @param value - speed value to be written
         * @return true - successful write
         * @return false - failure to write
         */
        bool updateValue(double value);

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

#endif // COMMGENERATOR_HPP
