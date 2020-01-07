#include <iostream>
#include "seno.h"
#include "instrument_dumb.h"
#include "generico.h"
#include "perc.h"
#include "sample.h"


/*
  For each new instrument:
  - Add the header in this file
  - Add the call to the constructor in get_instrument() (also in this file)
  - Add the source file to src/meson.build
*/

using namespace std;

namespace upc {
  Instrument * get_instrument(const string &name,
			      const string &parameters) {
    Instrument * pInst = 0;
    //    cout << name << ": " << parameters << endl;
    if (name == "InstrumentDumb") {
      pInst = (Instrument *) new InstrumentDumb(parameters);
    }
    if (name == "seno") {
      pInst = (Instrument *) new Seno(parameters);
    }
    if (name == "generico") {
      pInst = (Instrument *) new generico(parameters);
    }
    if (name == "perc") {
      pInst = (Instrument *) new perc(parameters);
    }
    if (name == "sample") {
      pInst = (Instrument *) new sample(parameters);
    }
    return pInst;
  }
  
}
