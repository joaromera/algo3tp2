#!/bin/bash

# GENERATE ALL
# for i in `seq 31 50`; do
#     # mkdir -p "euclideos/todos/"$i
#     for j in `seq $(($i-1)) $((($i*($i-1))/2))`; do
#         echo "./euclidiangraphs " $i $j $(date +"%T")
#         ./euclidiangraphs $i $j $((i+j)) 2
#     done
# done

# GENERATE ONLY COMPLETE
# for i in `seq 31 50`; do
#     # mkdir -p "euclideos/completos/"
#     for j in `seq $((($i*($i-1))/2)) $((($i*($i-1))/2))`; do
#         echo "./euclidiangraphs " $i $j $(date +"%T")
#         ./euclidiangraphs $i $j $i
#     done
# done

# GENERATE ARBOLES
# for i in `seq 31 50`; do
#     # mkdir -p "euclideos/arboles/"
#     for j in `seq $((($i*($i-1))/2)) $((($i*($i-1))/2))`; do
#         echo "./euclidiangraphs " $i `expr $i - 1` $(date +"%T")
#         ./euclidiangraphs $i `expr $i - 1` $i
#     done
# done

# for i in grafos/completos/* ;
# do
#     if test -f $i && test ! -x $i ;
#     then
#         # echo $i D
#         # ./hiperauditados $i D 10
#         echo $i DPQ
#         ./hiperauditados $i DPQ 10
#         echo $i A
#         ./hiperauditados $i A 10
#         # echo $i BF
#         # ./hiperauditados $i BF
#         # echo $i FW
#         # ./hiperauditados $i FW
#         # echo $i DZ
#         # ./hiperauditados $i DZ
#     fi
# done

# # A* TREE
# # mkdir -p "resultados_euclidios/astar/arboles"
# for i in `seq 3 50`; do
#     for j in `seq $(($i-1)) $(($i-1))`; do 
#         # echo "./hiperauditados grafos/"$i"/"$i"v_"$j"e_2.txt DZ 50 "$(date +"%T")
#         ./astarvsdpq euclidios/arboles/"$i"v_"$j"e_euclid.txt A 50
#     done
# done
# ls resultados_euclidios/astar/arboles/* | sort | xargs cat >> resultados/astarvsdpqA.csv

# # DPQ TREE
# # mkdir -p "resultados_euclidios/dpq/arboles"
# for i in `seq 3 50`; do
#     for j in `seq $(($i-1)) $(($i-1))`; do 
#         # echo "./astar grafos/"$i"/"$i"v_"$j"e_2.txt DZ 50 "$(date +"%T")
#         ./astarvsdpq euclidios/arboles/"$i"v_"$j"e_euclid.txt DPQ 50
#     done
# done
# ls resultados_euclidios/dpq/arboles/* | sort | xargs cat >> resultados/astarvsdpqDPQ.csv

# # A* COMPLETE
# # mkdir -p "resultados_euclidios/astar/arboles"
# for i in `seq 3 30`; do
#     for j in `seq $((($i*($i-1))/2)) $((($i*($i-1))/2))`; do 
#         # echo "./hiperauditados grafos/"$i"/"$i"v_"$j"e_2.txt DZ 50 "$(date +"%T")
#         ./astarvsdpq euclidios/completos/"$i"v_"$j"e_euclid.txt A 50
#     done
# done
# ls resultados_euclidios/astar/completos/* | sort | xargs cat >> resultados/astarvsdpqAcomp.csv

# # DPQ COMPLETE
# # mkdir -p "resultados_euclidios/dpq/arboles"
# for i in `seq 3 30`; do
#     for j in `seq $((($i*($i-1))/2)) $((($i*($i-1))/2))`; do 
#         # echo "./astar grafos/"$i"/"$i"v_"$j"e_2.txt DZ 50 "$(date +"%T")
#         ./astarvsdpq euclidios/completos/"$i"v_"$j"e_euclid.txt DPQ 50
#     done
# done
# ls resultados_euclidios/dpq/completos/* | sort | xargs cat >> resultados/astarvsdpqDPQcomp.csv






# # A* COMPLETO
# # mkdir -p "resultados_euclidios/astar/arboles"
# for i in euclidios/completos/*; do
#     # for j in `seq $((($i*($i-1))/2)) $((($i*($i-1))/2))`; do 
#         # echo $i
#         # echo "./hiperauditados grafos/"$i"/"$i"v_"$j"e_2.txt DZ 50 "$(date +"%T")
#         ./astarvsdpq $i A 50
#     # done
# done
# ls resultados_euclidios/astar/completos/* | sort | xargs cat >> resultados/astarvsdpqAcomp.csv

# # DPQ COMPLETO
# # mkdir -p "resultados_euclidios/dpq/arboles"
# for i in euclidios/completos/*; do
#     # for j in `seq $((($i*($i-1))/2)) $((($i*($i-1))/2))`; do 
#         # echo "./astar grafos/"$i"/"$i"v_"$j"e_2.txt DZ 50 "$(date +"%T")
#         ./astarvsdpq $i DPQ 50
#         # ./astarvsdpq euclidios/completos/"$i"v_"$j"e_euclid.txt DPQ 50
#     # done
# done
# ls resultados_euclidios/dpq/completos/* | sort | xargs cat >> resultados/astarvsdpqDPQcomp.csv


# # A* ALL
# # mkdir -p "resultados_euclidios/astar/arboles"
# for i in euclidios/todos/*; do
#     # for j in `seq $((($i*($i-1))/2)) $((($i*($i-1))/2))`; do 
#         # echo $i
#         # echo "./hiperauditados grafos/"$i"/"$i"v_"$j"e_2.txt DZ 50 "$(date +"%T")
#         ./astarvsdpq $i A 50
#     # done
# done
# ls resultados_euclidios/astar/todos/* | sort | xargs cat >> resultados/astarvsdpqAall.csv

# # DPQ ALL
# # mkdir -p "resultados_euclidios/dpq/arboles"
# for i in euclidios/todos/*; do
#     # for j in `seq $((($i*($i-1))/2)) $((($i*($i-1))/2))`; do 
#         # echo "./astar grafos/"$i"/"$i"v_"$j"e_2.txt DZ 50 "$(date +"%T")
#         ./astarvsdpq $i DPQ 50
#         # ./astarvsdpq euclidios/todos/"$i"v_"$j"e_euclid.txt DPQ 50
#     # done
# done
# ls resultados_euclidios/dpq/todos/* | sort | xargs cat >> resultados/astarvsdpqDPQall.csv