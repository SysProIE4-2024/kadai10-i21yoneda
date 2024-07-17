/*
 *  mysystem.c : system 関数のクローン
 */

#include <stdio.h>
#include <stdlib.h>    // exit, system のため
#include <unistd.h>    // fork, execXX のため
#include <sys/wait.h>  // wait のため
#include "mysystem.h"  // インタフェース
char *excepath="/bin/sh";

// system関数のクローン
int mysystem(char *command) {
  int status;

  // ここにプログラムを書く
  int pid;
  if((pid=fork())<0){
    return -1;
  }
  if(pid!=0){
    while(wait(&status)!=pid);
  }else{
    execl(excepath,"sh","-c",command,NULL);
    perror(excepath);
    exit(127);
  }

  return status;
}

/* 実行例

yonedafuuta@yonedafuunoMacBook-Pro kadai10-i21yoneda % make
cc -Wall -std=c99 -o mysysmain mysysmain.c  mysystem.c
yonedafuuta@yonedafuunoMacBook-Pro kadai10-i21yoneda % ls -l
total 616
-rw-r--r--  1 yonedafuuta  staff     143  7  4 07:43 Makefile
-rw-r--r--  1 yonedafuuta  staff    2795  7  4 07:43 README.md
-rw-r--r--  1 yonedafuuta  staff  238232  7  4 07:43 README.pdf
-rwxr-xr-x  1 yonedafuuta  staff   50392  7  9 07:34 mysysmain
-rw-r--r--  1 yonedafuuta  staff     925  7  4 07:43 mysysmain.c
-rw-r--r--  1 yonedafuuta  staff     660  7  9 07:34 mysystem.c
-rw-r--r--  1 yonedafuuta  staff      90  7  4 07:43 mysystem.h
yonedafuuta@yonedafuunoMacBook-Pro kadai10-i21yoneda % ./mysysmain "ls -l"
mysystem:
total 616
-rw-r--r--  1 yonedafuuta  staff     143  7  4 07:43 Makefile
-rw-r--r--  1 yonedafuuta  staff    2795  7  4 07:43 README.md
-rw-r--r--  1 yonedafuuta  staff  238232  7  4 07:43 README.pdf
-rwxr-xr-x  1 yonedafuuta  staff   50392  7  9 07:34 mysysmain
-rw-r--r--  1 yonedafuuta  staff     925  7  4 07:43 mysysmain.c
-rw-r--r--  1 yonedafuuta  staff     660  7  9 07:34 mysystem.c
-rw-r--r--  1 yonedafuuta  staff      90  7  4 07:43 mysystem.h
retval = 00000000
system:
total 616
-rw-r--r--  1 yonedafuuta  staff     143  7  4 07:43 Makefile
-rw-r--r--  1 yonedafuuta  staff    2795  7  4 07:43 README.md
-rw-r--r--  1 yonedafuuta  staff  238232  7  4 07:43 README.pdf
-rwxr-xr-x  1 yonedafuuta  staff   50392  7  9 07:34 mysysmain
-rw-r--r--  1 yonedafuuta  staff     925  7  4 07:43 mysysmain.c
-rw-r--r--  1 yonedafuuta  staff     660  7  9 07:34 mysystem.c
-rw-r--r--  1 yonedafuuta  staff      90  7  4 07:43 mysystem.h
retval = 00000000
yonedafuuta@yonedafuunoMacBook-Pro kadai10-i21yoneda % ./mysysmain        
使い方 : ./mysysmain コマンド文字列
yonedafuuta@yonedafuunoMacBook-Pro kadai10-i21yoneda %
*/
