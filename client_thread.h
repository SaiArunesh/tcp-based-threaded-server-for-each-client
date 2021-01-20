/*    Include Files    */

#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <vector>
#include <thread>
#include <mutex>

using namespace std;

/*    Global defintions and variables    */

#define PORT 8080

/* Global variables */

mutex mtx;

/* Function declarations */

thread create_client_thread(int, int[], int, int);

void on_new_connection(int, int[], int, int);
