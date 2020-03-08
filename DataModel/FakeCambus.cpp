#include <FakeCambus.h>

FakeCambus::FakeCambus(){};

bool FakeCambus::Connect(){ return true;}

bool FakeCambus::Disconnect(){ return true;}

bool FakeCambus::GetLeak(){ return false;}

float FakeCambus::GetLight(){ return 3.6;}

float FakeCambus::GetTemp(){ return 2.5;}

bool FakeCambus::SetHV(float volts){ return true;}

float FakeCambus::GetHV(){ return 3.4;}

bool FakeCambus::SetLV(bool state){ return true;}

bool FakeCambus::GetLV(){ return true;}

bool FakeCambus::SetPower(bool state){ return true;}

bool FakeCambus::GetPower(){ return true;}


