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
		enc.Encode(arguments[1], arguments[2]);

	} else if (arguments[0] == "--decompress") {
		Decoder dec;
		dec.Decode(arguments[1]);
	}
}