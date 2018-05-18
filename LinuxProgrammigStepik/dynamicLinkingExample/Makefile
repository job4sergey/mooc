default: solution.c
	gcc solution.c -fPIC -ldl -o solution

shared:
	gcc -o libShared.so -fPIC -shared shared.c

clean:
	rm solution libShared.so 
