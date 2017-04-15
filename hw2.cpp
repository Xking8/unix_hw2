#include <dlfcn.h>
#include <stdio.h>
#include <sys/types.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
using namespace std;
static void myinit() __attribute__((constructor));
static uid_t (*old_getuid)(void) = NULL;
static char *(*old_getenv)(const char*) = NULL; 
static DIR *(*old_opendir)(const char*) = NULL; 
static DIR *(*old_fdopendir)(int) = NULL; 
static int (*old_closedir)(DIR*) = NULL;
static dirent *(*old_readdir)(DIR*) = NULL;

FILE* out;

void myinit() {
	char* output;
	out=fopen("monitor.out","w");
//	printf("!injected: %p\n", myinit);
	output=getenv("MONITOR_OUTPUT");
//	printf("get output%s\n",output);
	//cout<<"put="<<endl;

	if(output!=NULL)
	{
		if(!strcmp(output,"stderr"))
		{
			int n=dup2(STDERR_FILENO,fileno(out));
			printf("n=%d\n",n);
			if(n<0)
				;//fprintf(stderr,"dup2 error\n");
			
		}
	}
	else
	{
		//printf("info in monitor\n");
		//ofstream outputfile("monitor.out");
		//cout.rdbuf(outputfile.rdbuf());
	}
}


extern "C" uid_t getuid(void) {
	char* errmsg;
	if(old_getuid==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		//cout<<errmsg<<endl;
		//fprintf(out,"err=%s\n",errmsg);
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
		fprintf(out, "[monitor] getuid() = %d\n", old_getuid());
		//cout<<"[monitor] getuid() = "<<old_getuid()<<endl;
	}
	else 
		//cout<<"---[monitor]old_getuid is NULL"<<endl;
		fprintf(out,"---[monitor]old_getuid is NULL");
	return old_getuid();
}


extern "C" char *getenv(const char *name) {
		
	char* errmsg;
	if(old_getenv==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		//cout<<errmsg<<endl;
		//fprintf(out,"err=%s\n",errmsg);
		if(handle !=NULL)
		{
			//old_getuid = dlsym(handle, "getuid"); //c program can, but not c++
			dlerror();
			*(void**)(&old_getenv) =dlsym(handle, "getenv");
			//errmsg=dlerror();
			//cout<<errmsg<<endl;
			//fprintf(stderr,"%s\n",errmsg);
			//old_getuid =(uid_t (*)(uid_t))dlsym(handle, "getuid");//c++ natural way, but the C99 standard leaves casting from "void *" to a function pointer undefined.
		}
	}
	if(old_getenv !=NULL)
	{
		if(strcmp(name,"MONITOR_OUTPUT"))
			fprintf(out, "[monitor] getenv('%s') = '%s'\n",name, old_getenv(name));
		//cout<<"[monitor] getenv("<<name<<") = "<<old_getenv(name)<<endl;
	}
	else 
		//cout<<"---[monitor]old_getenv is NULL"<<endl;
		fprintf(out,"---[monitor]old_getenv is NULL");
	return old_getenv(name);
}

extern "C" DIR *opendir(const char *name) {
		
	char* errmsg;
	if(old_opendir==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		//cout<<errmsg<<endl;
		//fprintf(out,"err=%s\n",errmsg);
		if(handle !=NULL)
		{
			//old_getuid = dlsym(handle, "getuid"); //c program can, but not c++
			dlerror();
			*(void**)(&old_opendir) =dlsym(handle, "opendir");
			//errmsg=dlerror();
			//cout<<errmsg<<endl;
			//fprintf(stderr,"%s\n",errmsg);
			//old_getuid =(uid_t (*)(uid_t))dlsym(handle, "getuid");//c++ natural way, but the C99 standard leaves casting from "void *" to a function pointer undefined.
		}
	}
	if(old_opendir !=NULL)
	{
		fprintf(out, "[monitor] opendir('%s') = %p\n",name, old_opendir(name));
		//cout<<"[monitor] getenv("<<name<<") = "<<old_getenv(name)<<endl;
	}
	else 
		//cout<<"---[monitor]old_getenv is NULL"<<endl;
		fprintf(out,"---[monitor]old_opendir is NULL");
	return old_opendir(name);
}

