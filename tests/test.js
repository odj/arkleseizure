var Arkle = require('../arkleseizure').Arkleseizure;
var a = new Arkle();

a.SetInFormat('smi');
a.SetOutFormat('mol');
console.log(a.Convert("CCC"));

console.log('Arkleseizure sneezed!');

