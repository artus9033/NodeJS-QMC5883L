# 1. Table of contents
- Overview
- Usage
- Hardware Compatibility
- Libraries Used
- License

# 2. Overview
This is a NodeJS module that talks to the DA5883 magnetometer (QMC5883 board).

# 3. Usage
[TODO]

# 4. Hardware Compatibility
The module works on the Raspberry PI 3 (tested), but You can clone the repo and change the proper fields (I2C bus device path, I2C device address, I2C device register, etc.) in the binding.cc & other files, so that it is compatible with Your device.

# 5. Libraries Used
The module utilises Jeff Rowberg's I2Cdev (https://github.com/jrowberg/i2cdevlib) library for talking to I2C devices and parts of code from https://github.com/mechasolution/Mecha_QMC5883L, which contains all the register addresses.

# 6. License
This project is licensed under the GNU General Public License v3. You're allowed to clone the code, modify it and use provided that You mention the author (artus9033) and provide a link to this repository.
