#include "StreamReceive.h"

StreamReceive::StreamReceive():Tool(){}


bool StreamReceive::Initialise(std::string configfile, DataModel &data){

  if(configfile!="")  m_variables.Initialise(configfile);
  //m_variables.Print();

  m_data= &data;

  m_variables.Get("Port",m_port);

  sock=new zmq::socket_t(*(m_data->context), ZMQ_SUB);
  std::stringstream tmp;
  tmp<<"tcp://127.0.0.1:"<<m_port;
  sock->connect(tmp.str().c_str());
  sock->setsockopt(ZMQ_SUBSCRIBE, "", 0);
   
  items[0].socket = *sock;
  items[0].fd = 0;
  items[0].events = ZMQ_POLLIN;
  items[0].revents =0;

  return true;
}


bool StreamReceive::Execute(){

  
  zmq::poll(&items[0], 1, 0);

  if ((items [0].revents & ZMQ_POLLIN)) {

  m_data->MonData.Receive(sock);
  m_data->MonData.Print();

  }

  return true;
}


bool StreamReceive::Finalise(){

  delete sock;
  sock=0;

  return true;
}
