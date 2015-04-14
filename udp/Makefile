ROOT=..
#BIN=$(ROOT)/bin/1

EXTRALIBS=-pthread -lrt


include $(ROOT)/Makefile.defines




# 所有的文件
PROGS=$(CLIENT_PROG) $(SERVER_PROG)

CLIENT_PROG = udpclient
SERVER_PROG = udpserver

#  所有的目标文件OBJS
OBJS = $(SERVER_OBJS) $(CLIENT_OBJS)

SERVER_OBJS = udpserver.o server.o
CLIENT_OBJS = udpclient.o client.o



#all:$(CLIENT_OBJS) $(SERVER_OBJS)	
#	gcc $(CLIENT_OBJS) -o $(CLIENT_PROG)
#	gcc $(SERVER_OBJS) -o $(SERVER_PROG)


all:$(PROGS)


# 构建操作
$(CLIENT_PROG):$(CLIENT_OBJS)
	gcc $(CLIENT_OBJS) -o $@

$(SERVER_PROG):$(SERVER_OBJS)
	gcc $(SERVER_OBJS) -o $@

%.o:%.c
	$(CC)  $(CFLAGS) -c $^ -o $@ $(LDFLAGS) $(LDLIBS)

#
clean:
	rm $(OBJS)
	rm $(PROGS)
	
