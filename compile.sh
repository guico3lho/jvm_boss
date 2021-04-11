windows="-w"
linux="-l"

clear 

mkdir -p build 
cd build

echo "##### Creating Makefile ######"

if [[ $1 == ${windows} ]]
then 
  cmake .. -G "Unix Makefiles"
fi

if [[ $1 == ${linux} ]]
then 
  cmake .. 
fi

echo "#### Compiling ####"
make
cd ..

if [[ $1 == ${windows} ]]
then 
  echo "Finished build! Execute calling ./jvm_boss.exe"
fi

if [[ $1 == ${linux} ]]
then 
  echo "Finished build! Execute calling ./jvm_boss" 
fi


