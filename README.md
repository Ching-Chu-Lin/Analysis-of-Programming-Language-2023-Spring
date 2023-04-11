# README

### Week 1
compile and run my program

``` shell
$ cd week1
$ g++ main.cpp -o main.out
$ ./main.out [input_text_file]
``` 

I store all stop words in memory with hash set, read the input text line by line, and count all non stop words frequencies (ignoring words with size less than 2).