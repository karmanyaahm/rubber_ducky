set -xe

convert oreo3.png -resize 50% -quality 50 oreo3-1.png
pngquant oreo3-1.png -f
python polyglot.py oreo3-1-fs8.png 1oreo.png script.ps1

set +x
while ! $(df | grep -q CIRCUITPY); do echo waiting; sleep .2; done;

sleep 2
set -x

MTPATH="/run/media/karmanyaahm/CIRCUITPY"
cp code.py boot.py 1oreo.png $MTPATH/
sync $MTPATH $MTPATH/ $MTPATH/code.py $MTPATH/1oreo.png $MTPATH/boot.py
touch $MTPATH/1oreo.png
sleep 1 
umount $MTPATH
