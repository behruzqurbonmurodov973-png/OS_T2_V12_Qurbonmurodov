#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF 256

size_t my_strlen(const char *s)
{
    const char *p = s;
    while (*p != '\0')
        p++;
    return (size_t)(p - s);
}

/* dest pointer orqali o'zgartiriladi */
char *my_strcpy(char *dest, const char *src)
{
    char *d = dest;
    while ((*d++ = *src++) != '\0')
        ;
    return dest;
}

char *my_strdup(const char *s)
{
    size_t n = my_strlen(s);
    char *kopiya = malloc(n + 1);
    if (kopiya == NULL)
        return NULL;
    my_strcpy(kopiya, s);
    return kopiya;
}

int main(void)
{
    char buf[BUF];
    char *nusxa, *dup;
    size_t n;

    printf("Satr kiriting: ");
    if (fgets(buf, sizeof buf, stdin) == NULL) {
        printf("Xato: kiritish o'qilmadi.\n");
        return 1;
    }
    n = my_strlen(buf);
    if (n > 0 && *(buf + n - 1) == '\n')
        *(buf + n - 1) = '\0';
    else if (n == BUF - 1) {
        printf("Xato: satr juda uzun (maks. %d belgi).\n", BUF - 2);
        return 1;
    }
    if (*buf == '\0') {
        printf("Xato: bo'sh satr kiritildi.\n");
        return 1;
    }

    n = my_strlen(buf);
    printf("my_strlen = %zu (strlen = %zu)\n", n, strlen(buf));

    nusxa = malloc(n + 1);           /* hajm dastur ishlayotganda aniqlandi */
    if (nusxa == NULL) {
        printf("Xato: xotira ajratilmadi.\n");
        return 1;
    }
    my_strcpy(nusxa, buf);
    printf("my_strcpy natijasi: \"%s\" (manzil %p)\n", nusxa, (void *)nusxa);

    dup = my_strdup(buf);
    if (dup == NULL) {
        printf("Xato: xotira ajratilmadi.\n");
        free(nusxa);
        return 1;
    }
    printf("my_strdup natijasi: \"%s\" (manzil %p)\n", dup, (void *)dup);
    printf("Standart strcmp bilan tekshiruv: %s\n",
           (strcmp(nusxa, buf) == 0 && strcmp(dup, buf) == 0) ? "mos" : "mos emas");

    free(nusxa);
    nusxa = NULL;
    free(dup);
    dup = NULL;
    return 0;
}