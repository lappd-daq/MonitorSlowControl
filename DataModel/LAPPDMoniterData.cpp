#include <LAPPDMoniterData.h>

LAPPDMoniterData::LAPPDMoniterData(){};

bool LAPPDMoniterData::Send(zmq::socket_t* sock){

  zmq::message_t msg1(&leak,sizeof leak, NULL);
  zmq::message_t msg2(&light,sizeof light, NULL);
  zmq::message_t msg3(&temp,sizeof temp, NULL);
  zmq::message_t msg4(&HV,sizeof HV, NULL);
  zmq::message_t msg5(&LV,sizeof LV, NULL);
  zmq::message_t msg6(&power,sizeof power, NULL);

  sock->send(msg1,ZMQ_SNDMORE);
  sock->send(msg2,ZMQ_SNDMORE);
  sock->send(msg3,ZMQ_SNDMORE);
  sock->send(msg4,ZMQ_SNDMORE);
  sock->send(msg5,ZMQ_SNDMORE);
  sock->send(msg6);

  return true;

}

bool LAPPDMoniterData::Receive(zmq::socket_t* sock){

  zmq::message_t msg;
  
  sock->recv(&msg);
  leak=*(reinterpret_cast<bool*>(msg.data()));
  sock->recv(&msg);
  light=*(reinterpret_cast<float*>(msg.data()));
  sock->recv(&msg);  
  temp=*(reinterpret_cast<float*>(msg.data()));
  sock->recv(&msg);  
  HV=*(reinterpret_cast<float*>(msg.data()));
  sock->recv(&msg);  
  LV=*(reinterpret_cast<bool*>(msg.data()));
  sock->recv(&msg);  
  power=*(reinterpret_cast<bool*>(msg.data()));
  
  return true;

}


bool LAPPDMoniterData::Print(){

  std::cout<<"leak="<<leak<<std::endl;
  std::cout<<"light="<<light<<std::endl;
  std::cout<<"temp="<<temp<<std::endl;
  std::cout<<"HV="<<HV<<std::endl;
  std::cout<<"LV="<<LV<<std::endl;
  std::cout<<"power="<<power<<std::endl;

}
