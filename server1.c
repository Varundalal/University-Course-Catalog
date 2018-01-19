#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#define SERVER_PORT 5432
#define MAX_PENDING 5
#define MAX_LINE 1024
#define L1 1024



void search_File(char x[1024]);
void add_to_file(char y[1024]);
void delete_from_file(char z[1024]);

char buf[MAX_LINE];
char c[L1];
int len;
int s, new_s;

int main()
{
    struct sockaddr_in sin;
    size_t nread;
    
   
    /* build address data structure */
    bzero((char *)&sin, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(SERVER_PORT);
    /* setup passive open */
    if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        perror("simplex-talk: socket");
        exit(1);
    }
    if ((bind(s, (struct sockaddr *)&sin, sizeof(sin))) < 0) {
        perror("simplex-talk: bind");
        exit(1);
    }
    listen(s, MAX_PENDING);
    /* wait for connection, then receive and print text */
    
    while(1) {
                if ((new_s = accept(s, (struct sockaddr *)&sin, &len)) < 0) {
            perror("simplex-talk: accept");
            exit(1);
        }
        recv(new_s, c, sizeof(c), 0);
        switch(c[0])
        {
                
            case 1 :
                    {
                         FILE *fp;
                        char c1[1024];
                         fp=fopen("db.txt","r");
                         if(fp == NULL)
                        {
                         strcpy(buf,"Error no file to open");
                         buf[MAX_LINE-1]= '\0';
                         send(new_s, buf, sizeof(buf), 0);
                         exit(0);
                        }
                      
                        while( fgets(c1,sizeof(c1),fp))
                        {
                            strcat(buf,c1);
                        }
                        buf[MAX_LINE-1]= '\0';
                        send(new_s, buf, sizeof(buf), 0);
                        fclose(fp);
                    }
                break;
            case 2 :
                recv(new_s, buf, sizeof(buf), 0);
                search_File(buf);
                buf[0]='\0';
                break;
            case 3 :
                recv(new_s, buf, sizeof(buf), 0);
                printf("Incoming");
                add_to_file(buf);
                buf[0]='\0';
               
                break;
            case 4 :
                recv(new_s, buf, sizeof(buf), 0);
                delete_from_file(buf);
                buf[0]='\0';
               
                break;
                
                default : printf("Error Server");
        }
        
        
        
            close(new_s);
        
    }
    
    
    return 0;
    
}
void search_File(char x[1024])
{
   
    
    char temp[1024];
    
    FILE *fp=fopen("db.txt","r");
    
    //fgets is a function which takes a //line input from a file till a new line //character fgets(char[ ],int,FILE *)
    while(fgets(temp,sizeof(temp),fp))
    {
        strstr( temp ,x);
        if(strstr( temp ,x))
        {
            strcat(buf,temp);
            buf[MAX_LINE-1]= '\0';
            len = strlen(buf) + 1;
            send(new_s, buf, sizeof(buf), 0);
            exit(0);
        }
    }
    //Close the file if still open.
    if(fp) {
        fclose(fp);
    }
   	
}

void add_to_file(char y[1024])
{
    FILE *fp = fopen("db.txt","a");

    fprintf(fp,"\r%s",y);
    printf("Buffer value is:%s",&y);
    fclose(fp);
}

void delete_from_file(char z[1024])
{
    FILE *fileptr1, *fileptr2;
    //open file in read mode
    fileptr1 = fopen("db.txt", "r");
    fileptr2 = fopen("replica.txt", "w+");
    int linecount=0;

    char temp1[1024];
    while(fgets(temp1,sizeof(temp1),fileptr1))
    {
        if(!strstr(temp1,z))
        {
            fprintf(fileptr2,"%s",temp1);
        }
        
        linecount++;
    }
    
    remove("db.txt");
    //rename the file replica.c to original name
    rename("replica.txt", "db.txt");
    fclose(fileptr1);
    fclose(fileptr2);
}
































