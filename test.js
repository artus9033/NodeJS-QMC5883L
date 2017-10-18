var compass = require('./index.js');

// sample offset & scale data, generated myself, be sure
// to grab your own using the `node calibrate` function, because
// the magnetic field distortion is different in each place on the Earth

var offset = {
  x: 0,
  y: 0,
  z: 0,
}

var scale = {
  x: 1,
  y: 1,
  z: 1,
}

compass.setOffsetMatrix(offset.x, offset.y, offset.z);
compass.setScaleMatrix(scale.x, scale.y, scale.z);

if (compass.initialize()) {
  setInterval(function () {
    console.log("Azimuth: " + compass.readAzimuth());
  }, 500);
}
