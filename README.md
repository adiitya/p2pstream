# p2pstream
This project is a peer to peer live streaming application software that uses centralized peer to
peer architecture operating on an unstructured network topology. It is implemented in c++ using raw c++ sockets and uses pthread library for `Multithreading`.
p2pstream uses `peer-to-peer` paradigm on top of the `client-server` model which explains how a peer is both a client and a server. 

### Installation : 
	 git clone https://github.com/adiitya/p2pstream.git
	 cd ./p2pstream
	 make
_Note_: libvlc, SFML, pthread libraries should be installed before installing this.
### How it works: 
1. Start the centralServer - The backbone of the model.
```sh
        ./central <Own_IP/IP_of_central_server>
```
2. Start the Peer(Client + Server)
```sh
		./server <Own_IP>
		./client <IP_of_centralServer>
```		
_Note :_ For now the user need to manually enter the the File to IP mapping (i.e Name of file ---> IP address of peers having the file - space separated).
### Architecture
#### Model: 
* A central server listening for any request for a file from any peer(Client). It responds with the IP addresses of all the peers having the requested file, by looking up a map of file to IPs. While responding 

* The client then connects to these peers and starts downloading. 

* The peers online when requested for a file, responds with the file. _A peer can serve multiple peers at the same time and can also download packets for streaming for itself._
_Note_: The files to be served by a peer, should be in the server directory.

### Classes
p2pstream uses OOP paradigm.

##### These are the core classes used by all the peer classes
`Connection` class is used by all the peers to establish connection with central-server or any other other peer. 
* When a peer wants to connect to another peer, this class needs the IP address and port of the peer to connect and create a connection object. 
* Since a peer can act as both clinet/server so,  when a peer is listening for connections( Server part of a peer),the class takes a sockid as argument and creates a connection object with that peer for futher interactions. This peer can serve other peers on a different `thread` at the same time.

The `Data` class handles all the work related to reading and writing data:

`Data` will always transferred as stream of bytes. During sending/receiving it may be either a string (Eg. while searching for contents over various peers like movie or content name or any query to central server) or it can be a file to be downloaded or uploaded. 
So we have two derived data classes : `BufferData` and `FileData` inheriting Data class: 
So for sending or recieving as string we create a bufferData class object
```cpp 
	Data* dataObj = new BufferData(char_array, size_of_array);
```
And for sedning and recieving on or from a file simply creating a FileData object.
```cpp 
    Data* dataObj = new FileData(name_of_file, FileData::FTYPE::READ);
```
For reading and writing we just need to call the same functions of the Data class(The parent class)
For sending or receiving, we will use the object of the `connection` class which takes as argument a `Data` object. So basically it can take any of the two data types defined above and handles them accordingly.

#### UML Diagram
![uml classes](http://i.imgur.com/EI1FBSZ.jpg?1)

#### Implementation
* p2pstream is implemented using raw C++ sockets.
* It uses `pthread` library for Multithreading.
* It uses `libvlc` for processing the data-received.
* `SFML` is used for rendering the interface.

#### Demo
1. Request by one `Peer` with IP of central-server(Peer asked for the file to be downloaded):
![client](http://i.imgur.com/9j3mOpq.png?1)
2. Response by `central-server` with the list of IPs having file:
![central](http://i.imgur.com/pmTBVME.png?1)
3. Response by another `peer` with the file:
![server](http://i.imgur.com/slT6joq.png?1)
The test was successful with a `peer` serving `multiple peers` and downloading packets at the same time.
4. Streaming video in `SFML Player`
![screen](http://i.imgur.com/dR3yNF5.png)

### Contribution
Feel free to file [issues](https://github.com/adiitya/p2pstream/issues) and submit [pull requests](https://github.com/adiitya/p2pstream/pulls) – contributions are welcome.

### License:
p2pstream is licensed under the [MIT License](http://aditya.mit-license.org).
