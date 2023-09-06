#include "common.h"
#include "chunk.h"
#include "debug.h"

int main(int argc, const char* argv[]) {
    printf("Started...\n");
    Chunk chunk;
    initChunk(&chunk);

    int constant = addConstant(&chunk, 4.2);
    writeChunk(&chunk, OP_CONSTANT, 122);
    writeChunk(&chunk, constant, 122);

    writeChunk(&chunk, OP_RETURN, 122);

    disassembleChunk(&chunk, "test chunk");
    freeChunk(&chunk);
    return 0;
}