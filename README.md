# Assignment 2
**Due by 11:59pm on Wednesday, 4/21/2018**

**Demo due by 11:59pm on Wednesday 5/5/2018**

This assignment is intended to give you practice writing C code (e.g. allocating and freeing memory, working with pointers, etc.) and also to have you start working with one of the most fundamental data structures we'll see in this course: the dynamic array.  There are several parts to the assignment, each described below.

For this assignment, you are provided with some starter code that defines the structures you'll be working with and prototypes the functions you'll be writing. You will only edit the products.c file provided. *It's important that you don't modify the function prototypes.*  To help grade your assignment, we will use a set of unit tests that assume these functions exist and have the same prototypes that are defined in the starter code.  If you change the prototypes, it will cause the unit tests to break, and your grade for the assignment will likely suffer.  Feel free, however, to write any additional functions you need to accomplish the tasks described below.

Within the provided starter code is a dynamic array implementation in `dynarray.h` and `dynarray.c`.  You should use this implementation to provide the dynamic array functionality needed by several of the functions you'll write for the assignment.  We will review this implementation in lecture.

Importantly, your work for this assignment will be limited to the file `products.c`, where you will implement the functions described below.  You should not modify any other file in this repository.  In addition to the descriptions below, there is documentation in `products.c` describing how each function you'll write should behave.

## 1. Implement a function to allocate and initialize a single `struct product`

In `create_product()`, implement a function that initializes the values of a single newly-allocated product structure.  In particular, this function will be passed values for `name`, `inventory`, and `price`.  You should allocate memory to store a `struct product`.  You should also allocate memory to store a copy of `name` and copy `name` into that memory.  Then, you should assign the copy of `name`, `inventory`, and `price` to the corresponding fields in the product structure you allocated and return a pointer to that structure. For something like a struct-defined node like this, allocating basically amounts to declaring the `struct product` using the `struct` keyword, and then allocating memory the name (this is a string, or an array of characters allocated using malloc), copying the contents of the provided name. 

## 2. Implement a function to free the memory held by a single `struct product`

In `free_product()`, implement a function that frees any memory that was allocated by `create_product()` for a single product.  This function will be passed a pointer to the product whose held memory is to be freed.  You must free any memory allocated for the fields of that product structure as well as the memory allocated for the structure itself.  Importantly, this function must free all relevant memory and cannot result in a memory leak. Basically, freeing the memory of the product name, and then freeing the product. 

## 3. Implement a function to create a dynamic array of `struct product`s

In `create_product_array()`, implement a function to allocate and initialize a dynamic array (i.e. `struct dynarray`), store a collection of products in that newly-created dynamic array, and then return a pointer to the array.  This function will be provided with arrays specifying the names, inventories, and prices of the products to be stored in the array.  You should use your `create_product()` function to allocate and initialize a product structure for each set of provided values and store each allocated product structure in the new dynamic array.  In the returned array, the `i`th product should have the `i`th name, the `i`th inventory, and the `i`th price.  Make sure to use the provided dynamic array functions (e.g. `dynarray_create()` and `dynarray_insert()`) to allocate and modify the dynamic array. In essence, this is creating a dynamic array of pointers. Each pointer will point to a `struct product`, and those should be allocated by the function created in #1. 

## 4. Implement a function to free the memory in a dynamic array of `struct product`s

In `free_product_array()`, implement a function that frees all of the memory allocated by `create_product_array()`.  In particular, you should use your `free_product()` function to free the memory held by each individual product in the array, and then you should free the memory held by the array itself.  Again, make sure to use the provided dynamic array functions to access elements in the dynamic array and to free the array itself.  Importantly, this function must free *all* of the memory associated with a dynamic array of product structures.  In other words, it may not result in memory leaks.

## 5. Implement a function to print a dynamic array of `struct product`s

In `print_products()`, implement a function that prints the name, inventory, and price of each product in a dynamic array, one product per line.  As before, make sure to use the provided dynamic array functions to access elements in the dynamic array.

## 6. Implement functions to find the products in an array with the highest price and highest investment, where investment=price*inventory

In `find_max_price()` and `find_max_investment()`, implement functions to respectively find the product with the highest price and the one with the highest investment, defined as price*inventory in an array.  These functions should return a pointer to these products.  Importantly, you should not make a copy of the product returned by these functions.  Instead, you should simply return the pointer to a product structure that's already stored in the array.

## 7. Implement a function to sort the products in a dynamic array by ascending inventory

