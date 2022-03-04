/**
 * @file zvm_defs.h
 * @author xiongcl (xiongcl@hnu.edu.cn)
 * @brief This file aim to add some macro for the function name that
 * will add to asm file 
 * @version 0.1
 * @date 2022-03-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __ZVM_DEFS_H_
#define __ZVM_DEFS_H_


#define __DEF_BASE_SECTION "data"

/*
 * This macro is base implementations of variable declarations and definitions.
 */
#define __IMP_ATTR(sec) __attribute__((section(__DEF_BASE_SECTION  sec)))



/* This macro aim to declare some structe name for func call */
#define _Z_DEFINE_SECTION(type, name, sec)   __IMP_ATTR(sec) __typeof__(type) name


/* define variable */
#define Z_DEFINE_D(type, name)  _Z_DEFINE_SECTION(type, name, " ")



#endif // !__ZVM_DEFS_H_
