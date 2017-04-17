#include <dlfcn.h>
#include <stdio.h>
#include <pwd.h>
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
//static void mydes() __attribute__((destructor));
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
static char* (*old_tempnam)(const char *dir, const char *pfx) = NULL;
static FILE *(*old_tmpfile)(void) = NULL;
static char* (*old_tmpnam)(char* s) = NULL;
static void (*old_exit)(int) = NULL;
static void (*old__exit)(int) = NULL;
static char* (*old_mkdtemp)(char*) = NULL;
static int (*old_mkstemp)(char*) = NULL;
static int (*old_putenv)(char*) = NULL;
static int (*old_rand)() = NULL;
static int (*old_r_rand)(unsigned int*) = NULL;
static void (*old_srand)(unsigned int) = NULL;
//ROW3
static int (*old_setenv)(const char *name, const char *value, int overwrite) = NULL;
static int (*old_system)(const char *command) = NULL;
static int (*old_chdir)(const char *) = NULL;
static int (*old_fchdir)(int) = NULL;
static int (*old_chown)(const char *path, uid_t owner, gid_t group) = NULL;
static int (*old_close)(int) = NULL;
static int (*old_dup)(int) = NULL;
static int (*old_dup2)(int, int) = NULL;
static int (*old_execl)(const char*, const char*, ...) = NULL;
static int (*old_execlp)(const char*, const char*, ...) = NULL;
static int (*old_execle)(const char*, const char*, ...) = NULL;
static int (*old_execve)(const char*, char *const[], char *const[]) = NULL;
static int (*old_execvp)(const char *filename, char *const argv[]) = NULL;
static int (*old_execv)(const char*, char *const[]) = NULL;
static int (*old_fchown)(int fd, uid_t owner, gid_t group) = NULL;
static int (*old_fork)(void) = NULL;
static int (*old_fsync)(int fd) = NULL;
static int (*old_ftruncate)(int fd, off_t length) = NULL;
static char* (*old_getcwd)(char *buf, size_t size);
static gid_t (*old_getegid)(void) = NULL;
static uid_t (*old_geteuid)(void) = NULL;
static gid_t (*old_getgid)(void) = NULL;
static int (*old_link)(const char*, const char*) = NULL;
static int (*old_pipe)(int pipefd[2]) = NULL;
static ssize_t (*old_pread)(int fd, void *buf, size_t count, off_t offset) = NULL;
static ssize_t (*old_pwrite)(int fd, const void *buf, size_t count, off_t offset) = NULL;
static ssize_t (*old_read)(int fd, void *buf, size_t count) = NULL;
static ssize_t (*old_write)(int fd, const void *buf, size_t count) = NULL;
static ssize_t (*old_readlink)(const char *path, char *buf, size_t bufsiz) = NULL;
static int (*old_rmdir)(const char *path) = NULL;
static int (*old_seteuid)(uid_t euid) = NULL;
static int (*old_setegid)(gid_t egid) = NULL;
static int (*old_setuid)(uid_t uid) = NULL;
static int (*old_setgid)(gid_t gid) = NULL;
static unsigned int (*old_sleep)(unsigned int seconds) = NULL;
static int (*old_nanosleep)(const struct timespec *req, const struct timespec *rem) = NULL;
static int (*old_symlink)(const char *, const char *) = NULL;
static int (*old_unlink)(const char *pathname)  = NULL;
static int (*old_fchmodat)(int dirfd, const char *pathname, mode_t mode, int flags) = NULL;
static int (*old_chmod)(const char*, mode_t mode) = NULL;
static int (*old_fchmod)(int fd, mode_t mode) = NULL;
static int (*old___xstat)(int ver, const char * path, struct stat *stat_buf) = NULL;
static int (*old___lxstat)(int ver, const char * path, struct stat *stat_buf) = NULL;
static int (*old___fxstat)(int ver, int path, struct stat *stat_buf) = NULL;
static int (*old_mkdir)(const char *pathname, mode_t mode) = NULL;
static int (*old_mkfifo)(const char *pathname, mode_t mode) = NULL;
static mode_t (*old_umask)(mode_t mode) = NULL;
static void *(*old_realloc)(void *ptr, size_t size) = NULL;
static int (*old_fflush)(FILE *stream) = NULL;
static int (*old_fputs_unlocked)(const char *s, FILE *stream) = NULL;
static int (*old___freading)(FILE *stream) = NULL;
static int (*old_fclose)(FILE *stream) = NULL;
static void (*old_free)(void *ptr) = NULL;
static char *(*old_setlocale)(int category, const char *locale) = NULL;
static void *(*old_memmove)(void *dest, const void * src, size_t n) = NULL;
static int (*old_fileno)(FILE* stream) = NULL;

