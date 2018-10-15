#include <bits/stdc++.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std;

#define BUFFER_SIZE 33554432

class FileReader {

  public:
    
    FileReader(const string& filename) {
        this->_filename = filename;
        if (!fileExists()) {
            throw runtime_error("File" + this->_filename + "not exists.");
        }
        this->_bytesRead = 0;
        this->_linePointer = this->_buffer;
    };

    ~FileReader();

    bool road(const string& filename) {
        this->_filename = filename;
        
        if (!fileExists()){
            throw runtime_error("File" + this->_filename + "not exists.");
        }

        this->_bytesRead = 0;
        this->_linePointer = this->_buffer - 1;
        _bytesRead = read(_fileDescriptor, _buffer, BUFFER_SIZE);

        return true;
    };

    int getline(string& dest){
        _linePointer++;

        int size = (int) ((_buffer + _bytesRead) - _linePointer);
        
        char* pointer = (char *) memchr(_linePointer, '\n', size);

        int linesize = (int) (pointer - _linePointer);

        char aux[linesize+1];
        
        strncpy(aux,_linePointer, linesize);
        aux[linesize] = '\0';

        dest =  string(aux);

        return 0;
    };

private:
    string _filename;
    int _fileDescriptor;
    char _buffer[BUFFER_SIZE+1];
    int _bytesRead;
    char* _linePointer;

    bool fileExists() {
        struct stat buffer;
        return (stat(this->_filename.c_str(), &buffer) == 0);
    };

    void openFile(){
        int fd = open(this->_filename.c_str(), O_RDONLY);
        if (fd == -1)
            throw runtime_error("Error tryin to open" + this->_filename + ".");

        posix_fadvise(fd, 0, 0, 1); // FDADVICE_SEQUENTIAL
    }
};