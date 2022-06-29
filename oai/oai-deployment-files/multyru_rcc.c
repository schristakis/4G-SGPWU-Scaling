#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

//and code in targets/ARCH/ETHERNET/USERSPACE/LIB/eth_raw.c
//fuction trx_eth_write_raw_IF4p5(..)

struct rcc_con_data
{
  const char *remote_ip;
  int remote_port;
};


char **test;

void trim (char *dest, char *src);


void* find_rcc_address(){
  // Print value received as argument:
  printf("Value recevied as argument in starting routine: \n");

  //char **tmp = (char **)rcc;
  //test kubernet command in order to find ips form enbs
  FILE *popen(const char *command, const char *mode);
  int pclose(FILE *stream);
  int i=0,index=0;
  FILE *cmd;
  char result[1024],cstr[1024];
  

  cmd = popen("kubectl get pods -n oai | cut -f 1 -d ' ' | grep oai-enb | xargs kubectl -n oai -o yaml get pod | grep 192.168.18", "r");
  if (cmd == NULL) 
  {
      perror("popen");
      exit(EXIT_FAILURE);
  }
  while (fgets(result, sizeof(result), cmd)) 
  { 

    if ( i++%2 == 0)
    {
      if(index > 0)
      {
        test = realloc( test, (index + 1) * sizeof(char*)); 	  
      }

      trim(cstr,result);
      test[index] = malloc(20 * sizeof(char));
      strcpy(test[index++], cstr);
      //printf("%s", result);

    }

  }

  pclose(cmd);


  //for(i=0; i<index; i++)
  //{
  //  printf("In main! rrc_addres: %s\n", test[i]);
  //}

  // Return reference to global variable:
  pthread_exit(NULL);
}


int main(void){
  // Declare variable for thread's ID:
  pthread_t id;
  test = malloc(1 * sizeof(char*));


  if(test == NULL)
  {
    printf("Memory allocation failed");
    return 0;
  }


  pthread_create(&id, NULL, find_rcc_address, NULL);
  //int* ptr;
  // Wait for foo() and retrieve value in ptr;
  pthread_join(id, NULL);
  // printf(Value recevied by parent from child:);
  // printf(%i\n, *ptr);

  printf("exit from thread an now will terminate!\n"); 

  int i;
  for(i=0; i<4; i++)
  {     
    printf("In main! rcc_addres: %s\n", test[i]);
  }

  sleep(5);
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
}
