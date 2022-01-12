char* replace()
{
    char *cuv1, *cuv2, *text, *result;

    cuv1 = malloc(sizeof(char));
    cuv2 = malloc(sizeof(char));
    text = malloc(sizeof(char) * 256);

    gets(cuv1); //citire cuv1
    gets(cuv2); //citire cuv2
    gets(text); //citire text

    //printf("%s\n%s\n%s", cuv1, cuv2, text);

    result = malloc(strlen(text) + (cuv2 - cuv1) * count_occurrences(text, cuv1) + 1);
    char *aux = result;


    int nr_replaced = count_occurrences(text, cuv1);

    if(nr_replaced == 0) //daca nu sunt cuvinte de inlocuit
        return text;


    *aux = 0;

    while(*text)
    {
        if (!strncmp (text, cuv1, strlen(cuv1)) &&
            (text[strlen(cuv1)] == 0 || text[strlen(cuv1)] == ' '))
        {
            strcat (aux, cuv2);
            text += strlen(cuv1);
            aux += strlen(cuv2);
        } else
        {
            while (*text && *text != ' ')
            {
                *aux = *text;
                aux++;
                text++;
            }
            while (*text == ' ')
            {
                *aux = *text;
                aux++;
                text++;
            }
        }
    }

    *aux = 0;

    printf("%s", result);
    return result;
}