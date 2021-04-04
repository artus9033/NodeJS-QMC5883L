var compass = require("./index.js");

// sample offset & scale data that do nothing, generated myself, be sure
// to grab your own using the `node calibrate` function, because
// the magnetic field distortion is different in each place on the Earth

var offset = {
  x: 0,
  y: 0,
  z: 0,
};

var scale = {
  x: 1,
  y: 1,
  z: 1,
};

var precision = 2;

compass.setOffsetMatrix(offset.x, offset.y, offset.z);
compass.setScaleMatrix(scale.x, scale.y, scale.z);

//apply the local declination angle correction
//values for Tarnowskie Gory, Poland: 5 degrees, 1 minute
//taken from: http://magnetic-declination.com/
//formula: declinationAngle = (degrees + (minutes / 60.0)) / (180 / PI);
var declinationAngle = (5.0 + 1.0 / 60.0) / (180 / Math.PI);
compass.setDeclinationAngle(declinationAngle);

console.log("Declination angle correction: " + declinationAngle);
console.log("Scale matrix: " + JSON.stringify(scale));
console.log("Offset matrix: " + JSON.stringify(offset));
console.log("Precision (digits after comma): " + precision);

if (compass.initialize()) {
  setInterval(function () {
    console.log("Azimuth: " + compass.readAzimuth().toFixed(precision));
  }, 500);
}
