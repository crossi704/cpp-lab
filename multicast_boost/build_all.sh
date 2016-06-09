#!/bin/bash
set -e

echo "Cleaning up..."
rm -f sender
rm -f recv

echo "Building sender..."
./build_sender.sh

echo "Building recv..."
./build_recv.sh


echo "DONE"
exit 0
