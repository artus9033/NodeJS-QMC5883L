#include "binding.h"

using namespace v8;

MechaQMC5883 da5883;

// control variables
bool ready = false;  // if da5883 was already initialized

void ReadCompassData(const FunctionCallbackInfo<Value>& args){
  int16_t x, y, z;
  Isolate* isolate = args.GetIsolate();
  Local<Context> context = isolate->GetCurrentContext();
  Local<Object> obj = Object::New(isolate);
  if(ready){
    da5883.read(&x, &y, &z);
  }else{
    x = 0;
    y = 0;
    z = 0;
  }
  obj->CreateDataProperty(context, String::NewFromUtf8(isolate, "x"), Number::New(isolate, x));
  obj->CreateDataProperty(context, String::NewFromUtf8(isolate, "y"), Number::New(isolate, y));
  obj->CreateDataProperty(context, String::NewFromUtf8(isolate, "z"), Number::New(isolate, z));
  args.GetReturnValue().Set(obj);
}

void ReadAzimuth(const FunctionCallbackInfo<Value>& args){
  int16_t x, y, z;
  float azimuth;
  Isolate* isolate = args.GetIsolate();
  if(ready){
    da5883.read(&x, &y, &z, &azimuth);
  }else{
    x = 0;
    y = 0;
    z = 0;
    azimuth = 0;
  }
  args.GetReturnValue().Set(Number::New(isolate, azimuth));
}

void InitCompass(const FunctionCallbackInfo<Value>& args) {
  da5883.init();
  da5883.setMode(Mode_Continuous,ODR_200Hz,RNG_8G,OSR_256);
  ready = true;
  args.GetReturnValue().Set(true);
}

void Initialize(Local<Object> exports) {
  NODE_SET_METHOD(exports, "initialize", InitCompass);
  NODE_SET_METHOD(exports, "readData", ReadCompassData);
  NODE_SET_METHOD(exports, "readAzimuth", ReadAzimuth);
}

NODE_MODULE(module_name, Initialize)