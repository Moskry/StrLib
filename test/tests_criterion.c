#include <StrLib.h>
#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/parameterized.h>

typedef struct datastruct {
  String x, y;
  str result, expected;
} DataStruct;

struct datastruct data;

void connections_init(void) {
  data.x = new_string(NULL);
  data.y = new_string(NULL);
  data.result = NULL;
}
void connections_fini(void) {
  data.x->free(&data.x);
  data.y->free(&data.y);
  free(data.result);
}

TestSuite(connections, .init = connections_init, .fini = connections_fini);

static void test_concat(str a, str b, const char *expected) {
  if (data.result != NULL)
    free(data.result);
  data.result = NULL;

  data.x->assign(data.x, a);
  data.y->assign(data.y, b);
  data.x = data.x->concat(&data.x, &data.y);
  data.result = data.x->copy_to_str(data.x);
  cr_assert(eq(str, data.result, expected));
  data.y = new_string(NULL);
}

Test(connections, concat) {
  test_concat("Blue", " Zenith", "Blue Zenith");
  test_concat("Auto", "mobil", "Automobil");
}

struct datastruct append_data;

static void test_append(str a, str b, const char *expected) {
  if (data.result != NULL)
    free(data.result);
  data.result = NULL;

  data.x->assign(data.x, a);
  data.y->assign(data.y, b);
  data.x->append(data.x, &data.y);
  // b is now dangling

  data.result = data.x->copy_to_str(data.x);
  cr_assert_str_eq(data.result, expected, "expected %s, got %s", expected,
                   data.result);
  cr_assert_null(b, "b expect to be null, got %p", b);
}

Test(connections, append_null) {
  data.x->assign(data.x, "");
  data.y->free(&data.y);
  data.y = new_string(NULL);
  data.x->append(data.x, &data.y);
  data.result = data.x->copy_to_str(data.x);
  cr_assert(eq(str, data.result, "", "Expected \"\", found %s, ", data.result));
  data.y = new_string(NULL);
}

/*
void cleanup_append(struct criterion_test_params *params) {
  DataStruct *array = params->params;
  for (int i = 0; i < params->length; i++) {
    cr_log_warn("times in the loop: %d", i + 1);
    array[i].x->free(array[i].x);
    array[i].y->free(array[i].y);
    if (array[i].result != NULL)
      free(array[i].result);
    free(array[i].expected);
  }
  cr_free(array);
}
*/


struct Strings {
  char a[50];
  char b[50];
  char expected[100];
};

void cleanup_append(struct criterion_test_params *params) {
  cr_free((struct Strings *)(params->params));
}

ParameterizedTestParameters(connections, append) {

  struct Strings *strings = cr_malloc(sizeof(struct Strings));
  strings[0] =
      (struct Strings){.a = "first", .b = "second", .expected = "firstsecond"};
  strings[1] = (struct Strings){.a = "", .b = "", .expected = ""};
  strings[2] = (struct Strings){.a = "", .b = "Gday", .expected = "Gday"};

  return cr_make_param_array(struct Strings, strings, 3);
}

ParameterizedTest(struct Strings *ds, connections, append) {
  data.x->assign(data.x, ds->a);
  data.y->assign(data.y, ds->b);

  data.x->append(data.x, &data.y);
  data.result = data.x->copy_to_str(data.x);
  cr_assert(eq(str, data.result, ds->expected), "expected %s, got %s",
            ds->expected, data.result);
  cr_expect(eq(ptr, data.y, NULL), "expected NULL, got %p", data.y);
  if (data.y == NULL)
    data.y = new_string(NULL);
}
