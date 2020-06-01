#include <napi.h>
#include <string>
#include <openabe/openabe.h>
#include <openabe/zsymcrypto.h>

class JsOABE : public Napi::ObjectWrap<JsOABE> {

public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  JsOABE(const Napi::CallbackInfo& info);
  ~JsOABE();
  Napi::Value encrypt(const Napi::CallbackInfo &info);
  Napi::Value decrypt(const Napi::CallbackInfo &info);
  Napi::Value keygen(const Napi::CallbackInfo &info);

protected:
  oabe::OpenABECryptoContext *cpabe;

private:
  static Napi::FunctionReference constructor;
};
