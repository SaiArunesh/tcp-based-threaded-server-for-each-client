/*    Include Files    */

#include "server.h"

/*************************************************************************
    Name: get_current_time()
    Function: return current time in HH::MM::SS DD/MM/YYYY format
    Args: nil
    Returns: string
*************************************************************************/

string get_current_time()
{
	time_t my_time = time(NULL);
	char current_time[80];
	strftime(current_time, 80, "%H:%M:%S %d/%m/%Y", localtime(&my_time));
	return string(current_time);
}

/*************************************************************************
    Name: create_server_thread()
    Function: creates a new server thread
    Args: socket id, number of newly connected client
    Returns: thread
*************************************************************************/

thread create_server_thread(int new_socket, char i)
{
	thread t(on_new_connection, new_socket, i);
	return t;
}

/*************************************************************************
    Name: on_new_connection()
    Function: Server thread
    Args: socket id, client number
    Returns: nil
*************************************************************************/

void on_new_connection(int new_socket, char i)
{

	/*cout << endl
		 << "thread id = \t" << this_thread::get_id() << endl;
	cout << "Socket no = \t" << new_socket << endl;*/

	int buffer[1024] = {0};
	int valread, size, even_count;
	string fprint;

	fprint.clear();
	fprint += "\nECU_Client" + to_string(i) + " connnected\n";

	mtx.lock();

	cout << fprint << endl;

	logger->file_print(fprint);

	mtx.unlock();

	fprint.clear();

	while (1)
	{
		valread = recv(new_socket, buffer, 1024, 0);

		if (valread == 0)
		{
			fprint += "\nECU_Client" + to_string(i) + "  disconnected";

			mtx.lock();

			logger->file_print(fprint);

			cout << fprint << endl;

			mtx.unlock();

			fprint.clear();

			break;
		}

		size = valread / sizeof(int);

		even_count = 0;

		fprint += "ECU_Client" + to_string(i) + "  ";

		for (int i = 0; i < size; i++)
		{
			fprint += to_string(buffer[i]) + "  ";
			if (buffer[i] % 2 == 0)
				even_count++;
		}

		int even[even_count];

		for (int i = 0, j = 0; i < size; i++)
		{
			if (buffer[i] % 2 == 0)
				even[j++] = buffer[i];
		}

		fprint += get_current_time();

		mtx.lock();

		logger->file_print(fprint);

		cout << fprint << endl;

		mtx.unlock();

		fprint.clear();

		send(new_socket, &even, sizeof(even), 0);

		this_thread::sleep_for(chrono::seconds(3));
	}
	close(new_socket);
}

int main(int argc, char const *argv[])
{
	int server_fd, new_socket;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);

	string fprint;

	int i = 0;

	logger = logger->get_instance();

	vector<thread> thread_list;

	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	// Forcefully attaching socket to the port 8080
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	// Forcefully attaching socket to the port 8080
	if (bind(server_fd, (struct sockaddr *)&address,
			 sizeof(address)) < 0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

	if (listen(server_fd, 3) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}

	while (i <= 2)
	{
		if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
		{
			perror("accept");
			exit(EXIT_FAILURE);
		}
		if (i == 0)
		{
			fprint += "Server Opened at " + get_current_time() + "\n";
			logger->file_print(fprint);

			cout << fprint << endl;

			fprint.clear();
		}
		i++;
		thread_list.push_back(create_server_thread(new_socket, i));
	}

	for (auto t = thread_list.begin(); t != thread_list.end(); t++)
		t->join();

	fprint += "\nServer Closed at " + get_current_time();
	logger->file_print(fprint);

	cout << fprint << endl;

	fprint.clear();

	return 0;
}
