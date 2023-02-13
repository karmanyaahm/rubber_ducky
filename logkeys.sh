set -x
logkeys -k
while true; 
do 
	while [ "$(cat /proc/bus/input/devices  | grep -A4 -E 'xiao.*board|trinkey' -i | tail -n 1 | cut -d ' ' -f5)" != "event5" ]; 
	do 
		echo waiting
		sleep 1
	done
	logkeys -s --no-daemon  --device=$(cat /proc/bus/input/devices  | grep -A4 'xiao.*board|trinkey' -i | tail -n 1 | cut -d ' ' -f5)
	sleep 1
done

