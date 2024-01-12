#!/bin/bash

# Function to check if a command succeeded
check_command() {
    if [ $? -ne 0 ]; then
        echo "Error: $1 failed."
        exit 1
    fi
}

# Check if a command argument is provided
if [ $# -eq 0 ]; then
    echo "Usage: $0 <command_to_run>"
    exit 1
fi

command_to_run="$1"

# 1. Disable DVFS (Dynamic Voltage and Frequency Scaling)
echo "Disabling DVFS..."
echo "performance" | sudo tee /sys/devices/system/cpu/cpu*/cpufreq/scaling_governor
check_command "Disabling DVFS"
echo core > /proc/sys/kernel/core_patter

# 2. Add kernel parameters to /etc/default/grub
echo "Adding kernel parameters to /etc/default/grub..."
sudo sed -i 's/GRUB_CMDLINE_LINUX="[^"]*/& nosmt isolcpus=1 nokaslr/' /etc/default/grub
check_command "Adding kernel parameters"

# Update grub to apply the changes
sudo update-grub
check_command "Updating grub"

# 3. Set the workload on isolated CPUs with taskset
echo "Setting workload on isolated CPUs..."
# Replace '1' with the CPU core you want to isolate.
taskset -c 1 $command_to_run
check_command "Setting workload on isolated CPUs"

echo "DVFS disabled, kernel parameters added, and workload set on isolated CPUs."

# Verification - You can add checks here to verify the changes

# Check if DVFS is disabled
if [ "$(cat /sys/devices/system/cpu/cpu*/cpufreq/scaling_governor | grep -c 'performance')" -eq 0 ]; then
    echo "Error: DVFS is not disabled."
    exit 1
fi

# Check if kernel parameters are set in /etc/default/grub
if ! grep -q "nosmt isolcpus=1 nokaslr" /etc/default/grub; then
    echo "Error: Kernel parameters not set in /etc/default/grub."
    exit 1
fi

echo "Script completed successfully."

# End of the script

