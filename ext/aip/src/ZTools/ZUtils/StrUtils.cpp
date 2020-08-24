#include "StrUtils.h"
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
//========================================================================//
// ���������� ����� strcpy !!!!!

void strapp(char* dest, const char* src, int maxtotalsize)
{
  int n = strlen(dest), i = 0;
  while(src[i] && n<maxtotalsize-1)
  {
    dest[n++] = src[i++];
  }
  dest[n] = 0;
}
//----------------------------------------------------------------------//
void strappn(char* dest, const char* src, int num, int maxtotalsize)
{
  int n = strlen(dest), i = 0;
  while(src[i] && i<num && n<maxtotalsize-1)
  {
    dest[n++] = src[i++];
  }
  dest[n] = 0;
}
//========================================================================//
const char* string(const int i)
{
  static char buf[18];
  sprintf(buf, "%i", i);
  return buf;
}
const char* string(const unsigned u)
{
  static char buf[18];
  sprintf(buf, "%u", u);
  return buf;
}
//========================================================================//
// �������� \n, \r, \t �� �������
// ������� ������������� �������
// ������� ������� � ������ � � ����� ������
//---------------------------------------------------------------------//
void alltrim(char *s, bool replace_cr)
{
  char *p = s;
  while(*p && replace_cr)
  {
    if(*p == '\n' || *p == '\r' || *p == '\t')
      *p = ' ';
    p++;
  }

  p = s;
  while(*p == ' ')
    memmove(p, p+1, strlen(p));

  while(*p)
  {
    if(*p==' ' && *(p+1)==' ')
      memmove(p, p+1, strlen(p));
    else
      p++;
  }

  if(p>s && *(--p) == ' ')
   *p = '\0';
}
//========================================================================//
// ��������� ���� �����
// caseflag = TRUE  - � ������ ��������
//          = FALSE - ��� ����� ��������
// ����������:
//      0   -  s1 = s2
//      -1  -  s1 < s2
//      -2  -  s1 < s2 � s1 ������������ � s2
//      1   -  s1 > s2
//      2   -  s1 > s2 � s2 ������������ � s1
//------------------------------------------------------------------------//
int strcmpcase(const char* s1, const char* s2, bool caseflag)
{
  unsigned char* p1 = (unsigned char*)s1;
  unsigned char* p2 = (unsigned char*)s2;

  while(*p1 && (caseflag ? *p1==*p2 : tolower(*p1)==tolower(*p2)))
    { p1++; p2++; }

  if(!*p1 && !*p2)
    return 0;
  if(!*p1 && *p2)
    return -2;
  if(*p1 && !*p2)
    return 2;
  if(caseflag ? (unsigned)*p1>(unsigned)*p2 : tolower(*p1)>tolower(*p2))
    return 1;
  else
    return -1;
}
//=====================================================================//
char wbrsigns[] = ".,;:?!-$%@#&*�_<>/ ";
//---------------------------------------------------------------------//
// ���������� ����� ������� ����� � str
// ���� str ���������� � �����������, ���������� 1
// ���� str ������ ������, ���������� 0
size_t GetWordLen(const char* str)
{
  if(str == NULL || !*str)
    return 0;

  size_t n = strcspn(str, wbrsigns);
  if(n == 0)
    return 1;
  else
    return n;
}
//---------------------------------------------------------------------//
// ���������� ��������� �� ��������� �����
// ���������� ������� ����� ��������� ������
// ���� ���������� ����� ���, ��������� �� '\0'
// ���������� null, ���� ������ ������
const char* GetNextWord(const char* str)
{
  if(str == NULL || !*str)
    return NULL;

  int n = strcspn(str, wbrsigns);
  if(n == 0)
    n++;

  while(*(str+n) == ' ')
    n++;

  return str + n;
}
//=====================================================================//
char* fgets_n(char* buf, int size, FILE* f)
{
  char* p = fgets(buf, size, f);
  if(p)
  {
    while(buf[0] != '\0' && (buf[strlen(buf)-1] == '\n' || buf[strlen(buf)-1] == '\r'))
      buf[strlen(buf)-1] = '\0';
  }

  return p;
}
//=====================================================================//
