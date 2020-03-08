#include "Poll.h"

Poll::Poll():Tool(){}


bool Poll::Initialise(std::string configfile, DataModel &data){

  if(configfile!="")  m_variables.Initialise(configfile);
  //m_variables.Print();

  m_data= &data;

  long time_sec=0;

  m_variables.Get("Period",time_sec);

  period=boost::posix_time::seconds(time_sec);
  last=boost::posix_time::second_clock::local_time();

  m_data->Cambus= new FakeCambus();

  m_data->Cambus->Connect(); 

  return true;
}


bool Poll::Execute(){

  boost::posix_time::ptime current(boost::posix_time::second_clock::local_time());
  boost::posix_time::time_duration lapse(period - (current - last));

  if (!lapse.is_negative()) usleep(100);
  else{

    m_data->MonData.leak =  m_data->Cambus->GetLeak();
    m_data->MonData.light =  m_data->Cambus->GetLight();
    m_data->MonData.temp =  m_data->Cambus->GetTemp();
    m_data->MonData.HV =  m_data->Cambus->GetHV();
    m_data->MonData.LV =  m_data->Cambus->GetLV();
    m_data->MonData.power =  m_data->Cambus->GetPower();

  }

  return true;
}


bool Poll::Finalise(){


  m_data->Cambus->Disconnect();
  delete m_data->Cambus;
  m_data->Cambus=0;

  return true;
}
