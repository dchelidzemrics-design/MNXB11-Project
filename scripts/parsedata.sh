#!/bin/sh

# Extract the .tar file 
echo "Extracting raw data files..."
cd ../datasets
tar -xvzf ../datasets/datasets.tgz

# Parse the desired raw data file 
echo "Parsing dataset for Lund..."
cd ../scripts
python parsedata.py
echo "Created pareseddata.csv file in: " 
pwd 
echo "Done" 


