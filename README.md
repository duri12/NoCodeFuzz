# NoCodeFuzz

NoCodeFuzz is a powerful fuzzer tool based on the HonggFuzz project by Google. It utilizes side channels to fuzz unavailable code, making it ideal for black-box testing scenarios. This tool empowers security researchers and developers to discover vulnerabilities in software systems by exploring potential attack vectors through side channels.

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Installation](#installation)
- [Requirements](#requirements)
- [Usage](#usage)

## Introduction

NoCodeFuzz is designed to facilitate black-box testing by using side channels for fuzzing. It extends the capabilities of HonggFuzz to explore inaccessible code, enabling the discovery of vulnerabilities that might otherwise remain undetected. By leveraging side channels, NoCodeFuzz offers a unique approach to fuzzing that can uncover critical security issues in software systems.

## Features

- Utilizes side channels for fuzzing unavailable code
- Enables black-box testing scenarios
- Identifies vulnerabilities through exploration of potential attack vectors
- Extends the capabilities of the HonggFuzz project

## Installation

To use NoCodeFuzz, follow these simple steps:

1. **Clone the Repository:**
   ```bash
   git clone https://github.com/duri12/NoCodeFuzz.git
   ```
   
2. **run this bash script**
   ```bash
   sudo apt-get install binutils-dev libunwind-dev libblocksruntime-dev clang
   cd honggfuzz
   make
   cd ..
   ```
   
## Requirements

   * **Linux** - The BFD library (libbfd-dev) and libunwind (libunwind-dev/libunwind8-dev), clang-5.0 or higher 

## Usage
   Ensure you meet the requirements and have installed the necessary dependencies. Then, follow these steps to use NoCodeFuzz:
1. *Prepare Target Application:*
   Replace some_runable_code with the path to your target executable.
   for now some_runable_code should just be any executable and change the target is subproc.c file 
2. *Run NoCodeFuzz:*
   ```bash
   taskset -c 1 honggfuzz/honggfuzz --linux_perf_instr -i Inputs/ -o outputs/ -s  -n 1  -l log.txt -- some_runable_code
   ```
3. *Background Execution:*
   To run NoCodeFuzz in the background, use the following command:
   ```bash
   nohup taskset -c 1 honggfuzz/honggfuzz --linux_perf_instr -i Inputs/ -o outputs/ -s  -n 1  -l log.txt -- toRun &
   ```
