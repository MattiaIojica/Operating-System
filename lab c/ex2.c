int count_occurrences(const char* text, const char* word)
{
    int nr = 0;
    char sep[]=",. ";
    char *copy = strdup(text);

    char *p;
    p = strtok(copy, sep);

    while(p != NULL)
    {
       // printf("%s\n", p);
        if(strcmp(p, word) == 0)
            nr++;

        p = strtok(NULL, sep);
    }

    return nr;
}
