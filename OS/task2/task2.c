#include <stdlib.h>
#include <time.h>
#include <stdio.h>
int main()
{
    time_t now;
    time( &now );
    putenv("TZ=America/Tijuana");
    printf("%s", ctime( &now ) );
}
