# REAL TIME SYSTEMS (UNAL MED): TRAIN PROJECT

This project shows an structure (without implementation) of a modularized system, in this case a representation of a train.

## How to run project? #
- [Configure and install VM](https://github.com/roboticamed/ROS_101/tree/master/MaquinaVirtual)
- [Configure ssh](https://github.com/roboticamed/ROS_101/tree/edit/SSH)
- inside VM with Ubuntu, install ```git```, ```build-essentials``` and ```cmake```:
    
    - ```~$ sudo apt install git``` 
    - ```~$ sudo apt install build-essential``` 
    - ```~$ sudo apt install cmake```
    
- clone this project:

    - ```~$ git clone https://github.com/aldajo92/RTS_UNAL_TRAIN```
    
- Run this project:
    - ```~$ cd RTS_UNAL_TRAIN```
    - ```~$ cmake .```
    - ```~$ make```
    - ```~$ ./main```

## References
https://www.tutorialspoint.com/makefile/why_makefile.htm
https://www.w3schools.in/c-tutorial/c-header-files/