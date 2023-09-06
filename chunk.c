#include <stdlib.h>

#include "chunk.h"
#include "memory.h"

void initChunk(Chunk* chunk) {
    chunk->count = 0;
    chunk->lines_ix = 0;
    chunk->capacity = 0;
    chunk->code = NULL;
    chunk->lines = NULL;
    initValueArray(&chunk->constants);
}

void freeChunk(Chunk* chunk) {
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
    FREE_ARRAY(int, chunk->lines, chunk->capacity);
    freeValueArray(&chunk->constants);
    initChunk(chunk);
}

void writeChunk(Chunk* chunk, uint8_t byte, int line) {
  if (chunk->capacity < chunk->count + 1) {
    int oldCapacity = chunk->capacity;
    chunk->capacity = GROW_CAPACITY(oldCapacity);
    chunk->code = GROW_ARRAY(uint8_t, chunk->code,
        oldCapacity, chunk->capacity);
    chunk->lines = GROW_ARRAY(int, chunk->lines,
        oldCapacity, chunk->capacity);
  }
  chunk->code[chunk->count] = byte;
  if(chunk->lines_ix > 0 && chunk->lines[chunk->lines_ix-1] == line) {
    chunk->lines[chunk->lines_ix]++;
  } else {
    if (chunk->lines_ix > 0)
      chunk->lines_ix++;
    chunk->lines[chunk->lines_ix] = line;
    chunk->lines_ix++;
    chunk->lines[chunk->lines_ix] = 1;
  }
  chunk->count++;
}

int getLine(Chunk* chunk, int offset) {
  int ix = 1;
  int num = chunk->lines[ix];
  while (offset+1 > num) {
    ix += 2;
    num += chunk->lines[ix];
  }
  return chunk->lines[ix-1];
}

int addConstant(Chunk* chunk, Value value) {
  writeValueArray(&chunk->constants, value);
  return chunk->constants.count - 1;
}