/*
 * This file contains executable code for testing your work in this assignment.
 */

#include <stdio.h>
#include <stdlib.h>

#include "products.h"
#include "dynarray.h"

/*
 * This is the total number of products in the testing data set.
 */
#define NUM_TESTING_PRODUCTS 8


/*
 * These are the names of the products that'll be used for testing.
 */
char* TESTING_NAMES[] = {
  "apples",
  "soup",
  "milk",
  "tofu",
  "poptarts",
  "lightbulbs",
  "soda",
  "chips",
};


/*
 * These are the product inventorys for the products in the array above that will be
 * used for testing.
 */
int TESTING_INVENTORIES[] = {
  7,
  6,
  3,
  1,
  2,
  0,
  5,
  24
};


/*
 * These are the prices of the products above that will be used for testing.
 */
float TESTING_PRICES[] = {
  3.99,
  1.99,
  2.50,
  4.50,
  5.99,
  8.05,
  2.99,
  1.99
};


int main(int argc, char** argv) {
  struct product* s = NULL;
  struct dynarray* products;
  int i;

  /*
   * Create a product using create_product() and print the results.
   */
  s = create_product(TESTING_NAMES[0], TESTING_INVENTORIES[0], TESTING_PRICES[0]);
  printf("\n== Here are the results of create_product():\n");
  if (s) {
    printf("  - name: %s\tinventory: %d\tprice: %f\n", s->name, s->inventory, s->price);
  } else {
    printf("  - NULL\n");
  }

  /*
   * Free the product created above.
   */
  free_product(s);

  /*
   * Create an array of products using create_product_array() and print the
   * results.
   */
  products = create_product_array(NUM_TESTING_PRODUCTS, TESTING_NAMES,
    TESTING_INVENTORIES, TESTING_PRICES);
  printf("\n== Here are the results of create_product_array():\n");
  print_products(products);

  /*
   * Use find_max_price() to find the product with the highest price and print
   * the result.
   */
  s = find_max_price(products);
  printf("\n== Here's the product with the highest price:\n");
  if (s) {
    printf("  - name: %s\tinventory: %d\tprice: %f\n", s->name, s->inventory, s->price);
  } else {
    printf("  - NULL\n");
  }

  /*
   * Use find_max_investment() to find the product with the highest investment, defined as price*inventory
   * the result.
   */
  s = find_max_investment(products);
  printf("\n== Here's the product with the maximum investment:\n");
  if (s) {
    printf("  - name: %s\tinventory: %d\tprice: %f\n", s->name, s->inventory, s->price);
  } else {
    printf("  - NULL\n");
  }

  /*
   * Use sort_by_inventory() to order the products by ascending inventory and
   * print the
   * results.
   */
  sort_by_inventory(products);
  printf("\n== Here are the products ordered by increasing inventory:\n");
  print_products(products);

  /*
   * Free the memory we allocated to the array.  You should use valgrind to
   * verify that you don't have memory leaks.
   */
  free_product_array(products);

  return 0;
}
