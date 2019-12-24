#include "c_headers.h"

#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5
#define PARAGRAPH_DELIM '\n'
#define SENTENCE_DELIM '.'
#define WORD_DELIM ' '

struct word {
    char* data;
};

struct sentence {
    struct word* data;
    int word_count;//denotes number of words in a sentence
};

struct paragraph {
    struct sentence* data  ;
    int sentence_count;//denotes number of sentences in a paragraph
};

struct document {
    struct paragraph* data;
    int paragraph_count;//denotes number of paragraphs in a document
};

int get_next_idx(char * txt, int start, int end, int limit, char delim)
{
    int i, count;
    count = 0;
    for (i = start; i < end && count != limit; i++)
        if (txt[i] == delim)
            ++count;
    return start >= end ? -1 : i;
}

int get_count(char * txt, int start, int end, char delim)
{
    int i, count, len;
    count = 0;
    len = strlen(txt);
    for (i = start; i < len && i < end; i++)
        if (txt[i] == delim)
            ++count;
    return count;
}

struct document get_document(char* text)
{
    struct document doc;
    int len;
    int word_idx, snt_idx, para_idx,
        p_prev_idx, p_next_idx,
        s_prev_idx, s_next_idx,
        w_prev_idx, w_next_idx;
    
    doc.paragraph_count = get_count(text, 0, strlen(text), PARAGRAPH_DELIM) + 1; // Last para doesn't end w/ para delim
    doc.data = (struct paragraph *) malloc(sizeof(struct paragraph) * doc.paragraph_count);
    
    p_next_idx = -1;
    p_prev_idx = 0;
    para_idx = 0;
    len = strlen(text);
    while ((p_next_idx = get_next_idx(text,p_next_idx + 1, len, 1, PARAGRAPH_DELIM)) != -1) {
        int s_cnt = get_count(text, p_prev_idx, p_next_idx, SENTENCE_DELIM);
        doc.data[para_idx].sentence_count = s_cnt;
        doc.data[para_idx].data = (struct sentence *) malloc(sizeof(struct sentence) * s_cnt);
        
        snt_idx = 0;
        s_next_idx = p_prev_idx - 1;
        s_prev_idx = p_prev_idx;
        while ((s_next_idx = get_next_idx(text, s_next_idx + 1, p_next_idx, 1, SENTENCE_DELIM)) != -1) {
            int w_cnt = get_count(text, s_prev_idx, s_next_idx, WORD_DELIM) + 1; // Last word doesn't end w/ word delim
            doc.data[para_idx].data[snt_idx].word_count = w_cnt;
            doc.data[para_idx].data[snt_idx].data = (struct word *) malloc(sizeof(struct word) * w_cnt);

            word_idx = 0;
            w_next_idx = s_prev_idx - 1;
            w_prev_idx = s_prev_idx;
            while ((w_next_idx = get_next_idx(text, w_next_idx + 1, s_next_idx, 1, WORD_DELIM)) != -1) {
                int w_size = w_next_idx - w_prev_idx;
                doc.data[para_idx].data[snt_idx].data[word_idx].data = (char *) malloc(sizeof(char) * w_size);
                strncpy(doc.data[para_idx].data[snt_idx].data[word_idx].data, text + w_prev_idx, w_size);
                doc.data[para_idx].data[snt_idx].data[word_idx].data[w_size - 1] = '\0';
                w_prev_idx = w_next_idx;
                ++word_idx;
            }
            s_prev_idx = s_next_idx;
            ++snt_idx;
        }
        p_prev_idx = p_next_idx;
        ++para_idx;
    }

    return doc;
}

struct word kth_word_in_mth_sentence_of_nth_paragraph(struct document Doc, int k, int m, int n) 
{
    if(--k < 0 || --m < 0 || --n < 0) return (struct word){};

    struct word w;
    if(n < Doc.paragraph_count)
        if(m < Doc.data[n].sentence_count)
            if(k < Doc.data[n].data[m].word_count)
                w = Doc.data[n].data[m].data[k];
    return w;
}

struct sentence kth_sentence_in_mth_paragraph(struct document Doc, int k, int m)
{ 
    if(--k < 0 || --m < 0) return (struct sentence){};

    struct sentence s;
    if(m < Doc.paragraph_count)
            if(k < Doc.data[m].sentence_count)
                s = Doc.data[m].data[k];
    return s;
}

struct paragraph kth_paragraph(struct document Doc, int k)
{
    if(--k < 0) return (struct paragraph){};

    struct paragraph p;
    if(k < Doc.paragraph_count)
        p = Doc.data[k];
    return p;
}


void print_word(struct word w) {
    printf("%s", w.data);
}

void print_sentence(struct sentence sen) {
    for(int i = 0; i < sen.word_count; i++) {
        print_word(sen.data[i]);
        if (i != sen.word_count - 1) {
            printf(" ");
        }
    }
}

void print_paragraph(struct paragraph para) {
    for(int i = 0; i < para.sentence_count; i++){
        print_sentence(para.data[i]);
        printf(".");
    }
}

void print_document(struct document doc) {
    for(int i = 0; i < doc.paragraph_count; i++) {
        print_paragraph(doc.data[i]);
        if (i != doc.paragraph_count - 1)
            printf("\n");
    }
}

char* get_input_text() {  

    int paragraph_count;
    scanf("%d", &paragraph_count);

    char p[MAX_PARAGRAPHS][MAX_CHARACTERS], doc[MAX_CHARACTERS];
    memset(doc, 0, sizeof(doc));
    getchar();
    for (int i = 0; i < paragraph_count; i++) {
        scanf("%[^\n]%*c", p[i]);
        strcat(doc, p[i]);
        if (i != paragraph_count - 1)
            strcat(doc, "\n");
    }

    char* returnDoc = (char*)malloc((strlen (doc)+1) * (sizeof(char)));
    strcpy(returnDoc, doc);
    return returnDoc;
}

int main() 
{
    char* text = get_input_text();
    struct document Doc = get_document(text);

    int q;
    scanf("%d", &q);

    while (q--) {
        int type;
        scanf("%d", &type);

        if (type == 3){
            int k, m, n;
            scanf("%d %d %d", &k, &m, &n);
            struct word w = kth_word_in_mth_sentence_of_nth_paragraph(Doc, k, m, n);
            print_word(w);
        }

        else if (type == 2) {
            int k, m;
            scanf("%d %d", &k, &m);
            struct sentence sen= kth_sentence_in_mth_paragraph(Doc, k, m);
            print_sentence(sen);
        }

        else{
            int k;
            scanf("%d", &k);
            struct paragraph para = kth_paragraph(Doc, k);
            print_paragraph(para);
        }
        printf("\n");
    }     
}
