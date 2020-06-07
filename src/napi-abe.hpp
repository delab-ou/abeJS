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
  Napi::Value importMPK(const Napi::CallbackInfo &info);
  Napi::Value importMSK(const Napi::CallbackInfo &info);
  Napi::Value exportMPK(const Napi::CallbackInfo &info);
  Napi::Value exportMSK(const Napi::CallbackInfo &info);

protected:
  static oabe::OpenABECryptoContext *abe;

private:
  static Napi::FunctionReference constructor;
};
