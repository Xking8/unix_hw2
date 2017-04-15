#include <dlfcn.h>
#include <stdio.h>
#include <sys/types.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdarg.h>
#include <errno.h>
using namespace std;
static void myinit() __attribute__((constructor));
static uid_t (*old_getuid)(void) = NULL;
static char *(*old_getenv)(const char*) = NULL; 
static DIR *(*old_opendir)(const char*) = NULL; 
static DIR *(*old_fdopendir)(int) = NULL; 
static int (*old_closedir)(DIR*) = NULL;
static dirent *(*old_readdir)(DIR*) = NULL;
static int (*old_readdir_r)(DIR* dirp,struct dirent *entry, struct dirent **result) = NULL;
static void (*old_rewinddir)(DIR* dirp) = NULL;
static void (*old_seekdir)(DIR *dirp,long loc) = NULL;
static long (*old_telldir)(DIR* dirp) = NULL;
static int (*old_open)(const char* filename,int flags, ...) = NULL;
//static int (*old_open)(const char* filename,int flags) = NULL;
static int (*old_create)(const char* pathname, mode_t mode) = NULL; 
static int (*old_remove)(const char* pathname) = NULL; 
static int (*old_rename)(const char*, const char*) = NULL;
static void (*old_setbuf)(FILE *stream, char *buf) = NULL;
static int (*old_setvbuf)(FILE *stream, char *buf, int mode, size_t size) = NULL;
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
	int ret_val;
	if(old_getuid !=NULL)
	{
		ret_val=old_getuid();
		fprintf(out, "[monitor] getuid() = %d\n", ret_val);
		//cout<<"[monitor] getuid() = "<<old_getuid()<<endl;
	}
	else 
		//cout<<"---[monitor]old_getuid is NULL"<<endl;
		fprintf(out,"---[monitor]old_getuid is NULL");
	return ret_val;
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
	char* ret_val;
	if(old_getenv !=NULL)
	{
		if(strcmp(name,"MONITOR_OUTPUT"))
		{
			ret_val=old_getenv(name);
			fprintf(out, "[monitor] getenv('%s') = '%s'\n",name, ret_val);
			
		}
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
	DIR* ret_val;
	if(old_opendir !=NULL)
	{
		ret_val=old_opendir(name);
		fprintf(out, "[monitor] opendir('%s') = %p\n",name, ret_val);
		//cout<<"[monitor] getenv("<<name<<") = "<<old_getenv(name)<<endl;
	}
	else 
		//cout<<"---[monitor]old_getenv is NULL"<<endl;
		fprintf(out,"---[monitor]old_opendir is NULL");
	return ret_val;
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
	DIR* ret_val;
	if(old_fdopendir !=NULL)
	{
		ret_val=old_fdopendir(fd);
		fprintf(out, "[monitor] fdopendir('%d') = %p\n",fd, ret_val);
		//cout<<"[monitor] getenv("<<name<<") = "<<old_getenv(name)<<endl;
	}
	else 
		//cout<<"---[monitor]old_getenv is NULL"<<endl;
		fprintf(out,"---[monitor]old_opendir is NULL");
	return ret_val;
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
		//char* param = readdir(dirp);
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
		if(ret_val)//make sure ret_val is not NULL, this happens at read end of a directory
		{
			fprintf(out, "[monitor] readdir(%p) = '%s'\n",dirp, ret_val->d_name);
		}
		else
			fprintf(out, "[monitor] readdir(%p) = %p\n",dirp, ret_val);
		//cout<<"[monitor] getenv("<<name<<") = "<<old_getenv(name)<<endl;
	}
	else 
		//cout<<"---[monitor]old_getenv is NULL"<<endl;
		fprintf(out,"---[monitor]old_readdir is NULL");
	return ret_val;

}
extern "C" int readdir_r(DIR* dirp,struct dirent *entry, struct dirent **result) {
	char* errmsg;
	if(old_readdir_r==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		//cout<<errmsg<<endl;
		//fprintf(out,"err=%s\n",errmsg);
		if(handle !=NULL)
		{
			//old_getuid = dlsym(handle, "getuid"); //c program can, but not c++
			dlerror();
			*(void**)(&old_readdir_r) =dlsym(handle, "readdir_r");
			//errmsg=dlerror();
			//cout<<errmsg<<endl;
			//fprintf(stderr,"%s\n",errmsg);
			//old_getuid =(uid_t (*)(uid_t))dlsym(handle, "getuid");//c++ natural way, but the C99 standard leaves casting from "void *" to a function pointer undefined.
		}
	}
	int ret_val;//return value
	if(old_readdir_r !=NULL)
	{
		ret_val=old_readdir_r(dirp,entry,result);
		if(*result)//make sure ret_val is not NULL, this happens at read end of a directory
		{
			fprintf(out, "[monitor] readdir_r(%p,'%s','%s') = %d\n",dirp, entry->d_name, (*result)->d_name, ret_val);
		}
		else
			fprintf(out, "[monitor] readdir_r(%p,'%s',%p) = %d\n",dirp, entry->d_name, *result, ret_val);
		//cout<<"[monitor] getenv("<<name<<") = "<<old_getenv(name)<<endl;
	}
	else 
		//cout<<"---[monitor]old_getenv is NULL"<<endl;
		fprintf(out,"---[monitor]old_readdir is NULL");
	return ret_val;


}
extern "C" void rewinddir(DIR* dirp)
{
	char* errmsg;
	if(old_rewinddir==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		//cout<<errmsg<<endl;
		//fprintf(out,"err=%s\n",errmsg);
		if(handle !=NULL)
		{
			//old_getuid = dlsym(handle, "getuid"); //c program can, but not c++
			dlerror();
			*(void**)(&old_rewinddir) =dlsym(handle, "rewinddir");
			//errmsg=dlerror();
			//cout<<errmsg<<endl;
			//fprintf(stderr,"%s\n",errmsg);
			//old_getuid =(uid_t (*)(uid_t))dlsym(handle, "getuid");//c++ natural way, but the C99 standard leaves casting from "void *" to a function pointer undefined.
		}
	}
	//int ret_val;//return value
	if(old_rewinddir !=NULL)
	{
		old_rewinddir(dirp);
		fprintf(out, "[monitor] rewinddir(%p)\n",dirp);
		//cout<<"[monitor] getenv("<<name<<") = "<<old_getenv(name)<<endl;
	}
	else 
		//cout<<"---[monitor]old_getenv is NULL"<<endl;
		fprintf(out,"---[monitor]old_rewinddir is NULL");
	//return ret_val;
}
extern "C" void seekdir(DIR *dirp,long loc) {

	char* errmsg;
	if(old_seekdir==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		//cout<<errmsg<<endl;
		//fprintf(out,"err=%s\n",errmsg);
		if(handle !=NULL)
		{
			//old_getuid = dlsym(handle, "getuid"); //c program can, but not c++
			dlerror();
			*(void**)(&old_seekdir) =dlsym(handle, "seekdir");
			//errmsg=dlerror();
			//cout<<errmsg<<endl;
			//fprintf(stderr,"%s\n",errmsg);
			//old_getuid =(uid_t (*)(uid_t))dlsym(handle, "getuid");//c++ natural way, but the C99 standard leaves casting from "void *" to a function pointer undefined.
		}
	}
	//int ret_val;//return value
	if(old_seekdir !=NULL)
	{
		old_seekdir(dirp,loc);
		fprintf(out, "[monitor] seekdir(%p,%ld)\n",dirp,loc);
		//cout<<"[monitor] getenv("<<name<<") = "<<old_getenv(name)<<endl;
	}
	else 
		//cout<<"---[monitor]old_getenv is NULL"<<endl;
		fprintf(out,"---[monitor]old_seekdir is NULL");
	//return ret_val;

}
extern "C" long telldir(DIR* dirp) {

	char* errmsg;
	if(old_telldir==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		//cout<<errmsg<<endl;
		//fprintf(out,"err=%s\n",errmsg);
		if(handle !=NULL)
		{
			//old_getuid = dlsym(handle, "getuid"); //c program can, but not c++
			dlerror();
			*(void**)(&old_telldir) =dlsym(handle, "telldir");
			//errmsg=dlerror();
			//cout<<errmsg<<endl;
			//fprintf(stderr,"%s\n",errmsg);
			//old_getuid =(uid_t (*)(uid_t))dlsym(handle, "getuid");//c++ natural way, but the C99 standard leaves casting from "void *" to a function pointer undefined.
		}
	}
	long ret_val;//return value
	if(old_telldir !=NULL)
	{
		ret_val=old_telldir(dirp);
		fprintf(out, "[monitor] telldir(%p) = %ld\n",dirp, ret_val);
		//cout<<"[monitor] getenv("<<name<<") = "<<old_getenv(name)<<endl;
	}
	else 
		//cout<<"---[monitor]old_getenv is NULL"<<endl;
		fprintf(out,"---[monitor]old_telldir is NULL");
	return ret_val;

}

