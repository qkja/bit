/**
* User: Qkj
* Description: 
* Date: 2022-11-13
* Time: 21:06
*/
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main()
{
  //打开文件
  FILE* pf = fopen("bit", "w");
  if(pf == NULL)
  {
    printf("%s\n", strerror(errno));
    return 1;
  }

  // 写文件
  const char* msg = "linux so easy!";
  fprintf(pf, "%s", msg);

  fclose(pf);
  pf = NULL;

  pf = fopen("bit", "r");
  int ch = 0;
	while ((ch = fgetc(pf)) != EOF)
	{
		fputc(ch, stdout);
	}
  // 关闭文件
  fclose(pf);
  pf = NULL;
  return 0;
}
