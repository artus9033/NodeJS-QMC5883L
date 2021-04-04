#include "binding.h"

using namespace v8;

MechaQMC5883 da5883;
bool ready = false;
float offsetX = 0;
float offsetY = 0;
float offsetZ = 0;
float scaleX = 1;
float scaleY = 1;
float scaleZ = 1;
float declinationAngle = 0;

void InitCompass(const FunctionCallbackInfo<Value> &args)
{
  da5883.init();
  da5883.setMode(Mode_Continuous, ODR_200Hz, RNG_8G, OSR_256);
  ready = true;
  args.GetReturnValue().Set(true);
}

Local<String> constructLocalString(Isolate *isolate, const char *value)
{
  return String::NewFromUtf8(isolate, value, NewStringType::kNormal).ToLocalChecked();
}

void SetCompassOffset(const FunctionCallbackInfo<Value> &args)
{
  Isolate *isolate = args.GetIsolate();
  Local<Context> context = isolate->GetCurrentContext();

  if (args.Length() != 3)
  {
    isolate->ThrowException(Exception::TypeError(constructLocalString(isolate, "This function expects exactly 3 arguments: x, y & z offsets")));
    return;
  }

  if (!args[0]->IsNumber())
  {
    isolate->ThrowException(Exception::TypeError(
        constructLocalString(isolate, "The first argument has to be a number")));
    return;
  }

  if (!args[1]->IsNumber())
  {
    isolate->ThrowException(Exception::TypeError(
        constructLocalString(isolate, "The second argument has to be a number")));
    return;
  }

  if (!args[2]->IsNumber())
  {
    isolate->ThrowException(Exception::TypeError(
        constructLocalString(isolate, "The third argument has to be a number")));
    return;
  }

  offsetX = args[0]->NumberValue(context).ToChecked();
  offsetY = args[1]->NumberValue(context).ToChecked();
  offsetZ = args[2]->NumberValue(context).ToChecked();
}

void SetCompassScale(const FunctionCallbackInfo<Value> &args)
{
  Isolate *isolate = args.GetIsolate();
  Local<Context> context = isolate->GetCurrentContext();

  if (args.Length() != 3)
  {
    isolate->ThrowException(Exception::TypeError(
        constructLocalString(isolate, "This function expects exactly 3 arguments: x, y & z scales")));
    return;
  }

  if (!args[0]->IsNumber())
  {
    isolate->ThrowException(Exception::TypeError(
        constructLocalString(isolate, "The first argument has to be a number")));
    return;
  }

  if (!args[1]->IsNumber())
  {
    isolate->ThrowException(Exception::TypeError(
        constructLocalString(isolate, "The second argument has to be a number")));
    return;
  }

  if (!args[2]->IsNumber())
  {
    isolate->ThrowException(Exception::TypeError(
        constructLocalString(isolate, "The third argument has to be a number")));
    return;
  }

  scaleX = args[0]->NumberValue(context).ToChecked();
  scaleY = args[1]->NumberValue(context).ToChecked();
  scaleZ = args[2]->NumberValue(context).ToChecked();
}

void applyMatrixes(int16_t *x, int16_t *y, int16_t *z)
{
  *x += offsetX;
  *y += offsetY;
  *z += offsetZ;
  *x *= scaleX;
  *y *= scaleY;
  *z *= scaleZ;
}

void ReadRawCompassData(const FunctionCallbackInfo<Value> &args)
{
  Isolate *isolate = args.GetIsolate();

  Local<Context> context = isolate->GetCurrentContext();
  Local<Object> obj = Object::New(isolate);

  int16_t x, y, z;

  if (ready)
  {
    da5883.read(&x, &y, &z);
  }
  else
  {
    x = 0;
    y = 0;
    z = 0;
  }

  obj->CreateDataProperty(context, constructLocalString(isolate, "x"), Number::New(isolate, x));
  obj->CreateDataProperty(context, constructLocalString(isolate, "y"), Number::New(isolate, y));
  obj->CreateDataProperty(context, constructLocalString(isolate, "z"), Number::New(isolate, z));

  args.GetReturnValue().Set(obj);
}

void ReadCorrectedCompassData(const FunctionCallbackInfo<Value> &args)
{
  Isolate *isolate = args.GetIsolate();
  Local<Context> context = isolate->GetCurrentContext();

  int16_t x, y, z;

  Local<Object> obj = Object::New(isolate);

  if (ready)
  {
    da5883.read(&x, &y, &z);
    applyMatrixes(&x, &y, &z);
  }
  else
  {
    x = 0;
    y = 0;
    z = 0;
  }

  obj->CreateDataProperty(context, constructLocalString(isolate, "x"), Number::New(isolate, x));
  obj->CreateDataProperty(context, constructLocalString(isolate, "y"), Number::New(isolate, y));
  obj->CreateDataProperty(context, constructLocalString(isolate, "z"), Number::New(isolate, z));

  args.GetReturnValue().Set(obj);
}

void ReadAzimuth(const FunctionCallbackInfo<Value> &args)
{
  Isolate *isolate = args.GetIsolate();

  int16_t x, y, z;
  float azimuth;

  if (ready)
  {
    da5883.read(&x, &y, &z);
    applyMatrixes(&x, &y, &z);
    azimuth = da5883.azimuth(&y, &x, (float)declinationAngle);
  }
  else
  {
    x = 0;
    y = 0;
    z = 0;
    azimuth = 0;
  }

  args.GetReturnValue().Set(Number::New(isolate, azimuth));
}

void SetCompassDeclinationAngle(const FunctionCallbackInfo<Value> &args)
{
  Isolate *isolate = args.GetIsolate();
  Local<Context> context = isolate->GetCurrentContext();

  if (args.Length() != 1)
  {
    isolate->ThrowException(Exception::TypeError(
        constructLocalString(isolate, "This function expects exactly 1 arguments: the declination angle")));
    return;
  }

  if (!args[0]->IsNumber())
  {
    isolate->ThrowException(Exception::TypeError(
        constructLocalString(isolate, "The first argument has to be a number")));
    return;
  }

  declinationAngle = args[0]->NumberValue(context).ToChecked();
}

void Initialize(Local<Object> exports)
{
  NODE_SET_METHOD(exports, "initialize", InitCompass);
  NODE_SET_METHOD(exports, "setOffsetMatrix", SetCompassOffset);
  NODE_SET_METHOD(exports, "setScaleMatrix", SetCompassScale);
  NODE_SET_METHOD(exports, "setDeclinationAngle", SetCompassDeclinationAngle);
  NODE_SET_METHOD(exports, "readRawData", ReadRawCompassData);
  NODE_SET_METHOD(exports, "readCorrectedData", ReadCorrectedCompassData);
  NODE_SET_METHOD(exports, "readAzimuth", ReadAzimuth);
}

NODE_MODULE(module_name, Initialize)
