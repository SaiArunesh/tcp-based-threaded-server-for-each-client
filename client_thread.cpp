/*    Include Files    */

#include "client_thread.h"

/*************************************************************************
    Name: create_client_thread()
    Function: creates a new client thread
    Args: socket id, array to be sent, number of newly connected client, 
            size of array
    Returns: thread
*************************************************************************/

thread create_client_thread(int new_socket, int a[], int client_no, int size = 10)
{
    thread t(on_new_connection, new_socket, a, client_no, size);
    return t;
}

/*************************************************************************
    Name: on_new_connection()
    Function: Client thread
    Args: socket id, array to be sent, client number, size of array
    Returns: nil
*************************************************************************/

void on_new_connection(int sock, int a[], int client_no, int size = 10)
{
    int buffer[1024] = {0};

    while (1)
    {
        send(sock, a, size * sizeof(int), 0);

        mtx.lock();
        cout << "ECU_Client" << client_no << "  Array sent\t\t\t";
        for (int i = 0; i < 10; i++)
            cout << a[i] << "  ";
        int valread = read(sock, &buffer, 1024);
        cout << "\nECU_Client" << client_no << "  Even numbers received\t";
        for (int i = 0; i < valread / sizeof(buffer[0]); i++)
            cout << buffer[i] << " ";
        cout << endl;
        mtx.unlock();
        this_thread::sleep_for(chrono::seconds(3));
    }
}

int main(int argc, char const *argv[])
{
    int sock = 0, valread;
    struct sockaddr_in serv_addr;

    int client_count = 0;

    vector<thread> thread_list;
    int a[10], b[10], c[10];

    for (int i = 0; i < 10; i++)
        a[i] = i + 12;
    for (int i = 0; i < 10; i++)
        b[i] = i + 21;
    for (int i = 0; i < 10; i++)
        c[i] = i + 39;

    while (client_count <= 2)
    {
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            cout << endl
                 << "Socket creation error" << endl;
            return -1;
        }

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(PORT);

        if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
        {
            cout << endl
                 << "Invalid address/ Address not supported" << endl;
            return -1;
        }
        if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        {
            sleep(1);

            continue;
        }
        switch (client_count)
        {
        case 0:
            thread_list.push_back(create_client_thread(sock, a, client_count + 1, 10));
            break;

        case 1:
            thread_list.push_back(create_client_thread(sock, b, client_count + 1, 10));
            break;
        case 2:
            thread_list.push_back(create_client_thread(sock, c, client_count + 1, 10));
            break;
        }
        client_count++;
    }

    for (auto t = thread_list.begin(); t != thread_list.end(); t++)
        t->join();

    return 0;
}
