#include <stdio.h>
#include <string.h>
#include "jansson.h"

void dump_json_error(json_error_t *error) {
  printf("error msg: %s\n", error->text);
  printf("at line %d and column %d (position %d)\n",  \
          error->line, error->column, error->position);
}

int main() {
  json_t *json, *json_obj;
  json_error_t error;
  void *iter;
  const char *key;
  char *str = NULL;
  int value, boolean, len;

  // Load the file
  json = json_load_file("src/data/file.json", 0, &error);
  if(!json) { // If NULL then loading is unsuccessful
    dump_json_error(&error);    // Display the error
    return -1;
  }

  // Dump the the content
  str = json_dumps(json, JSON_INDENT(4));
  printf(str); puts("");
  free(str);

  iter = json_object_iter(json);
  key = json_object_iter_key(iter);
  printf("key:%s\n", key);
  json_obj = json_object_iter_value(iter);
  // Print only when the 'value' is a string
  if(json_is_string(json_obj))
    printf("value:%s\n", json_string_value(json_obj));

  iter = json_object_iter_next(json, iter);
  key = json_object_iter_key(iter);
  printf("key:%s\n", key);
  json_obj = json_object_iter_value(iter);
  // Print only when the 'value' is an integer
  if(json_is_integer(json_obj))
    printf("value:%d\n", json_integer_value(json_obj));


  json_unpack(json, "{s:s%, s:i, s:b}", "key_string", &str, &len, "key_integer", &value, "key_boolean", &boolean);
  printf("key_string:%s(%d), key_integer:%d, key_boolean:%d", str, len, value, boolean);

  json_decref(json);
  return 0;
}