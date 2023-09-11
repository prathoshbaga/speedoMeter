/*----------------------------------------------------------------------
# library for IPC using pipe for asynchronous communication
#-----------------------------------------------------------------------
#  @file         pipe.cpp
#  @author       Prathosh
------------------------------------------------------------------------
*/

#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include "pipe.hpp"
#include <cerrno> 
#include <cstring>

const std::string g_pipeName = "/tmp/ipc_pipe";
const int g_pipePermissions = 0666;


namespace pipecomm{
/**
 * @brief method which creates a pipe
 * 
 * @return true - Successful pipe creation
 * @return false - Unsuccessful pipe creation
 */
bool createPipe(std::string pipeName, const int perm){
    std::cout<<"createPipe()"<<std::endl;
    int result = mkfifo(pipeName.c_str(), perm);
    std::cout<<"createPipe() result : "<<result<<std::endl;
    if(result<0){
        std::cout<<"createPipe() : creation of pipe failed !!"<<std::endl;
        if (errno == EEXIST) {
            // If the file already exists, you can handle it accordingly
            std::cerr << "The FIFO pipe already exists." << std::endl;
            return true;
        } else {
            // Print a generic error message using perror() and strerror()
            perror("mkfifo() failed");
            std::cerr << "Error: " << strerror(errno) << std::endl;
        }
        return false;
    }
    return true;
}

/**
 * @brief method to open the pipe using relevant access
 * 
 * @param openMode - mode to be used for opening the Pipe, either read/write
 * @return true - Successful opening of the pipe
 * @return false - Unsuccessful opening of the pipe
 */

int openPipe(const std::string& pipeName, const int openMode){
    std::cout<<"openPipe()"<<std::endl;
    //mode_t permissions = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH | O_NONBLOCK;
    int fd = open(pipeName.c_str(), openMode);
    if(fd == -1){
        std::cout<<"openPipe() : open failed !!"<<std::endl;
        if (errno == EEXIST) {
            // If the file already exists, you can handle it accordingly
            std::cerr << "The FIFO pipe already exists." << std::endl;
            return true;
        } else {
            // Print a generic error message using perror() and strerror()
            perror("mkfifo() failed");
            std::cerr << "Error: " << strerror(errno) << std::endl;
        }
    }
    return fd;
}

/**
 * @brief method to write values into pipe
 * 
 * @param val - data to be written
 * @param size - size of the data to be written
 * @return true - Successful write to pipe
 * @return false - Unsuccessful write to pipe
 */

bool writeData(const int& fd, double& val, size_t size){
    std::cout<<"writeData()"<<std::endl;
    if(fd == -1){
        std::cerr<<"writeData() : Pipe not open for writing !!"<<std::endl;
        return false;
    }

    ssize_t bytesWritten = write(fd, &val, size);
    std::cout<<"writeData() : bytes written : "<<bytesWritten<<std::endl;
    return bytesWritten == static_cast<ssize_t> (size);
}

/**
 * @brief method to read values from pipe
 * 
 * @param val - val into which value to be read
 * @param size - size of the value to be read
 * @return true - Successful read from pipe
 * @return false - Unsuccessful read from pipe
 */

bool readData(const int& fd, double& val, size_t size){
    std::cout<<"readData()"<<std::endl;
    if(fd == -1){
        std::cerr<<"readData() : Pipe not open for reading !!"<<std::endl;
        return false;
    }

    ssize_t bytesRead = read(fd, &val, size);
    return bytesRead == static_cast<ssize_t> (size);
}


/**
 * @brief Construct a new async Pipe::close Pipe object
 * 
 */
void closePipe(int& fd, const std::string& pipeName){
    std::cout<<"closePipe()"<<std::endl;
    if(fd !=-1 ){
        std::cout<<"closePipe() : closing pipe"<<std::endl;
        close(fd);
        unlink(pipeName.c_str());
        fd = -1;
    }

}

/**
 * @brief method to check if the pipe is emtpy
 * 
 * @return true - if pipe is empty
 * @return false - if pipe is not empty
 */
bool isPipeEmpty(const std::string& pipeName){
    std::cout<<"isPipeEmpty()"<<std::endl;
    struct stat pipeStat;
    if(stat(pipeName.c_str(),& pipeStat)==-1){
        std::cerr<<"Failed to get pipe status!!"<<std::endl;
    }

    std::cout<<"isPipeEmpty() : pipe size : "<<pipeStat.st_size<<std::endl;
    return pipeStat.st_size==0;
}

/**
 * @brief method to check if the pipe opened on the reading end.
 * 
 * @return true - if pipe is opened at reading end.
 * @return false - if pipe is not opened at reading end.
 */

bool isPipeWriteReady(const std::string& pipeName){
    std::cout<<"isPipeWriteReady()"<<std::endl;
    if (access(pipeName.c_str(), R_OK) != -1) {
        std::cout << "isPipeWriteReady(): pipe is open for reading by another application." << std::endl;
        return true;
    } else {
        std::cout << "isPipeWriteReady(): pipe is not open for reading by another application." << std::endl;
        return false;
    }
}

}