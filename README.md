# Data Buffer C

A data buffer implementation in C11 for reading and writing binary data including byte array's and strings.

# Examples

```c
// write integer
uint8_t some_value = 0xFF;
buffer_write_uint8(buffer, some_value);

// write length-prefixed string
const char str[] = "Hello World!";
buffer_t *buffer = buffer_init();
buffer_write_string(buffer, str, sizeof(str));

buffer_iterator_t *buffer_iterator = buffer_iterator_init(buffer);

// read integer
uint8_t some_value_out = buffer_read_uint8(buffer);
printf("some_value_out=%u\n", some_value_out);

// read length-prefixed string back into a regular string
char *out_str = NULL;
buffer_read_string(buffer_iterator, &out_str);
printf("str=%s\n", str);
printf("out_str=%s\n", out_str);
free(out_str);

buffer_iterator_free(buffer_iterator);
buffer_free(buffer);
```

# License

Data Buffer C is licensed under the "MIT License" for more info, refer to the [LICENSE](LICENSE) file.
