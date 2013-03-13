//
//  BoardLoader.h
//  words
//
//  Created by Mark Udit on 3/10/13.
//
//

#import <Foundation/Foundation.h>
#include "ios_bridge.h"


@interface BoardLoader : NSObject

// basic check create instance for singleton
+ (void) checkCreateInstance;

// Loads the file from disk
+ (void) LoadFile;

// reads a liine from precalculated boards file
- (NSArray*) readLineFromPrecalcBoardFile;

// prints the name of current thread executing this code
- (void) printCurrentThreadName;
@end
