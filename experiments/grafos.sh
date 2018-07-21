#!/bin/bash

# GENERATE ALL
# for i in `seq 3 16`; do
    # mkdir -p "grafos/"$i
    # for j in `seq $(($i-1)) $((($i*($i-1))/2))`; do
        # echo "./generator " $i $j $(date +"%T") " hiperauditados"
        # ./generator $i $j $((i+j)) 2
    # done
# done

# GENERATE TREE
# for i in `seq 3 60`; do
    # mkdir -p "grafos/"$i
    # for j in `seq $(($i-1)) $(($i-1))`; do
        # echo "./generator " $i $j $(date +"%T") " hiperauditados"
        # ./generator $i $j $((i+j)) 2
    # done
# done

# GENERATE ONLY COMPLETE
# for i in `seq 3 60`; do
    # mkdir -p "grafos/"$i
    # for j in `seq $((($i*($i-1))/2)) $((($i*($i-1))/2))`; do
        # echo "./generator " $i $j $(date +"%T") " hiperauditados"
        # ./generator $i $j $((i+j)) 2
    # done
# done

# GENERATE EUCLIDEAN
# for i in `seq 3 80`; do
    # mkdir -p "grafos/"$i
    # for j in `seq $(($i-1)) $((($i*($i-1))/2))`; do
        # echo "./euclideangraphs " $i $j $(date +"%T")
        # ./euclideangraphs $i $j $((i+j))
    # done
# done

# PRIM
# mkdir -p "resultados/prim"
# for i in `seq 3 35`; do
    # for j in `seq $(($i-1)) $((($i*($i-1))/2))`; do 
        # echo "./hiperconectados grafos/"$i"/"$i"v_"$j"e.txt P 50 "$(date +"%T")
        # ./hiperconectados grafos/"$i"/"$i"v_"$j"e.txt P 50
    # done
# done
# ls resultados/prim/*.* | sort | xargs cat >> resultados/prim.csv

# KRUSKAL
# mkdir -p "resultados/kruskal"
# for i in `seq 3 35`; do
    # for j in `seq $(($i-1)) $((($i*($i-1))/2))`; do
        # echo "./hiperconectados grafos/"$i"/"$i"v_"$j"e.txt K 50 "$(date +"%T")
        # ./hiperconectados grafos/"$i"/"$i"v_"$j"e.txt K 50
    # done
# done
# ls resultados/kruskal/*.* | sort | xargs cat >> resultados/kruskal.csv

# KRUSKALPC
# mkdir -p "resultados/kruskalpc"
# for i in `seq 3 35`; do
    # for j in `seq $(($i-1)) $((($i*($i-1))/2))`; do
        # echo "./hiperconectados grafos/"$i"/"$i"v_"$j"e.txt KPC 50 "$(date +"%T")
        # ./hiperconectados grafos/"$i"/"$i"v_"$j"e.txt KPC 50
    # done
# done
# ls resultados/kruskalpc/*.* | sort | xargs cat >> resultados/kruskalpc.csv

# PRIM COMPLETOS
# mkdir -p "resultados/prim"
# for i in `seq 3 60`; do
    # for j in `seq $((($i*($i-1))/2)) $((($i*($i-1))/2))`; do
        # echo "./hiperconectados grafos/"$i"/"$i"v_"$j"e.txt P 50 "$(date +"%T")
        # ./hiperconectados grafos/"$i"/"$i"v_"$j"e.txt P 50
    # done
# done
# ls resultados/prim/*.* | sort | xargs cat >> resultados/primcompleto.csv

# KRUSKAL COMPLETOS
# mkdir -p "resultados/kruskal"
# for i in `seq 3 60`; do
    # for j in `seq $((($i*($i-1))/2)) $((($i*($i-1))/2))`; do
        # echo "./hiperconectados grafos/"$i"/"$i"v_"$j"e.txt K 50 "$(date +"%T")
        # ./hiperconectados grafos/"$i"/"$i"v_"$j"e.txt K 50
    # done
