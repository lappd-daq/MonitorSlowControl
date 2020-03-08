#ifndef LAPPDMONITERDATA_H
#define LAPPDMONITERDATA_H

#include "zmq.hpp"
#include <SerialisableObject.h>
#include <iostream>

class LAPPDMoniterData : public SerialisableObject{

 friend class boost::serialization::access;

 public:

  LAPPDMoniterData();
  bool Send(zmq::socket_t* sock);
  bool Receive(zmq::socket_t* sock);
  bool leak;
  float light;
  float temp;
  float HV;
  bool LV;
  bool power;

  bool Print();

 private:
 
 template <class Archive> void serialize(Archive& ar, const unsigned int version){

  ar & leak;
  ar & light;
  ar & temp;
  ar & HV;
  ar & LV;
  ar & power;
  
 }
 
};

#endif
