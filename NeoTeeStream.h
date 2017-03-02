#ifndef _NEOTEESTREAM_H_
#define _NEOTEESTREAM_H_

#include <NeoTee.h>

class NeoTeeStream : public Stream
{
  NeoTee Prints;
public:

  NeoTeeStream( Stream **streams, uint8_t numStreams )
    : NeoTee( streams, numStreams )
      {};

  virtual size_t write(uint8_t c) { return Prints.write( c ); };

  using Stream::write; // make the other overloads visible

  virtual void flush()
    {
      for (uint8_t i=0; i<NumStreams; i++)
        Streams[i]->flush();
    }
    
  virtual int available()
    {
      int total = 0;
      for (uint8_t i=0; i<NumStreams; i++)
        total += Streams[i]->available();
      return total;
    }

  virtual int read()
    {
      for (uint8_t i=0; i<NumStreams; i++)
        if (Streams[i]->available())
          return Streams[i]->read();
      return -1;
    }

  virtual int peek()
    {
      for (uint8_t i=0; i<NumStreams; i++)
        if (Streams[i]->available())
          return Streams[i]->peek();
      return -1;
    }

};