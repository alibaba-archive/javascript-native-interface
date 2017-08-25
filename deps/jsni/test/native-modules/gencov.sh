# first, cp *.gcda and *.gcno to build dir;
#   use lcov gen *.info--each;
#   and for each, copy *.info to tmp/;
# second, use lcov to add all *.info to all.info.
# last, use genhtml to gen index.html

# Enjoy to read the index.html.


# Usage:
# 1. Use cpbind.sh to replace binding.gyp
# with another gyp which is configured with -lgcov

# 2. Use gencov.sh:
# $./gencov.sh 


# *gcno, *.gcda
root_dir=`pwd`"/../../../"
GCS="Release/obj.target/native/native.*"
JSNIGCS=$root_dir"/out/Release/obj.target/jsni/deps/jsni/src/v8/*"
JSNISRC=$root_dir"/deps/jsni/src/v8/"
TESTSRC=$root_dir"/deps/jsni/test/"
JSNIGENDIR=$root_dir"/out"

# result and *.info dir.
COVDIR="tmp_cov"
INFODIR="info"

# tmp/ dir
mkdir -p $COVDIR
mkdir -p $COVDIR/$INFODIR

for i in `ls -d *-test`; do
  cd $i
    cd build/
    # cp *.gcda *gcno
    cp $GCS .
    # gen info.
    lcov -d . -t "$i" -o $i.info -b . -c
    # cp info.
    cp $i.info ../../$COVDIR/$INFODIR/
    cd .. 
  cd ..
done

# process jsni cov info.
cd $JSNIGENDIR
cd ..
mkdir -p jsnicov
cd jsnicov
# cp *.gcda *.gcno
cp $JSNIGCS .
lcov -d . -t jsni -o jsni.info -b . -c
cp jsni.info $TESTSRC/$COVDIR/$INFODIR/
cd $TESTSRC

echo "=================genhtml================="
# *.infos are ready. Lets gen html.
cd $COVDIR
genhtml -o result $INFODIR/*.info
cp result/index.html result/result.html
cd ..

