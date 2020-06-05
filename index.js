
console.log("test");
const napi = require("bindings")("napi_abe")
const abe= new napi.JsOABE("KP-ABE");

console.log("instantiate abe");
var attr1="attr1";
var attr2="attr2";
var ctext;
var ptext="text1";
var ptext2="text2";

abe.keygen("(attr1 or attr2)", "key0");
abe.keygen("(attr3 and attr4)","key1");
abe.keygen("(attr3 or attr5)","key2");
var cctext=abe.encrypt("attr1",ptext);
var c3o4text=abe.encrypt("attr4",ptext2);

console.log(cctext);
console.log(c3o4text);

var dtext=abe.decrypt("key0",cctext);
console.log(dtext);
dtext=abe.decrypt("key2",c3o4text);
console.log("decrypt \""+dtext+"\"");
