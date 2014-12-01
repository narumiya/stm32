#ifndef CHATA_H
#define CHATA_H

#define EDGE_UP	11
#define EDGE_DOWN 99

#define ON			1
#define OFF		0

unsigned short positive_chattering( int swi, int  );

unsigned short negative_chattering( int swi, int );

#endif
