#include "SetSend.h"

SetSend::SetSend():Tool(){}


bool SetSend::Initialise(std::string configfile, DataModel &data){

  if(configfile!="")  m_variables.Initialise(configfile);
  //m_variables.Print();

  m_data= &data;

  if(!m_variables.Get("Port",m_port)) m_port=4444;

  sock=new zmq::socket_t(*(m_data->context), ZMQ_DEALER);
  std::stringstream tmp;
  tmp<<"tcp://127.0.0.1:"<<m_port;
  sock->connect(tmp.str().c_str());

  items[0].socket = *sock;
  items[0].fd = 0;
  items[0].events = ZMQ_POLLOUT;
  items[0].revents =0;

  long time_sec=0;

  if(!m_variables.Get("Period",time_sec)) time_sec=10;

  period=boost::posix_time::seconds(time_sec);
  last=boost::posix_time::second_clock::local_time();

  return true;
}


bool SetSend::Execute(){

  boost::posix_time::ptime current(boost::posix_time::second_clock::local_time());
  boost::posix_time::time_duration lapse(period - (current - last));
  
  if (!lapse.is_negative()) usleep(100);
  else{
    
    zmq::poll(&items[0], 1, 100);
    
    if ((items [0].revents & ZMQ_POLLOUT)) {
      
      zmq::message_t key(6);
      snprintf ((char *) key.data(), 6 , "%s" , "SetHV");
      
      float voltage=1000.0;
      zmq::message_t value(&voltage, sizeof voltage, NULL);
      
      std::cout<<"sending voltage: "<<voltage<<std::endl;
      sock->send(key,ZMQ_SNDMORE);
      sock->send(value);
      std::cout<<"sent"<<std::endl;
      
      zmq::message_t answer;
      sock->recv(&answer);
      bool ret=0;
      ret=*(reinterpret_cast<bool*>(answer.data()));
      
      std::cout<<"answer was: "<<ret<<std::endl<<std::endl;    
     
      last=boost::posix_time::second_clock::local_time();
 
    }

  }

  return true;
}


bool SetSend::Finalise(){

  delete sock;
  sock=0;

  return true;
}
