#include"FileWriter.h"

void FileWriter::Write_encoded_file (int *numbers, int table_size, int num_size, string file_name) {
    int byte_size, bits_number, byte_number;
    char byte_size_char;

    ofstream file;
    file.open(file_name, ios::binary);

    if (log2(table_size) > (float)(int)log2(table_size)){
        byte_size = (int)log2(table_size) + 1;
    }
    else {
        byte_size = (int)log2(table_size);
    }

    byte_size_char = (char)byte_size;

    file.write(&byte_size_char, 1);
    file.write((char*)&(num_size), sizeof(int));

    bits_number = byte_size * num_size;
    
    if (bits_number % 8 != 0){
        byte_number = bits_number / 8 + 1;
    }
    else {
        byte_number = bits_number / 8;
    }

    char *byte = new char[byte_number];

    for (int i = 0; i < byte_number; i++) {
        byte[i] = 0;
    }

    int bit_int = byte_size - 1;
    int bit_char = 7;
    int int_number = 0;
    int char_number = 0;
    int res;

    for (int i = 0; i < bits_number; i++) {
        res = (numbers[int_number] & (1 << bit_int)) >> bit_int;
        byte[char_number] = byte[char_number] | (res << bit_char);


        if (bit_int == 0) {
            bit_int = byte_size - 1;
            int_number++;
        } else {
            bit_int--;
        }

        if (bit_char == 0) {
            bit_char = 7;
            char_number++;
        } else {
            bit_char--;
        }
    }

    file.write(byte, byte_number);

    file.close();
}

void FileWriter::Write_decoded_file (char *bytes, string name, int size) {
    ofstream file;
    
    file.open(name, ios::binary);

    file.write(bytes, size);

    file.close();
}