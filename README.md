# *NodeJS-QMC5883L*

# 1. Table of contents
- Overview & Installation
- Usage
- Hardware Compatibility
- Libraries Used
- License
- TODO

# 2. Overview & Installation
This is a simple NodeJS module that talks to the DA5883 magnetometer (on the QMC5883L board). You can install it by running ```npm install --save nodejs-qmc5883l```. Every magnetometer reading is a bit mistaken (caused by soft and hard iron effect), but that can be handled by calibrating the compass. Calibration gives you an offset matrix and a scale matrix that need to be applied on raw magnetometer data before any further computation (in the future I'll implement this so that you will only need to pass the matrixes to the constructor). For now you can do this manually and to find the matrixes, just run ```node calibrate``` in the module's main directory, rotate the magnetometer in all directions until the script finishes running and the matrixes will be printed in the console.

# 3. Usage
The module is very simple - it provides three methods:

_**Before you start**_
Simply require the module library and assign it to a variable:
```node
var compass = require('nodejs-qmc5883l');
```

_**1. initialize()**_
* always returns true (in the future will return false if the compass cannot be initialized)
* is obligatory to be called before any data is read
* sets the compass mode to continuous, output data rate to 200Hz, the RNG to 8 Gauss and over-sampling ratio to 256

_**2. readData()**_
* returns a javascript Object of format { x: value, y: value, z: value }
* if the initialize() function had not been called earlier, the x, y & z value are 0

_**3. readAzimuth()**_
* returns an azimuth value (calculated using the atan2 function) in degrees
* it does *not* include any hard iron error minimalization function, etc.

# 4. Example
A functional example is located in the test.js file in the module's main directory (you can also run it by executing ```npm run test``` in it).

# 5. Hardware Compatibility
The module works on the Raspberry PI 3 (tested) on NodeJS 8, but You can clone the repo and change the proper fields (I2C bus device path, I2C device address, I2C device register, etc.) in the binding.cc & other files, so that it is compatible with Your device.

# 6. Libraries Used
The module utilises Jeff Rowberg's [I2Cdev library][i2cdev] for talking to I2C devices and uses modified parts of code from [MechaQMC5883 library][qmclib], which contains all needed register addresses. The calibration code is based on the one used in [this HMC5883 library][hmclib].

# 7. License
This project is licensed under the GNU General Public License v3. You're allowed to clone the code, modify it and use provided that You mention the author (artus9033) and provide a link to this repository.

# 8. TODO
1. Add a function to the binding to set the RNG, OSR, ODR & Mode parameters
2. Make the initialize() function return false if connection didn't succeed
3. Add offset & scale matrixes functionality

[i2cdev]: https://github.com/jrowberg/i2cdevlib
[qmclib]: https://github.com/mechasolution/Mecha_QMC5883L
[hmclib]: https://github.com/psiphi75/compass-hmc5883l