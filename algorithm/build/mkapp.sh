
BUILD_TYPE=0

while getopts "d" OPT
do
    case $OPT in
        d)
            echo $OPTARG
            BUILD_TYPE="debug";;
        ?)
            echo "error"
            exit 1;;
    esac
done

rm -rf ../output/*
rm -rf __cache__

mkdir __cache__
cd __cache__
cmake -D CMAKE_BUILD_TYPE=$BUILD_TYPE ../..
make
cd ..
rm -rf __cache__

echo "==================run llt start====================="
if [ $BUILD_TYPE == "debug" ]; then
../output/test_main
else
../output/test_main
fi
echo "==================run llt end====================="