
if [ $1 == "clean" ]
then
    echo "cleaning..."
    rm -rf build
    rm -rf CMakeFiles
    exit
fi

mkdir -p build
echo "compiling..."
cmake .
sudo make
