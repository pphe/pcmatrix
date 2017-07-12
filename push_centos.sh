#!/bin/bash
IP=
PORT=
LOGIN=


echo "Deleting remote project directory."
ssh -t -p $PORT $LOGIN@$IP "cd ~/Desktop/pcmatrix && exec rm -rf *"
echo

echo "Pushing pcmatrix folder."
scp -r -P $PORT * $LOGIN@$IP:~/Desktop/pcmatrix/.
echo

echo "Connecting to centos VM."
ssh -t -p $PORT $LOGIN@$IP "cd ~/Desktop/pcmatrix && exec $SHELL"
echo
