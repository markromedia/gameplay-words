//
//  BoardLoader.m
//  words
//
//  Created by Mark Udit on 3/10/13.
//
//

#import "BoardLoader.h"

@implementation BoardLoader
static BoardLoader* instance;

+ (void) checkCreateInstance {
    if (instance == Nil) {
        instance = [[BoardLoader alloc] init];
    }
}

+ (void) LoadFile {
    [self.class checkCreateInstance];
    NSLog(@"%@", @"inside objective-c");
}

//
//
//
char* readBoardLoaderLine() {
    [BoardLoader LoadFile];
    return NULL;
}

@end
