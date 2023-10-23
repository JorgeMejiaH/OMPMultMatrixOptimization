echo "Thread test in progress..."
echo "Size;Threads;Time" > MultMatrixOMP.csv

for i in {1..10}; do
    echo "Running iteration $i"
    for t in 2 4 8 16 32; do
        for j in 32 64 128 256 512 1024 2048; do
            result=$(./MultMatrixOMP $j $t)
            echo "$j;$t;$result" >> MultMatrixOMP.csv
        done
    done
done

echo "" >> 'MultMatrixOMP.csv'
echo "done"