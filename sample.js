let str = '';
let str10 = ''
let str100 ='';
let str1k='';

let hw='helloworld';

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
str100=genStr(10,hw);
str1k=genStr(10,str100);
str10k=genStr(10,str1k);
str100k=genStr(10,str10k);
str1M=genStr(10,str100k);

console.log(str10);
console.log('str100 length='+str100.length);
console.log('str1k length'+str1k.length);

let attr=genAttr(1,'and');


console.log(attr);
// expected output: "012345678"
