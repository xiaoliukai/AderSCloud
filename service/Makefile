ROOT=..
#BIN=$(ROOT)/bin/1

EXTRALIBS=-pthread -lrt


include $(ROOT)/Makefile.defines



# 所有的文件
PROGS =	server

#  所有的目标文件OBJS
OBJS = server.o main.o 


# 构建操作
$(PROGS):$(OBJS)
	gcc $(OBJS) -o $@

%.o:%.c
	$(CC)  $(CFLAGS) -c $^ -o $@ $(LDFLAGS) $(LDLIBS)

#
clean:
	rm $(OBJS)
	rm $(PROGS)
	
