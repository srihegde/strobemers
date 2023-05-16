#!/bin/bash


genome1=$1
genome2=$2

IFS=$'\n'       # make newlines the only separator
# set -f          # disable globbing
TIME_FORMAT="%E real\n%M maxresident"

#######################################################
#######################################################
########## INFORMATION ABOUT THE SCRIPT ###############
#######################################################
#######################################################

# RUN scripts e.g. as:   ./genome_mappings_eval.sh <genome1> <genome2>

# The mummerplot lines can be activated for plotting dotplots 

# WARNING: The genome_mapping_metrics.py script should not be used 
# for large outfiles (e.g., files with more than 10M-20M matches as
# it uses too much memory and becomes slow. 

#######################################################
# Randstrobe alignment evaluations
#######################################################
# /usr/bin/time -f $TIME_FORMAT ./randstrobe_benchmark -n 2 -k 15 -v 1 -w 100 -o tmp.tsv -x 3 -l 1 $genome1 $genome2 2> runtime.txt 1> stdout.txt
# echo -n "StrobeMap  & (2, 15, 1, 100) & " 
# python genome_mapping_metrics.py tmp.tsv runtime.txt --refs $genome2 --collinear_matches_out coll_sol.tsv


#######################################################
# Randstrobe variants
#######################################################
# 1: method1 (sahlin modulo), 
/usr/bin/time -f $TIME_FORMAT ./randstrobe_benchmark -n 2 -k 30 -v 31 -w 100 -o tmp.tsv -x 3 -l 1 $genome1 $genome2 2> runtime.txt  1> stdout.txt
echo -n "StrobeMap & (2, 30, 31, 100) & sahlin modulo & " 
python genome_mapping_metrics.py tmp.tsv runtime.txt --refs $genome2

# 2: method2 (shen bitwise AND), 
/usr/bin/time -f $TIME_FORMAT ./randstrobe_benchmark -n 2 -k 30 -v 31 -w 100 -o tmp.tsv -x 3 -l 2 $genome1 $genome2 2> runtime.txt  1> stdout.txt
echo -n "StrobeMap & (2, 30, 31, 100) & shen bitwise AND & "
python genome_mapping_metrics.py tmp.tsv runtime.txt --refs $genome2

# 3: method3 (guo_pibri XOR), 
/usr/bin/time -f $TIME_FORMAT ./randstrobe_benchmark -n 2 -k 30 -v 31 -w 100 -o tmp.tsv -x 3 -l 3 $genome1 $genome2 2> runtime.txt  1> stdout.txt
echo -n "StrobeMap & (2, 30, 31, 100) & guo_pibri XOR & "
python genome_mapping_metrics.py tmp.tsv runtime.txt --refs $genome2

# 4: method4 (sahlin bitcount XOR), 
/usr/bin/time -f $TIME_FORMAT ./randstrobe_benchmark -n 2 -k 30 -v 31 -w 100 -o tmp.tsv -x 3 -l 4 $genome1 $genome2 2> runtime.txt  1> stdout.txt
echo -n "StrobeMap & (2, 30, 31, 100) & sahlin bitcount XOR & "
python genome_mapping_metrics.py tmp.tsv runtime.txt --refs $genome2

# 5: method5 (Liu-Patro-Li, concatenation), 
/usr/bin/time -f $TIME_FORMAT ./randstrobe_benchmark -n 2 -k 30 -v 31 -w 100 -o tmp.tsv -x 3 -l 5 $genome1 $genome2 2> runtime.txt  1> stdout.txt
echo -n "StrobeMap & (2, 30, 31, 100) & Liu-Patro-Li, concatenation & "
python genome_mapping_metrics.py tmp.tsv runtime.txt --refs $genome2

# 6: method6 (Liu-Patro-Li, concatenation using wyhash for linking).
/usr/bin/time -f $TIME_FORMAT ./randstrobe_benchmark -n 2 -k 30 -v 31 -w 100 -o tmp.tsv -x 3 -l 6 $genome1 $genome2 2> runtime.txt  1> stdout.txt
echo -n "StrobeMap & (2, 30, 31, 100) & Liu-Patro-Li, concatenation using wyhash for linking & "
python genome_mapping_metrics.py tmp.tsv runtime.txt --refs $genome2

# 7: method7 (Spectral Minimizer_1).
/usr/bin/time -f $TIME_FORMAT ./randstrobe_benchmark -n 2 -k 30 -v 31 -w 100 -o tmp.tsv -x 3 -l 7 $genome1 $genome2 2> runtime.txt  1> stdout.txt
echo -n "StrobeMap & (2, 30, 31, 100) & Spectral Minimizer_1 & "
python genome_mapping_metrics.py tmp.tsv runtime.txt --refs $genome2

# # 7: method7 (Spectral Minimizer_2).
# /usr/bin/time -f $TIME_FORMAT ./randstrobe_benchmark -n 2 -k 30 -v 31 -w 100 -o tmp.tsv -x 3 -l 8 $genome1 $genome2 2> runtime.txt  1> stdout.txt
# echo -n "StrobeMap & (2, 30, 31, 100) & Spectral Minimizer_2 & "
# python genome_mapping_metrics.py tmp.tsv runtime.txt --refs $genome2

# # 9: method7 (Spectral Stabilizer).
# /usr/bin/time -f $TIME_FORMAT ./randstrobe_benchmark -n 2 -k 30 -v 31 -w 100 -o tmp.tsv -x 3 -l 9 $genome1 $genome2 2> runtime.txt  1> stdout.txt
# echo -n "StrobeMap & (2, 30, 31, 100) & Spectral Stabilizer & "
# python genome_mapping_metrics.py tmp.tsv runtime.txt --refs $genome2

#######################################################
#######################################################
#######################################################