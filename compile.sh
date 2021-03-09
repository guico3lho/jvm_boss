mkdir -p build

cd build

echo "##### Creating Makefile ######"

cmake ..

echo "#### Compiling ####"

make

cd ..

echo "Finished build! Execute calling ./sim-camada-fisica"
