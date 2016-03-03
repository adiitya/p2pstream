# p2pstream
This project is a peer to peer live streaming application software that uses centralized peer to
peer architecture operating on an unstructured network topology. It is implemented in c++ using raw c++ scokets and uses pthread library for `Multithreading`.
p2pstream uses `peer-to-peer` paradigm on top of the `client-server` model which explains how a peer is both a client and a server. 
### Architecture
#### Model: 
* A central server listening for any request for a file from any peer(Client). It responds with the IP addresses of all the peers having the requested file, by looking up a map of file to IPs. While responding 

* The client then connects to these peers and starts downloading. 

* The peers online when requested for a file, responds with the file. _A peer can serve multiple peers at the same time and can also download packets for streaming for itself._

### Classes
p2pstream uses OOP paradigm.




### Installation : 
	 git clone https://github.com/adiitya/p2pstream.git
	 cd ./p2pstream
	 make
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

### Contribution
Feel free to file [issues](https://github.com/adiitya/p2pstream/issues) and submit [pull requests](https://github.com/adiitya/p2pstream/pulls) – contributions are welcome.

### License:
p2pstream is licensed under the [MIT License](aditya.mit-license.org).