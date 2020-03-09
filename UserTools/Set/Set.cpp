#include "Set.h"

Set::Set():Tool(){}


bool Set::Initialise(std::string configfile, DataModel &data){

  if(configfile!="")  m_variables.Initialise(configfile);
  //m_variables.Print();

  m_data= &data;

  if(!m_variables.Get("Port",m_port)) m_port=4444;

  sock=new zmq::socket_t(*(m_data->context), ZMQ_DEALER);
  std::stringstream tmp;
  tmp<<"tcp://*:"<<m_port;
  sock->bind(tmp.str().c_str());

  items[0].socket = *sock;
  items[0].fd = 0;
  items[0].events = ZMQ_POLLIN;
  items[0].revents =0;

  return true;
}


bool Set::Execute(){

  zmq::poll(&items[0], 1, 100);

  if ((items [0].revents & ZMQ_POLLIN)) {

    ret=false;

    zmq::message_t key;
    sock->recv(&key);
 
    std::istringstream iss(static_cast<char*>(key.data()));

    zmq::message_t value;
    sock->recv(&value);

    if(iss.str()=="SetHV"){
      
      float voltage=0;
      voltage=*(reinterpret_cast<float*>(value.data()));
      ret=m_data->Cambus->SetHV(voltage);
      
    }
    
    else if(iss.str()=="SetLV"){
    
      bool on=0;
      on=*(reinterpret_cast<bool*>(value.data()));
      ret=m_data->Cambus->SetLV(on);  
      
    }
    
    zmq::message_t answer(&ret,sizeof ret, NULL);
    sock->send(answer);
    
  }
  
  return true;
}


bool Set::Finalise(){

  return true;
}
