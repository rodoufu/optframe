#!/usr/bin/env bash

instance=0
#for size in 10 25 50 100 250 500 1000 1100 1250 1500 2000 5000 10000
for size in 100000 200000 300000 400000 500000 600000 700000 800000 900000 1000000
do
    for i in {0..0}
    do
        if [[ "$instance" -lt 10 ]]; then p_instance="0${instance}"; else p_instance="${instance}"; fi
        echo "python3 generate_input.py ${size} 1 101010 ${instance} > ${p_instance}""_npp_${size}.in"
        python3 generate_input.py ${size} 1 101010 ${instance} > ${p_instance}_npp_${size}.in
        instance=$((instance + 1))
    done
done
