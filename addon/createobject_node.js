console.time('for');

var ary = [];
for(var i=0;i<10000000;i++){
ary.push({"aaa":123})
}


console.timeEnd('for');