# done
# ls resultados/kruskal/*.* | sort | xargs cat >> resultados/kruskalcompleto.csv

# KRUSKALPC COMPLETOS
# mkdir -p "resultados/kruskalpc"
# for i in `seq 3 60`; do
    # for j in `seq $((($i*($i-1))/2)) $((($i*($i-1))/2))`; do
        # echo "./hiperconectados grafos/"$i"/"$i"v_"$j"e.txt KPC 50 "$(date +"%T")
        # ./hiperconectados grafos/"$i"/"$i"v_"$j"e.txt KPC 50
    # done
# done
# ls resultados/kruskalpc/*.* | sort | xargs cat >> resultados/kruskalpccompleto.csv

# PRIM TREE
# mkdir -p "resultados/prim"
# for i in `seq 3 90`; do
    # echo "./hiperconectados grafos/"$i"/"$i"v_"$(($i-1))"e.txt P 100 "$(date +"%T")
    # ./hiperconectados grafos/"$i"/"$i"v_"$(($i-1))"e.txt P 100
# done
# ls resultados/prim/*.* | sort | xargs cat >> resultados/primsimple.csv

# KRUSKAL TREE
# mkdir -p "resultados/kruskal"
# for i in `seq 3 90`; do
    # echo "./hiperconectados grafos/"$i"/"$i"v_"$(($i-1))"e.txt K 100 "$(date +"%T")
    # ./hiperconectados grafos/"$i"/"$i"v_"$(($i-1))"e.txt K 100
# done
# ls resultados/kruskal/*.* | sort | xargs cat >> resultados/kruskalsimple.csv

# KRUSKALPC TREE
# mkdir -p "resultados/kruskalpc"
# for i in `seq 3 90`; do
    # echo "./hiperconectados grafos/"$i"/"$i"v_"$(($i-1))"e.txt KPC 100 "$(date +"%T")
    # ./hiperconectados grafos/"$i"/"$i"v_"$(($i-1))"e.txt KPC 100
# done
# ls resultados/kruskalpc/*.* | sort | xargs cat >> resultados/kruskalpcsimple.csv

# DIJKSTRA
# mkdir -p "resultados/dijkstra"
# for i in `seq 3 16`; do
    # for j in `seq $(($i-1)) $((($i*($i-1))/2))`; do 
        # echo "./hiperauditados grafos/"$i"/"$i"v_"$j"e_2.txt D 50 "$(date +"%T")
        # ./hiperauditados grafos/"$i"/"$i"v_"$j"e_2.txt D 50
    # done
# done
# ls resultados/dijkstra/*.* | sort | xargs cat >> resultados/dijkstra.csv

# DIJKSTRAPQ
# mkdir -p "resultados/dijkstrapq"
# for i in `seq 3 16`; do
    # for j in `seq $(($i-1)) $((($i*($i-1))/2))`; do 
        # echo "./hiperauditados grafos/"$i"/"$i"v_"$j"e_2.txt DPQ 50 "$(date +"%T")
        # ./hiperauditados grafos/"$i"/"$i"v_"$j"e_2.txt DPQ 50
    # done
# done
# ls resultados/dijkstrapq/*.* | sort | xargs cat >> resultados/dijkstrapq.csv

# ASTAR
# mkdir -p "resultados/astar"
# for i in `seq 3 16`; do
    # for j in `seq $(($i-1)) $((($i*($i-1))/2))`; do 
        # echo "./hiperauditados grafos/"$i"/"$i"v_"$j"e_2.txt A 50 "$(date +"%T")
        # ./hiperauditados grafos/"$i"/"$i"v_"$j"e_2.txt A 50
    # done
# done
# ls resultados/astar/*.* | sort | xargs cat >> resultados/astar.csv

