//
//  BoardLoader.m
//  words
//
//  Created by Mark Udit on 3/10/13.
//
//

#import "iOSHandler.h"
#import <dispatch/dispatch.h>

#include "../src/solver_worker.hpp"

typedef SolverWorker SolverWorker;

@interface BoardLoader ()
@property (nonatomic, strong) NSArray *lines;
@property (nonatomic, assign) int currentIndex;
@property (nonatomic, assign) bool running;
@property (nonatomic, assign) SolverWorker *worker;
@end

@implementation BoardLoader

//synthesize stuffs
@synthesize lines;
@synthesize currentIndex;
@synthesize running;
@synthesize worker;

//singleton
static BoardLoader* instance;

//instanced background queue
dispatch_queue_t backgroundQueue;

//lock we're gonna use
pthread_mutex_t mutex;

- (BoardLoader*) init {
    worker = new SolverWorker();
    pthread_mutex_init(&mutex, NULL);
    backgroundQueue = dispatch_queue_create("com.markromedia.bgqueue", NULL);
    return self;
}

+ (void) checkCreateInstance {
    if (instance == Nil) {
        instance = [[BoardLoader alloc] init];
    }
}

+ (void) LoadFile {
    [self.class checkCreateInstance];
    
    //load precalculated file
    NSString* path = [[NSBundle mainBundle] pathForResource:@"res/dict/precalculated_boards"
                                                     ofType:@"txt"];
    NSString* content = [NSString stringWithContentsOfFile:path
                                                  encoding:NSUTF8StringEncoding
                                                     error:NULL];
    //split it up into new line separated strings
    instance.lines = [content componentsSeparatedByString:@"\n"];
    
    //TODO. skip the dice check for now
    instance.currentIndex = 16;
}

- (NSArray*) readLineFromPrecalcBoardFile {
    if (self.currentIndex > [self.lines count]) {
        //TODO. might need to clear up the lines array for mem
        return nil;
    }
    
    NSArray* values = [[NSArray alloc] init];
    NSString* line = [lines objectAtIndex: currentIndex];
    //increment counter
    currentIndex++;
    
    return [line componentsSeparatedByString:@" "];
}

- (void) printCurrentThreadName {
    NSLog(@"%@", [NSThread currentThread]);
}

- (void) startWorker {
    running = true;
    
    dispatch_async(backgroundQueue, ^(void) {
        while (running) {
            pthread_mutex_lock(&mutex);
            if (running) { //might not be running after lock is acquired
                self.worker->PerformSolverTask();
            }
            pthread_mutex_unlock(&mutex);
        }
    });
}

- (void) stopWorker {
    pthread_mutex_lock(&mutex);
    running = false;
    
}

//
// C stuff goes here
//
void loadPrecalculatedBoardsFile() {
    [BoardLoader LoadFile];
}

int* readLineFromPrecalculateBoardsFile() {
    NSArray* lineValues = [instance readLineFromPrecalcBoardFile];
    int val_count = [lineValues count];
    if (lineValues == nil || [lineValues count] < 33) {
        return NULL;
    }
    
    int* int_line_vals = new int[33];
    for (int i = 0; i < 33; i++) {
        int_line_vals[i] = [[lineValues objectAtIndex:i] intValue];
    }
    return int_line_vals;
}

void printThreadName() {
    [instance printCurrentThreadName];
}

void startWorkerThread() {
    [instance startWorker];
}

void stopWorkerThread() {
    [instance stopWorker];
}

void releaseWorkerLock() {
    pthread_mutex_unlock(&mutex);
}

@end
