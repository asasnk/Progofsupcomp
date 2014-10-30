#!/bin/bash
#@ job_type = MPICH
#@ class = fat
#@ node = 1
#@ total_tasks = 1
#@wall_clock_limit = 1:20:00
#@ job_name = A1
#@ input = job.in
#@ output = job$(jobid).out
#@ error = job$(jobid).err



#@ node_usage = not_shared
#@ island_count = 1
#@ initialdir = $(home)/SupMuc
#@ notification=always
#@ notify_user=shashank.nith@gmail.com
#@ queue
. /etc/profile
. /etc/profile.d/modules.sh
module unload mpi.ibm
module load mpi.intel

module load papi

## Flag -o1
cd ../o1
./gccg text ../data/cojack.dat run01
./gccg text ../data/cojack.dat run02
./gccg text ../data/cojack.dat run03
./gccg text ../data/cojack.dat run04
./gccg text ../data/cojack.dat run05
./gccg text ../data/tjunc.dat run06
./gccg text ../data/tjunc.dat run07
./gccg text ../data/tjunc.dat run08
./gccg text ../data/tjunc.dat run09
./gccg text ../data/tjunc.dat run10

## Flag -o3
cd ../o3
./gccg text ../data/cojack.dat run11
./gccg text ../data/cojack.dat run12
./gccg text ../data/cojack.dat run13
./gccg text ../data/cojack.dat run14
./gccg text ../data/cojack.dat run15
./gccg text ../data/tjunc.dat run16
./gccg text ../data/tjunc.dat run17
./gccg text ../data/tjunc.dat run18
./gccg text ../data/tjunc.dat run19
./gccg text ../data/tjunc.dat run20


## Flag -o1 for binary files
cd ../o1
./gccg bin ../data/cojack.bin run21
./gccg bin ../data/cojack.bin run22
./gccg bin ../data/cojack.bin run23
./gccg bin ../data/cojack.bin run24
./gccg bin ../data/cojack.bin run25
./gccg bin ../data/tjunc.bin run26
./gccg bin ../data/tjunc.bin run27
./gccg bin ../data/tjunc.bin run28
./gccg bin ../data/tjunc.bin run29
./gccg bin ../data/tjunc.bin run30

## Flag -o3 for binary files
cd ../o3
./gccg bin ../data/cojack.bin run31
./gccg bin ../data/cojack.bin run32
./gccg bin ../data/cojack.bin run33
./gccg bin ../data/cojack.bin run34
./gccg bin ../data/cojack.bin run35
./gccg bin ../data/tjunc.bin run36
./gccg bin ../data/tjunc.bin run37
./gccg bin ../data/tjunc.bin run38
./gccg bin ../data/tjunc.bin run39
./gccg bin ../data/tjunc.bin run40



module unload papi
