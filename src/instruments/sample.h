#ifndef SAMPLE
#define SAMPLE

#include <vector>
#include <string>
#include "instrument.h"
#include "envelope_adsr.h"

namespace upc {
  class sample: public upc::Instrument {
    EnvelopeADSR adsr;
    unsigned int index;
    float fase;
	float A;
  float deltai;
    std::vector<float> tbl;
  public:
    sample(const std::string &param = "");
    void command(long cmd, long note, long velocity=1); 
    const std::vector<float> & synthesize();
    bool is_active() const {return bActive;} 
  };
}

#endif