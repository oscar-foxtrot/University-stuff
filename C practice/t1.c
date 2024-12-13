#include <sys/epoll.h>
#include <sys/signalfd.h>
#include <signal.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/timerfd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main() {
	signal(SIGPIPE, SIG_IGN);

	sigset_t ss;
	sigemptyset(&ss);
	sigaddset(&ss, SIGINT);
	sigprocmask(SIG_BLOCK, &ss, NULL);
	int sfd = signalfd(-1, &ss, SFD_NONBLOCK);
	
	int tfd = timerfd_create(CLOCK_REALTIME, TFD_NONBLOCK);
	struct itimerspec its = { .it_interval = { .tv_sec = 1, .tv_nsec = 0 }, \
		.it_value = { .tv_sec = 1, .tv_nsec = 0 } };
	timerfd_settime(tfd, 0, &its, NULL);

	{
		int cur = fcntl(0, F_GETFL);
		fcntl(0, F_SETFL, cur | O_NONBLOCK);
	}
	
	int afd = socket(PF_INET, SOCK_STREAM, 0);
	{
		int val = 1;
		setsockopt(afd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
		struct sockaddr_in sin;
		sin.sin_family = AF_INET;
		sin.sin_addr.s_addr = INADDR_ANY;
		sin.sin_port = htons(55234);
		bind(afd, (struct sockaddr*)&sin, sizeof(sin));
		listen(afd, 5);
		int cur = fcntl(afd, F_GETFL);
		fcntl(afd, F_SETFL, cur | O_NONBLOCK);
	}


	int efd = epoll_create1(0);
	{
		struct epoll_event ev = { .events = EPOLLIN, .data = { .fd = sfd } };
		epoll_ctl(efd, EPOLL_CTL_ADD, sfd, &ev);
	}
	{
		struct epoll_event ev = { .events = EPOLLIN, .data = { .fd = tfd } };
		epoll_ctl(efd, EPOLL_CTL_ADD, tfd, &ev);
	}
	{
		struct epoll_event ev = { .events = EPOLLIN, .data = { .fd = 0 } };
		epoll_ctl(efd, EPOLL_CTL_ADD, 0, &ev);
	}
	{
        struct epoll_event ev = { .events = EPOLLIN, .data = { .fd = afd } };
        epoll_ctl(efd, EPOLL_CTL_ADD, afd, &ev);
    }

	while (1) {
		enum { WSIZE = 16 };
		struct epoll_event evs[WSIZE];
		int r = epoll_wait(efd, evs, WSIZE, -1);
		for (int i = 0; i < r; ++i) {
			struct epoll_event *pev = &evs[i];
			if ((pev->events & EPOLLIN) && (pev->data.fd == sfd)) {
				struct signalfd_siginfo sss;
				while (1) {
					int rr = read(sfd, &sss, sizeof(sss));
					if (rr < 0 && errno == EAGAIN) {
						break;
					}
					printf("Signal received: %d\n", rr);
				}
			} else if ((pev->events & EPOLLIN) && (pev->data.fd == tfd)) {
				while (1) {
					uint64_t val;
					int rr = read(tfd, &val, sizeof(val));
					if (rr < 0 && errno == EAGAIN) {
						break;
					}
					printf("Timer alert\n");
				}
			} else if ((pev->events & EPOLLIN) && (pev->data.fd == 0)) {
				while (1) {
					char buf[64];
					int z = read(0, buf, sizeof(buf) - 1);
					if (z < 0 && errno == EAGAIN) {
						break;
					}
					buf[z] = 0;
					printf("command: %s", buf);
					if (!strcmp(buf, "exit\n")) { 
						exit(0);
					}
				}
			} else if ((pev->events & EPOLLIN) && (pev->data.fd == afd)) {
                while (1) {
					struct sockaddr_in new_addr;
					socklen_t new_len = sizeof(struct sockaddr_in);
					int cfd = accept(afd, (struct sockaddr*)&new_addr, &new_len);
					if (cfd < 0 && errno == EAGAIN) {
						break;
					}
					printf("connected: %s %d\n", inet_ntoa(new_addr.sin_addr), \
						ntohs(new_addr.sin_port));
					struct epoll_event ev = { .events = EPOLLIN, .data = {.fd = cfd } };
					epoll_ctl(efd, EPOLL_CTL_ADD, cfd, &ev);
					int cur = fcntl(cfd, F_GETFL);
        			fcntl(cfd, F_SETFL, cur | O_NONBLOCK);
                }
            } else if ((pev->events & EPOLLIN)) {
				while (1) {
					char buf[64];
					int z = read(pev->data.fd, buf, sizeof(buf) - 1);
					if (z < 0 && errno == EAGAIN) {
						break;
					}
					if (z <= 0) {
						epoll_ctl(efd, EPOLL_CTL_DEL, pev->data.fd, NULL);
						close(pev->data.fd);
						break;
					}
					buf[z] = 0;
					printf("data from %d: %s", pev->data.fd, buf);
				}
			}
		}
	}

	return 0;
}
