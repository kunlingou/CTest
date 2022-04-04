
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

cd `dirname $0`
cd ..
PROJECT_ROOT_PATH=$(pwd)

rm -rf ${PROJECT_ROOT_PATH}/output/*
rm -rf ${PROJECT_ROOT_PATH}/build/__cache__
mkdir ${PROJECT_ROOT_PATH}/build/__cache__

cd ${PROJECT_ROOT_PATH}/build/__cache__
cmake -D CMAKE_BUILD_TYPE=$BUILD_TYPE ../..
make
cd ..
rm -rf __cache__

echo "==================run llt start====================="
if [ $BUILD_TYPE == "debug" ]; then
${PROJECT_ROOT_PATH}/output/test_main
else
${PROJECT_ROOT_PATH}/output/test_main
fi
echo "==================run llt end====================="