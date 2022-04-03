rm -rf ../output/*
rm -rf __cache__

mkdir __cache__
cd __cache__
cmake ../..
make
cd ..
rm -rf __cache__

echo "==================run llt start====================="
../output/test_main
echo "==================run llt end====================="