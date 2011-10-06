var Arkle = require('../arkleseizure');
var a = new Arkle.OBConvert();
var b = new Arkle.OBConvert();

a.SetInFormat('smi');
a.SetOutFormat('can');
console.log('Input format: ' + a.GetInFormat());
console.log('Output format: ' + a.GetOutFormat());

console.log(a.Convert("CCC"));
console.log(a.Convert("CCC=C"));
console.log(a.Convert("CCC(CCC)(CC)C"));


b.SetInFormat('smi');
b.SetOutFormat('mdl');
console.log('Input format: ' + b.GetInFormat());
console.log('Output format: ' + b.GetOutFormat());

console.log(b.Convert("CCC"));
console.log(b.Convert("CCC=C"));
console.log(b.Convert("CCC(CCC)(CC)C"));
console.log('Arkleseizure sneezed!');

