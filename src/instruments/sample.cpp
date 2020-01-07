#include <iostream>
#include <math.h>
#include "sample.h"
#include "keyvalue.h"
#include "wavfile_mono.h"

#include <stdlib.h>

using namespace upc;
using namespace std;

sample::sample(const std::string &param) 
  : adsr(SamplingRate, param) {
  bActive = false;
  x.resize(BSIZE);

  /*
    You can use the class keyvalue to parse "param" and configure your instrument.
    Take a Look at keyvalue.h    
  */
  KeyValue kv(param);
    
  std::string file_name;
static string kv_null;
if ((file_name = kv("file")) == kv_null) {
    cerr << "Error sample.cpp: no se ha encontrado el campo con el fichero de la señal para un instrumento FicTabla" << endl;
    throw -1;
}
unsigned int fm;




if ( readwav_mono(file_name, fm, tbl)< 0) {
    cerr << "Error: no se puede leer el fichero " << file_name << " para un instrumentoFicTabla" << endl;
    throw -1;
}


}


void sample::command(long cmd, long note, long vel) {
  if (cmd == 9) {		//'Key' pressed: attack begins
    bActive = true;
    adsr.start();
    index = 0;
	  A = vel / 127.;
      fase = 0;

    deltai = 1;
  }  
}


const vector<float> & sample::synthesize() {
  if (not adsr.active()) {
    x.assign(x.size(), 0);
    bActive = false;
    return x;
  }
  else if (not bActive)
    return x;

  for (unsigned int i=0; i<x.size(); ++i) {
    fase = fase + deltai;
    
    if(fase > tbl.size()){
        adsr.end();
        x[i]=0;
    } else{
        x[i] = A*(tbl[fase]);    
    }
    
  }
 
  return x;
}
