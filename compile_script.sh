#!/bin/bash
md5file="/tmp/md5file"
tmpfile="/tmp/tmpfile"
if [ $# == 0 ]
then
    echo "ФАЕЛ УКАЖИ МУДЛО"
    exit 1

touch $md5file
md5prev=$(cat "$md5file")
md5sum "$1" >$md5file
md5now=$(cat "$md5file")

if ! [ -f a.out ] || ! [[ $md5prev == $md5now ]]
then
    echo "Compiling..."
    if ! g++ -fsanitize=undefined -fsanitize=address -std=c++11 -Wshadow -Wformat=2 -Wfloat-equal -Wconversion -Wlogical-op -Wcast-qual -Wcast-align -DHOMIE -Wall -Wextra -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC $1
    then
        echo "Compilation Error"
        rm $md5file
        exit 1
    fi
else
    echo "Not changed"
fi

if [[ $2 == "-f" ]]
then
    touch $tmpfile
    setterm -foreground green
    cat $tmpfile
else
    setterm -foreground red
    echo "Waiting for input..."
    setterm -foreground green
    cat <&0 >$tmpfile
fi

./a.out <$tmpfile
setterm -foreground white
echo ''
echo '-------------------'
echo 'Done'
exit 0
