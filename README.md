# _NodeJS-QMC5883L_

### **!!!** Compatible with NodeJS versions `10.X - 12.X` **!!!**

# 1. Table of contents

- Overview & Installation
- Usage
- Hardware Compatibility
- Libraries Used
- License
- TODO

# 2. Overview & Installation

This is a simple NodeJS module that talks to the DA5883 magnetometer (on the QMC5883L board). You can install it by running `npm install --save nodejs-qmc5883l`. Every magnetometer reading is a bit mistaken (caused e.g. by soft and hard iron effect), but that can be corrected by calibrating the compass. Calibration gives you an offset matrix and a scale matrix that needs to be applied on raw magnetometer data before any further computation. To do this, run `node calibrate` in the module's main directory, rotate the magnetometer in all directions until the script finishes running and the matrixes will be printed in the console, and then call `setOffsetMatrix` and `setScaleMatrix` on the module object. After doing so, you can read the compensated data via the `readCorrectedData()` function (if you use the `readAzimuth` function, then the azimuth is computed on the already compensated data).

# 3. Usage

The module is very simple - it provides three methods:

_**Before you start**_
Simply require the module library and assign it to a variable:

```node
var compass = require("nodejs-qmc5883l");
```

_**1. initialize()**_

- always returns true (in the future will return false if the compass cannot be initialized)
- is obligatory to be called before any data is read
- sets the compass mode to continuous, output data rate to 200Hz, the RNG to 8 Gauss and over-sampling ratio to 256

_**2. readRawData()**_

- returns a javascript Object of format { x: value, y: value, z: value } with raw magnetometer data (without scale & offset matrixes)
- if the initialize() function had not been called earlier, the x, y & z value are 0

_**3. readCorrectedData()**_

- returns a javascript Object of format { x: value, y: value, z: value } with compensated magnetometer data (with scale & offset matrixes applied)
- if the initialize() function had not been called earlier, the x, y & z value are 0

_**4. setOffsetMatrix(offsetX, offsetY, offsetZ)**_

- sets the offset matrix used by the readCorrectedData()

_**5. setScaleMatrix(scaleX, scaleY, scaleZ)**_

- sets the scale matrix used by the readCorrectedData()

_**6. readAzimuth()**_

- returns an azimuth value (calculated using the atan2 function) in degrees
- it takes the readCorrectedData() function for data input
- if the initialize() function had not been called earlier, returns 0

_**7. setDeclinationAngle(declinationAngle)**_

- takes a single declinationAngle parameter of any number type
- sets the declination angle that is added to the azimuth when calling readAzimuth() to correct the magnetic field differences
- you can calculate the angle using the following formula: declinationAngle = (degrees + (minutes / 60.0)) / (180 / PI)
  _(see test.js)_

# 4. Example

A functional example is located in the test.js file in the module's main directory (you can also run it by executing `npm run test` in it).

# 5. Hardware Compatibility

The module works on the Raspberry PI 3 (tested) on NodeJS 8, but You can clone the repo and change the proper fields (I2C bus device path, I2C device address, I2C device register, etc.) in the binding.cc & other files, so that it is compatible with Your device.

# 6. Libraries Used

The module utilises Jeff Rowberg's [I2Cdev library][i2cdev] for talking to I2C devices and uses modified parts of code from [MechaQMC5883 library][qmclib], which contains all needed register addresses. The calibration code is based on the one used in [this HMC5883 library][hmclib].

# 7. License

This project is licensed under the GNU General Public License v3. You're allowed to clone the code, modify it and use provided that You mention the author (artus9033) and provide a link to this repository.

# 8. TODO

1. Add a function to the binding to set the RNG, OSR, ODR & Mode parameters
2. Make the initialize() function return false if connection didn't succeed

[i2cdev]: https://github.com/jrowberg/i2cdevlib
[qmclib]: https://github.com/mechasolution/Mecha_QMC5883L
[hmclib]: https://github.com/psiphi75/compass-hmc5883l
