#include <iostream>
#include <math.h>
#include "FM.h"
#include "keyvalue.h"

#include <stdlib.h>

using namespace upc;
using namespace std;

FM::FM(const std::string &param) 
  : adsr(SamplingRate, param) {
  bActive = false;
  x.resize(BSIZE);

  //cout << param << endl;

  KeyValue kv(param);

  if (!kv.to_float("N1",N1))    N1 = 1; //default value

  if (!kv.to_float("N2",N2))    N2 = 1; //default value
  if (!kv.to_float("I",I))    I = 1; //default value
}

void FM::command(long cmd, long note, long vel) {
  if (cmd == 9) {
    bActive = true;
    adsr.start();
   
    float f0=440.0*pow(2,(((float)note-69.0)/12.0));     
    float nota = f0/SamplingRate;

    step1 = 2 * M_PI * nota;
    step2 = 2 * M_PI * (N2/N1) * nota;

    //I = m/step2;

    velc = vel/127.0;
  
    phase1 = 0; phase2 = 0; 

    cout << vel << endl;

  } else if (cmd == 0 || cmd == 8) {
    adsr.stop();
  }
}


const vector<float> & FM::synthesize() {

  if (!bActive)
    return x;

  if (!adsr.active()) {
    bActive = false;
    x.assign(x.size(), 0);
    return x;
  }

  
  for (unsigned int i=0; i<x.size(); ++i) {
    x[i] = 1*velc*sin(phase1 + I*sin(phase2));

    phase1 += step1;
    phase2 += step2;

    while(phase1>2*M_PI) phase1 -= 2*M_PI;
    while(phase2>2*M_PI) phase2 -= 2*M_PI;
  }

  adsr(x); //apply envelope to x (and updates internal status of adsr)

  return x;
}