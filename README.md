# SEM_Console
### This repository contains 3 tools:
  - ACME : A tool that receives an EBD file (***synth_system.ebd***) and a set of coordinates that define the area where the user wants to inject errors using a SEM core. It then outputs a text file (***injectionRange.txt***) containing the Linear Frame Adresses (**LFA**) corresponding to the essential bits of the target area, which can then be used to inject errors in this block.
  - SEM : Contains C functions that allow to easily communicate with a SEM Core via a serial port and a example script that automatically injects errors using the addresses available at ***injectionRange.txt***, with a random rate based on a Weibull distribution. **Note:** If using a UltraScale+ device, remenber to uncomment ``#define ULTRASCALE_P`` in the ***sem.h*** file.
  - console : A console that allows to communicate with the SEM core via a serial port and the usage of the automatic injection script present in the ***SEM*** directory. The serial port can be changed in the ``SERIAL`` parameter present in the ***Makefile*** (default=``/dev/ttyUSB2``).

### There are 3 main Make targets:
  - ``make run`` : compiles and runs the serial console
  - ``make acme`` : compiles and runs the ACME tool. It also copies the (***injectionRange.txt***) file to the console directory.
  - ``make clean`` : deletes generated files
