/*    Include Files    */

#include <unistd.h>
#include <iostream>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <thread>
#include <vector>
#include <chrono>
#include <mutex>
#include "logger.cpp"
#include <time.h>

using namespace std;

/*    Global defintions and variables    */

#define PORT 8080

mutex mtx;
Logger *logger;

/*    Function Declarations    */

string get_current_time();

thread create_server_thread(int, char);

void on_new_connection(int, char);