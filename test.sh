#!/bin/bash

# On compile
make

# Tableau des input
declare -a inputs=(
    "2+2"
    "3+1"
    "3*2"
    "3e3+1.1"
    "3+"
    "(3+1)*4"
    "1/0"
    "(((3)))"
    "(3+1"
    "220*2.0000000000000000001"
    "2147483647+10"
    "3.4e40*100"
    "2.3.4"
    "ceci est un texte"
    "(3*1.1)+2+3+3+4+4+4+4"
    "2/3"
    "9999*9999*9999*9999*9999*9999*9999*9999*9999*9999*9999*9999*9999*9999*9999*9999*9999*9999*9999*9999*9999*9999*9999*9999*9999*9999*9999*9999*9999*9999*9999*9999*9999"
    "388....*bonjour"
    "😀*😥"
    "(((2+1)*+34"
    "635.1-1828"
)
# Tableau des output
declare -a outputs

# Boucle sur les input
for input in "${inputs[@]}"
do
    # input dans la calc, recupere output, supprime les ">"
    output=$(echo -e "$input\nq\n" | stdbuf -o0 ./calc | grep -v '^>$' | sed 's/> //g')
    # ajoute au tableau des output
    outputs+=(" $output")
done

# creation du fichier CSV
echo "Inputs,Outputs" > results.csv
for index in "${!inputs[@]}"
do
    echo "${inputs[index]},${outputs[index]}" >> results.csv
done

# info fin prgm
if [ $? -eq 0 ]; then
    echo "Program completed successfully"
else
    echo "Program encountered an error"
fi