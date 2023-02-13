import storage
#storage.disable_usb_drive()
storage.remount("/", False) # writeable by circuitpython, read-only to computer

