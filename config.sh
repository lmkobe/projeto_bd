#!/bin/bash

echo "Configuring the environment:"
echo "Checking dependencies..."
sudo apt-get update -y > logs && \
sudo apt-get -qq install postgresql postgresql-contrib -y 2>> logs && \
echo "postgresql OK."
echo "postgresql-contrib OK."
sudo apt-get -qq install qt5-default -y 2>> logs && \
echo "qt5-default OK."
sudo apt-get -qq install libqt5sql5-psql -y 2>> logs && \
echo "libqt5sql5-psql OK."
sudo apt-get -qq install python3-regex -y 2>> logs && \
echo "python3-regex OK."
sudo apt-get -qq install python3-rstr -y 2>> logs && \
echo "python3-rstr OK."
sudo -H pip3 install Faker >> logs
echo "Faker OK."
echo "Done."

qmake -makefile projeto_bd.pro
echo "Compiling the program..."
make -s && \
rm -rf *.o moc*
echo "Done."

echo "Setting up database..."
./run.sh >> logs
echo "Done."

echo "Sucessfully configured."
echo "Execute: $ ./projeto_bd"