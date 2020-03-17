
# HW1
Run `make all` to compile
## Part 1
`./hw1-1 n a c g t k p outfile`

* *n* (**int**): sequence length
* *a c g t* (**int**): fraction of letters A, C, G, and T
* *k* (**int**): number of sequences
* *p* (**float** [0:1]): mutation probability
* *outfile* (**string**): output file


## Part 2
`./hw1-2 infile min max outfile`

* *infile* (**string**): input file
* *x* (**int**): minimum fragment length
* *y* (**int**): minimum fragment length (y ≥ x)
* *outfile* (**string**): output file

## Part 3
`./hw1-3 infile s r d outfile`

* *infile* (**string**): input file
* *s* (**int**): match score (>0)
* *r* (**int**): replace penalty (<0)
* *d* (**int**): insert/delete penalty (<0)
* *outfile* (**string**): output file
