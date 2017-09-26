gyp="../common-gyp/binding-code-coverage.gyp"
for i in `ls -d *-test`;do
  cd $i
  cp $gyp binding.gyp
  node-gyp rebuild 1> t.log 2>~/tmp/$i.log
  node --expose-gc native.js
  if [ $? -ne 0 ]; then
    echo "============Case: $i FAILED!============"
    #cat ~/tmp/$i.log
    rm -f t.log
    echo "Fail: $i"
    exit
  else
    echo "Success: $i"
    #rm
  fi
  #rm build -r
  #rm binding.gyp
  rm -f t.log
  cd ..
done
