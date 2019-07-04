# Assignment 5
## How to Compile
```
./build.sh
```
This will create the build folder and start  the cmake build process.
You will find the executable in the *./build/source* folder.
## How to Use
```sh
# run tests
$ ./build/source/tests

# print help information
$ ./build/source/main --help
Bentley–Ottmann algorithm
Usage:
  ./build/source/main [OPTION...]

  -h, --help      give this help list
  -n, --num arg   number of segments to generate (default: 10)
  -x, --minX arg  minimum x value (default: -100)
  -X, --maxX arg  maximum x value (default: 100)
  -y, --minY arg  minimum y value (default: -100)
  -Y, --maxY arg  maximum y value (default: 100)

# run the Bentley-Ottmann algorithm with different inputs
$ ./example.sh
```