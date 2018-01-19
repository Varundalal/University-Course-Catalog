Instructions to run the implementation client-server program using TCP and C language. 

The zip file contains the following file.

1.Client1.c
2.Server1.c
3.db.txt
4.readme.txt

Instructions : 

1. Unzip the advanceOSp1 file.
2. Move the Client1.c to your client ( tested on eros.cs.txstate.edu and zeus.cs.txstate.edu )
3. Move the Server1.c and db.txt or the program will create a new empty db for you, to your server ( tested on eros.cs.txstate.edu and zeus.cs.txstate.edu )
4. From console[linux]/terminal[mac]/putty[Windows] enter the following.
Commands for compiling and running server on eros.cs.txstate.edu :

$ cd (your file location)
$ gcc -o server1 server1.c
$ ./server1

Command for compiling and running client on zeus or eros : 
$ cd (your file location)
$ gcc -o client1 client1.c
$ ./client1 zeus.cs.txstate.edu (if your server is zeus)
  or
$ ./client1 eros.cs.txstate.edu (if your server is eros)

5. After successful execution the program should run on the client end.

Note 1 : Make sure that the server program is running , prior to executing the client program.

Note 2 : Search function in the program is Case Sensitive.

Note 3 : Kindly follow the in-program guidelines for the Add function.

Note 4 : Delete function in the program is Case Sensitive.





