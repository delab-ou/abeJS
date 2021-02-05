
console.log("test");
const napi = require("bindings")("napi-abe")
var fs = require('fs');
var keys = JSON.parse(fs.readFileSync('./keys.json'));
var abetype="KP-ABE";
const abe=new napi.JsOABE(abetype,keys[abetype]["mpk"],keys[abetype]["msk"]);
console.log("instantiate abe");

var attr1="attr1";
var attr2="attr2";
var ctext;
var ptext="text1";
var ptext2="text2";

console.log("msk = \n\""+keys[abetype]["msk"]+"\"");
console.log("mpk = \n\""+keys[abetype]["mpk"]+"\"");
abe.keygen("(attr1 or attr2)", "key0");
abe.keygen("(attr3 and attr4)","key1");
abe.keygen("(attr3 or attr5)","key2");

var cctext=abe.encrypt("attr1",ptext);
var c3o4text=abe.encrypt("attr4",ptext2);

console.log("cctext\n"+cctext);
console.log("c3o4text\n"+c3o4text);

var dtext=abe.decrypt(
  "key0",
  "AAAA86ETqm/Kkr0fhtQyQmxhI1Fy9awqy6HcoQdDX2F0dHIxoSSyoSEDGu6nQQHrEGA+8eddx0BRK5Ha14KoYMklThwFanL/1sehBENwcjKhRLOhQQMKQlP57OBOJix296Nk7jU2ocn2qML3lN3gYF5hwam3nxg+PX4YRyvHq4M1PjXrx1bZ3FLQHEKLH7D9POJS4JYgoQNfRUShRR0AAABARcBnCSMfFs0c/tIk1reMBAluAEjdNSgwz0iiEIre4ILHiJUa/6Lj8V9iN6VyqALVpKN+9qx4dMM4xcv1hQmS66EKYXR0cmlidXRlc6EHfGF0dHIxfAAAAF6hE6oARpK9H4bUMkJsYSNRcvWsKsuhR6ECQ1ShCh0AAAAF2grdneihAklWoRUdAAAAECdlEEO1rr97lLKbq4e5hrOhA1RhZ6EVHQAAABAaSmOJ4uy/VJOyC8ItalSeAAAA86ETqm/Kf9WlBkTor9EHy13E76M076HcoQdDX2F0dHI0oSSyoSECDkk28uvDdMJP6pYYUCpi7fU5ZBd/EqeEAdLknJ6wLzehBENwcjKhRLOhQQMEurKxpv3FQTfdutBIFCBz/LvNGJEZeSTMyh7RuK8QagOQwovUxSUOyXqRdWjENxzhwStSNqvRydtPnKON4nu9oQNfRUShRR0AAABAB5t+sdmSQ8KOPX3yJynYmxk4UiOLg8aj/DK/bX96VDUbI/92/rdPS1rIu4vLaMEZSgw3vioAWSmCUyFtWU45F6EKYXR0cmlidXRlc6EHfGF0dHI0fAAAAF6hE6oARn/VpQZE6K/RB8tdxO+jNO+hR6ECQ1ShCh0AAAAFBWTdCROhAklWoRUdAAAAEMVDyFTkUAabdIH3UOBjkquhA1RhZ6EVHQAAABC2kMUOlFOQ1XBElJU0fPJw");
console.log("dtext\n"+dtext);
dtext=abe.decrypt("key2",c3o4text);
console.log("decrypt \""+dtext+"\"");
