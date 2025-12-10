#!/bin/bash

echo "Available input devices:"
xinput list
echo

# no need for tablet
# read -rp "Enter the device ID for your tablet: " tablet_id
read -rp "Enter the device ID for your pen: " pen_id

echo
echo "Available screens:"
xrandr | grep " connected"
echo

read -rp "Enter the screen output to map the tablet to: " monitor_out

# no need for tablet
# xinput map-to-output "$tablet_id" "$monitor_out"
xinput map-to-output "$pen_id" "$monitor_out"

echo "Tablet and pen mapped to $monitor_out"

