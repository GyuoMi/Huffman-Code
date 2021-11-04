# Huffman-Code
An encoder and decoder that works with double digit frequencies\
These two files can be run as a pipe in the terminal, so the output from the encoder will be used as the input for the decoder.\
The decoder accepts 3 lines total: 2 lines to build a binary tree and 1 line for the Huffman Encoded string.

Input for the decoder is as follows:
```
  T a b c d e f g h i j k l m n o p q r s t u v w x y z
8 1 1 1 1 1 3 1 1 2 1 1 1 1 1 1 4 1 1 2 1 1 2 1 1 1 1 1
01110101111010110001000001010111011010100111010110000001001110101111101100110110011101111001000000100111111111001011101001110011010000011011100010111101011000110011111111011111001100110010001010
```

Output: 
```
The quick brown fox jumps over the lazy dog
```