//ROW2
/*
extern "C" int open(const char* filename,int flags,mode_t mode) {
	char* errmsg;
	if(old_open2==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		//cout<<errmsg<<endl;
		//fprintf(out,"err=%s\n",errmsg);
		if(handle !=NULL)
		{
			//old_getuid = dlsym(handle, "getuid"); //c program can, but not c++
			dlerror();
			*(void**)(&old_open2) =dlsym(handle, "open");
			//errmsg=dlerror();
			//cout<<errmsg<<endl;
			//fprintf(stderr,"%s\n",errmsg);
			//old_getuid =(uid_t (*)(uid_t))dlsym(handle, "getuid");//c++ natural way, but the C99 standard leaves casting from "void *" to a function pointer undefined.
		}
	}
	int ret_val;//return value
	if(old_open !=NULL)
	{
		ret_val=old_open2(filename,flags,mode);
		fprintf(out, "[monitor] open(%s, %d, %d) = %d\n",filename, flags, mode, ret_val);
		//cout<<"[monitor] getenv("<<name<<") = "<<old_getenv(name)<<endl;
	}
	else 
		//cout<<"---[monitor]old_getenv is NULL"<<endl;
		fprintf(out,"---[monitor]old_open is NULL");
	return ret_val;

}*/
extern "C" int open(const char* filename,int flags, ...) {

	char* errmsg;
	if(old_open==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		//cout<<errmsg<<endl;
		//fprintf(out,"err=%s\n",errmsg);
		if(handle !=NULL)
		{
			//old_getuid = dlsym(handle, "getuid"); //c program can, but not c++
			dlerror();
			*(void**)(&old_open) =dlsym(handle, "open");
			//errmsg=dlerror();
			//cout<<errmsg<<endl;
			//fprintf(stderr,"%s\n",errmsg);
			//old_getuid =(uid_t (*)(uid_t))dlsym(handle, "getuid");//c++ natural way, but the C99 standard leaves casting from "void *" to a function pointer undefined.
		}
	}
	va_list ap;
	va_start(ap, flags);
	int mode= va_arg(ap,int);
	va_end(ap);
	//fprintf(out,"mode = %d\n",mode);
	//fprintf(out,"is not NULL\n");
	int ret_val;//return value
	if(old_open !=NULL)
	{
		if(mode>=0 && mode <=777)//if out of this range, mode isn't passed to open()
		{
			ret_val=old_open(filename,flags,mode);
			fprintf(out, "[monitor] open('%s', %d, %d) = %d\n",filename, flags, mode, ret_val);
		}
		else
		{
			ret_val=old_open(filename,flags);
			fprintf(out, "[monitor] open('%s', %d) = %d\n",filename, flags, ret_val);
		}
	}
	else 
		//cout<<"---[monitor]old_getenv is NULL"<<endl;
		fprintf(out,"---[monitor]old_open is NULL");
	return ret_val;

}
extern "C" int create(const char* pathname, mode_t mode) {

	char* errmsg;
	if(old_create==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		//cout<<errmsg<<endl;
		//fprintf(out,"err=%s\n",errmsg);
		if(handle !=NULL)
		{
			//old_getuid = dlsym(handle, "getuid"); //c program can, but not c++
			dlerror();
			*(void**)(&old_create) =dlsym(handle, "create");
			//errmsg=dlerror();
			//cout<<errmsg<<endl;
			//fprintf(stderr,"%s\n",errmsg);
			//old_getuid =(uid_t (*)(uid_t))dlsym(handle, "getuid");//c++ natural way, but the C99 standard leaves casting from "void *" to a function pointer undefined.
		}
	}
	int ret_val;//return value
	if(old_create !=NULL)
	{
		ret_val=old_create(pathname,mode);
		fprintf(out, "[monitor] create('%s', %d) = %d\n",pathname, mode, ret_val);
		//cout<<"[monitor] getenv("<<name<<") = "<<old_getenv(name)<<endl;
	}
	else 
		//cout<<"---[monitor]old_getenv is NULL"<<endl;
		fprintf(out,"---[monitor]old_create is NULL");
	return ret_val;

}
extern "C" int remove(const char* pathname) {

	char* errmsg;
	if(old_remove==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		//cout<<errmsg<<endl;
		//fprintf(out,"err=%s\n",errmsg);
		if(handle !=NULL)
		{
			//old_getuid = dlsym(handle, "getuid"); //c program can, but not c++
			dlerror();
			*(void**)(&old_remove) =dlsym(handle, "remove");
			//errmsg=dlerror();
			//cout<<errmsg<<endl;
			//fprintf(stderr,"%s\n",errmsg);
			//old_getuid =(uid_t (*)(uid_t))dlsym(handle, "getuid");//c++ natural way, but the C99 standard leaves casting from "void *" to a function pointer undefined.
		}
	}
	int ret_val;//return value
	if(old_remove !=NULL)
	{
		ret_val=old_remove(pathname);
		fprintf(out, "[monitor] remove('%s') = %d\n",pathname, ret_val);
		//cout<<"[monitor] getenv("<<name<<") = "<<old_getenv(name)<<endl;
	}
	else 
		//cout<<"---[monitor]old_getenv is NULL"<<endl;
		fprintf(out,"---[monitor]old_remove is NULL");
	return ret_val;
}
extern "C" int rename(const char *oldpath, const char *newpath) {
	
	char* errmsg;
	if(old_rename==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		//cout<<errmsg<<endl;
		//fprintf(out,"err=%s\n",errmsg);
		if(handle !=NULL)
		{
			//old_getuid = dlsym(handle, "getuid"); //c program can, but not c++
			dlerror();
			*(void**)(&old_rename) =dlsym(handle, "rename");
			//errmsg=dlerror();
			//cout<<errmsg<<endl;
			//fprintf(stderr,"%s\n",errmsg);
			//old_getuid =(uid_t (*)(uid_t))dlsym(handle, "getuid");//c++ natural way, but the C99 standard leaves casting from "void *" to a function pointer undefined.
		}
	}
	int ret_val;//return value
	if(old_rename !=NULL)
	{
		ret_val=old_rename(oldpath, newpath);
		fprintf(out, "[monitor] rename('%s', '%s') = %d\n", oldpath, newpath, ret_val);
		//cout<<"[monitor] getenv("<<name<<") = "<<old_getenv(name)<<endl;
	}
	else 
		//cout<<"---[monitor]old_getenv is NULL"<<endl;
		fprintf(out,"---[monitor]old_rename is NULL");
	return ret_val;
}
extern "C" void setbuf(FILE *stream, char *buf)
{
	char* errmsg;
	if(old_setbuf==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		//cout<<errmsg<<endl;
		//fprintf(out,"err=%s\n",errmsg);
		if(handle !=NULL)
		{
			//old_getuid = dlsym(handle, "getuid"); //c program can, but not c++
			dlerror();
			*(void**)(&old_setbuf) =dlsym(handle, "rename");
			//errmsg=dlerror();
			//cout<<errmsg<<endl;
			//fprintf(stderr,"%s\n",errmsg);
			//old_getuid =(uid_t (*)(uid_t))dlsym(handle, "getuid");//c++ natural way, but the C99 standard leaves casting from "void *" to a function pointer undefined.
		}
	}
	//int ret_val;//return value
	if(old_setbuf !=NULL)
	{
		old_setbuf(stream, buf);
		fprintf(out, "[monitor] setbuf(%p, '%s')\n", stream, buf);
		//cout<<"[monitor] getenv("<<name<<") = "<<old_getenv(name)<<endl;
	}
	else 
		//cout<<"---[monitor]old_getenv is NULL"<<endl;
		fprintf(out,"---[monitor]old_setbuf is NULL");
	//return ret_val;
}
extern "C" int setvbuf(FILE *stream, char *buf, int mode, size_t size)
{
	char* errmsg;
	if(old_setvbuf==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		//cout<<errmsg<<endl;
		//fprintf(out,"err=%s\n",errmsg);
		if(handle !=NULL)
		{
			//old_getuid = dlsym(handle, "getuid"); //c program can, but not c++
			dlerror();
			*(void**)(&old_setvbuf) =dlsym(handle, "rename");
			//errmsg=dlerror();
			//cout<<errmsg<<endl;
			//fprintf(stderr,"%s\n",errmsg);
			//old_getuid =(uid_t (*)(uid_t))dlsym(handle, "getuid");//c++ natural way, but the C99 standard leaves casting from "void *" to a function pointer undefined.
		}
	}
	int ret_val;//return value
	if(old_setvbuf !=NULL)
	{
		ret_val=old_setvbuf(stream, buf, mode, size);
		fprintf(out, "[monitor] setvbuf(%p, '%s', %d, %lu) = %d\n", stream, buf, mode, size, ret_val);
		//cout<<"[monitor] getenv("<<name<<") = "<<old_getenv(name)<<endl;
	}
	else 
		//cout<<"---[monitor]old_getenv is NULL"<<endl;
		fprintf(out,"---[monitor]old_setvbuf is NULL");
	return ret_val;
}