# BELLMANFORD
# mkdir -p "resultados/bellmanford"
# for i in `seq 3 16`; do
    # for j in `seq $(($i-1)) $((($i*($i-1))/2))`; do 
        # echo "./hiperauditados grafos/"$i"/"$i"v_"$j"e_2.txt BF 50 "$(date +"%T")
        # ./hiperauditados grafos/"$i"/"$i"v_"$j"e_2.txt BF 50
    # done
# done
# ls resultados/bellmanford/*.* | sort | xargs cat >> resultados/bellmanford.csv

# FLOYDWARSHALL
# mkdir -p "resultados/floydwarshall"
# for i in `seq 3 16`; do
    # for j in `seq $(($i-1)) $((($i*($i-1))/2))`; do 
        # echo "./hiperauditados grafos/"$i"/"$i"v_"$j"e_2.txt FW 50 "$(date +"%T")
        # ./hiperauditados grafos/"$i"/"$i"v_"$j"e_2.txt FW 50
    # done
# done
# ls resultados/floydwarshall/*.* | sort | xargs cat >> resultados/floydwarshall.csv

# DANTZIG
# mkdir -p "resultados/dantzig"
# for i in `seq 3 16`; do
    # for j in `seq $(($i-1)) $((($i*($i-1))/2))`; do 
        # echo "./hiperauditados grafos/"$i"/"$i"v_"$j"e_2.txt DZ 50 "$(date +"%T")
        # ./hiperauditados grafos/"$i"/"$i"v_"$j"e_2.txt DZ 50
    # done
# done
# ls resultados/dantzig/*.* | sort | xargs cat >> resultados/dantzig.csv

# DIJKSTRA TREE
# mkdir -p "resultados/dijkstra"
# for i in `seq 3 60`; do
    # for j in `seq $(($i-1)) $(($i-1))`; do 
        # echo "./hiperauditados grafos/"$i"/"$i"v_"$j"e_2.txt D 15 "$(date +"%T")
        # ./hiperauditados grafos/"$i"/"$i"v_"$j"e_2.txt D 15
    # done
# done
# ls resultados/dijkstra/*.* | sort | xargs cat >> resultados/dijkstratree.csv

# DIJKSTRAPQ TREE
# mkdir -p "resultados/dijkstrapq"
# for i in `seq 3 60`; do
    # for j in `seq $(($i-1)) $(($i-1))`; do 
        # echo "./hiperauditados grafos/"$i"/"$i"v_"$j"e_2.txt DPQ 15 "$(date +"%T")
        # ./hiperauditados grafos/"$i"/"$i"v_"$j"e_2.txt DPQ 15
    # done
# done
# ls resultados/dijkstrapq/*.* | sort | xargs cat >> resultados/dijkstrapqtree.csv

# ASTAR TREE
# mkdir -p "resultados/astar"
# for i in `seq 3 60`; do
    # for j in `seq $(($i-1)) $(($i-1))`; do 
        # echo "./hiperauditados grafos/"$i"/"$i"v_"$j"e_2.txt A 15 "$(date +"%T")
        # ./hiperauditados grafos/"$i"/"$i"v_"$j"e_2.txt A 15
    # done
# done
# ls resultados/astar/*.* | sort | xargs cat >> resultados/astartree.csv

# BELLMANFORD TREE
# mkdir -p "resultados/bellmanford"
# for i in `seq 3 60`; do
    # for j in `seq $(($i-1)) $(($i-1))`; do 
        # echo "./hiperauditados grafos/"$i"/"$i"v_"$j"e_2.txt BF 15 "$(date +"%T")
        # ./hiperauditados grafos/"$i"/"$i"v_"$j"e_2.txt BF 15
    # done
# done
# ls resultados/bellmanford/*.* | sort | xargs cat >> resultados/bellmanfordtree.csv

# FLOYDWARSHALL TREE
# mkdir -p "resultados/floydwarshall"
# for i in `seq 3 60`; do
    # for j in `seq $(($i-1)) $(($i-1))`; do 
        # echo "./hiperauditados grafos/"$i"/"$i"v_"$j"e_2.txt FW 15 "$(date +"%T")
        # ./hiperauditados grafos/"$i"/"$i"v_"$j"e_2.txt FW 15
    # done
