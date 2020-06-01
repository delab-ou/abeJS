#include "napi-abe.hpp"

Napi::FunctionReference JsOABE::constructor;

Napi::Object JsOABE::Init(Napi::Env env, Napi::Object exports){
    Napi::HandleScope scope(env);

    Napi::Function func = DefineClass(env, "JsOABE", {
        InstanceMethod("encrypt", &JsOABE::encrypt),
        InstanceMethod("decrypt", &JsOABE::decrypt),
        InstanceMethod("keygen", &JsOABE::keygen),
    });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    exports.Set("JsOABE", func);
    cpabe=new oabe::OpenABECryptoContext("CP-ABE");
    return exports;
}


JsOABE::JsOABE(const Napi::CallbackInfo& info): Napi::ObjectWrap<JsOABE>(info){
  
}
JsOABE::~JsOABE(){
  delete this->cpabe;
}
Napi::Value JsOABE::encrypt(const Napi::CallbackInfo &info){
  auto env = info.Env();
  if (info.Length() < 1) {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }
  std::cout<<info[0]<<std::endl;

}
Napi::Value JsOABE::decrypt(const Napi::CallbackInfo &info){
  auto env = info.Env();
  if (info.Length() < 1) {
      Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
      return env.Null();
    }
  std::cout<<info[0]<<std::endl;
}
Napi::Value JsOABE::keygen(const Napi::CallbackInfo &info){auto env = info.Env();
  if (info.Length() < 1) {
      Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
      return env.Null();
    }
}

Napi::Object init(Napi::Env env, Napi::Object exports)
{
    // ラッパークラスを初期化する
    JsOABE::Init(env, exports);

    // エクスポート結果を返却
    return exports;
}
NODE_API_MODULE(napi_abe, init)
