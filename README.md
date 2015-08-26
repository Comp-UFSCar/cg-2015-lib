# Computer Graphics and Multimedia (UFSCar/Fall 2015)

How to Compile/Execute
----------------------

Library **X11 is required** to run this code so if you're using *Debian-based* (Linux Mint / Ubuntu) don't forget to:
` sudo apt-get install libX11-dev `


```bash
# Clone the repository
git clone https://github.com/thamenato/computer_graphics_ufscar2015.git
# Cloning into 'computer_graphics_ufscar2015'...
# ...

# Navigate to the directory
cd computer_graphics_ufscar2015
# Make a build directory and navigate to it
mkdir build
cd build

# Generate CMake cache and other stuff
cmake ..
# Time to compile
make

# If everything goes well and you see [100%] Built target monitor_cthulhu
# Execute the binary
./bin/monitor_cthulhu
```



