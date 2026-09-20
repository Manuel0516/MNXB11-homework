#!/bin/sh

#SBATCH -J "MNXB11 Calculate Pi homework"
#SBATCH --time=00:08:00
#SBATCH -A hep2023-1-6
#SBATCH --mem 26G

# Launch the calculatePI.sh application script using the container script
run_in_container_calculatePI.sh
