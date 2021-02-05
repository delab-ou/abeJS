
console.log("test");
const { PerformanceObserver, performance } = require('perf_hooks');
const napi = require("bindings")("napi-abe")
var fs = require('fs');
var keys = JSON.parse(fs.readFileSync('./keys.json'));
//var abetype="KP-ABE";
//const abe=new napi.JsOABE(abetype,keys[abetype]["mpk"],keys[abetype]["msk"]);
//console.log("instantiate abe");

function genStr(num,str){
  let v='';
  for(let i=0; i<num;i++){
    v+=str;
  }
  return v;
}

function genAttr(num,andor){
  let attr='attr1';
  for(let i=2;i<=num;i++){
    attr=attr+' '+andor+' attr'+i;
  }
  return attr;
}

function runABE(abe,encattr,keyattr,data){
  let keygentime=performance.now();
  abe.keygen(keyattr, "key0");//"attr1 | attr2 | attr3 | attr4"
  keygentime=performance.now()-keygentime;

  let cctex='';
  let enctime=performance.now();
  for(let k=0;k<100;k++){
    cctext=abe.encrypt(encattr,data);
  }
  enctime=performance.now()-enctime;

  let dectime=performance.now();
    for(let k=0;k<1000;k++){
      let dtext=abe.decrypt('key0',cctext);
    }
  dectime=performance.now()-dectime;
  console.log('keygen:'+keygentime+','+
      'encryption:'+enctime+','+
      'decryption:'+dectime+","+
      'plain:'+data.length+","+
      'cipher:'+cctext.length);
}

function runKPABE(){
  const abe=new napi.JsOABE('KP-ABE',keys["KP-ABE"]["mpk"],keys["KP-ABE"]["msk"]);
  let initialdata=genStr(10,'helloworld');//1k length
  for(let i=0;i<4;i++){
    let data=genStr(10,initialdata);
    for(let j=10;j<=100;j=j+10){
      encattr=genAttr(j,"|");
      keyattrOr=genAttr(j,"or");
      keyattrAnd=genAttr(j,"and")
      console.log("kp "+"data length="+data.length+" attributes="+j+" type=and");
      runABE(abe,encattr,keyattrAnd,data);
      console.log("kp "+"data length="+data.length+" attributes="+j+" type=or");
      runABE(abe,encattr,keyattrOr,data);
    }
    initialdata=data;
  }
}

runKPABE();
