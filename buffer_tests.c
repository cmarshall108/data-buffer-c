#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "buffer.h"
#include "buffer_iterator.h"

int main(int argc, char const *argv[])
{
  buffer_t *buffer = buffer_init();
  assert(buffer != NULL);
  assert(buffer_get_size(buffer) == 0);

  // pack

  // write messages
  const char *msg = "Hello World!";
  assert(buffer_write_string(buffer, msg, strlen(msg)) == 0);

  const char *msg1 = "The quick brown fox jumps over the lazy dog.";
  assert(buffer_write_string(buffer, msg1, strlen(msg1)) == 0);

  const char *msg2 = "THE QUICK BROWN FOX JUMPED OVER THE LAZY DOG'S BACK 1234567890";
  assert(buffer_write_string(buffer, msg2, strlen(msg2)) == 0);

  // write bytes
  const char *data = "\x00\x01\x12Hello World!";
  assert(buffer_write_string(buffer, data, 16) == 0);
  assert(buffer_write_bytes(buffer, (uint8_t*)data, 16) == 0);

  const char *data1 = "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x44The quick brown fox jumps over the lazy dog.\x00\x00\x01\x00\x00\x00\x00\xfe\x00\xab";
  assert(buffer_write_string(buffer, data1, 64) == 0);
  assert(buffer_write_bytes(buffer, (uint8_t*)data1, 64) == 0);

  const char *data2 = "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0fe\xff\x0cb\x02\x003\x00\x01\x02\x03\x04\x05\x06\x07\x08\x62THE QUICK BROWN FOX JUMPED OVER THE LAZY DOG'S BACK 1234567890\x00\x00\x01\x00\x00\x00\x00\xfe\x00\xab\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\x01\x01\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xf4";
  assert(buffer_write_string(buffer, data2, 128) == 0);
  assert(buffer_write_bytes(buffer, (uint8_t*)data2, 128) == 0);

  // unpack
  buffer_iterator_t *buffer_iterator = buffer_iterator_init(buffer);

  // read messages
  char *str = NULL;
  uint8_t *bytes = NULL;

  assert(buffer_read_string(buffer_iterator, &str) == 0);
  assert(memcmp(str, msg, strlen(msg)) == 0);

  assert(buffer_read_string(buffer_iterator, &str) == 0);
  assert(memcmp(str, msg1, strlen(msg1)) == 0);

  assert(buffer_read_string(buffer_iterator, &str) == 0);
  assert(memcmp(str, msg2, strlen(msg2)) == 0);

  // read bytes
  assert(buffer_read_string(buffer_iterator, &str) == 0);
  assert(memcmp(str, data, strlen(data)) == 0);

  assert(buffer_read_bytes(buffer_iterator, &bytes) == 0);
  assert(memcmp(bytes, data, strlen(data)) == 0);

  assert(buffer_read_string(buffer_iterator, &str) == 0);
  assert(memcmp(str, data1, strlen(data1)) == 0);

  assert(buffer_read_bytes(buffer_iterator, &bytes) == 0);
  assert(memcmp(bytes, data1, strlen(data1)) == 0);

  assert(buffer_read_string(buffer_iterator, &str) == 0);
  assert(memcmp(str, data2, strlen(data2)) == 0);

  assert(buffer_read_bytes(buffer_iterator, &bytes) == 0);
  assert(memcmp(bytes, data2, strlen(data2)) == 0);

  assert(buffer_get_remaining_size(buffer_iterator) == 0);
  buffer_iterator_free(buffer_iterator);
  buffer_free(buffer);

  buffer_t *buffer1 = buffer_init();
  assert(buffer1 != NULL);
  assert(buffer_get_size(buffer1) == 0);

  // write

  // unsigned
  assert(buffer_write_uint8(buffer1, 0xFF) == 0);
  assert(buffer_write_uint16(buffer1, 0xFFFF) == 0);
  assert(buffer_write_uint32(buffer1, 0xFFFFFFFF) == 0);
  assert(buffer_write_uint64(buffer1, 0xFFFFFFFFFFFFFFFF) == 0);

  // signed
  assert(buffer_write_int8(buffer1, 0x7F) == 0);
  assert(buffer_write_int16(buffer1, 0x7FFF) == 0);
  assert(buffer_write_int32(buffer1, 0x7FFFFFFF) == 0);
  assert(buffer_write_int64(buffer1, 0x7FFFFFFFFFFFFFFF) == 0);

  assert(buffer_write_int8(buffer1, -0x7F) == 0);
  assert(buffer_write_int16(buffer1, -0x7FFF) == 0);
  assert(buffer_write_int32(buffer1, -0x7FFFFFFF) == 0);
  assert(buffer_write_int64(buffer1, -0x7FFFFFFFFFFFFFFF) == 0);

  // copy the contents of buffer1 to buffer2
  buffer_t *buffer2 = buffer_init();
  assert(buffer2 != NULL);
  assert(buffer_copy(buffer2, buffer1) == 0);
  assert(buffer_get_size(buffer2) == buffer_get_size(buffer1));
  assert(memcmp(buffer_get_data(buffer1), buffer_get_data(buffer2), buffer_get_size(buffer1)) == 0);
  buffer_free(buffer2);

  // read
  buffer_iterator_t *buffer_iterator1 = buffer_iterator_init(buffer1);

  // unsigned
  uint8_t v1 = 0;
  assert(buffer_read_uint8(buffer_iterator1, &v1) == 0);
  assert(v1 == 0xFF);

  uint16_t v2 = 0;
  assert(buffer_read_uint16(buffer_iterator1, &v2) == 0);
  assert(v2 == 0xFFFF);

  uint32_t v3 = 0;
  assert(buffer_read_uint32(buffer_iterator1, &v3) == 0);
  assert(v3 == 0xFFFFFFFF);

  uint64_t v4 = 0;
  assert(buffer_read_uint64(buffer_iterator1, &v4) == 0);
  assert(v4 == 0xFFFFFFFFFFFFFFFF);

  // signed
  int8_t v5 = 0;
  assert(buffer_read_int8(buffer_iterator1, &v5) == 0);
  assert(v5 == 0x7F);

  int16_t v6 = 0;
  assert(buffer_read_int16(buffer_iterator1, &v6) == 0);
  assert(v6 == 0x7FFF);

  int32_t v7 = 0;
  assert(buffer_read_int32(buffer_iterator1, &v7) == 0);
  assert(v7 == 0x7FFFFFFF);

  int64_t v8 = 0;
  assert(buffer_read_int64(buffer_iterator1, &v8) == 0);
  assert(v8 == 0x7FFFFFFFFFFFFFFF);

  int8_t v9 = 0;
  assert(buffer_read_int8(buffer_iterator1, &v9) == 0);
  assert(v9 == -0x7F);

  int16_t v10 = 0;
  assert(buffer_read_int16(buffer_iterator1, &v10) == 0);
  assert(v10 == -0x7FFF);

  int32_t v11 = 0;
  assert(buffer_read_int32(buffer_iterator1, &v11) == 0);
  assert(v11 == -0x7FFFFFFF);

  int64_t v12 = 0;
  assert(buffer_read_int64(buffer_iterator1, &v12) == 0);
  assert(v12 == -0x7FFFFFFFFFFFFFFF);

  assert(buffer_get_remaining_size(buffer_iterator1) == 0);
  buffer_iterator_free(buffer_iterator1);
  buffer_free(buffer1);
  return 0;
}
