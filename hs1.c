#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <hs/hs.h>

static int eventHandler(unsigned int id, unsigned long long from,
                        unsigned long long to, unsigned int flags, void *ctx) {
    printf("Match for pattern \"%s\" at offset %llu\n", (char *)ctx, to);
    return 0;
}

/*
/ compile: g++ hs1.c -o hs1 -I/usr/local/include/hs -lhs
*/


int main()
{
        //char *pattern = "\^([a-z]{3})\\.(\\w+)\\.com";
        char *pattern = "([a-z]+)";
        char *data = "www.test.com";
        hs_database_t *database;
        hs_compile_error_t *compile_err;
        if (hs_compile(pattern,HS_FLAG_DOTALL|HS_FLAG_SINGLEMATCH ,HS_MODE_BLOCK ,NULL,&database,
        //if (hs_compile(pattern,HS_FLAG_DOTALL,HS_MODE_BLOCK ,NULL,&database,
                                &compile_err) != HS_SUCCESS) {
                fprintf(stderr, "ERROR: Unable to compile pattern \"%s\": %s\n",
                                pattern, compile_err->message);
                hs_free_compile_error(compile_err);
                return -1;
        }

        hs_scratch_t *scratch = NULL;
        if (hs_alloc_scratch(database, &scratch) != HS_SUCCESS) {
                fprintf(stderr, "ERROR: Unable to allocate scratch space. Exiting.\n");
                hs_free_database(database);
                return -1;
        }

        if (hs_scan(database,data,strlen(data),0,scratch,eventHandler,
                                pattern) != HS_SUCCESS) {
                fprintf(stderr, "ERROR: Unable to scan input buffer. Exiting.\n");
                hs_free_scratch(scratch);
                hs_free_database(database);
                return -1;
        }
}
