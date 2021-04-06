#ifndef OOP_MAIN_H
#define OOP_MAIN_H
	
	#ifndef _STDLIB_H
		#include <stdlib.h>
	#endif

	/**
	* grab an interface definition by calling it's macro.
	* @param i Interface name
	*/
		#define eIMPLEMENTS(i) eINTERFACE_##i()

	/**
	* add a parent class struct to gain access to it's public methods
	* @param c Class
	* @param p Property name
	*/
		#define eEXTENDS(c,p) struct c p

	/**
	* helper macro to denote that this parent is upcastable (this macro must be first element of containing
	* struct for this to be true)
	* @param c Class
	* @param p Property name
	*/
		#define eDIR_EXTENDS(c,p) eEXTENDS(c,p)
	
	/**
	* Instantiate an object 'o*' of type 'c' by using function 'c_instatiate()'
	* @param c Struct type
	* @param o Object variable name
	* @param ... any further arguments
	*/
		#define eNEW_INS(c,o, ...) c##_instantiate(o, __VA_ARGS__)
	
	/**
	* Call allocation method and imediately fire instantiation function for heap object
	* @param c Struct type
	* @param o Object variable name
	* @param ... any further arguments
	*/
		#define eNEW(c,o, ...) struct c*o = (struct c *)malloc(sizeof(struct c)); eNEW_INS(c,o, __VA_ARGS__)
	
	/**
	* Call allocation method and imediately fire instantiation function for heap object, sub struct
	* @param c Struct type
	* @param o Object variable name
	* @param ... any further arguments
	*/
		#define eNEW_S(c,o, ...) o = (struct c *)malloc(sizeof(struct c)); eNEW_INS(c,o, __VA_ARGS__)
	
		/**
	* Instantiate an object 'o*' of type 'c' by using function 'c_instatiate()', no arguments
	* @param c Struct type
	* @param o Object variable name
	*/
		#define eNEW_INS_NOARGS(c,o) c##_instantiate(o)
	
	/**
	* Call allocation method and imediately fire instantiation function for heap object, no arguments
	* @param c Struct type
	* @param o Object variable name
	*/
		#define eNEW_NOARGS(c,o) struct c*o = (struct c *)malloc(sizeof(struct c)); eNEW_INS_NOARGS(c,o)
	
	/**
	* Call allocation method and imediately fire instantiation function for heap object, no arguments, sub struct
	* @param c Struct type
	* @param o Object variable name
	*/
		#define eNEW_NOARGS_S(c,o) o = (struct c *)malloc(sizeof(struct c)); eNEW_INS_NOARGS(c,o)
	
	/**
	* Instantiate a parent class
	* @param c Struct type
	* @param p Property variable name
	*/
		#define eNEW_PARENT(c, p) c##_instantiate(&p)
	
	/**
	* public property DECLARATION
	* @param t Type
	* @param p Property name
	*/
		#define ePROP_DEC(t, p) t p
	
	/**
	* public property DEFINITION
	* @param p Property name
	* @param v Value
	*/
		#define ePROP_DEF(p, v) self->p = v
	
	/**
	* private property PUBLIC function-pointer DECLARATIONS for public struct
	* @param t Type
	* @param p Property name
	* @param m get/set/getset
	*/
		#define ePRIV_PROP_DEC_get(t,p) t (*get_##p)(void * eOBJ)
		#define ePRIV_PROP_DEC_set(t,p) void (*set_##p)(void * eOBJ, t v)
		#define ePRIV_PROP_DEC_getset(t,p) ePRIV_PROP_DEC_get(t,p); ePRIV_PROP_DEC_set(t,p)
		#define ePRIV_PROP_DEC_PUB(t, p, m) ePRIV_PROP_DEC_##m(t,p)
	
	/**
	* private property PRIVATE function-pointer DECLARATIONS for private struct
	* @param t Type
	* @param p Property name
	* @param m get/set/getset
	*/
		#define ePRIV_PROP_DEC_PRIV(t, p, m) ePROP_DEC(t,p); ePRIV_PROP_DEC_##m(t,p)
	
	/**
	* private property PUBLIC function DECLARATIONS
	* @param c Type
	* @param t Function return type
	* @param p Property name
	* @param m get/set/getset
	*/
		#define ePRIV_PROP_FUNC_DEC_get(c, t, p) t c##_get_##p(void * eOBJ);
		#define ePRIV_PROP_FUNC_DEC_set(c, t, p) void c##_set_##p(void * eOBJ, t v );
		#define ePRIV_PROP_FUNC_DEC_getset(c, t, p) ePRIV_PROP_FUNC_DEC_get(c, t, p) ePRIV_PROP_FUNC_DEC_set(c, t, p)
		#define ePRIV_PROP_FUNC_DEC(c, t, p, m) ePRIV_PROP_FUNC_DEC_##m(c, t, p)
	
	/**
	* private property function ALLOCATIONS for object function pointers in instantiate
	* @param c Type
	* @param p Property name
	* @param v Property value
	* @param m get/set/getset
	*/
		#define ePRIV_PROP_DEF_get(c, p) self->get_##p = &c##_get_##p
		#define ePRIV_PROP_DEF_set(c, p) self->set_##p = &c##_set_##p
		#define ePRIV_PROP_DEF_getset(c, p) ePRIV_PROP_DEF_get(c, p); ePRIV_PROP_DEF_set(c, p)
		#define ePRIV_PROP_DEF(c, p, v, m) self->p = v; ePRIV_PROP_DEF_##m(c, p)
	
	/**
	* private property PUBLIC get/set function DEFINITIONS
	* @param c Type
	* @param t Function return type
	* @param p Property name
	* @param m get/set/getset
	*/
		#define ePRIV_PROP_FUNC_DEF_get(c, t, p) t c##_get_##p(void * eOBJ){ eSELF(c); return self->p; }
		#define ePRIV_PROP_FUNC_DEF_set(c, t, p) void c##_set_##p(void * eOBJ, t v ){ eSELF(c); self->p = v; }
		#define ePRIV_PROP_FUNC_DEF_getset(c, t, p) ePRIV_PROP_FUNC_DEF_get(c, t, p) ePRIV_PROP_FUNC_DEF_set(c, t, p)
		#define ePRIV_PROP_FUNC_DEF(c, t, p, m) ePRIV_PROP_FUNC_DEF_##m(c, t, p)
	
	/**
	* Cast "self" back into the class type
	* @param c Struct type
	*/
		#define eSELF(c) c * self = (c*)eOBJ
	
	/**
	* upCast "self" to parent struct type. Parent struct type must be first struct member publically
	* Can only be called from scope where child object is instantiated
	* @param c Struct type
	* @param v Variable name to use
	*/
		#define ePARENT(c, v) struct c * v = (struct c *)self
	
	/**
	* Get the value of a protected variable 'p' within object 'o'
	* Prints to stderr if property is private
	* @param o Object
	* @param p Object property
	*/
		#define eGET(o, p) o->get_##p(o)
	
	/**
	* Set the value of a protected variable 'x' within object 'o'
	* Prints to stderr if property is private
	* @param var o Object
	* @param var p Object property
	* @param var v The new value
	*/
		#define eSET(o, p, v) o->set_##p(o, v)
	
	/**
	* Method call wrapper that passes object as first argument for use of eSELF()
	* @param o Object
	* @param m The method
	* @param ... Other args
	*/
		#define eCALL(o, m, ...) (*o->m)(o, __VA_ARGS__)
	
	/**
	* Method call wrapper that passes object as first argument for use of eSELF(), no arguments
	* @param o Object
	* @param m The method
	* @param ... Other args
	*/
		#define eCALL_NOARGS(o, m) (*o->m)(o)
		
	/**
	* Free memory on heap for object
	* @param var o Object variable name
	*/
		#define eDESTROY(o) free(o); o = ((void*)0)
		
#endif //OOP_MAIN_H
