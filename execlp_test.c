#include <unistd.h>

int main() {
/*	char* argv[]= {"ls","-r","-t","-l",NULL};
	char* myenv[]={NULL};
	int a = execve("/bin/ls",argv,myenv);
	printf("a=%d\n",a);
*/	
	//char *env[]={"PATH=/bin",NULL};
	int r =	execlp("ls", "ls", "-r", "-t", "-l", NULL);
	printf("execlp fail\n");
	//execl("/bin/kk", "/bin/lk", "-r", "-t", "-l", NULL);
}
