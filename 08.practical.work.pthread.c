
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 10


typedef struct {
  char type; // 0=fried chicken, 1=French fries , 2=Accessory
  int amount; // pieces or weight
  char unit; // 0=piece, 1=gram
} item;

item buffer[BUFFER_SIZE];
int first = 0;
int last = 0;

void printLog();

void produce(item *i){
  while ((first + 1) % BUFFER_SIZE == last){
    //do nothing -- no free buffer item
    printf("No free buffer item!\n");
  }
  memcpy(&buffer[first], i, sizeof(item));
  first = (first + 1) % BUFFER_SIZE;
  printLog();
}

item* consume(){
  item* i = malloc(sizeof(item));
  while (first == last){
    // do nothing -- nothing to consume
    printf("Nothing to consume!\n");
  }
  memcpy(i, &buffer[last], sizeof(item));
  last = (last + 1) % BUFFER_SIZE;
  printLog();
  return i;
}

item* create(char type, int amount, char unit){
  item* newItem = malloc(sizeof(item));
  newItem->type = type;
  newItem->amount = amount;
  newItem->unit = unit;
  return newItem;
}

void *produceThread(void *param){
  item *newItem1 = create('3',50,'1');
  item *newItem2 = create('2',40,'9');
  item *newItem3 = create('10',80,'1');
  produce(newItem1);
  printf("Type:%c,Amount:%d,Unit:%c",newItem1->type, newItem1->amount, newItem1->unit);
  produce(newItem2);
  printf("Type:%c,Amount:%d,Unit:%c",newItem2->type, newItem2->amount, newItem2->unit);
  produce(newItem3);
  printf("Type:%c,Amount:%d,Unit:%c",newItem3->type, newItem3->amount, newItem3->unit);
}

void *consumerThread(void *param){
  item *cons;
  for (int i = 0; i < 3; ++i){
    cons = consume();
    printf("\nConsumed item %d: %c, %d, %c\n", i, consume->type, consume->amount, consume->unit);
    printf("First: %d, Last: %d\n", first, last);
    }
}

void printLog() {
  printf("first = %d  last = %d\n", first, last);
  return;
}

int main() {
  pthread_t a, b;
  pthread_create(&a, NULL, produceThread, NULL );
  pthread_create(&b, NULL, consumerThread,NULL);
  pthread_join(a, NULL);
  pthread_join(b, NULL);
  return 0;
}

