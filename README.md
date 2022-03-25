# gps-mapper

This project was created using a Particle Boron and GPS module to map cell reception signal strength. 

## Particle Project Link:
https://go.particle.io/shared_apps/5ee1516449afab0007c22522

## Materials
* Particle Boron
* Featherwing Tripler
* Adafruit Ultimate GPS FeatherWing
* IPEX mini PCI to SMA Connector
* 4G LTE SMA Antenna
* 2000 mAH Lipo Battery
* Enclosure (Boron Dev Kit Case Pictured)
* 2 Position Terminal SPDT Latching Mini Toggle Switch

*Not Pictured*
* Vehicle SMA GPS Antenna
* 1/2" PVC ~4'
* 1/2" PVC T-connector
* 2 * 1/2" PVC 90 Degree Elbow Connectors 


![Cell-sig-logger](https://user-images.githubusercontent.com/11817583/135155303-3fac4cbb-ecd5-449d-9526-e3e3c8369aa3.png)


---
# VS Code - Particle Workbench Extention Info

## Welcome to your project!

Every new Particle project is composed of 3 important elements that you'll see have been created in your project directory for gps-mapper.

#### ```/src``` folder:  
This is the source folder that contains the firmware files for your project. It should *not* be renamed. 
Anything that is in this folder when you compile your project will be sent to our compile service and compiled into a firmware binary for the Particle device that you have targeted.

If your application contains multiple files, they should all be included in the `src` folder. If your firmware depends on Particle libraries, those dependencies are specified in the `project.properties` file referenced below.

#### ```.ino``` file:
This file is the firmware that will run as the primary application on your Particle device. It contains a `setup()` and `loop()` function, and can be written in Wiring or C/C++. For more information about using the Particle firmware API to create firmware for your Particle device, refer to the [Firmware Reference](https://docs.particle.io/reference/firmware/) section of the Particle documentation.

#### ```project.properties``` file:  
This is the file that specifies the name and version number of the libraries that your project depends on. Dependencies are added automatically to your `project.properties` file when you add a library to a project using the `particle library add` command in the CLI or add a library in the Desktop IDE.

## Adding additional files to your project

#### Projects with multiple sources
If you would like add additional files to your application, they should be added to the `/src` folder. All files in the `/src` folder will be sent to the Particle Cloud to produce a compiled binary.

#### Projects with external libraries
If your project includes a library that has not been registered in the Particle libraries system, you should create a new folder named `/lib/<libraryname>/src` under `/<project dir>` and add the `.h`, `.cpp` & `library.properties` files for your library there. Read the [Firmware Libraries guide](https://docs.particle.io/guide/tools-and-features/libraries/) for more details on how to develop libraries. Note that all contents of the `/lib` folder and subfolders will also be sent to the Cloud for compilation.

## Compiling your project

When you're ready to compile your project, make sure you have the correct Particle device target selected and run `particle compile <platform>` in the CLI or click the Compile button in the Desktop IDE. The following files in your project folder will be sent to the compile service:

- Everything in the `/src` folder, including your `.ino` application file
- The `project.properties` file for your project
- Any libraries stored under `lib/<libraryname>/src`