extern "C" DIR *fdopendir(int fd) {
		
	char* errmsg;
	if(old_fdopendir==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		//cout<<errmsg<<endl;
		//fprintf(out,"err=%s\n",errmsg);
		if(handle !=NULL)
		{
			//old_getuid = dlsym(handle, "getuid"); //c program can, but not c++
			dlerror();
			*(void**)(&old_fdopendir) =dlsym(handle, "fdopendir");
			//errmsg=dlerror();
			//cout<<errmsg<<endl;
			//fprintf(stderr,"%s\n",errmsg);
			//old_getuid =(uid_t (*)(uid_t))dlsym(handle, "getuid");//c++ natural way, but the C99 standard leaves casting from "void *" to a function pointer undefined.
		}
	}
	if(old_fdopendir !=NULL)
	{
		fprintf(out, "[monitor] fdopendir('%d') = %p\n",fd, old_fdopendir(fd));
		//cout<<"[monitor] getenv("<<name<<") = "<<old_getenv(name)<<endl;
	}
	else 
		//cout<<"---[monitor]old_getenv is NULL"<<endl;
		fprintf(out,"---[monitor]old_opendir is NULL");
	return old_fdopendir(fd);
}
extern "C" int closedir(DIR* dirp) {	
	char* errmsg;
	if(old_closedir==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		//cout<<errmsg<<endl;
		//fprintf(out,"err=%s\n",errmsg);
		if(handle !=NULL)
		{
			//old_getuid = dlsym(handle, "getuid"); //c program can, but not c++
			dlerror();
			*(void**)(&old_closedir) =dlsym(handle, "closedir");
			//errmsg=dlerror();
			//cout<<errmsg<<endl;
			//fprintf(stderr,"%s\n",errmsg);
			//old_getuid =(uid_t (*)(uid_t))dlsym(handle, "getuid");//c++ natural way, but the C99 standard leaves casting from "void *" to a function pointer undefined.
		}
	}
	int ret_val;//return value
	if(old_closedir !=NULL)
	{
		ret_val=old_closedir(dirp);
		fprintf(out, "[monitor] closedir(%p) = %d\n",dirp, ret_val);
		//cout<<"[monitor] getenv("<<name<<") = "<<old_getenv(name)<<endl;
	}
	else 
		//cout<<"---[monitor]old_getenv is NULL"<<endl;
		fprintf(out,"---[monitor]old_closedir is NULL");
	return ret_val;
}
extern "C" dirent *readdir(DIR* dirp) {
	char* errmsg;
	if(old_readdir==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		//cout<<errmsg<<endl;
		//fprintf(out,"err=%s\n",errmsg);
		if(handle !=NULL)
		{
			//old_getuid = dlsym(handle, "getuid"); //c program can, but not c++
			dlerror();
			*(void**)(&old_readdir) =dlsym(handle, "readdir");
			//errmsg=dlerror();
			//cout<<errmsg<<endl;
			//fprintf(stderr,"%s\n",errmsg);
			//old_getuid =(uid_t (*)(uid_t))dlsym(handle, "getuid");//c++ natural way, but the C99 standard leaves casting from "void *" to a function pointer undefined.
		}
	}
	dirent* ret_val;//return value
	if(old_readdir !=NULL)
	{
		ret_val=old_readdir(dirp);
		if(ret_val)
		{
			fprintf(out, "[monitor] readdir(%p) = '%s'\n",dirp, ret_val->d_name);
		}
		//cout<<"[monitor] getenv("<<name<<") = "<<old_getenv(name)<<endl;
	}
	else 
		//cout<<"---[monitor]old_getenv is NULL"<<endl;
		fprintf(out,"---[monitor]old_readdir is NULL");
	return ret_val;

//	return old_readdir(dirp);
}