FILE* out;
void myinit() {
	char* output;
	out=fopen("monitor.out","a+");
	//printf("!injected: %p\n", myinit);
	output=getenv("MONITOR_OUTPUT");
//	printf("get output%s\n",output);
	//cout<<"put="<<endl;

	if(output!=NULL)
	{
		if(!strcmp(output,"stderr"))
		{
			if(old_dup2==NULL) {
				void *handle = dlopen("libc.so.6",RTLD_LAZY);
				if(handle !=NULL)
				{
					dlerror();
					*(void**)(&old_dup2) =dlsym(handle, "dup2");
				}
			}
			int ret_val;//return value
			if(old_dup2 !=NULL)
			{
				ret_val=old_dup2(STDERR_FILENO,fileno(out));
			}
			
		}
	}
	else
	{
		//printf("info in monitor\n");
		//ofstream outputfile("monitor.out");
		//cout.rdbuf(outputfile.rdbuf());
	}
}
/*
void mydes() {

}*/

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
		struct passwd *p = getpwuid(ret_val);
		fprintf(out, "[monitor] getuid() = %s\n", p->pw_name);
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
			*(void**)(&old_setbuf) =dlsym(handle, "setbuf");
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
			*(void**)(&old_setvbuf) =dlsym(handle, "setvbuf");
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
extern "C" char* tempnam(const char *dir, const char *pfx) {

	char* errmsg;
	if(old_tempnam==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		//cout<<errmsg<<endl;
		//fprintf(out,"err=%s\n",errmsg);
		if(handle !=NULL)
		{
			//old_getuid = dlsym(handle, "getuid"); //c program can, but not c++
			dlerror();
			*(void**)(&old_tempnam) =dlsym(handle, "tempnam");
			//errmsg=dlerror();
			//cout<<errmsg<<endl;
			//fprintf(stderr,"%s\n",errmsg);
			//old_getuid =(uid_t (*)(uid_t))dlsym(handle, "getuid");//c++ natural way, but the C99 standard leaves casting from "void *" to a function pointer undefined.
		}
	}
	char* ret_val;//return value
	if(old_tempnam !=NULL)
	{
		ret_val=old_tempnam(dir,pfx);
		fprintf(out, "[monitor] tempnam('%s', '%s') = '%s'\n", dir, pfx, ret_val);
		//cout<<"[monitor] getenv("<<name<<") = "<<old_getenv(name)<<endl;
	}
	else 
		//cout<<"---[monitor]old_getenv is NULL"<<endl;
		fprintf(out,"---[monitor]old_tempnam is NULL");
	return ret_val;
}
extern "C" FILE *tmpfile(void) {

	char* errmsg;
	if(old_tmpfile==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		//cout<<errmsg<<endl;
		//fprintf(out,"err=%s\n",errmsg);
		if(handle !=NULL)
		{
			//old_getuid = dlsym(handle, "getuid"); //c program can, but not c++
			dlerror();
			*(void**)(&old_tmpfile) =dlsym(handle, "tmpfile");
			//errmsg=dlerror();
			//cout<<errmsg<<endl;
			//fprintf(stderr,"%s\n",errmsg);
			//old_getuid =(uid_t (*)(uid_t))dlsym(handle, "getuid");//c++ natural way, but the C99 standard leaves casting from "void *" to a function pointer undefined.
		}
	}
	FILE* ret_val;//return value
	if(old_tmpfile !=NULL)
	{
		ret_val=old_tmpfile();
		fprintf(out, "[monitor] tmpfile() = %p\n", ret_val);
		//cout<<"[monitor] getenv("<<name<<") = "<<old_getenv(name)<<endl;
	}
	else 
		//cout<<"---[monitor]old_getenv is NULL"<<endl;
		fprintf(out,"---[monitor]old_tmpfile is NULL");
	return ret_val;
}
extern "C" char* tmpnam(char* s) {

	char* errmsg;
	if(old_tmpnam==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		//cout<<errmsg<<endl;
		//fprintf(out,"err=%s\n",errmsg);
		if(handle !=NULL)
		{
			//old_getuid = dlsym(handle, "getuid"); //c program can, but not c++
			dlerror();
			*(void**)(&old_tmpnam) =dlsym(handle, "tmpnam");
			//errmsg=dlerror();
			//cout<<errmsg<<endl;
			//fprintf(stderr,"%s\n",errmsg);
			//old_getuid =(uid_t (*)(uid_t))dlsym(handle, "getuid");//c++ natural way, but the C99 standard leaves casting from "void *" to a function pointer undefined.
		}
	}
	char* ret_val;//return value
	if(old_tmpnam !=NULL)
	{
		ret_val=old_tmpnam(s);
		fprintf(out, "[monitor] tmpnam('%s') = '%s'\n", s, ret_val);
		//cout<<"[monitor] getenv("<<name<<") = "<<old_getenv(name)<<endl;
	}
	else 
		//cout<<"---[monitor]old_getenv is NULL"<<endl;
		fprintf(out,"---[monitor]old_tmpnam is NULL");
	return ret_val;

}
extern "C" void exit(int status) {

	char* errmsg;
	if(old_exit==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		//cout<<errmsg<<endl;
		//fprintf(out,"err=%s\n",errmsg);
		if(handle !=NULL)
		{
			//old_getuid = dlsym(handle, "getuid"); //c program can, but not c++
			dlerror();
			*(void**)(&old_exit) =dlsym(handle, "exit");
			//errmsg=dlerror();
			//cout<<errmsg<<endl;
			//fprintf(stderr,"%s\n",errmsg);
			//old_getuid =(uid_t (*)(uid_t))dlsym(handle, "getuid");//c++ natural way, but the C99 standard leaves casting from "void *" to a function pointer undefined.
		}
	}
	//FILE* ret_val;//return value
	if(old_exit !=NULL)
	{
		fprintf(out, "[monitor] exit(%d)\n", status);
		old_exit(status);
	}
	else 
		//cout<<"---[monitor]old_getenv is NULL"<<endl;
		fprintf(out,"---[monitor]old_exit is NULL");
	//return ret_val;
}
extern "C" void _exit(int status) {

	char* errmsg;
	if(old__exit==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		//cout<<errmsg<<endl;
		//fprintf(out,"err=%s\n",errmsg);
		if(handle !=NULL)
		{
			//old_getuid = dlsym(handle, "getuid"); //c program can, but not c++
			dlerror();
			*(void**)(&old__exit) =dlsym(handle, "_exit");
			//errmsg=dlerror();
			//cout<<errmsg<<endl;
			//fprintf(stderr,"%s\n",errmsg);
			//old_getuid =(uid_t (*)(uid_t))dlsym(handle, "getuid");//c++ natural way, but the C99 standard leaves casting from "void *" to a function pointer undefined.
		}
	}
	//FILE* ret_val;//return value
	if(old__exit !=NULL)
	{
		fprintf(out, "[monitor] _exit(%d)\n", status);
		old__exit(status);
		//cout<<"[monitor] getenv("<<name<<") = "<<old_getenv(name)<<endl;
	}
	else 
		//cout<<"---[monitor]old_getenv is NULL"<<endl;
		fprintf(out,"---[monitor]old__exit is NULL");
	//return ret_val;
}
extern "C" char *mkdtemp(char *templ) {

	char* errmsg;
	if(old_mkdtemp==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		//cout<<errmsg<<endl;
		//fprintf(out,"err=%s\n",errmsg);
		if(handle !=NULL)
		{
			//old_getuid = dlsym(handle, "getuid"); //c program can, but not c++
			dlerror();
			*(void**)(&old_mkdtemp) =dlsym(handle, "mkdtemp");
			//errmsg=dlerror();
			//cout<<errmsg<<endl;
			//fprintf(stderr,"%s\n",errmsg);
			//old_getuid =(uid_t (*)(uid_t))dlsym(handle, "getuid");//c++ natural way, but the C99 standard leaves casting from "void *" to a function pointer undefined.
		}
	}
	char* ret_val;//return value
	if(old_mkdtemp !=NULL)
	{
		ret_val=old_mkdtemp(templ);
		fprintf(out, "[monitor] mkdtemp('%s') = '%s'\n", templ, ret_val);
		//cout<<"[monitor] getenv("<<name<<") = "<<old_getenv(name)<<endl;
	}
	else 
		//cout<<"---[monitor]old_getenv is NULL"<<endl;
		fprintf(out,"---[monitor]old_mkdtemp is NULL");
	return ret_val;
}
extern "C" int mkstemp(char *templ) {

	char* errmsg;
	if(old_mkstemp==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		if(handle !=NULL)
		{
			dlerror();
			*(void**)(&old_mkstemp) =dlsym(handle, "mkstemp");
		}
	}
	int ret_val;//return value
	if(old_mkstemp !=NULL)
	{
		ret_val=old_mkstemp(templ);
		fprintf(out, "[monitor] mkstemp('%s') = %d\n", templ, ret_val);
	}
	else 
		fprintf(out,"---[monitor]old_mkstemp is NULL");
	return ret_val;
}
extern "C" int putenv(char *string) {

	char* errmsg;
	if(old_putenv==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		if(handle !=NULL)
		{
			dlerror();
			*(void**)(&old_putenv) =dlsym(handle, "putenv");
		}
	}
	int ret_val;//return value
	if(old_putenv !=NULL)
	{
		ret_val=old_putenv(string);
		fprintf(out, "[monitor] putenv('%s') = %d\n", string, ret_val);
	}
	else 
		fprintf(out,"---[monitor]old_putenv is NULL");
	return ret_val;
}
extern "C" int rand(void) {

	char* errmsg;
	if(old_rand==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		if(handle !=NULL)
		{
			dlerror();
			*(void**)(&old_rand) =dlsym(handle, "rand");
		}
	}
	int ret_val;//return value
	if(old_rand !=NULL)
	{
		ret_val=old_rand();
		fprintf(out, "[monitor] rand() = %d\n", ret_val);
	}
	else 
		fprintf(out,"---[monitor]old_rand is NULL");
	return ret_val;
}
extern "C" int r_rand(unsigned int *seedp) {

	char* errmsg;
	if(old_r_rand==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		if(handle !=NULL)
		{
			dlerror();
			*(void**)(&old_r_rand) =dlsym(handle, "r_rand");
		}
	}
	int ret_val;//return value
	if(old_r_rand !=NULL)
	{
		ret_val=old_r_rand(seedp);
		fprintf(out, "[monitor] r_rand(%u) = %d\n", *seedp, ret_val);
	}
	else 
		fprintf(out,"---[monitor]old_r_rand is NULL");
	return ret_val;
}
extern "C" void srand(unsigned int seed) {

	char* errmsg;
	if(old_srand==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		if(handle !=NULL)
		{
			dlerror();
			*(void**)(&old_srand) =dlsym(handle, "srand");
		}
	}
	//int ret_val;//return value
	if(old_srand !=NULL)
	{
		old_srand(seed);
		fprintf(out, "[monitor] srand(%u)\n", seed);
	}
	else 
		fprintf(out,"---[monitor]old_srand is NULL");
	//return ret_val;
}

