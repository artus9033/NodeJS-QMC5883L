#include "MechaQMC5883.h"

//Credits for this file go to the original author
//taken from here: https://github.com/mechasolution/Mecha_QMC5883L

void MechaQMC5883::setAddress(uint8_t addr){
  address = addr;
}

void MechaQMC5883::WriteReg(byte Reg,byte val){
  I2Cdev::writeByte(address, Reg, val);
}

void MechaQMC5883::init(){
  WriteReg(0x0B,0x01);
  //Define Set/Reset period
  setMode(Mode_Continuous,ODR_200Hz,RNG_8G,OSR_512);
  /*
  Define
  OSR = 512
  Full Scale Range = 8G(Gauss)
  ODR = 200HZ
  set continuous measurement mode
  */
}

void MechaQMC5883::setMode(uint16_t mode,uint16_t odr,uint16_t rng,uint16_t osr){
  WriteReg(0x09,mode|odr|rng|osr);
}


void MechaQMC5883::softReset(){
  WriteReg(0x0A,0x80);
}

void MechaQMC5883::read(int16_t* x, int16_t* y, int16_t* z){
  //WriteReg(0x00, 0x1);
  //uint8_t buffer = ;
  uint8_t* buffer = new uint8_t[6];
  uint8_t reg = 0x00;
  I2Cdev::readBytes(address, reg, (uint8_t) 6, buffer);
  *x = buffer[0]; //LSB  x
  *x |= buffer[1] << 8; //MSB  x
  *y = buffer[2]; //LSB  z
  *y |= buffer[3] << 8; //MSB z
  *z = buffer[4]; //LSB y
  *z |= buffer[5] << 8; //MSB y
}

void MechaQMC5883::read(int16_t* x,int16_t* y,int16_t* z,int* a){
  read(x,y,z);
  *a = (int) azimuth(y,x,0);
}

void MechaQMC5883::read(int16_t* x,int16_t* y,int16_t* z,float* a){
  read(x,y,z);
  *a = azimuth(y,x,0);
}


float MechaQMC5883::azimuth(int16_t *a, int16_t *b, float declinationAngle){
  float azimuth = atan2(*a, *b);
  if (azimuth < 0) {
    azimuth += 2 * PI;
  }
  if (azimuth > 2 * PI) {
    azimuth -= 2 * PI;
  }
  azimuth *= (180.0 / PI);
  azimuth += declinationAngle;
  return azimuth;
}