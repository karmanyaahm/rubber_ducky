WRITABLE = not True
import storage
#storage.disable_usb_drive()
storage.remount("/", False ^ WRITABLE) # writeable by circuitpython, read-only to computer
import usb_midi

usb_midi.disable()
import usb_cdc
usb_cdc.disable()

