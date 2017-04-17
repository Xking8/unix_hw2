#include <unistd.h>

int main() {
	char* argv[]= {"/bin/ls","-r","-t","-l",NULL};
	//char* myenv[]={NULL};
	int a = execv("/bin/ls",argv);
	printf("a=%d\n",a);
	
	//char *env[]={"PATH=/bin",NULL};
//	int r =	execlp("ls", "ls", "-r", "-t", "-l", NULL);
	printf("execv fail\n");
	//execl("/bin/kk", "/bin/lk", "-r", "-t", "-l", NULL);
}
