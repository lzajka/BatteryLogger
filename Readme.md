# BatteryLogger

A simple C application/service that logs time, battery level & health every 15 minutes into a csv document in user's home directory.

## How to install

1. install dependencies

    the installation process depends on your distro.
    You'll need to install those:
    * cmake
    * make
    * git

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

NOTE: this will install locally for the user. No idea if this works with sudo. 
