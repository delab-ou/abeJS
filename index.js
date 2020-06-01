
console.log("test");
const abe = require("bindings")("napi-abe")

var attr1="attr1";
var attr2="attr2";
var ctext;
var ptext="text1";

var cctext=abe.encrypt(attr1+attr2,ptext,ctext);
