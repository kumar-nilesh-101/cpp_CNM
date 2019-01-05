#include <fstream>
#include <string>
#include <vector>
#ifndef FSTREAMEXTENSION_H
#define FSTREAMEXTENSION_H

class fstreamExtension : public std::fstream
{
    private:

        const std::string fileIdentifier;

    public:

        using std::fstream::fstream;
//        using std::fstream::open;

        ~fstreamExtension();

        inline void fileName (const std::string& __fileIdentifier)
        {
            const_cast<std::string &>(this -> fileIdentifier) = __fileIdentifier;
        }

        inline bool exists ()
        {
            if (FILE *file = fopen(fileIdentifier.c_str(), "r"))
            {
                fclose(file);
                return true;
            }

            else
                return false;
        }

        inline unsigned long long int fileSize ()
        {
            if(this -> exists())
            {
                std::ifstream tempStream(fileIdentifier.c_str(), std::ios::ate | std::ios::binary);
                unsigned long long int __size = tempStream.tellg();
                tempStream.close();
                return __size;
            }

            else return 0;
        }

///returns a pointer to a buffer to read the contents of file into it./
///        uint8_t* returnReadBuffer();/

///creates a copy of file referenced by the file, arguement specifies the name of copy file./
        bool copyFile (const std::string&);

///accepts a pointer to buffer of size of file./
        void readBytes (uint8_t*);

///accepts a pointer to buffer of given size and same number of bytes are read./
        void readBytesLimited (uint8_t* , long long int);

///appends a byte at the end of the file./
        void appendByte(uint8_t);

///accepts a pointer to a buffer and it's size and write the contents of buffer to a file./
        void writeBytes(uint8_t*, long long int);
};

#endif // FSTREAMEXTENSION_H
