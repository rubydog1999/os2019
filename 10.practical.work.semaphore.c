#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#define BUFFER_SIZE 10

typedef struct {
    char type; // 0=fried chicken, 1=French fries
    int amount; // pieces or weight
    char unit; // 0=piece, 1=gram
} item;

item buffer[BUFFER_SIZE];
int first = 0;
int last = 0 ;

void produce(item *i) {
    while ((first + 1) % BUFFER_SIZE == last) {
        // do nothing -- no free buffer item
    }
    memcpy(&buffer[first], i, sizeof(item));
    first = (first + 1) % BUFFER_SIZE;
    printLog();
    return i;
}

item *consume() {
    item *i = malloc(sizeof(item));
    while (first == last) {
        // do nothing -- nothing to consume
    }
    memcpy(i, &buffer[last], sizeof(item));
    last = (last + 1) % BUFFER_SIZE;
    printLog();
    return i;
}

item *initItem(char type, int amount, char unit) {
	item *i = malloc(sizeof(item));
	i->amount=amount;
	i->type=type;
	i->unit=unit;
	return i;
}

void *produceThread(void* param) {
	item *i1=initItem('2',10,'1');
    item *i2=initItem('3',2,'3');
    item *i3=initItem('4',6,'0');
    produce(i1);
    produce(i2);
    produce(i3);
	pthread_exit(NULL);
}

void *consumeThread(void* param) {
	consume();
	consume();
	pthread_exit(NULL);
}
void printLog() {
    printf(" last = %d\n first = %d", last, first);
    return;
}


int main() {
    pthread_t a,b;
    printf("Thread for produce function\n");
    pthread_create(&a,NULL,consumeThread,NULL);
    printf("Thread for consume function\n");
    pthread_create(&b,NULL,consumeThread,NULL);
    pthread_join(a,NULL);
    pthread_join(b,NULL);
}
