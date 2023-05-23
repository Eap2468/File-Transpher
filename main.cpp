//
//  main.cpp
//  Download
//
//  Created by Ethan Phelps on 5/23/23.
//

#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include <fstream>

#define BUFFERSIZE 1024

int main(int argc, const char * argv[]) {
    const char* newFilePath = "";
    const char* ip = "";
    
    int clientfd = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(4444);
    
    int enable = 1;
    setsockopt(clientfd, SOL_SOCKET, SO_REUSEPORT, &enable, sizeof(int));
    
    connect(clientfd, (sockaddr*)&addr, sizeof(addr));
    
    std::ofstream file(newFilePath);
    char buffer[BUFFERSIZE];
    long bytes_recieved = 0;
    
    while((bytes_recieved = recv(clientfd, buffer, BUFFERSIZE, 0)) > 0)
    {
        file.write(buffer, bytes_recieved);
    }
    file.close();
    close(clientfd);
    return 0;
}
