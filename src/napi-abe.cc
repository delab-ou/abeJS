#include "napi-abe.hpp"

Napi::FunctionReference JsOABE::constructor;
oabe::OpenABECryptoContext *JsOABE::abe;

Napi::Object JsOABE::Init(Napi::Env env, Napi::Object exports){
    Napi::HandleScope scope(env);

    Napi::Function func = DefineClass(env, "JsOABE", {
        InstanceMethod("encrypt", &JsOABE::encrypt),
        InstanceMethod("decrypt", &JsOABE::decrypt),
        InstanceMethod("keygen", &JsOABE::keygen),
        InstanceMethod("exportMPK",&JsOABE::exportMPK),
        InstanceMethod("exportMSK",&JsOABE::exportMSK),
        InstanceMethod("importMPK",&JsOABE::importMPK),
        InstanceMethod("importMSK",&JsOABE::importMSK)
    });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    exports.Set("JsOABE", func);

    return exports;
}


JsOABE::JsOABE(const Napi::CallbackInfo& info): Napi::ObjectWrap<JsOABE>(info){

  auto env = info.Env();
  std::string abetype;
  oabe::InitializeOpenABE();

  if (info.Length() >= 1) {
      std::string tmp = info[0].As<Napi::String>().ToString();
      if((tmp != "CP-ABE") && (tmp!="KP-ABE")){
        abetype="KP-ABE";
      }
      else{
        abetype=tmp;
      }
  }
  else{
    abetype="KP-ABE";
  }

  std::cout << "type:" << abetype << std::endl;
  this->abe=new oabe::OpenABECryptoContext(abetype);
  //this->abe->generateParams();

  if (info.Length() ==3) {
    std::string mpk = info[1].As<Napi::String>().ToString();
    std::string msk = info[2].As<Napi::String>().ToString();
    this->abe->importPublicParams(mpk);
    this->abe->importSecretParams(msk);
  }
}

JsOABE::~JsOABE(){
  oabe::ShutdownOpenABE();
  delete this->abe;
}

Napi::Value JsOABE::exportMSK(const Napi::CallbackInfo &info){
  auto env = info.Env();
  std::string msk;
  this->abe->exportSecretParams(msk);
  std::cout << "export msk = " << msk <<std::endl;
  return Napi::String::New(env, msk);
}

Napi::Value JsOABE::exportMPK(const Napi::CallbackInfo &info){
  auto env = info.Env();
  std::string mpk;
  this->abe->exportPublicParams(mpk);
  std::cout << "export mpk = " << mpk <<std::endl;

  return Napi::String::New(env, mpk);
}

Napi::Value JsOABE::importMPK(const Napi::CallbackInfo &info){
  auto env = info.Env();
  if (info.Length() !=1) {
      Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
      return env.Null();
  }
  std::string mpk = info[0].As<Napi::String>().ToString();
  std::cout << "import mpk = " << mpk <<std::endl;
  this->abe->importPublicParams(mpk);
  return env.Null();
}

Napi::Value JsOABE::importMSK(const Napi::CallbackInfo &info){
  auto env = info.Env();
  if (info.Length() !=1) {
      Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
      return env.Null();
  }
  std::string msk = info[0].As<Napi::String>().ToString();
  std::cout << "import msk = " << msk <<std::endl;
  this->abe->importSecretParams(msk);
  return env.Null();

}

Napi::Value JsOABE::keygen(const Napi::CallbackInfo &info){
  auto env = info.Env();
  if (info.Length() !=2) {
      Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
      return env.Null();
    }
    std::string attrs = info[0].As<Napi::String>().ToString();
    std::string key = info[1].As<Napi::String>().ToString();

    //std::cout<<"attr:"<<attrs<<" key:"<<key<<std::endl;
    this->abe->keygen(attrs,key);
    //std::cout<<"attr:"<<attrs<<" key:"<<key<<std::endl;
    return env.Null();

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

  this->abe->encrypt(attrs, plain, cipher);

  //std::cout<<"cipher text="<< cipher <<std::endl;

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

    bool result = this->abe->decrypt(attrs, cipher, plain);
    return (result)?Napi::String::New(env, plain):Napi::String::New(env, "");

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
