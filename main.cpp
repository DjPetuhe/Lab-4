#include<iostream>
#include "Encoder.h"
#include "Decoder.h"

using namespace std;

int main (int argc, char* argv[])
{
	string arguments [argc - 1];

	for (int i = 1; i < argc; i++) {
		arguments[i - 1] = (string)argv[i];
	}
	
	if (arguments[0] == "--compress") {
		Encoder enc;
		enc.Encode(arguments[1], arguments[1]);
		if (argc == 5) {
			enc.Encode(arguments[2], arguments[2]);
			enc.combine (arguments[1], arguments[2], arguments[3]);
		}

	} else if (arguments[0] == "--decompress") {
		Decoder dec;
		string file1, file2;
		dec.decombine(arguments[1], &file1, &file2);
		dec.Decode(file1);
		dec.Decode(file2);
	}
}