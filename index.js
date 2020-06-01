
console.log("test");
const napi = require("bindings")("napi_abe")
const abe= new napi.JsOABE("cp-abe");

console.log("instantiate abe");
var attr1="attr1";
var attr2="attr2";
var ctext;
var ptext="text1";

abe.keygen("|attr1|attr2|", "key0");

var cctext=abe.encrypt(attr1+" and "+attr2,ptext);

console.log(cctext);

var dtext=abe.decrypt("key0",cctext);
console.log(dtext);
