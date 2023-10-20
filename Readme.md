# BatteryLogger

A simple C application/service that logs time, battery level & health every 15 minutes into a csv document in user's home directory.

## How to install

1. install dependencies

    the installation process depends on your distro.
    You'll need to install those:
    * cmake
    * make
    * git
    * gcc

2. First clone the repository

``
git clone https://github.com/lzajka/BatteryLogger
``

3. create and cd into the build directory
   
`` 
mkdir build && cd build
``

4. now build it

``
cmake ..
make
``

5. Install

``
make install
``

**NOTE**: When installing/making/cmaking do not use _sudo_ as the BatteryLogger is supposed to be installed for the user.
System-wide installation will not work.
