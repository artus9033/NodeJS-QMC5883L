var compass = require('./index.js');

if (compass.initialize()) {
  setInterval(function () {
    console.log("Azimuth: " + compass.readAzimuth());
  }, 500);
}
