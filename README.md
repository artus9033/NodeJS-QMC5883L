# *NodeJS-QMC5883L*

# 1. Table of contents
- Overview
- Usage
- Hardware Compatibility
- Libraries Used
- License
- TODO

# 2. Overview
This is a NodeJS module that talks to the DA5883 magnetometer (on the QMC5883L board).

# 3. Usage
The module is very simple - it provides three methods:

0. _**require**_
* simply require the module and assign it to a variable:
```node
var compass = require('nodejs-qmc5883l');
```

1. _**initialize()**_
* always returns true (in the future will return false if the compass cannot be initialized)
* is obligatory to be called before any data is read
* sets the compass mode to continuous, output data rate to 200Hz, the RNG to 8 Gauss and over-sampling ratio to 256

2. _**readData()**_
* returns a javascript Object of format { x: value, y: value, z: value }
* if the initialize() function had not been called earlier, the x, y & z value are 0

3. _**readAzimuth()**_
* returns an azimuth value (calculated using the atan2 function) in degrees
* it does *not* include any hard iron error minimalization function, etc.

# 4. Example
A functional example is located in the test.js file in the module's main directory (you can also run it by executing ```npm run test``` in it).

# 5. Hardware Compatibility
The module works on the Raspberry PI 3 (tested) on NodeJS 8, but You can clone the repo and change the proper fields (I2C bus device path, I2C device address, I2C device register, etc.) in the binding.cc & other files, so that it is compatible with Your device.

# 6. Libraries Used
The module utilises Jeff Rowberg's [I2Cdev library][i2cdev] for talking to I2C devices and uses modified parts of code from [MechaQMC5883 library][qmclib], which contains all needed register addresses.

# 7. License
This project is licensed under the GNU General Public License v3. You're allowed to clone the code, modify it and use provided that You mention the author (artus9033) and provide a link to this repository.

# 8. TODO
1. Add a function to the binding to set the RNG, OSR, ODR & Mode parameters
2. Make the initialize() function return false if connection didn't succeed

[i2cdev]: https://github.com/jrowberg/i2cdevlib
[qmclib]: https://github.com/mechasolution/Mecha_QMC5883L
