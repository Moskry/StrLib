#include <StrLib.h>
#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/parameterized.h>
#include <criterion/theories.h>

typedef struct datastruct {
  String x, y;
  str result, expected;
} DataStruct;

struct datastruct data;
/* CONNECTIONS */

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

  return cr_make_param_array(struct Strings, strings, 3, cleanup_append);
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

TheoryDataPoints(connections, test_append_copy) = {
    DataPoints(str, "first", ""),
    DataPoints(str, "second", ""),
};

Theory((str xstr, str ystr), connections, test_append_copy) {
  data.x->assign(data.x, xstr);
  data.y->assign(data.y, ystr);

  data.x->append_copy(data.x, data.y);
  data.result = data.x->copy_to_str(data.x);
  data.expected = malloc((strlen(xstr) + strlen(ystr) + 1) * sizeof(char));
  strcpy(data.expected, xstr);
  strcat(data.expected, ystr);

  cr_assert(eq(str, data.result, data.expected), "Expected %s, got %s",
            data.expected, data.result);
  cr_assert(ne(ptr, data.y, NULL), "Did not expect NULL");
}

TheoryDataPoints(connections, test_append_str) = {
    DataPoints(str, "", "word: "),
    DataPoints(str, "", "second"),
};

Theory((str first, str second), connections, test_append_str) {
  data.x->assign(data.x, first);

  data.x->append_str(data.x, second);
  data.result = data.x->copy_to_str(data.x);
  data.expected = malloc((strlen(first) + strlen(second) + 1) * sizeof(char));
  strcpy(data.expected, first);
  strcat(data.expected, second);

  cr_assert(eq(str, data.result, data.expected), "Expected %s, got %s",
            data.expected, data.result);
  data.y = new_string(NULL);
}

/* ASSIGN */

void assign_init(void) {
  data.x = new_string(NULL);
  data.result = NULL;
}

void assign_fini(void) {
  data.x->free(&data.x);
  free(data.result);
}

TestSuite(assign, .init = assign_init, .fini = assign_fini);

TheoryDataPoints(assign,
                 normal) = {DataPoints(str, "", "Something", "Something else",
                                       "Something else entirely\n")};

Theory((str for_string), assign, normal) {
  data.x->assign(data.x, for_string);
  data.result = data.x->copy_to_str(data.x);
  cr_assert(eq(str, data.result, for_string), "Expected %s, got %s", for_string,
            data.result);

  // Unclean string
  data.x->assign(data.x, "already something");
  free(data.result);

  data.x->assign(data.x, for_string);
  data.result = data.x->copy_to_str(data.x);
  cr_assert(eq(str, data.result, for_string), "Expected %s, got %s", for_string,
            data.result);
}

TheoryDataPoints(assign, pop) = {
    DataPoints(str, "", "Something"),
    DataPoints(str, "", " else"),
};

Theory((str old, str new), assign, pop) {
  cr_assume(strcmp( old, new) != 0);
  data.x->assign(data.x, old);
  data.result = data.x->pop_assign(data.x, new);

  cr_expect(eq(str, data.result, old), "Expected %s, got %s", old, data.result);
  cr_expect(ne(str, data.result, new), "Did not expect %s", new);

  free(data.result);
  data.result = data.x->copy_to_str(data.x);

  cr_assert(eq(str, data.result, new), "Expected %s, got %s", new, data.result);
  cr_assert(ne(str, data.result, old), "Did not expect %s", old);
}

/* CLEAR */
Test(empty, clear) {
  String a = new_string("Something");
  a->clear(a);
  str result = a->copy_to_str(a);

  cr_assert(eq(str, result, ""));
  free(result);
  a->free(&a);
}

/* INSERT */
Test(empty, insert) {
  String a = new_string(NULL);
  a->insert_at(a, "first", 0);
  str result = a->copy_to_str(a);
  cr_assert(eq(str, result, "first"));
  a->insert_at(a, "second", 4);
  free(result);
  result = a->copy_to_str(a);
  cr_assert(eq(str, result, "firssecondt"), "Expected firssecondt, got %s", result);
  free(result);
  a->free(&a);
}

/* DELETE */
Test(empty, delete) {
  String a = new_string("firssecondt");
  a->delete_at(a, 4, 6);
  str result = a->copy_to_str(a);
  cr_assert(eq(str, result, "first"), "Expected first, got %s", result);
  free(result);
  a->free(&a);
}

/* SLICE */
Test(empty, slice) {
  String a = new_string("Something");
  str slicea = a->slice(a, 4, 20);
  str sliceb = a->slice(a, 2, 4);
  cr_expect(eq(str, slicea, "thing"), "Expected %s got %s", "thing", slicea);
  cr_expect(eq(str, sliceb, "me"), "Expected me got %s", sliceb);
  free(slicea);
  free(sliceb);
  a->free(&a);
}

String name;

/* TO_STR */
void to_str_fini(void) { name->free(&name); }

void to_str_init(void) { name = new_string("Diablo"); }

TestSuite(to_str, .init = to_str_init, .fini = to_str_fini);

Test(to_str, copy) {
  str test = name->copy_to_str(name);
  str test1 = name->copy_to_str(name);
  cr_assert(eq(str, test, test1), "Expected equal copies");
  free(test);
  free(test1);
}

Test(to_str, std) {
  str test = name->to_str(&name);

  cr_assert(eq(ptr, name, NULL), "Expected NULL");
  cr_assert(eq(str, test, "Diablo"), "Expected Diablo, got %s", test);

  if (name == NULL)
    name = new_string(NULL);
}

void truncate_init(void) { name = new_string_reserve(50, "something"); }
void truncate_fini(void) { name->free(&name); }

TestSuite(truncate, .init = truncate_init, .fini = truncate_fini);

Test(truncate, length) {
  long old_size = name->size(name);
  str scpold = name->copy_to_str(name);
  name->truncate_size(name);
  str scp = name->copy_to_str(name);

  cr_assert(ge(i64, old_size, name->size(name)), "Expected smaller name: %ld",
            name->size(name));
  cr_assert(eq(i64, name->size(name), name->length(name) + 1),
            "Expected size to be equivalent to length + 1");
  cr_assert(eq(str, scpold, scp), "Expected equal return strs");

  free(scpold);
  free(scp);
}

Test(truncate, at) {
  name->truncate(name, 5);
  str result = name->copy_to_str(name);

  cr_assert(eq(i64, name->size(name), 6), "Expected size of 6");
  cr_assert(eq(i64, name->length(name), 5), "Expected length of 5");
  cr_assert(eq(str, result, "somet"), "Expected result somet, got %s", result);

  free(result);
}
