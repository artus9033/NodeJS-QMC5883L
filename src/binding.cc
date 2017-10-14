#include "I2Cdev.h"
#include "MechaQMC5883.h"
#include "node.h"

using namespace v8;

MechaQMC5883 da5883;

// control variables
bool ready = false;  // if da5883 was already initialized


/*NAN_METHOD(ReadAzimuth) {
  Isolate * isolate = info.GetIsolate();
  uint16_t x, y, z;
  int* a;
  da5883.read(&x, &y, &z, a);
  info.GetReturnValue().Set(Number::New(isolate, static_cast<double>(*a)));
}*/

void readCompassData(const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = args.GetIsolate();
  uint16_t x, y, z;
  da5883.read(&x, &y, &z);
  Local<Object> obj = Object::New(isolate);
  obj.Set(String::NewFromUtf8(isolate, "x"), Number::New(isolate, x));
  info.GetReturnValue().Set(obj);
}

void InitCompass(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  da5883.init();
  da5883.setMode(Mode_Continuous,ODR_200Hz,RNG_2G,OSR_256);
  ready = true;
  info.GetReturnValue().Set(true);
}

void Initialize(Local<Object> exports) {
  NODE_SET_METHOD(exports, "init", InitCompass);
}

NODE_MODULE(module_name, Initialize)