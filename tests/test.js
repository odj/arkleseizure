var Arkle = require('../arkleseizure').Arkleseizure;
var a = new Arkle();
var b = new Arkle();

a.SetInFormat('smi');
a.SetOutFormat('can');

b.SetInFormat('smi');
b.SetOutFormat('mol');

console.log(a.Convert("CCC"));
console.log(b.Convert("CCC"));

console.log(a.Convert("CCC=C"));
console.log(b.Convert("CCC=C"));

console.log(a.Convert("CCC(CCC)(CC)C"));
console.log(b.Convert("CCC(CCC)(CC)C"));

console.log('Arkleseizure sneezed!');

