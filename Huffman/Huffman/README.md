Huffman
=======

Encoder and Decoder run from the command line

uses huffman encoding to compress a file.  This example is compressed to 60%.  The compressed file uses the extension .mcf (my compressed file).  The decompressed file is prefixed with "out_" for the purposes of testing, as it leaves the original intact.

-o decode decoder.cpp
-o encode encoder.cpp
./encode USConstitution.txt
./decode 
