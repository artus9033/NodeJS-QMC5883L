var compass = require('./build/Release/binding');

if (compass.initialize()) {
  setInterval(function () {
    console.log(compass.readAzimuth());
  }, 10);
}
