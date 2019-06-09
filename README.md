# Data Buffer C

A data buffer implementation in C for reading and writing binary data including byte array's and strings.

# Examples

```c
const char str[] = "Hello World!";
buffer_t *buffer = buffer_init();
buffer_write_string(buffer, str, sizeof(str));

buffer_iterator_t *buffer_iterator = buffer_iterator_init(buffer);
char *out_str = NULL;
buffer_read_string(buffer_iterator, &out_str);
printf("str=%s\n", str);
printf("out_str=%s\n", out_str);

buffer_iterator_free(buffer_iterator);
buffer_free(buffer);
```

# License

Data Buffer C is licensed under the "MIT License" for more info, refer to the [LICENSE](LICENSE) file.
