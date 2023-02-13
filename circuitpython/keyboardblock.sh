while true; do for i in `xinput | grep 'xiao.*\[slave' -i | grep -o 'id=..' | cut -d '=' -f2`; do xinput disable $i; xinput float $i; echo $i; done; sleep .1; done

