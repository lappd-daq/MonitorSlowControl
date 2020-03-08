#ifndef FAKECAMBUS_H
#define FAKECAMBUS_H

class FakeCambus{


 public:

  FakeCambus();
  bool Connect();
  bool Disconnect();
  bool GetLeak();
  float GetLight();
  float GetTemp();
  bool SetHV(float volts);
  float GetHV();
  bool SetLV(bool state);
  bool GetLV();
  bool SetPower(bool state);
  bool GetPower();


 private:



};

#endif
