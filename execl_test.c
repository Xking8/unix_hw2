#include <unistd.h>

int main() {
/*	char* argv[]= {"ls","-r","-t","-l",NULL};
	char* myenv[]={NULL};
	int a = execve("/bin/ls",argv,myenv);
	printf("a=%d\n",a);
*/	
	execl("/bin/ls", "/bin/ls", "-r", "-t", "-l", NULL);
	//execl("/bin/kk", "/bin/lk", "-r", "-t", "-l", NULL);
}
