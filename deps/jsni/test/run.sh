for i in `ls -d *-test`;do
  cd $i
  cp ../common_gyp/binding.gyp .
  node-gyp rebuild 1> t.log 2>~/tmp/$i.log
  rm binding.gyp
  node --expose-gc native.js
  rm build -r
  if [ $? -ne 0 ]; then
    echo "============Case: $i FAILED!============"
    cat ~/tmp/$i.log
    rm -f t.log
    echo "Fail: $i"
    exit
  else
    echo "Success: $i"
    #rm
  fi
  rm -f t.log
  cd ..
done