# done
# ls resultados/floydwarshall/*.* | sort | xargs cat >> resultados/floydwarshalltree.csv

# DANTZIG TREE
# mkdir -p "resultados/dantzig"
# for i in `seq 3 60`; do
    # for j in `seq $(($i-1)) $(($i-1))`; do 
        # echo "./hiperauditados grafos/"$i"/"$i"v_"$j"e_2.txt DZ 15 "$(date +"%T")
        # ./hiperauditados grafos/"$i"/"$i"v_"$j"e_2.txt DZ 15
    # done
# done
# ls resultados/dantzig/*.* | sort | xargs cat >> resultados/dantzigtree.csv

# DIJKSTRA COMPLETE
# mkdir -p "resultados/dijkstra"
# for i in `seq 3 40`; do
    # for j in `seq $((($i*($i-1))/2)) $((($i*($i-1))/2))`; do 
        # echo "./hiperauditados grafos/"$i"/"$i"v_"$j"e_2.txt D 50 "$(date +"%T")
        # ./hiperauditados grafos/"$i"/"$i"v_"$j"e_2.txt D 50
    # done
# done
# ls resultados/dijkstra/*.* | sort | xargs cat >> resultados/dijkstracomplete.csv

# DIJKSTRAPQ COMPLETE
# mkdir -p "resultados/dijkstrapq"
# for i in `seq 3 40`; do
    # for j in `seq $((($i*($i-1))/2)) $((($i*($i-1))/2))`; do 
        # echo "./hiperauditados grafos/"$i"/"$i"v_"$j"e_2.txt DPQ 50 "$(date +"%T")
        # ./hiperauditados grafos/"$i"/"$i"v_"$j"e_2.txt DPQ 50
    # done
# done
# ls resultados/dijkstrapq/*.* | sort | xargs cat >> resultados/dijkstrapqcomplete.csv

# ASTAR COMPLETE
# mkdir -p "resultados/astar"
# for i in `seq 3 40`; do
    # for j in `seq $((($i*($i-1))/2)) $((($i*($i-1))/2))`; do 
        # echo "./hiperauditados grafos/"$i"/"$i"v_"$j"e_2.txt A 50 "$(date +"%T")
        # ./hiperauditados grafos/"$i"/"$i"v_"$j"e_2.txt A 50
    # done
# done
# ls resultados/astar/*.* | sort | xargs cat >> resultados/astarcomplete.csv

# BELLMANFORD COMPLETE
# mkdir -p "resultados/bellmanford"
# for i in `seq 3 40`; do
    # for j in `seq $((($i*($i-1))/2)) $((($i*($i-1))/2))`; do 
        # echo "./hiperauditados grafos/"$i"/"$i"v_"$j"e_2.txt BF 50 "$(date +"%T")
        # ./hiperauditados grafos/"$i"/"$i"v_"$j"e_2.txt BF 50
    # done
# done
# ls resultados/bellmanford/*.* | sort | xargs cat >> resultados/bellmanfordcomplete.csv

# FLOYDWARSHALL COMPLETE
# mkdir -p "resultados/floydwarshall"
# for i in `seq 3 40`; do
    # for j in `seq $((($i*($i-1))/2)) $((($i*($i-1))/2))`; do 
        # echo "./hiperauditados grafos/"$i"/"$i"v_"$j"e_2.txt FW 50 "$(date +"%T")
        # ./hiperauditados grafos/"$i"/"$i"v_"$j"e_2.txt FW 50
    # done
# done
# ls resultados/floydwarshall/*.* | sort | xargs cat >> resultados/floydwarshallcomplete.csv

