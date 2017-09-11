#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h> 
#include <fcntl.h>
int zero_fd = -1;

unsigned int alarm(unsigned int secondes)
{
	return 0;
}



unsigned int sleep(unsigned int secondes)
{
	return 0;
}


void usleep(unsigned int usecondes)
{
	return ;
}

unsigned int send(int fd, void *buf, size_t size, int flags )
{
	return write(fd, size, buf);
}

unsigned int recv(int fd, void *buf , size_t size, int flags)
{
	return read(fd, size, buf);
}


// gets, scanf, 
//


void send_mesg(char *mesg)
{
	char command[1000];

	snprintf(command,1000,"touch ./thermal_grease/seeds/%s", (const char*)getenv("BIN_NAME"));
	strcat(command, mesg);
	system(command);
}



char *gets(char* str)
{
	static char* (*n_gets)(char*) = NULL;
	n_gets = dlsym(RTLD_NEXT, "gets");
	
	char* command[1000] = {0,};
	
	send_mesg("/gets_bof");
	return n_gets(str);
}



__attribute__((constructor))
void open_fd(){
	zero_fd = open("/dev/zero",0);
}


char writable(void *p)
{
	char *cp = (char*)p;
	char backup = *cp;
	if(read(zero_fd,p,1) == 1)
	{
		*cp = backup;
		return 1; //1 if writable
	}
	else
	{
		return 0;
	}
}


int printf(const char *buf, ...)
{
	static int (*n_printf)(char* , ...) = NULL;
	n_printf = dlsym(RTLD_NEXT, "printf");
	char command[1000] = {0,};
	va_list ap;

	if(writable(buf))
	{
		send_mesg("/printf_format_string");
	}

	return n_printf(buf, ap);
}

int sprintf(char *buf, const char *format, ...)
{
	static int (*n_sprintf)(char* ,const char* , ...) = NULL;
	n_sprintf = dlsym(RTLD_NEXT, "sprintf");
	char command[1000] = {0,};

	va_list ap;
	if(writable(format))
	{
		send_mesg("/sprint_format_string");
	}
	if(strstr(format, "%s"))
	{
		send_mesg("/sprint_bof");
	}

	return n_sprintf(buf, format, ap);
}


