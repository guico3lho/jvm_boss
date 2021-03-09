mkdir -p build 
cd build

echo "##### Creating Makefile ######"
cmake .. -G "Unix Makefiles"

echo "#### Compiling ####"
make
cd ..

echo "Finished build! Execute calling ./jvm_boss.exe"