//ROW3
extern "C" int setenv(const char *name, const char *value, int overwrite) {

	char* errmsg;
	if(old_setenv==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		if(handle !=NULL)
		{
			dlerror();
			*(void**)(&old_setenv) =dlsym(handle, "setenv");
		}
	}
	int ret_val;//return value
	if(old_setenv !=NULL)
	{
		ret_val=old_setenv(name,value,overwrite);
		fprintf(out, "[monitor] setenv('%s', '%s', %d) = %d\n", name, value, overwrite, ret_val);
	}
	else 
		fprintf(out,"---[monitor]old_setenv is NULL");
	return ret_val;
}
extern "C" int system(const char *command) {

	char* errmsg;
	if(old_system==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		if(handle !=NULL)
		{
			dlerror();
			*(void**)(&old_system) =dlsym(handle, "system");
		}
	}
	int ret_val;//return value
	if(old_system !=NULL)
	{
		ret_val=old_system(command);
		fprintf(out, "[monitor] system('%s') = %d\n", command, ret_val);
	}
	else 
		fprintf(out,"---[monitor]old_system is NULL");
	return ret_val;
}
extern "C" int chdir(const char *path) {

	char* errmsg;
	if(old_chdir==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		if(handle !=NULL)
		{
			dlerror();
			*(void**)(&old_chdir) =dlsym(handle, "chdir");
		}
	}
	int ret_val;//return value
	if(old_chdir !=NULL)
	{
		ret_val=old_chdir(path);
		fprintf(out, "[monitor] chdir('%s') = %d\n", path, ret_val);
	}
	else 
		fprintf(out,"---[monitor]old_chdir is NULL");
	return ret_val;
}
extern "C" int fchdir(int fd) {

	char* errmsg;
	if(old_fchdir==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		if(handle !=NULL)
		{
			dlerror();
			*(void**)(&old_fchdir) =dlsym(handle, "fchdir");
		}
	}
	int ret_val;//return value
	if(old_fchdir !=NULL)
	{
		ret_val=old_fchdir(fd);
		fprintf(out, "[monitor] fchdir(%d) = %d\n", fd, ret_val);
	}
	else 
		fprintf(out,"---[monitor]old_fchdir is NULL");
	return ret_val;
}
extern "C" int chown(const char *path, uid_t owner, gid_t group) {

	char* errmsg;
	if(old_chown==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		if(handle !=NULL)
		{
			dlerror();
			*(void**)(&old_chown) =dlsym(handle, "chown");
		}
	}
	int ret_val;//return value
	if(old_chown !=NULL)
	{
		ret_val=old_chown(path, owner, group);
		fprintf(out, "[monitor] chown('%s', %d, %d) = %d\n", path, owner, group, ret_val);
	}
	else 
		fprintf(out,"---[monitor]old_chown is NULL");
	return ret_val;
}
extern "C" int close(int fd) {

	char* errmsg;
	if(old_close==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		if(handle !=NULL)
		{
			dlerror();
			*(void**)(&old_close) =dlsym(handle, "close");
		}
	}
	int ret_val;//return value
	if(old_close !=NULL)
	{
		ret_val=old_close(fd);
		fprintf(out, "[monitor] close(%d) = %d\n", fd, ret_val);
	}
	else 
		fprintf(out,"---[monitor]old_close is NULL");
	return ret_val;
}
extern "C" int dup(int oldfd) {
	char* errmsg;
	if(old_dup==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		if(handle !=NULL)
		{
			dlerror();
			*(void**)(&old_dup) =dlsym(handle, "dup");
		}
	}
	int ret_val;//return value
	if(old_dup !=NULL)
	{
		ret_val=old_dup(oldfd);
		fprintf(out, "[monitor] dup(%d) = %d\n", oldfd, ret_val);
	}
	else 
		fprintf(out,"---[monitor]old_dup is NULL");
	return ret_val;
}
extern "C" int dup2(int oldfd, int newfd) {
	char* errmsg;
	if(old_dup2==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		if(handle !=NULL)
		{
			dlerror();
			*(void**)(&old_dup2) =dlsym(handle, "dup2");
		}
	}
	int ret_val;//return value
	if(old_dup2 !=NULL)
	{
		ret_val=old_dup2(oldfd,newfd);
		fprintf(out, "[monitor] dup2(%d,%d) = %d\n", oldfd, newfd, ret_val);
	}
	else 
		fprintf(out,"---[monitor]old_dup2 is NULL");
	return ret_val;
}
extern "C" int execl(const char *path, const char *arg, ...) {	
	
	char* errmsg;
	if(old_execve==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		if(handle !=NULL)
		{
			dlerror();
			*(void**)(&old_execve) =dlsym(handle, "execve");
		}
	}

	int argc;
	va_list ap;
	va_start(ap,arg);
	for(argc=1; va_arg (ap,const char*); argc++)
	{	
		;
	}
	int ret_val;//return value
	if(old_execve !=NULL)
	{
		va_end (ap);
		int i;
		char *argv[argc+1];
		va_start(ap,arg);
		argv[0]=(char*) arg;
		for(i=1; i<=argc; i++)
		{
			argv[i]=va_arg(ap, char*);
		}
		va_end(ap);
		///
		fprintf(out, "[monitor] execl('%s','%s'", path, argv[0]);
		for(int q=1; q<argc; q++)
			fprintf(out,", '%s'",argv[q]);
		fprintf(out, ")\n");
		int ret_val = old_execve(path,argv,__environ);
		if (ret_val==-1)
		{
			fprintf(out, "[monitor] execl('%s','%s'", path, argv[0]);
			for(int q=1; q<argc; q++)
				fprintf(out,", '%s'",argv[q]);
			fprintf(out, ") = -1\n");
			return ret_val;
		}
	}
	else 
		fprintf(out,"---[monitor]old_execve is NULL");
	return ret_val;


}
extern "C" int execle(const char *path, const char *arg, ...) {	
	
	char* errmsg;
	if(old_execve==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		if(handle !=NULL)
		{
			dlerror();
			*(void**)(&old_execve) =dlsym(handle, "execve");
		}
	}

	int argc;
	va_list ap;
	va_start(ap,arg);
	for(argc=1; va_arg (ap,const char*); argc++)
	{	
		;
	}
	int ret_val;//return value
	if(old_execve !=NULL)
	{
		va_end (ap);
		int i;
		char *argv[argc+1];
		char **envp;
		va_start(ap,arg);
		argv[0]=(char*) arg;
		for(i=1; i<=argc; i++)
		{
			argv[i]=va_arg(ap, char*);
		}
		envp=va_arg(ap,char**);
		va_end(ap);
		///
		fprintf(out, "[monitor] execle('%s','%s'", path, argv[0]);
		for(int q=1; q<argc; q++)
			fprintf(out,", '%s'",argv[q]);
		for(int w=0; envp[w]!=NULL;w++)
			fprintf(out,", '%s'",envp[w]);
		fprintf(out, ")\n");
		int ret_val = old_execve(path,argv,envp);
		if (ret_val==-1)
		{
			fprintf(out, "[monitor] execle('%s','%s'", path, argv[0]);
			for(int q=1; q<argc; q++)
				fprintf(out,", '%s'",argv[q]);
			fprintf(out, ") = -1\n");
			return ret_val;
		}
	}
	else 
		fprintf(out,"---[monitor]old_execve is NULL");
	return ret_val;
}
extern "C" int execlp(const char *file, const char *arg, ...) {	
	
	char* errmsg;
	if(old_execvp==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		if(handle !=NULL)
		{
			dlerror();
			*(void**)(&old_execvp) =dlsym(handle, "execvp");
		}
	}

	int argc;
	va_list ap;
	va_start(ap,arg);
	for(argc=1; va_arg (ap,const char*); argc++)
	{	
		;
	}
	int ret_val;//return value
	if(old_execvp !=NULL)
	{
		va_end (ap);
		int i;
		char *argv[argc+1];
		va_start(ap,arg);
		argv[0]=(char*) arg;
		for(i=1; i<=argc; i++)
		{
			argv[i]=va_arg(ap, char*);
		}
		va_end(ap);
		///
		fprintf(out, "[monitor] execlp('%s','%s'", file, argv[0]);
		fflush(out);
		sleep(10);
		for(int q=1; q<argc; q++)
			fprintf(out,", '%s'",argv[q]);
		fprintf(out, ")\n");
		int ret_val = old_execvp(file,argv);
		if (ret_val==-1)
		{
			fprintf(out, "[monitor] execlp('%s','%s'", file, argv[0]);
			for(int q=1; q<argc; q++)
				fprintf(out,", '%s'",argv[q]);
			fprintf(out, ") = -1\n");
			return ret_val;
		}
	}
	else 
		fprintf(out,"---[monitor]old_execvp is NULL");
	return ret_val;
}
extern "C" int execve(const char *filename, char *const argv[], char *const envp[]) {//some other exec* call this
	
	char* errmsg;
	if(old_execve==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		if(handle !=NULL)
		{
			dlerror();
			*(void**)(&old_execve) =dlsym(handle, "execve");
		}
	}
	int ret_val;//return value
	if(old_execve !=NULL)
	{

		fprintf(out, "[monitor] execve('%s','%s'", filename, argv[0]);
		for(int q=1; argv[q]; q++)
			fprintf(out,", '%s'",argv[q]);
		fprintf(out, ")\n");
		ret_val=old_execve(filename,argv,envp);
		if(ret_val==-1)
		{
			
			fprintf(out, "[monitor] execve('%s','%s'", filename, argv[0]);
			for(int q=1; argv[q]; q++)
				fprintf(out,", '%s'",argv[q]);
			fprintf(out, ") = -1\n");
			return ret_val;
		}

	}
	else 
		fprintf(out,"---[monitor]old_execve is NULL");
//	return ret_val;
}
extern "C" int execvp(const char *filename, char *const argv[]) {//some other exec* call this
	
	char* errmsg;
	if(old_execvp==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		if(handle !=NULL)
		{
			dlerror();
			*(void**)(&old_execvp) =dlsym(handle, "execvp");
		}
	}
	int ret_val;//return value
	if(old_execvp !=NULL)
	{

		fprintf(out, "[monitor] execvp('%s','%s'", filename, argv[0]);
		for(int q=1; argv[q]; q++)
			fprintf(out,", '%s'",argv[q]);
		fprintf(out, ")\n");
		ret_val=old_execvp(filename,argv);
		if(ret_val==-1)
		{
			
			fprintf(out, "[monitor] execvp('%s','%s'", filename, argv[0]);
			for(int q=1; argv[q]; q++)
				fprintf(out,", '%s'",argv[q]);
			fprintf(out, ") = -1\n");
			return ret_val;
		}

	}
	else 
		fprintf(out,"---[monitor]old_execvp is NULL");
//	return ret_val;
}
extern "C" int execv(const char *path, char *const argv[]) {//some other exec* call this
	
	char* errmsg;
	if(old_execv==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		if(handle !=NULL)
		{
			dlerror();
			*(void**)(&old_execv) =dlsym(handle, "execv");
		}
	}
	int ret_val;//return value
	if(old_execv !=NULL)
	{

		fprintf(out, "[monitor] execv(path:'%s','%s'", path, argv[0]);
		for(int q=1; argv[q]; q++)
			fprintf(out,", '%s'",argv[q]);
		fprintf(out, ")\n");
		ret_val=old_execv(path,argv);
		if(ret_val==-1)
		{
			
			fprintf(out, "[monitor] execv('%s','%s'", path, argv[0]);
			for(int q=1; argv[q]; q++)
				fprintf(out,", '%s'",argv[q]);
			fprintf(out, ") = -1\n");
			return ret_val;
		}

	}
	else 
		fprintf(out,"---[monitor]old_execv is NULL");
//	return ret_val;
}
//ROW6
extern "C" int fchown(int fd, uid_t owner, gid_t group) {

	char* errmsg;
	if(old_fchown==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		if(handle !=NULL)
		{
			dlerror();
			*(void**)(&old_fchown) =dlsym(handle, "fchown");
		}
	}
	int ret_val;//return value
	if(old_fchown !=NULL)
	{
		ret_val=old_fchown(fd, owner, group);
		fprintf(out, "[monitor] fchown(%d, %d, %d) = %d\n", fd, owner, group, ret_val);
	}
	else 
		fprintf(out,"---[monitor]old_fchown is NULL");
	return ret_val;
}
extern "C" int fork(void) {
	
	char* errmsg;
	if(old_fork==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		if(handle !=NULL)
		{
			dlerror();
			*(void**)(&old_fork) =dlsym(handle, "fork");
		}
	}
	int ret_val;//return value
	if(old_fork !=NULL)
	{
		ret_val=old_fork();
		if(ret_val>0)
			fprintf(out, "[monitor] fork() = %d\n", ret_val);
	}
	else 
		fprintf(out,"---[monitor]old_fork is NULL");
	return ret_val;

}
extern "C" int fsync(int fd) {

	char* errmsg;
	if(old_fsync==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		if(handle !=NULL)
		{
			dlerror();
			*(void**)(&old_fsync) =dlsym(handle, "fsync");
		}
	}
	int ret_val;//return value
	if(old_fsync !=NULL)
	{
		ret_val=old_fsync(fd);
		fprintf(out, "[monitor] fsynci(%d) = %d\n", fd,ret_val);
	}
	else 
		fprintf(out,"---[monitor]old_fsync is NULL");
	return ret_val;
}
extern "C" int ftruncate(int fd, off_t length) {

	char* errmsg;
	if(old_ftruncate==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		if(handle !=NULL)
		{
			dlerror();
			*(void**)(&old_ftruncate) =dlsym(handle, "ftruncate");
		}
	}
	int ret_val;//return value
	if(old_ftruncate !=NULL)
	{
		ret_val=old_ftruncate(fd,length);
		fprintf(out, "[monitor] ftruncate(%d, %ld) = %d\n", fd, length, ret_val);
	}
	else 
		fprintf(out,"---[monitor]old_ftruncate is NULL");
	return ret_val;
}
extern "C" char *getcwd(char *buf, size_t size) {

	char* errmsg;
	if(old_getcwd==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		if(handle !=NULL)
		{
			dlerror();
			*(void**)(&old_getcwd) =dlsym(handle, "getcwd");
		}
	}
	char *ret_val;//return value
	if(old_getcwd !=NULL)
	{
		ret_val=old_getcwd(buf,size);
		fprintf(out, "[monitor] getcwd('%s',%lu) = '%s'\n", buf, size, ret_val);
	}
	else 
		fprintf(out,"---[monitor]old_getcwd is NULL");
	return ret_val;
}
extern "C" gid_t getegid(void) {
	char* errmsg;
	if(old_getegid==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		if(handle !=NULL)
		{
			dlerror();
			*(void**)(&old_getegid) =dlsym(handle, "getegid");
		}
	}
	gid_t ret_val;//return value
	if(old_getegid !=NULL)
	{
		ret_val=old_getegid();
		fprintf(out, "[monitor] getegidi() = %d\n",ret_val);
	}
	else 
		fprintf(out,"---[monitor]old_getegid is NULL");
	return ret_val;

}
extern "C" uid_t geteuid(void) {
	char* errmsg;
	if(old_geteuid==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		if(handle !=NULL)
		{
			dlerror();
			*(void**)(&old_geteuid) =dlsym(handle, "geteuid");
		}
	}
	uid_t ret_val;//return value
	if(old_geteuid !=NULL)
	{
		ret_val=old_geteuid();
		struct passwd *p = getpwuid(ret_val);
		fprintf(out, "[monitor] getuid() = %s\n", p->pw_name);
	}
	else 
		fprintf(out,"---[monitor]old_geteuid is NULL");
	return ret_val;

}
extern "C" gid_t getgid(void) {
	char* errmsg;
	if(old_getgid==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		if(handle !=NULL)
		{
			dlerror();
			*(void**)(&old_getgid) =dlsym(handle, "getgid");
		}
	}
	gid_t ret_val;//return value
	if(old_getgid !=NULL)
	{
		ret_val=old_getgid();
		fprintf(out, "[monitor] getgid() = %d\n",ret_val);
	}
	else 
		fprintf(out,"---[monitor]old_getgid is NULL");
	return ret_val;

}
//ROW7
extern "C" int link(const char *oldpath, const char *newpath) {

	char* errmsg;
	if(old_link==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		if(handle !=NULL)
		{
			*(void**)(&old_link) =dlsym(handle, "link");
		}
	}
	int ret_val;//return value
	if(old_link !=NULL)
	{
		ret_val=old_link(oldpath, newpath);
		fprintf(out, "[monitor] link('%s', '%s') = %d\n", oldpath, newpath, ret_val);
	}
	else 
		fprintf(out,"---[monitor]old_link is NULL");
	return ret_val;
}
extern "C" int pipe(int pipefd[2]) {
	
	char* errmsg;
	if(old_pipe==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		if(handle !=NULL)
		{
			*(void**)(&old_pipe) =dlsym(handle, "pipe");
		}
	}
	int ret_val;//return value
	if(old_pipe !=NULL)
	{
		ret_val=old_pipe(pipefd);
		fprintf(out, "[monitor] pipe(%d, %d) = %d\n", pipefd[0], pipefd[1], ret_val);
	}
	else 
		fprintf(out,"---[monitor]old_pipe is NULL");
	return ret_val;


}
extern "C" ssize_t pread(int fd, void *buf, size_t count, off_t offset)
{

	char* errmsg;
	if(old_pread==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		if(handle !=NULL)
		{
			*(void**)(&old_pread) =dlsym(handle, "pread");
		}
	}
	ssize_t ret_val;//return value
	if(old_pread !=NULL)
	{
		ret_val=old_pread(fd, buf, count, offset);
		fprintf(out, "[monitor] pread(%d, %p, %lu, %ld) = %ld\n", fd, buf, count, offset, ret_val);
	}
	else 
		fprintf(out,"---[monitor]old_pread is NULL");
	return ret_val;
}
extern "C" ssize_t pwrite(int fd,const void *buf, size_t count, off_t offset)
{

	char* errmsg;
	if(old_pwrite==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		if(handle !=NULL)
		{
			*(void**)(&old_pwrite) =dlsym(handle, "pwrite");
		}
	}
	int ret_val;//return value
	if(old_pwrite !=NULL)
	{
		ret_val=old_pwrite(fd, buf, count, offset);
		fprintf(out, "[monitor] pwrite(%d, %p, %lu, %ld) = %d\n", fd, buf, count, offset, ret_val);
	}
	else 
		fprintf(out,"---[monitor]old_pwrite is NULL");
	return ret_val;
}
extern "C" ssize_t read(int fd, void *buf, size_t count)
{

	char* errmsg;
	if(old_read==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		if(handle !=NULL)
		{
			*(void**)(&old_read) =dlsym(handle, "read");
		}
	}
	int ret_val;//return value
	if(old_read !=NULL)
	{
		ret_val=old_read(fd, buf, count);
		fprintf(out, "[monitor] read(%d, %p, %lu) = %d\n", fd, buf, count, ret_val);
	}
	else 
		fprintf(out,"---[monitor]old_read is NULL");
	return ret_val;
}
extern "C" ssize_t write(int fd,const void *buf, size_t count)
{

	char* errmsg;
	if(old_write==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		if(handle !=NULL)
		{
			*(void**)(&old_write) =dlsym(handle, "write");
		}
	}
	int ret_val;//return value
	if(old_write !=NULL)
	{
		ret_val=old_write(fd, buf, count);
		fprintf(out, "[monitor] write(%d, '%s', %lu) = %d\n", fd, buf, count, ret_val);
	}
	else 
		fprintf(out,"---[monitor]old_write is NULL");
	return ret_val;
}
extern "C" ssize_t readlinklink(const char *path, char *buf, size_t bufsiz) {

	char* errmsg;
	if(old_readlink==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		if(handle !=NULL)
		{
			*(void**)(&old_readlink) =dlsym(handle, "readlink");
		}
	}
	int ret_val;//return value
	if(old_readlink !=NULL)
	{
		ret_val=old_readlink(path, buf, bufsiz);
		fprintf(out, "[monitor] readlink('%s', '%s', %lu) = %d\n", path, buf, bufsiz, ret_val);
	}
	else 
		fprintf(out,"---[monitor]old_readlink is NULL");
	return ret_val;
}
extern int rmdir(const char *path) {

	char* errmsg;
	if(old_rmdir==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		if(handle !=NULL)
		{
			dlerror();
			*(void**)(&old_rmdir) =dlsym(handle, "rmdir");
		}
	}
	int ret_val;//return value
	if(old_rmdir !=NULL)
	{
		ret_val=old_rmdir(path);
		fprintf(out, "[monitor] rmdir('%s') = %d\n",path, ret_val);
	}
	else 
		fprintf(out,"---[monitor]old_rmdir is NULL");
	return ret_val;

}
extern "C" int seteuid(uid_t euid) {

	char* errmsg;
	if(old_seteuid==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		if(handle !=NULL)
		{
			dlerror();
			*(void**)(&old_seteuid) =dlsym(handle, "seteuid");
		}
	}
	int ret_val;//return value
	if(old_seteuid !=NULL)
	{
		ret_val=old_seteuid(euid);
		fprintf(out, "[monitor] seteuid(%d) = %d\n",euid, ret_val);
	}
	else 
		fprintf(out,"---[monitor]old_seteuid is NULL");
	return ret_val;

}
extern "C" int setegid(gid_t egid) {

	char* errmsg;
	if(old_setegid==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		if(handle !=NULL)
		{
			dlerror();
			*(void**)(&old_setegid) =dlsym(handle, "setegid");
		}
	}
	int ret_val;//return value
	if(old_setegid !=NULL)
	{
		ret_val=old_setegid(egid);
		fprintf(out, "[monitor] setegid(%d) = %d\n",egid, ret_val);
	}
	else 
		fprintf(out,"---[monitor]old_setegid is NULL");
	return ret_val;

}
extern "C" int setuid(uid_t uid) {

	char* errmsg;
	if(old_setuid==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		if(handle !=NULL)
		{
			dlerror();
			*(void**)(&old_setuid) =dlsym(handle, "setuid");
		}
	}
	int ret_val;//return value
	if(old_setuid !=NULL)
	{
		ret_val=old_setuid(uid);
		fprintf(out, "[monitor] setuid(%d) = %d\n",uid, ret_val);
	}
	else 
		fprintf(out,"---[monitor]old_setuid is NULL");
	return ret_val;

}
extern "C" int setgid(gid_t gid) {

	char* errmsg;
	if(old_setgid==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		if(handle !=NULL)
		{
			dlerror();
			*(void**)(&old_setgid) =dlsym(handle, "setgid");
		}
	}
	int ret_val;//return value
	if(old_setgid !=NULL)
	{
		ret_val=old_setgid(gid);
		fprintf(out, "[monitor] setgid(%d) = %d\n",gid, ret_val);
	}
	else 
		fprintf(out,"---[monitor]old_setgid is NULL");
	return ret_val;

}
extern "C"  unsigned int sleep(unsigned int seconds) {

	char* errmsg;
	if(old_sleep==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		if(handle !=NULL)
		{
			dlerror();
			*(void**)(&old_sleep) =dlsym(handle, "sleep");
		}
	}
	unsigned int ret_val;//return value
	if(old_sleep !=NULL)
	{
		ret_val=old_sleep(seconds);
		fprintf(out, "[monitor] sleep(%u) = %u\n",seconds, ret_val);
	}
	else 
		fprintf(out,"---[monitor]old_sleep is NULL");
	return ret_val;
}
int nanosleep(const struct timespec *req, const struct timespec *rem) {//?
	char* errmsg;
	if(old_nanosleep==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		if(handle !=NULL)
		{
			dlerror();
			*(void**)(&old_nanosleep) =dlsym(handle, "nanosleep");
		}
	}
	int ret_val;//return value
	if(old_nanosleep !=NULL)
	{
		ret_val=old_nanosleep(req,rem);
		fprintf(out, "[monitor] nanosleep(%p, %p) = %u\n", req, rem, ret_val);
	}
	else 
		fprintf(out,"---[monitor]old_nanosleep is NULL");
	return ret_val;
}
extern "C" int symlink(const char *dir, const char *pfx) {

	char* errmsg;
	if(old_symlink==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		if(handle !=NULL)
		{
			*(void**)(&old_symlink) =dlsym(handle, "symlink");
		}
	}
	int ret_val;//return value
	if(old_symlink !=NULL)
	{
		ret_val=old_symlink(dir,pfx);
		fprintf(out, "[monitor] symlink('%s', '%s') = %d\n", dir, pfx, ret_val);
	}
	else 
		fprintf(out,"---[monitor]old_symlink is NULL");
	return ret_val;
}
extern "C" int unlink(const char *pathname) {

	char* errmsg;
	if(old_unlink==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		if(handle !=NULL)
		{
			dlerror();
			*(void**)(&old_unlink) =dlsym(handle, "unlink");
		}
	}
	int ret_val;//return value
	if(old_unlink !=NULL)
	{
		ret_val=old_unlink(pathname);
		fprintf(out, "[monitor] unlink('%s') = %d\n", pathname, ret_val);
	}
	else 
		fprintf(out,"---[monitor]old_unlink is NULL");
	return ret_val;
}
extern "C" int fchmodat(int dirfd, const char *pathname, mode_t mode, int flags) {

	char* errmsg;
	if(old_fchmodat==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		if(handle !=NULL)
		{
			dlerror();
			*(void**)(&old_fchmodat) =dlsym(handle, "fchmodat");
		}
	}
	int ret_val;//return value
	if(old_fchmodat !=NULL)
	{
		ret_val=old_fchmodat(dirfd,pathname,mode,flags);
		fprintf(out, "[monitor] fchmodat(%d, '%s', %d, %d) = %d\n", dirfd, pathname, mode, flags, ret_val);
	}
	else 
		fprintf(out,"---[monitor]old_fchmodat is NULL");
	return ret_val;
}
extern "C" int chmod(const char *pathname, mode_t mode) {

	char* errmsg;
	if(old_chmod==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		if(handle !=NULL)
		{
			dlerror();
			*(void**)(&old_chmod) =dlsym(handle, "chmod");
		}
	}
	int ret_val;//return value
	if(old_chmod !=NULL)
	{
		ret_val=old_chmod(pathname,mode);
		fprintf(out, "[monitor] chmod('%s', %d) = %d\n", pathname, mode, ret_val);
	}
	else 
		fprintf(out,"---[monitor]old_chmod is NULL");
	return ret_val;

}
extern "C" int fchmod(int fd, mode_t mode) {

	char* errmsg;
	if(old_fchmod==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		if(handle !=NULL)
		{
			dlerror();
			*(void**)(&old_fchmod) =dlsym(handle, "fchmod");
		}
	}
	int ret_val;//return value
	if(old_fchmod !=NULL)
	{
		ret_val=old_fchmod(fd,mode);
		fprintf(out, "[monitor] fchmod(%d, %d) = %d\n", fd, mode, ret_val);
	}
	else 
		fprintf(out,"---[monitor]old_fchmod is NULL");
	return ret_val;

}
extern "C" int __xstat(int ver, const char * path, struct stat *stat_buf) {
	
	char* errmsg;
	if(old___xstat==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		if(handle !=NULL)
		{
			dlerror();
			*(void**)(&old___xstat) =dlsym(handle, "__xstat");
		}
	}
	int ret_val;//return value
	if(old___xstat !=NULL)
	{
		ret_val=old___xstat(ver,path,stat_buf);
		fprintf(out, "[monitor] __xstat(%d, '%s', %p) = %d\n", ver, path, stat_buf, ret_val);
	}
	else 
		fprintf(out,"---[monitor]old___xstat is NULL");
	return ret_val;
}
extern "C" int __lxstat(int ver, const char * path, struct stat *stat_buf) {
	
	char* errmsg;
	if(old___lxstat==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		if(handle !=NULL)
		{
			dlerror();
			*(void**)(&old___lxstat) =dlsym(handle, "__lxstat");
		}
	}
	int ret_val;//return value
	if(old___lxstat !=NULL)
	{
		ret_val=old___lxstat(ver,path,stat_buf);
		fprintf(out, "[monitor] __lxstat(%d, '%s', %p) = %d\n", ver, path, stat_buf, ret_val);
	}
	else 
		fprintf(out,"---[monitor]old___lxstat is NULL");
	return ret_val;
}
extern "C" int __fxstat(int ver, int path, struct stat *stat_buf) {
	
	char* errmsg;
	if(old___fxstat==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		if(handle !=NULL)
		{
			dlerror();
			*(void**)(&old___fxstat) =dlsym(handle, "__fxstat");
		}
	}
	int ret_val;//return value
	if(old___fxstat !=NULL)
	{
		ret_val=old___fxstat(ver,path,stat_buf);
		fprintf(out, "[monitor] __fxstat(%d, %d, %p) = %d\n", ver, path, stat_buf, ret_val);
	}
	else 
		fprintf(out,"---[monitor]old___fxstat is NULL");
	return ret_val;
}
extern "C" int mkdir(const char *pathname, mode_t mode) {
	
	char* errmsg;
	if(old_mkdir==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		if(handle !=NULL)
		{
			dlerror();
			*(void**)(&old_mkdir) =dlsym(handle, "mkdir");
		}
	}
	int ret_val;//return value
	if(old_mkdir !=NULL)
	{
		ret_val=old_mkdir(pathname,mode);
		fprintf(out, "[monitor] mkdir('%s', %d) = %d\n", pathname, mode, ret_val);
	}
	else 
		fprintf(out,"---[monitor]old_mkdir is NULL");
	return ret_val;
}
extern "C" int mkfifo(const char *pathname, mode_t mode) {
	char* errmsg;
	if(old_mkfifo==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		if(handle !=NULL)
		{
			dlerror();
			*(void**)(&old_mkfifo) =dlsym(handle, "mkfifo");
		}
	}
	int ret_val;//return value
	if(old_mkfifo !=NULL)
	{
		ret_val=old_mkfifo(pathname,mode);
		fprintf(out, "[monitor] mkfifo('%s', %d) = %d\n", pathname, mode, ret_val);
	}
	else 
		fprintf(out,"---[monitor]old_mkfifo is NULL");
	return ret_val;
}
extern "C" mode_t umask(mode_t mode) {

	char* errmsg;
	if(old_umask==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		if(handle !=NULL)
		{
			dlerror();
			*(void**)(&old_umask) =dlsym(handle, "umask");
		}
	}
	mode_t ret_val;//return value
	if(old_umask !=NULL)
	{
		ret_val=old_umask(mode);
		fprintf(out, "[monitor] umask(%d) = %d\n", mode, ret_val);
	}
	else 
		fprintf(out,"---[monitor]old_umask is NULL");
	return ret_val;
}
extern "C" void *realloc(void *ptr, size_t size) {

	char* errmsg;
	if(old_realloc==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		if(handle !=NULL)
		{
			dlerror();
			*(void**)(&old_realloc) =dlsym(handle, "realloc");
		}
	}
	void * ret_val;//return value
	if(old_realloc !=NULL)
	{
		ret_val=old_realloc(ptr,size);
		fprintf(out, "[monitor] realloc(%p, %ld) = %p\n", ptr, size, ret_val);
	}
	else 
		fprintf(out,"---[monitor]old_realloc is NULL");
	return ret_val;
}
extern "C" int fflush(FILE *stream) {
	char* errmsg;
	if(old_fflush==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		if(handle !=NULL)
		{
			dlerror();
			*(void**)(&old_fflush) =dlsym(handle, "fflush");
		}
	}
	int ret_val;//return value
	if(old_fflush !=NULL)
	{
		ret_val=old_fflush(stream);
		fprintf(out, "[monitor] fflush(%p) = %d\n", stream, ret_val);
	}
	else 
		fprintf(out,"---[monitor]old_fflush is NULL");
	return ret_val;
}
extern "C" int fputs_unlocked(const char *s, FILE *stream) {

	char* errmsg;
	if(old_fputs_unlocked==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		if(handle !=NULL)
		{
			dlerror();
			*(void**)(&old_fputs_unlocked) =dlsym(handle, "fputs_unlocked");
		}
	}
	int ret_val;//return value
	if(old_fputs_unlocked !=NULL)
	{
		ret_val=old_fputs_unlocked(s,stream);
		fprintf(out, "[monitor] fputs_unlocked(%s, %p) = %d\n", s, stream, ret_val);
	}
	else 
		fprintf(out,"---[monitor]old_fputs_unlocked is NULL");
	return ret_val;
}
extern "C" int __freading(FILE* stream) {

	char* errmsg;
	if(old___freading==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		if(handle !=NULL)
		{
			dlerror();
			*(void**)(&old___freading) =dlsym(handle, "__freading");
		}
	}
	int ret_val;//return value
	if(old___freading !=NULL)
	{
		ret_val=old___freading(stream);
		fprintf(out, "[monitor] __freading(%p) = %d\n", stream, ret_val);
	}
	else 
		fprintf(out,"---[monitor]old___freading is NULL");
	return ret_val;

}
/*
extern "C" void free (void *ptr) {
	
	char* errmsg;
	if(old_free==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		if(handle !=NULL)
		{
			dlerror();
			*(void**)(&old_free) =dlsym(handle, "free");
		}
	}
	//int ret_val;//return value
	if(old_free !=NULL)
	{
		fprintf(out, "[monitor] free(%p)\n", ptr);
		old_free(ptr);
	}
	else 
		fprintf(out,"---[monitor]old_free is NULL");
	//return NULL;


}*/
extern "C" void *memmove(void *dest, const void * src, size_t n) {

	char* errmsg;
	if(old_memmove==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		if(handle !=NULL)
		{
			dlerror();
			*(void**)(&old_memmove) =dlsym(handle, "memmove");
		}
	}
	void* ret_val;//return value
	if(old_memmove !=NULL)
	{
		ret_val=old_memmove(dest,src,n);
		fprintf(out, "[monitor] memmove(%p, %p, %ld) = %p\n", dest, src, n,ret_val);
	}
	else 
		fprintf(out,"---[monitor]old_memmove is NULL");
	return ret_val;

}
extern "C" int fileno(FILE* stream) {

	char* errmsg;
	if(old_fileno==NULL) {
		void *handle = dlopen("libc.so.6",RTLD_LAZY);
		errmsg=dlerror();
		if(handle !=NULL)
		{
			dlerror();
			*(void**)(&old_fileno) =dlsym(handle, "fileno");
		}
	}
	int ret_val;//return value
	if(old_fileno !=NULL)
	{
		ret_val=old_fileno(stream);
		fprintf(out, "[monitor] fileno(%p) = %d\n", stream,ret_val);
	}
	else 
		fprintf(out,"---[monitor]old_fileno is NULL");
	return ret_val;
}
