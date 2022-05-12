#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>



//and code in targets/ARCH/ETHERNET/USERSPACE/LIB/eth_raw.c
//fuction trx_eth_write_raw_IF4p5(..)

struct rcc_con_data
{
  const char *remote_ip;
  int remote_port;
};

//global variables
char **rcc_address;
int *sizeofrcc_address;
pthread_mutex_t rcc_mutex;

void trim (char *dest, char *src);


void* find_rcc_address(){
  // Print value received as argument:
  printf("Value recevied as argument in starting routine: \n");

  //char **tmp = (char **)rcc;
  //rcc_address kubernet command in order to find ips form enbs
  FILE *popen(const char *command, const char *mode);
  int pclose(FILE *stream);
  int i=0,index=0;
  FILE *cmd;
  char result[1024],cstr[1024];
 
  
  while(1)
  { 
    
    pthread_mutex_lock( &rcc_mutex);	  
    i=0,index=0;	  
    pthread_mutex_unlock( &rcc_mutex);

    printf("Try to find ips!\n");
    cmd = popen("kubectl get pods -n oai | cut -f 1 -d ' ' | grep oai-enb | xargs kubectl -n oai -o yaml get pod | grep 192.168.18", "r");
    if (cmd == NULL) 
    {
      perror("popen");
      exit(EXIT_FAILURE);
    }
    pthread_mutex_lock( &rcc_mutex);
    while (fgets(result, sizeof(result), cmd)) 
    { 
      //return two times the same ip so we use mod to read only once
      if ( i++%2 == 0)
      {
        if(index > 0)
          rcc_address = realloc( rcc_address, (index + 1) * sizeof(char*)); 	  
        
        trim(cstr,result);
        char* substr = cstr + 1;
        memmove(cstr, substr, strlen(substr) + 1);
        rcc_address[index] = malloc(20 * sizeof(char));
        strcpy(rcc_address[index++], cstr);
        //printf("%s", result);
      }
    }

    pclose(cmd);
    sizeofrcc_address = &index;
    pthread_mutex_unlock( &rcc_mutex);
    sleep(5);
  }

  //for(i=0; i<index; i++)
  //{
  //  printf("In main! rrc_addres: %s\n", rcc_address[i]);
  //}

  // Return reference to global variable:
  pthread_exit(NULL);
}


int main(void){
  // Declare variable for thread's ID:
  pthread_t id;
  //initialize
  rcc_address = malloc(1 * sizeof(char*));
  int tmp= pthread_mutex_init( &rcc_mutex, NULL );


  if(rcc_address == NULL)
  {
    printf("Memory allocation failed");
    return 0;
  }


  pthread_create(&id, NULL, find_rcc_address, NULL);
  //int* ptr;
  // Wait for foo() and retrieve value in ptr;
  //pthread_join(id, NULL);
  // printf(Value recevied by parent from child:);
  // printf(%i\n, *ptr);

  printf("exit from thread an now will terminate!\n"); 

  /*int i;
  for(i=0; i<4; i++)
  {     
    printf("In main! rcc_addres: %s\n", rcc_address[i]);
  }*/

  int random_number;
  while(1)
  {
    if (sizeofrcc_address!=NULL)
    {	   
      //printf("%u\n", *sizeofrcc_address); /* 5 */
      srand(time(0));

      pthread_mutex_lock( &rcc_mutex);
      if(*sizeofrcc_address > 0)
        random_number = rand() % (*sizeofrcc_address);
      else
	random_number = 0;

      if( rcc_address[random_number]!=NULL)
         printf("random ip : %s\n", rcc_address[random_number]);
      else
	 printf("send to standar address 192.168.18.206");
      pthread_mutex_unlock( &rcc_mutex);

      sleep(3);
    }
  }
  return 0;
}

// trim: leading and trailing whitespace of string
void trim (char *dest, char *src)
{
    if (!src || !dest)
       return;

    int len = strlen (src);

    if (!len) {
        *dest = '\0';
        return;
    }
    char *ptr = src + len - 1;

    // remove trailing whitespace
    while (ptr > src) {
        if (!isspace (*ptr))
            break;
        ptr--;
    }

    ptr++;

    char *q;
    // remove leading whitespace
    for (q = src; (q < ptr && isspace (*q)); q++)
        ;

    while (q < ptr)
        *dest++ = *q++;


    *dest = '\0';

    //remove quotes from ip
    dest[strlen(dest)-1] = 0;    
    char* substr = dest + 1;
    memmove(dest, substr, strlen(substr) + 1);
}
