#include "Stream.h"

Stream::Stream():Tool(){}


bool Stream::Initialise(std::string configfile, DataModel &data){

  if(configfile!="")  m_variables.Initialise(configfile);
  //m_variables.Print();

  m_data= &data;

  if(!m_variables.Get("Port",m_port)) m_port=5555;

  sock=new zmq::socket_t(*(m_data->context), ZMQ_PUB);
  std::stringstream tmp;
  tmp<<"tcp://*:"<<m_port;
  sock->bind(tmp.str().c_str());
  

  long time_sec=0;

  if(!m_variables.Get("Period",time_sec)) time_sec=3;

  period=boost::posix_time::seconds(time_sec);
  last=boost::posix_time::second_clock::local_time();

  return true;
}


bool Stream::Execute(){

  boost::posix_time::ptime current(boost::posix_time::second_clock::local_time());
  boost::posix_time::time_duration lapse(period - (current - last)); 

  if (lapse.is_negative()){

    m_data->MonData.Send(sock);
    last=boost::posix_time::second_clock::local_time();

  }
    


  return true;
}


bool Stream::Finalise(){

  delete sock;
  sock=0;

  return true;
}
