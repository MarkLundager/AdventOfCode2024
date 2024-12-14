#!/bin/bash
for DAY in "$@"; do
    cd ./day${DAY} || exit
    echo -e "---------Day ${DAY}----------"
    ./day${DAY}
    echo -e "------------------------\n"
    cd .. || exit
done