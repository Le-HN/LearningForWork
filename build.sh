
if [ $1 == "clean" ]
then
    echo "cleaning..."
    rm -rf bin
    rm -rf lib
    exit
fi

if [ $1 == "compile" ]
then
    echo "compiling..."
    mkdir -p bin
    mkdir -p lib

    cd public
    sh build.sh
    cp libpublic.so ../lib/libpublic.so

    cd ../ExternalSort
    sh build.sh
    cp extsrt ../bin/external_sort

    cd ../HeapSort
    sh build.sh
    cp hpsrt ../bin/heap_sort
fi
