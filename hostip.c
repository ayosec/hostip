#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <arpa/inet.h>
#include <net/if.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>

int is_default_iface(char* buffer, char* out_iface, size_t out_len) {
  char *iface, *destination;

  iface = strsep(&buffer, "\t");
  destination = strsep(&buffer, "\t");

  if(strcmp(destination, "00000000") == 0) {
    strncpy(out_iface, iface, out_len);
    return 1;
  }
  return 0;
}

int main() {

  FILE *input;
  char iface[128] = { 0 };
  char buffer[4 * 1024];

  int socketfd;
  struct ifreq ifreq;

  /*
   * Parse route table to get default interface
   */

  if((input = fopen("/proc/net/route", "r")) == NULL) {
    perror("open /proc/net/route");
    exit(EXIT_FAILURE);
  }

  while(fgets(buffer, sizeof(buffer), input) != NULL) {
    if(is_default_iface(buffer, iface, sizeof(iface))) {
      break;
    }
  }

  if(iface[0] == 0) {
    fputs("No iface with gateway 0.0.0.0\n", stderr);
    exit(EXIT_FAILURE);
  }

  /*
   * Get address for the iface
   */

  if ((socketfd = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP)) == -1) {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  memset(&ifreq, 0, sizeof ifreq);
  strncpy(ifreq.ifr_name, iface, IFNAMSIZ - 1);

  if(ioctl(socketfd, SIOCGIFADDR, &ifreq) == -1) {
    perror("ioctl");
    exit(EXIT_FAILURE);
  }

  puts(inet_ntoa(((struct sockaddr_in *)&ifreq.ifr_addr)->sin_addr));

  return 0;
}
