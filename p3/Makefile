main = wordcount
mainans = wordcount_ans
CC = g++
CFLAGS = -Wall

$(main) : $(main).cpp
	$(CC) $(CFLAGS) $< -o $@

$(mainans) : $(mainans).cpp
	$(CC) $(CFLAGS) $< -o $@

.PHONY : ans
ans : $(mainans)
	mv $(mainans) $(main)

.PHONY : clean
clean :
	rm -f $(main) $(mainans)

