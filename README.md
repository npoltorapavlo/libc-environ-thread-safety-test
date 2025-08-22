```shell script
g++ -o libc-environ-thread-safety-test libc-environ-thread-safety-test.cpp
key1=x key2=y key3=z ./libc-environ-thread-safety-test
# Segmentation fault (core dumped)
key1=x key2=y key3=z gdb -ex=run ./libc-environ-thread-safety-test
# Thread 3 "libc-environ-th" received signal SIGSEGV, Segmentation fault.
# __GI_getenv (name=0x55555555902c "key1") at ./stdlib/getenv.c:31
```
