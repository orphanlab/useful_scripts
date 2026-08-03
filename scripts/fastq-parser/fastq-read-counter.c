#include <zlib.h>
#include <stdio.h>
#include "kseq.h"
KSEQ_INIT(gzFile, gzread)

int main(int argc, char *argv[])
{
    gzFile fp;
    kseq_t *seq;
    int l;
    if (argc == 1) {
        fprintf(stderr, "Usage: %s <in.seq>\n", argv[0]);
        return 1;
    }
    fp = gzopen(argv[1], "r");
    seq = kseq_init(fp);
    int seqcount = 0;
    long seqlen = 0;
    while ((l = kseq_read(seq)) >= 0) {
        seqcount = seqcount + 1;
        seqlen = seqlen + (long)strlen(seq->seq.s);
    }
    kseq_destroy(seq);
    gzclose(fp);
    printf("Number of sequences: %d\n", seqcount);
    printf("Number of bases in sequences: %ld\n", seqlen);
    return 0;
}
