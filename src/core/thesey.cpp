#include "thesey.h"

#include <vector>
#include <iostream>
#include <thread>

#include "sys/socket.h"

#include "pgpx/frontend.h"

const size_t THESEY_WORKER_THDS_CNT = 1 << 1;


class Accepter {
protected:
    int fd;

public:
    Accepter(int fd) : fd(fd) {
    }

    void run() {
        while (1/*  TBD: soft exit */) {

        }
    }

};

void thesey_run(void) {

    std::vector<std::thread> w;
    auto domain = AF_INET;
    auto type = SOCK_STREAM;
    auto protocol = 0; /* IP */
    /* domain AF_INET/AF_INET_6*/
    int sockfd = socket(domain, type, protocol);
    if (sockfd == -1) {
        /* bad */
        return;
    }

    w.push_back(std::thread([sockfd](){
        auto backlog = 128;
        auto rc = listen(sockfd, backlog);
        while (1 /*TBD: soft exit*/) {
            auto clientfd = accept(sockfd, NULL, NULL);
            /* schedule */
            /* TBD: fiber create etc ... */
            thesey_frontend(clientfd);
        }
    }));

    for (size_t i = 0; i < THESEY_WORKER_THDS_CNT; ++ i) {
        w.push_back(std::thread([sockfd] () {
            Accepter(sockfd).run();
        }));
    }
    

    for (size_t i = 0; i < THESEY_WORKER_THDS_CNT; ++ i) {
        w[i].join();
    }
}