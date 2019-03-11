#ifndef __SERIAL_H__
#define __SERIAL_H__

int serial_config(char *);
void send_data(int, char *, int, int);
void recv_data(int);
void close_dev(int);

#endif
