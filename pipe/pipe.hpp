/*----------------------------------------------------------------------
# library for IPC using pipe for asynchronous communication
#-----------------------------------------------------------------------
#  @file         pipe.hpp
#  @author       Prathosh
------------------------------------------------------------------------
*/

#include <string>

namespace pipecomm{
        bool createPipe(std::string pipeName, const int perm);
        int openPipe(const std::string& pipeName, const int openMode);
        bool writeData(const int& fd, double& val, size_t size);
        bool readData(const int& fd, double& val, size_t size);
        void closePipe(int& fd, const std::string& pipeName);
        bool isPipeEmpty(const std::string& pipeName);
        bool isPipeWriteReady(const std::string& pipeName);
}