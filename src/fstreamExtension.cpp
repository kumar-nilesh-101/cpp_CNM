#include <iostream>
#include <fstream>
#include <string>
#include "fstreamExtension.h"

bool fstreamExtension::copyFile (const std::string& __copyFile)
{
    uint8_t fByte;
    int __end_of_file;
    std::fstream copyStream(__copyFile.c_str(), std::ios::out|std::ios::trunc|std::ios::binary);

    if(!copyStream)
        return false;
    else
    {
        while(1)
        {
            this -> read (reinterpret_cast<char*> (&fByte), sizeof (uint8_t));
            copyStream.write (reinterpret_cast<char*> (&fByte), sizeof (uint8_t));

            if((__end_of_file = this -> peek()) == EOF)
                break;
        }
        return true;
    }
}

void fstreamExtension::readBytes (uint8_t* byteBuff)
{
    this -> read (reinterpret_cast<char*> (byteBuff), this -> fstreamExtension::fileSize());
//        if((__end_of_file = this -> peek ()) == EOF)
}

void fstreamExtension::readBytesLimited (uint8_t* byteBuff, long long int streamSize)
{
    this -> read (reinterpret_cast<char*> (byteBuff), streamSize);
}

void fstreamExtension::appendByte(uint8_t byte)
{
    this -> write(reinterpret_cast<char*> (&byte), sizeof(uint8_t));
}

void fstreamExtension::writeBytes (uint8_t* byteBuff, long long int streamSize)
{
    this -> write(reinterpret_cast<char*> (byteBuff), streamSize);
}

fstreamExtension::~fstreamExtension()
{
    std::fstream::close();
}
