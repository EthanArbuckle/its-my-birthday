//
//  main.m
//  bday
//
//  Created by Ethan Arbuckle on 1/10/16.
//  Copyright © 2016 Ethan Arbuckle. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <objc/runtime.h>

int main(int argc, const char * argv[]) {

    Class Age = objc_allocateClassPair([NSObject class], "Age", 0);
    
    IMP getAge = imp_implementationWithBlock(^(id _self, SEL selector) {
        return 0;
    });
    
    class_addMethod(Age, NSSelectorFromString(@"getAge"), getAge, "v@:");
    objc_registerClassPair(Age);
    
    int i = 0x12;
    while (i-- > 0) {
        
        IMP oldAge = class_getMethodImplementation(Age, NSSelectorFromString(@"getAge"));
        IMP newAge = imp_implementationWithBlock(^(id _self, SEL selector) {
            return ((NSInteger (*) (id, SEL))oldAge)(Age, NSSelectorFromString(@"getAge")) + 1;
        });
        
        method_setImplementation(class_getInstanceMethod(Age, NSSelectorFromString(@"getAge")), newAge);
    }
    
    NSLog(@"Age: %lu!", ((NSInteger (*) (id, SEL))class_getMethodImplementation(Age, NSSelectorFromString(@"getAge")))(Age, NSSelectorFromString(@"getAge")));
    
    return 0;
}
