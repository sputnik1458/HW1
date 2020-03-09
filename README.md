# HW1
## Part 1
`g++ -o hw1-1 hw1-1.cpp`

`./hw1-1 n a c g t k p outfile`

* *n* (**int**): sequence length
* *a c g t* (**int**): fraction of letters A, C, G, and T
* *k* (**int**): number of sequences
* *p* (**float** [0:1]): mutation probability
* *outfile* (**string**): output file


## Part 2

`g++ .\hw1-2.cpp -o hw1-2`

`.\hw1-2 inputfile min max outfile`


Input:
1. string: input file name
2. integer: x = minimum fragment length
3. integer: y = maximum fragment length (y ≥ x)
4. string: output file name
