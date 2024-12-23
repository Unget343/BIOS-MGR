#!/bin/bash

sudo apt-get update
sudo apt-get install -y python3-tk

gcc -o launch_os launch_os.c

if [ -f "launch_os" ]; then
    echo "C script 'launch_os' successfully compiled."
else
    echo "Failed to compile the 'launch_os' C script."
    exit 1
fi

echo "Copying the GUI script 'gui.py' to the current directory..."
cp gui.py .

echo "Backing up the current bootloader..."
sudo cp /etc/default/grub /etc/default/grub.bkp
sudo cp /boot/grub/grub.cfg /boot/grub/grub.cfg.bkp

echo "Installing BIOS MGR as the bootloader..."
sudo dd if=./bios_mgr_bootloader_mbr.bin of=/dev/sda bs=512 seek=1

sudo update-grub

echo "BIOS MGR has been installed as the primary bootloader."

echo "Rebooting the system to apply changes..."
echo ""
