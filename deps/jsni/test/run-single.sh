file=$1
echo $file
cd $file
cp ../common_gyp/binding.gyp .
node-gyp rebuild
node --expose-gc native.js
cd ..
