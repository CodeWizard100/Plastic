#!/bin/bash
if [ "$(id -u)" -ne 0 ]; then
  echo "This script must be run as root. Please run with sudo or as root user."
  exit 1
fi

sudo apt install -y git build-essential g++ gcc cmake
rm -rf Plastic; git clone https://github.com/CodeWizard100/Plastic.git || true
cd Plastic || true
chmod +x build.sh
./build.sh
cd build/bin
clear
echo "Build is done!"
echo "ls to see binaries!"
