main = primetest
ans = primetest_ans
CC = g++
CFLAGS = -Wall

$(main) : $(main).cpp
	$(CC) $(CFLAGS) $< -o $(main)

.PHONY : ans
ans : $(ans)

$(ans) : $(ans).cpp
	$(CC) $(CFLAGS) $< -o $(ans)
	mv $(ans) $(main)

.PHONY : clean
clean :
	rm -f $(main)

