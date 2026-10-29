# About
This repository contains a MNXB11 project that aims to make a program that performs four different analyses of meteorological data from SMHI (Sveriges meteorologiska och hydrologiska institut) collected in Lund.  Following the build
instructions creates a `main` executable that can be used to create a ROOT TTree that consists of a single branch with five leafs (year, month, day, hour and temperature). It can also take as argument a number corresponding to the analysis one wishes to perform. Please refer to the project report for a indepth description of the different analyses. In [`Workplan.md`](Workplan.md) there is a workflow chart that visualizes the different steps that was taken when working on this project.  

# Directory structure


- [datasets](datasets): Contains raw temperature data from SMHI. This is also where the parsed data file will end up after executing [`scripts/parsedata.sh`](scripts/parsedata.sh)

- [include](include): Contains all cutsom header files as well as [`Linkdef.h`](Linkdef.h) which will tell `rootcling` which classes should be added to the ROOT dictionary. 

- [scripts](scripts): Contains a BASH script [`parsedata.sh`](parsedata.sh) that extracts [`datasets.tgz`](datasets.tgz) and parses the data corresponding to Lund and writes it to a new file `parseddata.csv`.

- [macros](macros): Contains all ROOT macros that performs the analyses. 

- [results](results): The folder where the results will end up.

- [slurm](slurm): Contains a SLURM BATCH job file. 

- [src](src): Contains all source files other than [`main.cxx`](main.cxx). 


# Building the project
Below we go through, in order, all the steps needed to build the project. Before running any of the steps below, however, make sure you are inside the course container by executing 

```sh
# Enter the course container
/projects/hep/fs11/share/mnxb11/bin/startmnxb11container.sh bash
```
## Parsing the raw data
To extract and parse the raw data, change into the [scripts](scripts) folder and execute the BASH script [`parsedata.sh`](parsedata.sh). From the base directory, do the following
```sh
# Change into the scripts folder 
cd scripts

# Make sure you have permisson to execute the script 
chmod +x parsedata.sh

# Execute the script
./parsedata.sh
```
This will create a new file `parseddata.csv` inside the [datasets](datasets) folder that contains parsed data from the SMHI station in Lund. During the parsing, all data labeled by 'Y' (aggregated data) were exluded. 

## Adding external software libraries
The projects makes use of an external csv file parsing library that is used when extracting the data from `parseddata.csv`. From the base directory, do the following 

``` sh
# Create an external/include directory 
mkdir -pv external/include 

# Clone the csv parser library into the external/include folder and name it csv
git clone https://github.com/ben-strasser/fast-cpp-csv-parser external/include/csv
```
## Build the ROOT dictionary contaning custom library and `Observation` class
The data extraction part of the project makes use of a custom `Observation` class to generate a ROOT TTree object. Before creating the ROOT TTree the required library first have to be built. This is automated by embedding `rootcling` inside [`Makefile`](Makefile). From the base directory, do 

``` sh
# Generate ROOT dictionary 
make libObservation.so
```

## Build the `main` executable
Inside the base directory, do 

``` sh
# Generate ROOT dictionary 
make main
```

# Using the `main` executable
In order to generate the ROOT TTree called `temperature_tree.root` inside the base directory, simply run the `main` executable without any arguments 

``` sh
# Generate ROOT TTree
./main
```
To perform one of the four analyses, give the `main` executable as an argument the analysis you wish to perform 
``` sh
# Perform analysis 1
./main 1

# Perform analysis 2
./main 2

# Perform analysis 3
./main 3

# Perform analysis 4
./main 4
```
The results produced can be found inside the [results](results) folder.

# Clean the project
All object files, extracted/parsed data and ROOT dictionaries can be removed by executing 
``` sh
# Cleans the project 
make clean
```
This will remove everything except the generated results.
