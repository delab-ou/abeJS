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

    return exports;
}


JsOABE::JsOABE(const Napi::CallbackInfo& info): Napi::ObjectWrap<JsOABE>(info){

  auto env = info.Env();

  oabe::InitializeOpenABE();
  this->cpabe=new oabe::OpenABECryptoContext("CP-ABE");
  this->cpabe->generateParams();
}
JsOABE::~JsOABE(){
  oabe::ShutdownOpenABE();
  delete this->cpabe;
}

Napi::Value JsOABE::keygen(const Napi::CallbackInfo &info){
  auto env = info.Env();
  if (info.Length() !=2) {
      Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
      return env.Null();
    }
    std::string attrs = info[0].As<Napi::String>().ToString();
    std::string key = info[1].As<Napi::String>().ToString();

    std::cout<<"attr:"<<attrs<<" key:"<<key<<std::endl;
    this->cpabe->keygen(attrs,key);
    std::cout<<"attr:"<<attrs<<" key:"<<key<<std::endl;

}

Napi::Value JsOABE::encrypt(const Napi::CallbackInfo &info){
  auto env = info.Env();
  if (info.Length() !=2) {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  std::string attrs = info[0].As<Napi::String>().ToString();
  std::string plain = info[1].As<Napi::String>().ToString();
  std::string cipher="";

  this->cpabe->encrypt(attrs, plain, cipher);

  std::cout<<"cipher text="<< cipher <<std::endl;

  return Napi::String::New(env, cipher);
}

Napi::Value JsOABE::decrypt(const Napi::CallbackInfo &info){
  auto env = info.Env();
  if (info.Length() < 1) {
      Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
      return env.Null();
    }
    std::string attrs = info[0].As<Napi::String>().ToString();
    std::string cipher = info[1].As<Napi::String>().ToString();
    std::string plain="";
    bool result = this->cpabe->decrypt(attrs, cipher, plain);
    return Napi::String::New(env, plain);

}



Napi::Object init(Napi::Env env, Napi::Object exports)
{
    // ラッパークラスを初期化する
    JsOABE::Init(env, exports);

    std::cout<<"finish Init: "<<std::endl;
    // エクスポート結果を返却
    return exports;
}
NODE_API_MODULE(napi_abe, init)
