# README
compile and run my program

### 04-monolith

``` shell
$ g++ Four.cpp -o main.out
$ ./main.out [input_text_file]
``` 

Note that I use the same library call as in the example code. Library functions include isalnum() and lower(). I don't sort the word freq table but bubble up if needed when I add one to the frequency, so does the example code. In the example code, there is one line `stop_words.extend(list(string.ascii_lowercase))`. I don't extend the stop word list like this. Instead I ignore all words whose length is one when parsing the input text file(to ignore the cases such as man's parsing `man` and `s`).