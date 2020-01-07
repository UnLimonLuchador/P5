#ifndef PERC
#define PERC

#include <vector>
#include <string>
#include "instrument.h"
#include "envelope_adsr.h"

namespace upc {
  class perc: public upc::Instrument {
    EnvelopeADSR adsr;
    unsigned int index;
    float fase;
	float A;
  float deltai;
    std::vector<float> tbl;
  public:
    perc(const std::string &param = "");
    void command(long cmd, long note, long velocity=1); 
    const std::vector<float> & synthesize();
    bool is_active() const {return bActive;} 
  };
}

#endif