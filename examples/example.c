#include <stdlib.h>
#include <stdio.h>
#include <m_int_combo.h>

int
main(int argc, char** argv)
{
	int i;
	int ret;
	struct m_int_combo ic;
	char* err_str;
	intmax_t* next;
	intmax_t lo;
	intmax_t hi;

	m_int_combo_init(&ic);

	for (i = 1; i < argc; i++) {
		sscanf(argv[i], "%lld..%lld", &lo, &hi);
		m_int_combo_add(&ic, lo, hi);
	}

	m_int_combo_finalize(&ic, &next);

	while ((ret = m_int_combo_next(&ic)) == M_INT_COMBO_OK) {
		for (i = 0; i < (argc-1); i++)
			printf("%lld ", next[i]);
		printf("\n");
	}

	m_int_combo_free(&ic);

	if (ret != M_INT_COMBO_END) {
		m_intcombo_error_string(ret, &err_str);
		fprintf(stderr, "ERROR: %s\n", err_str);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