# DANTZIG COMPLETE
# mkdir -p "resultados/dantzig"
# for i in `seq 3 40`; do
    # for j in `seq $((($i*($i-1))/2)) $((($i*($i-1))/2))`; do 
        # echo "./hiperauditados grafos/"$i"/"$i"v_"$j"e_2.txt DZ 50 "$(date +"%T")
        # ./hiperauditados grafos/"$i"/"$i"v_"$j"e_2.txt DZ 50
    # done
# done
# ls resultados/dantzig/*.* | sort | xargs cat >> resultados/dantzigcomplete.csv

# A* VS DPQ TREE
# mkdir -p "resultados/astar"
# for i in `seq 3 80`; do
    # for j in `seq $(($i-1)) $(($i-1))`; do 
        # echo "./astarvsdpq grafos/"$i"/"$i"v_"$j"e_e.txt A 50 "$(date +"%T")
        # ./astarvsdpq grafos/"$i"/"$i"v_"$j"e_e.txt A 50
    # done
# done
# ls resultados/astar/*.* | sort | xargs cat >> resultados/vs_astar_tree.csv

# A* VS DPQ TREE
# mkdir -p "resultados/dijkstrapq"
# for i in `seq 3 80`; do
    # for j in `seq $(($i-1)) $(($i-1))`; do 
        # echo "./astarvsdpq grafos/"$i"/"$i"v_"$j"e_e.txt DPQ 50 "$(date +"%T")
        # ./astarvsdpq grafos/"$i"/"$i"v_"$j"e_e.txt DPQ 50
    # done
# done
# ls resultados/dijkstrapq/*.* | sort | xargs cat >> resultados/vs_dijsktrapq_tree.csv

# A* VS DPQ COMPLETE
# mkdir -p "resultados/astar"
# for i in `seq 3 80`; do
    # for j in `seq $((($i*($i-1))/2)) $((($i*($i-1))/2))`; do 
        # echo "./astarvsdpq grafos/"$i"/"$i"v_"$j"e_e.txt A 50 "$(date +"%T")
        # ./astarvsdpq grafos/"$i"/"$i"v_"$j"e_e.txt A 50
    # done
# done
# ls resultados/astar/*.* | sort | xargs cat >> resultados/vs_astar_complete.csv

# A* VS DPQ COMPLETE
# mkdir -p "resultados/dijkstrapq"
# for i in `seq 3 80`; do
    # for j in `seq $((($i*($i-1))/2)) $((($i*($i-1))/2))`; do 
        # echo "./astarvsdpq grafos/"$i"/"$i"v_"$j"e_e.txt DPQ 50 "$(date +"%T")
        # ./astarvsdpq grafos/"$i"/"$i"v_"$j"e_e.txt DPQ 50
    # done
# done
# ls resultados/dijkstrapq/*.* | sort | xargs cat >> resultados/vs_dijsktrapq_complete.csv

# A* VS DPQ ALL
# mkdir -p "resultados/astar"
# for i in `seq 3 80`; do
    # for j in `seq $(($i-1)) $((($i*($i-1))/2))`; do 
        # echo "./astarvsdpq grafos/"$i"/"$i"v_"$j"e_e.txt A 50 "$(date +"%T")
        # ./astarvsdpq grafos/"$i"/"$i"v_"$j"e_e.txt A 50
    # done
# done
# find resultados/astar/ -type f -name '*.csv' | sort | xargs cat >> resultados/vs_astar.csv

# A* VS DPQ ALL
# mkdir -p "resultados/dijkstrapq"
# for i in `seq 3 80`; do
    # for j in `seq $(($i-1)) $((($i*($i-1))/2))`; do 
        # echo "./astarvsdpq grafos/"$i"/"$i"v_"$j"e_e.txt DPQ 50 "$(date +"%T")
        # ./astarvsdpq grafos/"$i"/"$i"v_"$j"e_e.txt DPQ 50
    # done
# done
# find resultados/dijkstrapq/ -type f -name '*.csv' | sort | xargs cat >> resultados/vs_dijsktrapq.csv
