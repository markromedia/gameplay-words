//
//  BoardLoader.h
//  words
//
//  Created by Mark Udit on 3/10/13.
//
//

#import <Foundation/Foundation.h>
#include "board_loader_bridge.h"


@interface BoardLoader : NSObject

// basic check create instance for singleton
+ (void) checkCreateInstance;

// Loads the file from disk
+ (void) LoadFile;

- (NSArray*) readLine;
@end
