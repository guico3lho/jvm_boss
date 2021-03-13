verbose="-v"
warning="-w"
all="-all"

if [[ $1 == ${verbose} ]]
then 
  cppcheck --verbose ./src/$2.cpp
fi

if [[ $1 == ${warning} ]]
then 
  cppcheck --enable=warning ./src/$2.cpp
fi

if [[ $1 == ${all} ]]
then 
  cppcheck --verbose --enable=warning ./src/*.cpp
fi