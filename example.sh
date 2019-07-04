#!/bin/bash
echo -e "<<< FIRST EXAMPLE >>>\n"
./build/source/main
echo -e "<<< SECOND EXAMPLE >>>\n"
./build/source/main -n 30 -x -1000 -X 1000 -y -1000 -Y 1000
echo -e "<<< THIRD EXAMPLE >>>\n"
./build/source/main -n 10 -x -500 -X 500 -y -500 -Y 500