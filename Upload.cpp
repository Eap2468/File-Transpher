//
//  main.cpp
//  File transpher
//
//  Created by Ethan Phelps on 5/23/23.
//

#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include <fstream>

#define BUFFERSIZE 1024

int main(int argc, const char * argv[]) {
    const char* filePath = "";
    const char* ip = "";
    
    int serverfd = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(4444);
    socklen_t addrSize = sizeof(addr);
    
    int enable = 1;
    setsockopt(serverfd, SOL_SOCKET, SO_REUSEPORT, &enable, sizeof(int));
    
    bind(serverfd, (sockaddr*)&addr, addrSize);
    listen(serverfd, 1);
    
    std::cout << "server started" << std::endl;
    
    int clientfd = accept(serverfd, (sockaddr*)&addr, &addrSize);
    
    std::ifstream upload(filePath, std::ios::binary);
    
    char buffer[BUFFERSIZE];
    int bytes_read = 0;
    
    while((bytes_read = upload.read(buffer, BUFFERSIZE).gcount()) > 0)
    {
        if(send(clientfd, buffer, bytes_read, 0) != bytes_read)
        {
            std::cout << "Error" << std::endl;
            return -1;
        }
    }
    upload.close();
    close(clientfd);
    close(serverfd);
    return 0;
}