In `sort_by_inventory()`, implement a function to order the products in a dynamic array by ascending inventory (i.e. with the lowest inventoryat the beginning of the array).  You may use any sorting algorithm you like.  This function should abide by the following constraints:

  * It should sort the products *in place*.  In other words, you should not allocate memory for a new array in this function.
  * It should not use built-in functions like `qsort()`.  In other words, you have to implement the sorting yourself.  You may implement any in-place sorting algorithm you like.  Some possibilities are selection sort, insertion sort, bubble sort, and quicksort.

As with all of the other functions that work with dynamic arrays, make sure to use the provided dynamic array functions (e.g. `dynarray_get()`, `dynarray_set()`, etc.) to access and modify the contents of the dynamic array.

## A note on using void pointers

The dynamic array implementation in this assignment uses void pointers (i.e. `void*`) to store data.  You may not be familiar with the way void pointers work.  Simply put, void pointers are a mechanism that can be used to store *any* pointer type.  In other words, you can think of a void pointer as a generic pointer, capable of pointing to values of any type.  They are often used in C/C++ data structure implementations to allow those data structures to store data of many different types without needing to change the underlying source code of the data structure for each type.

In order to use a void pointer (e.g. one returned by a function), you'll likely want to cast or assign it back to its original type.  For example, below is some code that uses a void pointer to point to an integer and then prints that integer via the void pointer.  Note that we have to cast the void pointer as an integer pointer in order to dereference it and print the underlying integer value.
```C
int n = 16;
void* vptr = &n;  /* storing int* value in void* variable */
printf("%d\n", *(int*)vptr);
```
Alternatively, we could have assigned the address contained in `vptr` back into a variable of type `int*`, from which we could then print the underlying integer value:
```C
int* iptr = vptr;
printf("%d\n", *iptr);
```

Again, void pointers can hold a pointer to a value of any type.  For example, below is code that uses a void pointer to store the pointer to a `struct product` returned by `create_product()`.  This pointer is then assigned back into a variable of type `struct product*` in order to access the underlying values in the product structure.
```C
void* vptr = create_product(...);
struct product* sptr = vptr;
printf("%s\n", sptr->name);
```

Many of the functions from the dynamic array implementation you'll use in this assignment either take `void*` arguments or return `void*` values.  In general, it will work fine for you to pass `struct product*` values into `void*` arguments.  When working with `void*` return values, make sure to either cast back to `struct product*` or to assign to a variable of type `struct product*` if you want to access the underlying fields of the product structure.

## Testing your work

In addition to the dynamic array implementation and the skeleton code in `products.h` and `products.c`, you are also provided with some application code in `test.c` to help verify that your functions are behaving the way you want them to.  In particular, the code in `test.c` calls the functions from `products.c`, passing them appropriate arguments, and then prints the results.  You can use the provided `Makefile` to compile all of the code in the project together, and then you can run the testing code as follows:
```
make
./test
```

In order to verify that your memory freeing functions work correctly, it will be helpful to run the testing application through `valgrind`.

## Submission

We will submit assignments via Gradescope. To submit Assignment 2, you only need to submit `products.c`. No zip files needed. A link will be provided on the canvas assignment page.

## Grading criteria

Your program **MUST** compile and run on `flip.engr.oregonstate.edu`, so make sure you have tested your work there before you make your final submission, since a program that compiles and runs in one environment may not compile and run in another.  **Assignments that do not compile on flip will receive a grade of 0.**  If you do not have an ENGR account, you can create one at https://teach.engr.oregonstate.edu/.

The assignment is worth 100 total points, broken down as follows:

  * 10 points: `create_product()` allocates and initializes a `struct product` as described above
  * 10 points: `free_product()` frees the memory held by a `struct product` as described above (no memory leaks!)
  * 10 points: `create_product_array()` allocates and initializes a dynamic array of `struct product`s as described above
  * 10 points: `free_product_array()` frees the memory held by a dynamic array of `struct product`s as described above (no memory leaks!)
  * 10 points: `print_products()` prints a dynamic array of products as described above
  * 10 points: `find_max_price()` finds the product with the highest price as described above
  * 10 points: `find_max_investment()` finds the product with the highest investment, defined as price*inventory
  * 10 points: `sort_by_inventory()` sorts a dynamic array of products by ascending inventory, in place, as described above
  * 20 points: you can provide a satisfactory explanation of how your code works during your grading demo with the TA

Note that we will only consider changes to `products.c` when grading your work.  Changes to other files will be ignored.
