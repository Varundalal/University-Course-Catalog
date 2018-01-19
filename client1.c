
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#define SERVER_PORT 5432
#define MAX_LINE 1024
#define len1 1024
#define L1 1024
int main(int argc, char * argv[])
{
    FILE *fp;
    struct hostent *hp;
    struct sockaddr_in sin;
    char *host;
    char buf[MAX_LINE];
    char a[len1];
    int s,new_s;
    int len;
    int l2;
    char c[L1];
    if (argc==2) {
        host = argv[1];
    }
    else {
        fprintf(stderr, "usage: simplex-talk host\n");
        exit(1);
    }
    /* translate host name into peer’s IP address */
    hp = gethostbyname(host);
    if (!hp) {
        fprintf(stderr, "simplex-talk: unknown host: %s\n", host);
        exit(1);
    }
    /* build address data structure */
    bzero((char *)&sin, sizeof(sin));
    sin.sin_family = AF_INET;
    bcopy(hp->h_addr, (char *)&sin.sin_addr, hp->h_length);
    sin.sin_port = htons(SERVER_PORT);
    /* active open */
    if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        perror("simplex-talk: socket");
        exit(1);
    }
    if (connect(s, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
        perror("simplex-talk: connect");
        close(s);
        exit(1);
    }
    /* main loop: get and send lines of text */
    
    printf("Options \n");
    printf("1. List All Records\n");
    printf("2. Search Record\n");
    printf("3. Add Record\n");
    printf("4. Delete Record\n");
    printf("Enter choice : \n");
    scanf("%d",&a);
    a[len1-1]='\0';
    l2= strlen(a)+1;
    printf("\n",a[0]);
    send(s,a,l2,0);
    switch(a[0])
    {
        case 1 :
                recv(s, c, sizeof(c), 0);
                printf("%s",c);
                c[0]='\0';
                break;
        case 2 :
            printf("\n Enter the course to be searched :");
            scanf("%s",buf);
            buf[MAX_LINE-1]= '\0';
            len = strlen(buf) + 1;
            send(s, buf, len, 0);
            recv(s, c, sizeof(c), 0);
            printf("%s",c);
            c[0]='\0';
            break;
        case 3:
            printf("\n Enter the records to be added as Course Name, Course ID,Registered, Vacancies, Semester :");
            scanf("%s",&buf);
            send(s, buf, sizeof(buf), 0);
            break;
        case 4:
            printf("\n Enter the course name to be deleted:");
            scanf("%s",buf);
            buf[MAX_LINE-1]= '\0';
            len = strlen(buf) + 1;
            send(s, buf, len, 0);
            break;

        default : printf("Error Client");
    }
    close(s);
    
}































