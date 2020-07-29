# RPC_Election

A client/server program to simulate an election process based on [RPC](https://en.wikipedia.org/wiki/Remote_procedure_call)

## Steps to execute
-   Make sure rpcbind is installed and running:  
    `sudo apt install rpcbind`  
    `sudo rpcbind start`

-   Start the server:  
    `./election_server`

-   Start the client in a separate terminal:  
    `./election_client localhost`
