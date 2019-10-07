test: libhopen.so
	@cc -o main main.c
	@LD_PRELOAD=./libhopen.so ./main

libhopen.so: hook_open.c
	@gcc -shared -fPIC hook_open.c -o libhopen.so -ldl

clean:
	@rm -f libhopen.so main a.txt

