#include <dlfcn.h>
#include <stdio.h>
#include <sys/types.h>
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
using namespace std;
static void myinit() __attribute__((constructor));
//char* output;
static uid_t (*old_getuid)(void) = NULL;

void myinit() {
	char* output;
    printf("!injected: %p\n", myinit);
	output=getenv("MONITOR_OUTPUT");
	//printf("%s\n",output);
	//cout<<"put="<<endl;

	if(output!=NULL)
	{
		if(!strcmp(output,"stderr"))
			dup2(STDOUT_FILENO,STDERR_FILENO);
	}
	else
	{
		//printf("info in monitor\n");
		freopen("monitor.out","w",stdout);

	}
}


extern "C" uid_t getuid(void) {
	char* errmsg;
	if(old_getuid==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		//errmsg=dlerror();
		//cout<<errmsg<<endl;
		//fprintf(stderr,"%s\n",errmsg);
		if(handle !=NULL)
		{
			//old_getuid = dlsym(handle, "getuid"); //c program can, but not c++
			dlerror();
			*(void**)(&old_getuid) =dlsym(handle, "getuid");
			//errmsg=dlerror();
			//cout<<errmsg<<endl;
			//fprintf(stderr,"%s\n",errmsg);
			//old_getuid =(uid_t (*)(uid_t))dlsym(handle, "getuid");//c++ natural way, but the C99 standard leaves casting from "void *" to a function pointer undefined.
		}
	}
	if(old_getuid !=NULL)
	{
		//printf("~~~\n");
		//fprintf(stderr, "read uid = %d\n", old_getuid());
		cout<<"~~~"<<endl;
		cout<<"[monitor] getuid() = "<<old_getuid()<<endl;
	}
	else 
		cout<<"dlsym return NULL"<<endl;
	return 0;
}
